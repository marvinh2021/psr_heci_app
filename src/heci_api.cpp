/**
 * @file heci_api.cpp
 * @author Marvin Hsu (marvinh@intel.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <exception>
#include <system_error>
#include <cerrno>
#include "heci_api.h"
extern "C" {
#include "mei_data.h"
}

using namespace Heci;
using namespace std;

std::map<Guid_id, const uuid_le> Heci_command::guid_list = {
    {Guid_id::MKHI_HECI_FIXED_CLIENT_GUID, GUID_INIT(0x55213584, 0x9A29, 0x4916, 0xBA, 0xDF, 0x0F, 0xB7, 0xED, 0x68, 0x2A, 0xEB)},
    {Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID, GUID_INIT(0x8E6A6715, 0x9ABC, 0x4043, 0x88, 0xEF, 0x9E, 0x39, 0xC6, 0xF6, 0x3E, 0x0F)},
    {Guid_id::PSR_HECI_FIXED_CLIENT_GUID, GUID_INIT(0xEFA2AAA6, 0x0BB6, 0x4194, 0xAB, 0xA2, 0x9F, 0x59, 0xA6, 0x75, 0xEE, 0xBA)},
    {Guid_id::PSR_HECI_DYNAMIC_CLIENT_GUID, GUID_INIT(0xED6703FA, 0xD312, 0x4E8B, 0x9D, 0xDD, 0x21, 0x55, 0xBB, 0x2D, 0xEE, 0x65)},
    {Guid_id::MEI_HDCP_CLIENT_GUID, GUID_INIT(0xB638AB7E, 0x94E2, 0x4EA2, 0xA5, 0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)},
};

/**
 * @brief Construct a new Heci_command::Heci_command object
 * 
 * @param id GUID of the target MEI service
 */
Heci_command::Heci_command(Guid_id id)
{
    int res;
    struct mei_connect_client_data mei_connect_data;
    
    mei_connect_data.in_client_uuid = guid_list[id];

    if ((res = mei_connect(&mei_connect_data, &mei_client.handle)) < 0)
        throw std::system_error(-res, std::system_category());

    mei_client.properties.protocol_version = mei_connect_data.out_client_properties.protocol_version;
    mei_client.properties.max_msg_length = mei_connect_data.out_client_properties.max_msg_length;
}

Heci_command::~Heci_command()
{
    if (!(mei_client.handle < 0))
        mei_close(mei_client.handle);
}

/**
 * @brief Invoke MEI service command
 * 
 * @param tx_buff 
 * @param tx_len 
 * @param rx_buff 
 * @param rx_len 
 * @param timout_ms 
 * @return Heci_status 
 */
Heci_command::Heci_status Heci_command::Heci_cmd_transact(void *tx_buff, size_t tx_len,
                                void *rx_buff, size_t *rx_len,
                                const uint32_t timeout_ms)
{
    int res;

    if (nullptr == tx_buff || nullptr == rx_buff || nullptr == rx_len ||
        tx_len > mei_client.properties.max_msg_length)
        return INVALID_PARAMS;

    if ((res = mei_send_message(mei_client.handle, tx_buff, tx_len)) < 0)
        throw std::system_error(-res, std::system_category());

    if ((res = mei_receive_message(mei_client.handle, rx_buff, rx_len, (unsigned int)timeout_ms)) < 0)
        throw std::system_error(-res, std::system_category());

    return SUCCESS;
}
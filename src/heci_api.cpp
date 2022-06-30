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
#include "heci_api.h"
extern "C" {
#include "psr_data.h"
}

using namespace Heci;
using namespace std;

/**
 * @brief Construct a new Heci_command::Heci_command object
 * 
 * @param id GUID of the target MEI service
 */
Heci_command::Heci_command(Guid_id id)
{
    struct mei_connect_client_data mei_connect_data;
    
    mei_connect_data.in_client_uuid = guid_list[id];

    if (mei_connect(&mei_connect_data, &mei_client.handle) < 0) {
        //throw();
        cout << "MEI connection failed!" << endl;
        return;
    }

    mei_client.properties.protocol_version = mei_connect_data.out_client_properties.protocol_version;
    mei_client.properties.max_msg_length = mei_connect_data.out_client_properties.max_msg_length;
}

Heci_command::~Heci_command()
{
    mei_close(mei_client.handle);
}
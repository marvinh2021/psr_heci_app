/**
 * @file mkhi_cmd.cpp
 * @author Marvin Hsu (marvinh@intel.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "mkhi_cmd.h"
#include "heci_api.h"

using namespace Heci;
using namespace std;

bool Mkhi_command::Get_fw_version(Fw_version_resp *res)
{
    Fw_version_req input;
    size_t res_len = sizeof(*res);

    input.header.group_id = static_cast<Byte>(MKHI_GROUP_ID_GEN);
    input.header.command = static_cast<Byte>(GET_FW_VERSION_Command);
    input.header.result = 0;

    Heci_command::Heci_cmd_transact((void*)&input, sizeof(input), (void*)res, &res_len, 10000);

    return true;
}
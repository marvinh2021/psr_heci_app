/**
 * @file psr_api.cpp
 * @author Marvin Hsu (marvinh@intel.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "psr_api.h"
#include "heci_api.h"

using namespace Heci;
using namespace std;
using Heci::Psr_api;

bool Psr_api::is_psr_supported()
{
    return false;
}

Psr_api::Psr_status Psr_api::get_psr_log_state(Psr_log_state *res_state, Psr_availability *res_avail)
{
    Psr_heci_get_log_state_request input = {};
    Psr_heci_get_log_state_response res = {};
    size_t res_len = sizeof(res);

    input.header.command = Psr_heci_command::GET_LOG_STATE;

    if (nullptr == res_state || nullptr == res_avail)
        return Psr_status::INVALID_INPUT_PARAMETER;

    if (Heci_command::INVALID_PARAMS == Heci_cmd_transact((void*)&input, sizeof(input), (void*)&res, &res_len, 10000)) {
        return Psr_status::INVALID_INPUT_PARAMETER;
    }

    *res_state = res.log_state;
    *res_avail = res.avail_status;

    return res.status;
}
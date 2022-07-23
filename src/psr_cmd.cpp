/**
 * @file psr_cmd.cpp
 * @author Marvin Hsu (marvinh@intel.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <exception>
#include "psr_cmd.h"
#include "heci_api.h"

using namespace Heci;
using namespace std;
using Heci::Psr_command;

bool Psr_command::is_psr_supported()
{
    return false;
}

/**
 * @brief Get Platform Service Record Log State
 * 
 * @param res_state[out] PSR state can be STARTED/NOT_STARTED/STOPPED
 * @param res_avail[out] bit state of the PSR availability 
 * @return Psr_command::Psr_status 
 */
Psr_command::Psr_status Psr_command::get_psr_log_state(Psr_log_state *res_state, Psr_availability *res_avail)
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


Psr_command::Psr_status Psr_command::get_psr_log(Psr_heci_get_log_state_response *psr_log_response)
{
    Psr_heci_get_log_state_request input = {};
    size_t res_len = sizeof(Psr_heci_get_log_state_response);

    input.header.command = Psr_heci_command::PSR_RECORD_GET;

    if (nullptr == psr_log_response)
        return Psr_status::INVALID_INPUT_PARAMETER;

    if (Heci_command::INVALID_PARAMS == Heci_cmd_transact((void*)&input, sizeof(input),
                                            static_cast<void*>(psr_log_response), &res_len, 10000))
    {
        return Psr_status::INVALID_INPUT_PARAMETER;
    }

    return Psr_status::SUCCESS;
}

using rnd_byte_generator = std::independent_bits_engine<
                    std::default_random_engine, CHAR_BIT, uint8_t>;

void Psr_command::random_byte_array(uint8_t arr[], int len)
{
    rnd_byte_generator rnd_byte_gen;
    std::vector<uint8_t> buff(len);

    std::generate(begin(buff), end(buff), std::ref(rnd_byte_gen));
    std::copy(buff.begin(), buff.end(), arr);
}

Psr_command::Psr_status Psr_command::get_platform_service_record(Psr_heci_psr_get_response *psr_blob)
{
    Psr_heci_psr_get_request input = {};
    size_t res_len = sizeof(Psr_heci_psr_get_response);

    input.header.command = Psr_heci_command::PSR_RECORD_GET;
    input.header.length = PSR_NONCE_SIZE;
    random_byte_array(input.user_nonce, input.header.length);

    if (nullptr == psr_blob)
        return Psr_status::INVALID_INPUT_PARAMETER;

    if (Heci_command::INVALID_PARAMS == Heci_cmd_transact((void*)&input, sizeof(input),
                                            static_cast<void*>(psr_blob), &res_len, 1000000))
    {
        return Psr_status::INVALID_INPUT_PARAMETER;
    }

    if (sizeof(Psr_heci_psr_get_response) != res_len) {
        cerr << "PSR response size " << res_len << " bytes does not match the record size " <<
                sizeof(Psr_heci_psr_get_response) << " bytes!" << endl;
        return Psr_status::INTERNAL_ERROR;
    }

    return Psr_status::SUCCESS;
}
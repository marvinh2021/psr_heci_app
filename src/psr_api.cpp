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

bool Psr_api::is_psr_supported()
{
    return false;
}

Psr_api::Psr_status Psr_api::get_psr_log_status()
{
    // Verify PSR is supported
    if (!is_psr_supported()) {
        cout << "PSR is supported from Intel AMT release 16.1" << endl;
        return Psr_status::FEATURE_NOT_SUPPORTED;
    }

    return Psr_status::SUCCESS;
}
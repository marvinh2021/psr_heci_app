/**
 * @file psr_api.cpp
 * @author Marvin Hsu (marvinh@intel.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include "psr_api.h"

using namespace std;
using namespace Heci;
using namespace Psr_api;

string Platform_service_record::byte_array_to_hex_string(uint8_t arr[], int len)
{
    int i;
    std::stringstream sstrm;
    sstrm << std::hex;
    for (i=0; i < len; ++i) {
        sstrm << " ";
        sstrm << std::setw(2) << std::setfill('0') << static_cast<int>(arr[i]);
    }
    return sstrm.str();
}

bool Platform_service_record::is_psr_supported()
{
    return false;
}

Psr_status Platform_service_record::get_psr_blob(Psr_heci_psr_get_response *psr_blob)
{
    Psr_status status;
    Psr_command *psr_cmd = new Psr_command();

    try {
        status = psr_cmd->get_platform_service_record(psr_blob);
        delete psr_cmd;
    } catch(const std::exception& e) {
        delete psr_cmd;
        throw;
    }

    return status;
}

void Platform_service_record::display_platform_service_record()
{
    Psr_heci_psr_get_response psr_blob;

    try {
        if (Psr_status::SUCCESS != get_psr_blob(&psr_blob)) {
            cerr << "Failed to get PSR record!" << endl;
            return;
        }

    } catch (const std::system_error& se) {
		//cerr << se.code() << endl;
		//cerr << se.code().message() << endl;
		cerr << se.what() << endl;
		return;
	} catch (const std::runtime_error& e) {
		cerr << e.what() << endl;
		return;
	} catch (const std::logic_error& e) {
		cerr << e.what() << endl;
		return;
	} catch (...) {
		cerr << "Uncaught error!" << endl;
		return;
	}
    // General information
    cout << "General:" << endl;
    cout << "\tPSR Version: " << psr_blob.psr_version.major << "." << psr_blob.psr_version.minor << endl;
    cout << "\tLog State: " << static_cast<int>(psr_blob.log_state) << endl;
    cout << "\tPlatform Service Record ID: " <<  byte_array_to_hex_string(psr_blob.psr_record.psrid, Psr_command::PSR_UUID_LENGTH) << endl;
    cout << "\tUnique Platform ID: " <<  byte_array_to_hex_string(psr_blob.psr_record.upid, Psr_command::UPID_PLATFORM_ID_LENGTH) << endl;
}
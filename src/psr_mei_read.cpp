#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <system_error>
extern "C" {
#include "psr_data.h"
}
#include "heci_api.h"
#include "psr_api.h"
#include "mkhi_api.h"

using namespace std;
using namespace Heci;

int main(int argc, const char* argv[])
{
	Heci_command *pMei;
	Psr_api *pPsr;
	Mkhi_api *pMkhi;

	try {
		pMei = new Heci_command(Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	
	
		pMei = new Heci_command(Guid_id::MEI_HDCP_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	

		pMkhi = new Mkhi_api();
		Mkhi_api::Fw_version_resp mkhi_res{};
		if (pMkhi->Get_fw_version(&mkhi_res)) {
			cout << "MKHI Get FW version:" << endl;
			cout << "code major: " << mkhi_res.code_major << endl;
			cout << "code minor: " << mkhi_res.code_minor << endl;
			cout << "code build: " << mkhi_res.code_build << endl;
			cout << "code hotfix: " << mkhi_res.code_hotfix << endl;
			cout << "nftp major: " << mkhi_res.nftp_major << endl;
			cout << "nftp minor: " << mkhi_res.nftp_minor << endl;
			cout << "nftp build: " << mkhi_res.nftp_build << endl;
			cout << "nftp hotfix: " << mkhi_res.nftp_hotfix << endl;
			cout << endl;
		}
		delete pMkhi;

		pPsr = new Psr_api();	
		cout << *pPsr << endl;	
		Psr_api::Psr_log_state* pPsr_state = new Psr_api::Psr_log_state();
		Psr_api::Psr_availability* pPsr_avail = new Psr_api::Psr_availability();
		pPsr->get_psr_log_state(pPsr_state, pPsr_avail);
		//cout << *pPsr_state;
		//cout << *pPsr_avail;
		delete pPsr_state;
		delete pPsr_avail;
		delete pPsr;	
	} catch (const std::system_error& se) {
		//cerr << se.code() << endl;
		//cerr << se.code().message() << endl;
		cerr << se.what() << endl;
		return -1;
	} catch (const std::runtime_error& e) {
		cerr << e.what() << endl;
		return -1;
	} catch (...) {
		cerr << "Uncaught error!" << endl;
		return -1;
	}

	return 0;
}
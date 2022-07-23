#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <system_error>
extern "C" {
#include "mei_data.h"
}
#include "heci_api.h"
#include "psr_api.h"
#include "mkhi_cmd.h"

using namespace std;
using namespace Heci;
using namespace Psr_api;

int main(int argc, const char* argv[])
{
	Heci_command *pMei;
	Platform_service_record *pPsr;
	Mkhi_command *pMkhi;

	try {
		pMei = new Heci_command(Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	
	
		pMei = new Heci_command(Guid_id::MEI_HDCP_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	

		pMkhi = new Mkhi_command();
		Mkhi_command::Fw_version_resp mkhi_res{};
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

		// Get PSR blob and Dump
		pMei = new Heci_command(Guid_id::PSR_HECI_DYNAMIC_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	

		pPsr = new Platform_service_record();	
		pPsr->display_platform_service_record();
		delete pPsr;	

	} catch (const std::system_error& se) {
		//cerr << se.code() << endl;
		//cerr << se.code().message() << endl;
		cerr << se.what() << endl;
		return -1;
	} catch (const std::runtime_error& e) {
		cerr << e.what() << endl;
		return -1;
	} catch (const std::logic_error& e) {
		cerr << e.what() << endl;
		return -1;
	} catch (...) {
		cerr << "Uncaught error!" << endl;
		return -1;
	}

	return 0;
}
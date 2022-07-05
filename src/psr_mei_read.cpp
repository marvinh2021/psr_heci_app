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

using namespace std;
using namespace Heci;

int main(int argc, const char* argv[])
{
	Heci_command *pMei;
	Psr_api *pPsr;

	try {
		pMei = new Heci_command(Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	
	
		pMei = new Heci_command(Guid_id::MEI_HDCP_CLIENT_GUID);	
		cout << *pMei << endl;	
		delete pMei;	

		pPsr = new Psr_api();	
		cout << *pPsr << endl;	
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
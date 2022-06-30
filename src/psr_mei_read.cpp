#include <iostream>
#include <fstream>
#include <vector>
#include <string>
extern "C" {
#include "psr_data.h"
}
#include "heci_api.h"
#include "psr_api.h"

using namespace std;
using namespace Heci;

int main(int argc, const char* argv[])
{
	Heci_command *pMei = new Heci_command(Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID);
	Psr_api *pPsr;

	cout << *pMei << endl;
	delete pMei;

	pMei = new Heci_command(Guid_id::MEI_HDCP_CLIENT_GUID);
	cout << *pMei << endl;
	delete pMei;

	pPsr = new Psr_api();
	cout << *pPsr << endl;
	delete pPsr;

	return 0;
}
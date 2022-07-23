#ifndef PSR_API_H
#define PSR_API_H
#include "psr_cmd.h"

namespace Psr_api {
    using namespace Heci;
    using namespace std;
    using Psr_status = Psr_command::Psr_status;
    using Psr_heci_psr_get_response = Psr_command::Psr_heci_psr_get_response;

    class Platform_service_record {

        Psr_status get_psr_blob(Psr_heci_psr_get_response *psr_blob);

        string byte_array_to_hex_string(uint8_t arr[], int len);

    public:

        // Constructor
        Platform_service_record() {};

        bool is_psr_supported();    // Check if PSR is supported in FW

        void display_platform_service_record();
    };
}

#endif // PSR_API_H
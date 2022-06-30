#ifndef PSR_API_H
#define PSR_API_H
#include "heci_api.h"

namespace Heci {
    class Psr_api : public Heci_command {

    public:
        enum class Psr_status {
            SUCCESS = 0,
            FEATURE_NOT_SUPPORTED = 1,
            UPID_DISABLED = 2,
            ACTION_NOT_ALLOWED = 3,
            INVALID_INPUT_PARAMETER = 4,
            INTERNAL_ERROR = 5,
            NOT_ALLOWED_AFTER_EOP = 6
        };

        Psr_api() : Heci_command(Guid_id::PSR_HECI_DYNAMIC_CLIENT_GUID) {}   // Constructor

        bool is_psr_supported();    // Check if PSR is supported in FW

        Psr_status get_psr_log_status();
    };
}

#endif // PSR_API_H
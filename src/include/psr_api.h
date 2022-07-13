#ifndef PSR_API_H
#define PSR_API_H
#include "heci_api.h"

namespace Heci {
    class Psr_api : public Heci_command {

    public:
        // PSR constants
		static const int PSR_UUID_LENGTH = 16;
		static const int PSR_GENESIS_INFO_SIZE = 1284;
		static const int PSR_LEDGER_INFO_SIZE = 64;
		static const int PSR_EVENT_SIZE = 12;
		static const int PSR_CRITICAL_EVENTS_NUM_MAX = 100;
		static const int PSR_NONCE_SIZE = 20;
		static const int PSR_MAX_CERT_CHAIN_SIZE = 3000;
		static const int PSR_ODCA_CHAIN_LEN = 4;
		static const int PSR_MAX_SIGNATURE_LENGTH = 512;
		static const int PSR_GENESIS_FIELD_INFO_SIZE = 64;
		static const int PSR_GENESIS_DATA_STORE_INFO_SIZE = 1024;

        // UPID constants
        static const int UPID_PLATFORM_ID_LENGTH = 64;

        // Crypto constants
        static const int SHA512_LEN_BYTES = 64;

        // PSR Enumerations
        enum class Psr_status {
            SUCCESS = 0,
            FEATURE_NOT_SUPPORTED = 1,
            UPID_DISABLED = 2,
            ACTION_NOT_ALLOWED = 3,
            INVALID_INPUT_PARAMETER = 4,
            INTERNAL_ERROR = 5,
            NOT_ALLOWED_AFTER_EOP = 6
        };

        // PSR critical event types
        enum class Psr_critical_event_type {
            // 0x001xxx - log events
            EVENT_LOG_START = 8,
            EVENT_LOG_END = 9,

            // 0x01xxxx - CSME events
            EVENT_AR_FAILURE = 16,
            EVENT_MISSING = 17,
            EVENT_INVALID = 18,
            EVENT_PRTC_FAILURE = 19,
            EVENT_CSME_RECOVERY_STATE = 20,
            EVENT_CSME_DAM_STATE = 21,
            EVENT_CSME_UNLOCK_STATE = 22,
            EVENT_SVN_INCREASE = 23,

            // 0x1xxxxx - External events (BIOS)
            EVENT_CHASSIS_INTRUSION = 32,

            EVENT_MAX,
        };

        // PSR commands
        enum class Psr_heci_command : Byte {
            // 1 - 9 : management commands
            START_LOG = 1,

            // 10 - 19 : log data
            PSR_RECORD_GET = 10,
            GET_LOG_STATE = 11,

            // 20 - 30 : external events
            CHASSIS_INTRUSION_REPORT = 20,
            DEBUG = 30,
        };

        enum class Psr_log_state {
            NOT_STARTED = 0, // Default value
            STARTED,
            STOPPED
        };

        enum class Psr_signing_algorithm {
            ECDSA_SHA384 = 0,
        };

    protected:

        #pragma pack(1)

        union Psr_availability {
            struct {
                uint32_t upid_is_disabled : 1;  // bit-0
                uint32_t wrong_cpu : 1;         // bit-1
                uint32_t in_usage : 30;         // bit-2:31
            };
            uint32_t value;
        };

        struct Psr_heci_header {
            Psr_heci_command command;
            uint8_t reserved;
            uint16_t length; // Payload length in bytes
        };

        struct Psr_heci_response {
            Psr_heci_header header;
            Psr_status status;
        };

        struct Psr_version {
            uint16_t major;
            uint16_t minor;
        };

        struct Fw_version {
            uint16_t major;
            uint16_t minor;
            uint16_t hotfix;
            uint16_t build;
        };

        // PSR_HECI_START_LOG
        struct Psr_heci_start_log_request {
            Psr_heci_header header;
            uint32_t time;
        };

        struct Psr_heci_start_log_response {
            Psr_heci_header header;
            Psr_status status;
            uint8_t psrid[PSR_UUID_LENGTH];
        };

        // PSR_GET_LOG_STATE
        struct Psr_heci_get_log_state_request {
            Psr_heci_header header;
        };

        struct Psr_heci_get_log_state_response {
            Psr_heci_header header;
            Psr_status status;
            Psr_log_state log_state;
            Psr_availability avail_status;
        };

        // PSR_HECI_PLATFORM_SERVICE_RECORD_GET
        struct Psr_heci_psr_get_request {
            Psr_heci_header header;
            uint8_t user_nonce[PSR_NONCE_SIZE];
        };

        // Inner structure of genesis_info field
        struct Psr_genesis_record {
            uint32_t genesis_date;
            uint8_t oem_info[PSR_GENESIS_FIELD_INFO_SIZE];
            uint8_t oem_imake_info[PSR_GENESIS_FIELD_INFO_SIZE];
            uint8_t manufacture_country[PSR_GENESIS_FIELD_INFO_SIZE];
            uint8_t oem_data_store[PSR_GENESIS_DATA_STORE_INFO_SIZE];
        };

        // Inner structure of PSR single event
        struct Psr_critical_event {
            uint8_t event_id;
            uint8_t reserved[3];
            uint32_t time_stamp;
            uint32_t data;
        };

        // Inner structure of ledger_info field
        struct Psr_ledger_record {
            uint32_t s0_seconds_counter;
            uint32_t s0_to_s5_counter;
            uint32_t s0_to_s4_counter;
            uint32_t s0_to_s3_counter;
            uint32_t warm_reset_counter;
            uint32_t reserved[11];
        };

        struct Psr_platform_service_record {
            uint8_t psrid[PSR_UUID_LENGTH];
            uint8_t upid[UPID_PLATFORM_ID_LENGTH];
            Psr_genesis_record genesis_info;
            Psr_ledger_record ledger_info;
            uint32_t events_count;
            Psr_critical_event events_info[PSR_CRITICAL_EVENTS_NUM_MAX];
        };

        struct Psr_heci_psr_get_response {
            Psr_heci_header header;
            Psr_status status;
            Psr_log_state log_state;
            Psr_version psr_version;
            Psr_platform_service_record psr_record;
            uint8_t psr_hash[SHA512_LEN_BYTES];
            uint8_t user_nonce[PSR_NONCE_SIZE];
            uint8_t csme_nonce[PSR_NONCE_SIZE];
            Fw_version fw_version;
            Psr_signing_algorithm sig_algo;
            uint8_t signature[PSR_MAX_SIGNATURE_LENGTH];
            uint16_t certificate_lengths[PSR_ODCA_CHAIN_LEN];
            uint8_t certificates[PSR_MAX_CERT_CHAIN_SIZE];
        };
        #pragma pack()

    public:
        // PSR methods
        Psr_api() : Heci_command(Guid_id::PSR_HECI_DYNAMIC_CLIENT_GUID) {}   // Constructor

        bool is_psr_supported();    // Check if PSR is supported in FW

        Psr_status get_psr_log_state(Psr_log_state *res_state, Psr_availability *res_avail);
    };
}

#endif // PSR_API_H
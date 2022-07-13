#ifndef _MKHI_API_H_
#define _MKHI_API_H_
#include "heci_api.h"

namespace Heci {
    class Mkhi_api : public Heci_command {

        struct Mkhi_message_header {
            Byte group_id;
            Byte command;
            Byte reserved;
            Byte result;
        };

        struct Fw_version_req {
            Mkhi_message_header header;
        };

    public:

        static constexpr uint32_t MKHI_GROUP_ID_GEN = 0xFF;
        static constexpr uint32_t GET_FW_VERSION_Command = 0x02;

        enum Mkhi_status {
            SUCCESS = 0x0,
            INVALID_STATE = 0x1,
            MESSAGE_SKIPPED = 0x2,
            SIZE_ERROR = 0x5,
            ENINVAL = 0x16,
            NOT_FOUND = 0x81,
            INVALID_ACCESS = 0x84,
            INVALID_PARAMS = 0x85,
            NOT_READY = 0x88,
            NOT_SUPPORTED = 0x89,
            INVALID_ADDRESS = 0x8C,
            INVALID_COMMAND = 0x8D,
            FAILURE = 0x9E,
            GENERIC_FAILURE = 0x99,
            INVALID_RESOURCE = 0xE4,
            RESOURCE_IN_USE = 0xE5,
            NO_RESOURCE = 0xE6,
            RETRY = 0xFE,
            GENERAL_ERROR = 0xFF,
        };

        struct Fw_version_resp {
            Mkhi_message_header header;
            uint16_t code_minor;
            uint16_t code_major;
            uint16_t code_build;
            uint16_t code_hotfix;
            uint16_t nftp_minor;
            uint16_t nftp_major;
            uint16_t nftp_build;
            uint16_t nftp_hotfix;
            uint16_t fitc_minor;
            uint16_t fitc_major;
            uint16_t fitc_build;
            uint16_t fitc_hotfix;
        };

        Mkhi_api() : Heci_command(Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID) {}   // Constructor

        bool Get_fw_version(Fw_version_resp *res);
    };
};

#endif // _MKHI_API_H_
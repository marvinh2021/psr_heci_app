#ifndef HECI_API_H
#define HECI_API_H
#include <ostream>
#include <map>
extern "C" {
#include "psr_data.h"
}

using namespace std;

namespace Heci {

    enum class Guid_id {
        MKHI_HECI_FIXED_CLIENT_GUID = 1,
        MKHI_HECI_DYNAMIC_CLIENT_GUID,
        PSR_HECI_FIXED_CLIENT_GUID,
        PSR_HECI_DYNAMIC_CLIENT_GUID,
        MEI_HDCP_CLIENT_GUID,
    };

    class Heci_command {
    
    protected:
        std::map<Guid_id, const uuid_le> guid_list = {
            {Guid_id::MKHI_HECI_FIXED_CLIENT_GUID, GUID_INIT(0x55213584, 0x9A29, 0x4916, 0xBA, 0xDF, 0x0F, 0xB7, 0xED, 0x68, 0x2A, 0xEB)},
            {Guid_id::MKHI_HECI_DYNAMIC_CLIENT_GUID, GUID_INIT(0x8E6A6715, 0x9ABC, 0x4043, 0x88, 0xEF, 0x9E, 0x39, 0xC6, 0xF6, 0x3E, 0x0F)},
            {Guid_id::PSR_HECI_FIXED_CLIENT_GUID, GUID_INIT(0xEFA2AAA6, 0x0BB6, 0x4194, 0xAB, 0xA2, 0x9F, 0x59, 0xA6, 0x75, 0xEE, 0xBA)},
            {Guid_id::PSR_HECI_DYNAMIC_CLIENT_GUID, GUID_INIT(0xED6703FA, 0xD312, 0x4E8B, 0x9D, 0xDD, 0x21, 0x55, 0xBB, 0x2D, 0xEE, 0x65)},
            {Guid_id::MEI_HDCP_CLIENT_GUID, GUID_INIT(0xB638AB7E, 0x94E2, 0x4EA2, 0xA5, 0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)},
        };

        class mei_client_properties {
        public:
            Guid_id guid;
            unsigned char protocol_version;
            unsigned char max_num_connections;
            unsigned int max_msg_length;
        };

    private:
        class mei_client_connect {
        public:
            int handle;
            mei_client_properties properties;
        } mei_client;

    public:
        Heci_command() = delete;

        Heci_command(Guid_id);

        ~Heci_command();

        friend std::ostream& operator<<(std::ostream& os, const Heci_command& hcmd) {
            os << "Protocol version: " << static_cast<int>(hcmd.mei_client.properties.protocol_version) << endl;
            os << "Maximum message length: " << hcmd.mei_client.properties.max_msg_length << endl;
            return os;
        }
    };
}

#endif // HECI_API_H
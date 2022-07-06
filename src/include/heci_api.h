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
        static std::map<Guid_id, const uuid_le> guid_list;

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

        enum Heci_status {
            SUCCESS = 0,
            INVALID_STATE = 0x1,
            INVALID_PARAMS,
        };

        Heci_command() = delete;

        Heci_command(Guid_id);

        Heci_status Heci_cmd_transact(void *tx_buff, size_t tx_len,
                void *rx_buff, size_t *rx_len, const uint32_t timeout_ms);

        ~Heci_command();

        friend std::ostream& operator<<(std::ostream& os, const Heci_command& hcmd) {
            os << "Protocol version: " << static_cast<int>(hcmd.mei_client.properties.protocol_version) << endl;
            os << "Maximum message length: " << hcmd.mei_client.properties.max_msg_length << endl;
            return os;
        }
    };
}

#endif // HECI_API_H
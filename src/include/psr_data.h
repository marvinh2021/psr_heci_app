#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/mei.h>
#include <linux/uuid.h>

struct uuid_entry {
	const char* name;
	const uuid_le uuid;
};

int heci_open(struct mei_connect_client_data*, struct uuid_entry*);
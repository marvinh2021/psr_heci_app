#ifndef _MEI_DATA_H_
#define _MEI_DATA_H_
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/mei.h>
#include <linux/uuid.h>

#define MAX_MEI_TIMEOUT_MSEC	10000	// 10 sec

struct uuid_entry {
	const char* name;
	const uuid_le uuid;
};

struct mei_client_data {

};

int mei_connect(struct mei_connect_client_data*, int*);

int mei_send_message(int handle, void *buffer, size_t buff_len);

int mei_receive_message(int, void*, size_t*, unsigned int);

void mei_close(int);

#endif // _MEI_DATA_H_
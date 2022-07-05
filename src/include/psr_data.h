#ifndef _PSR_DATA_H_
#define _PSR_DATA_H_
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

int mei_send_message(struct mei_connect_client_data *client,
		int handle,
		unsigned char *buffer, unsigned int buff_len);

int mei_receive_message(struct mei_connect_client_data *client,
		int handle,
		unsigned char *buffer, unsigned int *buff_len,
		unsigned int timeout_ms);

void mei_close(int);

#endif // _PSR_DATA_H_
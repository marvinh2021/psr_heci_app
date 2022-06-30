#ifndef _PSR_DATA_H_
#define _PSR_DATA_H_
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/mei.h>
#include <linux/uuid.h>

struct uuid_entry {
	const char* name;
	const uuid_le uuid;
};

int mei_connect(struct mei_connect_client_data*, int*);

void mei_close(int);

#endif // _PSR_DATA_H_
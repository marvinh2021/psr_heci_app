/**
 * MEI IOCTL interface test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "psr_data.h"

#define MEI_DEVICE "/dev/mei0"

extern char const * errno_name(int errno_);

#if 0
int main()
{
	struct mei_connect_client_data data;

	memset((void *)&data, 0U, sizeof(data));
	for (int i=0; i < (sizeof(uuid_list)/sizeof(uuid_list[0])); i++) {
		if (heci_open(&data, &uuid_list[i]) != -1) {
			printf("\n%s: Ver=%d, MaxLen=%d\n",
				uuid_list[i].name,
				data.out_client_properties.protocol_version,
				data.out_client_properties.max_msg_length);
		}
	}

	return 0;
}
#endif //0

int heci_open(struct mei_connect_client_data *data, struct uuid_entry *uuid_ent)
{
	int fd;

	/* Open device file */
	fd = open(MEI_DEVICE, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		printf("Open file %s error!\n", MEI_DEVICE);
		return -1;
	}

	/* MEI connect client */
	data->in_client_uuid = uuid_ent->uuid;
	if (ioctl(fd, IOCTL_MEI_CONNECT_CLIENT, data) == -1) {
		char prompt[128];
		int err = errno;
		sprintf(prompt, "\n%s(%s)", uuid_ent->name, errno_name(err));
		perror(prompt);
		return -1;
	}
	close(fd);

	return 0;
}
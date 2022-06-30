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

int mei_connect(struct mei_connect_client_data *data, int *handle)
{
	int fd;

	if (!data) {
		perror("Input client_data ptr is NULL");
		return -1;
	}

	/* Open device file */
	fd = open(MEI_DEVICE, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		printf("Open file %s error!\n", MEI_DEVICE);
		return -1;
	}

	/* MEI connect client */
	if (ioctl(fd, IOCTL_MEI_CONNECT_CLIENT, data) == -1) {
		char prompt[128];
		int err = errno;
		sprintf(prompt, "\nioctl MEI connect failed: (%s)", errno_name(err));
		perror(prompt);
		return -1;
	}

	*handle = fd;
	return 0;
}

void mei_close(int handle)
{
	close(handle);
}

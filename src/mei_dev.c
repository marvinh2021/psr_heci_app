/**
 * MEI IOCTL interface test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include "mei_data.h"

#define MEI_DEVICE "/dev/mei0"

extern char const * errno_name(int errno_);

int mei_connect(struct mei_connect_client_data *data, int *handle)
{
	int fd;
	char prompt[128];

	if (!data) {
		perror("Input client_data ptr is NULL");
		return -1;
	}

	/* Open device file */
	fd = open(MEI_DEVICE, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		int err = errno;
		sprintf(prompt, "Open file %s error! (%s)", MEI_DEVICE, errno_name(err));
		//perror(prompt);
		printf("%s: ", prompt);
		return -err;
	}
	*handle = fd;

	/* MEI connect client */
	if (ioctl(fd, IOCTL_MEI_CONNECT_CLIENT, data) == -1) {
		int err = errno;
		sprintf(prompt, "ioctl MEI connect failed! (%s)", errno_name(err));
		//perror(prompt);
		printf("%s: ", prompt);
		return -err;
	}

	return 0;
}

/**
 * @brief  Send Message to MEI/HECI service
 * 
 * @param client 
 * @param handle 
 * @param buffer 
 * @param buff_len 
 * @param timeout 
 * @return int 
 */
int mei_send_message(int handle, void *buffer, size_t buff_len)
{
	ssize_t written_bytes;
	
	written_bytes = write(handle, (void *)buffer, (size_t)buff_len);
	if (written_bytes != (ssize_t)buff_len) {
		char prompt[128];
		int err = errno;
		sprintf(prompt, "%s: write to mei_dev file error(%s)", __func__, errno_name(err));
		perror(prompt);
		return -err; // msg tx error
	}

	return 0;
}

/**
 * @brief Receive Response (data blob) from MEI/HECI service
 * 
 * @param client 
 * @param handle  file descriptor of mei_dev file
 * @param buffer  pointer to output buffer
 * @param buff_len output buffer size in bytes
 * @param timeout_ms  Polling timeout in msec
 * @return int 
 */
int mei_receive_message(int handle, void *buffer, size_t *buff_len, unsigned int timeout_ms)
{
	ssize_t read_bytes;
	struct timeval tv;
	fd_set readfds;
	int ready;

	/* set timeout */	
	tv.tv_sec = (timeout_ms ? timeout_ms : MAX_MEI_TIMEOUT_MSEC) / 1000;
	tv.tv_usec = ((timeout_ms ? timeout_ms : MAX_MEI_TIMEOUT_MSEC) % 1000) * 1000;

	/* Check if mei_dev data ready to read */
	FD_ZERO(&readfds);
	FD_SET(handle, &readfds);

	ready = select(handle+1, &readfds, NULL, NULL, &tv);
	if (ready < 0) {
		// select error
		return -EBUSY;
	} else if (0 == ready) {
		// timeout
		return -ETIMEDOUT;
	} else if (!FD_ISSET(handle, &readfds)) {
		// internal error
		return -1;
	}

	/* read data */
	read_bytes = read(handle, buffer, *buff_len);
	if (read_bytes < 0) {
		// read error
		return -EIO;
	} else if (0 == read_bytes) {
		// No message response
		return -ENOMSG;
	}
	*buff_len = read_bytes;

	return 0;
}

void mei_close(int handle)
{
	close(handle);
}

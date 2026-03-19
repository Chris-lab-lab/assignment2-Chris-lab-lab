#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
	openlog("writer", LOG_PID, LOG_USER);

	if(argc != 3) {
		syslog(LOG_ERR, "Invalid arguments. Usage: writer <filepath> <string>");
		fprintf(stderr, "Usage: %s <filepath> <string>\n", argv[0]);
		closelog();
		return 1;
	}

	const char *filepath = argv[1];
	const char *writestr = argv[2];

	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		syslog(LOG_ERR, "Failed to open file %s", filepath);
		fprintf(stderr, "Error: could not open file %s\n", filepath);
		closelog();
		return 1;
	}

	ssize_t bytes_written = write(fd, writestr, strlen(writestr));
	if (bytes_written == -1) {
		syslog(LOG_ERR, "Failed to write file %s", filepath);
		fprintf(stderr, "Error: could not write to file %s\n", filepath);
		close(fd);
		closelog();
		return 1;
	}

	syslog(LOG_DEBUG, "Writing %s to %s", writestr, filepath);

	close(fd);
	closelog();
	return 0;
}

#include "relay.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 65432

int main() {
	int server_fd, new_socket;
	struct sockaddr_in address;
	//int opt = 1;
	int addrlen = sizeof(address);
	char buffer[64] = {};

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
/*	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
*/	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("Made it\n");
	while (strcmp(buffer, "SHUTDOWN") != 0) {
		if (listen(server_fd, 3) < 0) {
			perror("listen");
			exit(EXIT_FAILURE);
		}
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("Connected\n");

		while (read(new_socket, buffer, 64)) {
			printf("%s\n", buffer);
			if (strncmp(buffer, "SWITCH", 6) == 0) {
				int moduel_no = ((int) buffer[6]) - 48;
				if (relay_state(moduel_no) == 1) {
					relay_on(moduel_no);
				}
				else {
					relay_off(moduel_no);
				}
			}
			memset(buffer, 0, sizeof(buffer));
		}
		close(new_socket);
	}
}

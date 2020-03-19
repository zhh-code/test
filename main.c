#include <stdio.h>
#include <stdlib.h>
#include "thread_work.h"
#include "pub.h"

int socket_create(int port);
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: server port\n");
		exit(-1);
	}
	int port = atoi(argv[1]);
	
	if (port <= 0) {
		printf("port failed");
		exit(-1);
	}
	
	int st = sock_create(port);
	setdaemon();						//设置守护进程
	printf("my http server begin\n");
	socket_accept(st);
	return 0;
	//fasfasfaf
//fsafafas
///////////////////
}

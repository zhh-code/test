#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <stdio.h>

#include"pub.h"
#include"thread_work.h"
/*****************************************************************************
 函 数 名  : socket_create
 功能描述  : socket创建
 输入参数  : int port  
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年12月4日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
int socket_create(int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	int on = 1;
	if(fd == -1) {
		perror("socket error:");
		exit(-1);
	}
	//端口复用
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
		perror("setsockopt error:");
		exit(-1);
	}
	struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_port = htons(port);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1) {
		perror("bind error:");
		exit(-1);
	}
	if(listen(fd, 100) == -1) {
		perror("listen error:");
		exit(-1);
	}
	printf("start server success!\n");
	return fd;
}

/*****************************************************************************
 函 数 名  : setdaemon
 功能描述  : 设置守护进程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年12月3日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
void setdaemon()
{
	pid_t pid, sid;
	pid = fork();
	if(pid < 0) {
		perror("fork error:");
		exit(-1);
	}
	else if(pid > 0) {
		exit(0);
	}
	else {
		sid = setsid();
		if(sid < 0) {
			perror("setsid error");
			exit(-1);
		}
		/*
			if(chdir('/home/zhh') == -1) {
				perror("chdir failed:");
				exit(-1);
			}
		*/
		umask(0022);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

/*****************************************************************************
 函 数 名  : sock_accept
 功能描述  : 接受客户端链接
 输入参数  : fd(监听描述符)
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
	1.日    期   : 2019年12月4日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
int sock_accept(int fd)
{
	struct sockaddr_in client_addr;
	socklen_t len =sizeof(client_addr);
	
	pthread_t tid;
	pthread_attr_t attr;
	pthread_addt_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREAT_DETACHED);
	memset(&client_sockaddr, 0, sizeof(client_sockaddr));
	
	while(1) {
		client_st = accept(st, (struct sockaddr*) &client_addr, &len);
		if(client_st == -1) {
			perror("accept failed:");
			exit(-1);
		}
		else {
			int tmp = client_st;
			pthread_create(&tid, &attr, http_thread, (void *)tmp);
		}
	}
	pthread_destory(&attr);					//销毁线程属性
}
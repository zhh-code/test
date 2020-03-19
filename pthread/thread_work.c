#include"thread_work.h"
#include"pub.h"

#include <sys/types.h>
#include <sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
//http response
#define HEAD "HTTP/1.0 200 OK\n\
Content-Type: %s\n\
Transfer-Encoding: chunked\n\
Connection: Keep-Alive\n\
Accept-Ranges:bytes\n\
Content-Length:%d\n\n"
//http tags
#define TAIL "\n\n"
/*****************************************************************************
 函 数 名  : http_thread
 功能描述  : 线程回调函数
 输入参数  : fd(通信描述符)
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
	1.日    期   : 2019年12月4日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
void *http_thread(void *argc)
{
	char command[2048];
	memset(&command, '\0', sizeof(command));
	if (argc == NULL) {
		perror("pthread failed");
		exit(-1);
	}
	int fd = (int *)argc;
	char buf[2048];
	memset(buf,'\0', sizeof(buf));
	int ret = recv(fd, buf, sizeof(buf), 0);
	if(ret <= 0) {
		 perror("recv failed");
		 exit(-1);
	}
	else {
		printf("buf = %s\n", buf);
		get_http_command(buf, command);
		char *content = NULL;
		int len = make_http_content(command, &content);
		
		
	}
}

/*****************************************************************************
 函 数 名  : get_http_command
 功能描述  : 解析http请求行和空字符串
 输入参数  : http请求
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
	1.日    期   : 2019年12月5日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
void get_http_command(char* http_msg, char *command)
{
	//得到请求行方式
	char *p_end = http_msg;
	char *p_start = http_msg;
	while(*p_start) {					//GET /
		if(*p_start == '/') {
			break;
		}
		p_start++;
	}
	p_start++;							//过滤掉'/'
	//得到请求行URL
	p_end = strchr(http_msg, '\n');		//p_end等于请求行下面的那一堆
	while(1) {
		if (*p_end == ' ') {
			break;
		}
		p_end--;
	}
	strncpy(command, p_start, p_end - p_start);		//URL
	printf("request body\n");
	get_http_boody(http_msg);
}

/*****************************************************************************
 函 数 名  : get_http_body
 功能描述  : 解析http_body
 输入参数  : http请求
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
	1.日    期   : 2019年12月4日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
void get_http_body(char *http_body)
{
	
}

/*****************************************************************************
 函 数 名  : make_http_contend
 功能描述  : 根据请求的URL返回相应的数据
 输入参数  : URL和content地址
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
	1.日    期   : 2019年12月4日
	作    者   : zhh
	修改内容   : 新生成函数

*****************************************************************************/
int make_http_content(const char* command, char **content)
{
	char *file_buf;
	int file_length;
	char headbuf[1024];
	
	//如果URL是跟目录，指定html界面显示
	if(command[0] == 0) {
		file_length = get_file_content("index.html", &file_buf);
	}
	else {
		
	}
}
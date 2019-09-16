/* $Id: socket.c 1.1 1995/01/01 07:11:14 cthuang Exp $
 *
 * This module has been modified by Radim Kolar for OS/2 emx
 */

/***********************************************************************
  module:       socket.c
  program:      popclient
  SCCS ID:      @(#)socket.c    1.5  4/1/94
  programmer:   Virginia Tech Computing Center
  annotating ： FuJi--china
  compiler:     DEC RISC C compiler (Ultrix 4.1)
  environment:  DEC Ultrix 4.3 
  description:  UNIX sockets code.
 ***********************************************************************/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int Socket(const char *host, int clientPort)
{
    int sock; //套接字接收的
    unsigned long inaddr; //ip地址
    struct sockaddr_in ad; //套接字配置结构体，包括协议，等等
    /*可能他是这个。。
      struct sockaddr_in{
          unsigned short          sin_family;    协议族 
          unsigned short int      sin_port;      端口号
          struct in_addr          sin_addr;      地址配置结构体
          unsigned char           sin_zero[8];    字节填充
      }
     */
    struct hostent *hp; 
    
    memset(&ad, 0, sizeof(ad)); //初始化设置为0
    ad.sin_family = AF_INET; //使用ip4协议族

    inaddr = inet_addr(host); //把host这个字符串类型的地址转换成整数，中间参杂进行了大小端的转换
                              
    
  if (inaddr != INADDR_NONE)
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    else
    {
        hp = gethostbyname(host);
        if (hp == NULL)
            return -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}


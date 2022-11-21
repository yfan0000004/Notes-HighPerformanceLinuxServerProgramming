#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

/*
struct sockaddr_in
{
    sa_family_t sin_family;//地址族：AF_INET
    u_int16_t sin_port;//端口号，要用网络字节序表示
    struct in_addr sin_addr;//*IPv4地址结构体，见下面
};
struct in_addr
{
    u_int32_t s_addr;//IPv4地址，要用网络字节序表示
};
*/

int main()
{
    char *echo_host = "192.168.190.134";
    int echo_port = 5005;
    int sockfd;
    struct sockaddr_in *server = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

    //设置连接协议族，地址，端口
    server->sin_family = AF_INET;
    server->sin_port = htons(echo_port);            //将主机字节序转化为网络字节序
    server->sin_addr.s_addr = inet_addr(echo_host); //转化为网络字节序表示的IP地址

    //创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //连接到服务器
    printf("Connecting to %s \n", echo_host);
    printf("Numeric: %u \n", server->sin_addr);
    connect(sockfd, (struct sockaddr *)server, sizeof(*server));

    //发送消息
    char *msg = "Hello world";
    printf("\nSend: '%s' \n", msg);
    write(sockfd, msg, strlen(msg));

    //接收返回结果
    char *buf = (char *)malloc(1000);
    int bytes = read(sockfd, (void *)buf, 1000);
    printf("\nBytes received: %u\n", bytes);
    printf("Text: '%s'\n", buf);

    //通信结束，关闭套接字
    close(sockfd);
    return 1;
}
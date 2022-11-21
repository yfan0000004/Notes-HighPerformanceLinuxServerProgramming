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

int listen(int sockfd,int backlog);
内核版本2.2之后，backlog它只表示处于完全连接状态的socket的上限,典型值是5
*/

int main()
{
    char *echo_host = "192.168.190.134";
    int echo_port = 5005;
    int sockfd;
    struct sockaddr_in *server = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

    //设置连接协议族，地址，端口
    server->sin_family = AF_INET;
    server->sin_port = htons(echo_port); //将主机字节序转化为网络字节序
    // server->sin_addr.s_addr = htonl(INADDR_ANY);    //任意IP地址
    server->sin_addr.s_addr = inet_addr(echo_host); //指定IP地址。转化为网络字节序表示的IP地址

    //创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //绑定到一个地址
    bind(sockfd, (struct sockaddr *)server, sizeof(*server));

    //开始监听
    listen(sockfd, 5);

    //等待客户端发送的数据进入
    int clientfd;
    struct sockaddr_in *client = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    int client_size = sizeof(*client);
    printf("Wait for connection to port %u\n", echo_port);

    //接收连接请求
    clientfd = accept(sockfd, (struct sockaddr *)client, &client_size);
    printf("Connected to %s:%u\n\n", inet_ntoa(client->sin_addr), ntohs(client->sin_port));
    printf("Numeric: %u\n", ntohl(client->sin_addr.s_addr));

    int bytes;
    char *buf = (char *)malloc(1000);
    while (1)
    {
        bytes = read(clientfd, (void *)buf, 1000);
        if (bytes < 0)
        {
            close(clientfd);
            printf("Connection closed\n");
            break;
        }
        printf("Bytes received: %u\n", bytes);
        printf("Text: '%s'\n", buf);

        //响应发送数据
        write(clientfd, buf, bytes);
    }
    return 1;
}
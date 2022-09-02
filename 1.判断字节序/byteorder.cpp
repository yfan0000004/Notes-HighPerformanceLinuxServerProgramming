#include <stdio.h>
#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
using namespace std;

void byteorder()
{
    union
    {
        short value;
        char union_bytes[sizeof(value)];
    }test;
    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)){
        std::cout << "big endian\n" << std::endl;
    }else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)){
        std::cout << "little endian" << std::endl;
    }else std::cout << "unknow" << std::endl;
}

int main(){
    byteorder();

    //检验inet_ntoa函数的不可重入性
    char *szValue1 = inet_ntoa("1.2.3.4");
    char *szValue2 = inet_ntoa("10.194.71.60");
    printf("address 1:%s\n",szValue1);
    printf("address 2:%s\n",szValue2);
    
    return 1;
}
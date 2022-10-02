#ifndef __common__H__
#define __common__H__
#define MSG_LEN 1024
#define SERV_PORT "8080"
#define SERV_ADDR "127.0.0.1"
#define max 500

struct info{
    short s;
    long l;
};

struct who_s_data{
    char nickname[max];
    char address[max];
    unsigned short port;
    char date[max];
};
#endif

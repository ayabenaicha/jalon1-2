#ifndef __wr_H__
#define __wr_H__
#include"struct_msg.h"
#include"common.h"

void sending_msg(int socket, struct message *msg, void *donnee);
enum msg_type recevoir_msg(int socket, struct message *msg, void **donnee);


#endif

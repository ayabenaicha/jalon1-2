#include "struct_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enum.h"
char name[NICK_LEN];
#define null 0
enum msg_type demande( struct message *msg, void *donnee[],char *send){
int start=6;
int start_whois=7;
int start_msgall=8;
int start_msg_all=5;
int start_create=8;
int start_join=6;
int start_quit=6;

   if(strncmp(send, "/nick ", start) == null){

       msg->pld_len = 0;
        strcpy(msg->nick_sender, name);
        msg->type = NICKNAME_NEW;
         strcpy(msg->nick_sender, name);
        strcpy(msg->infos, send+start);

        *donnee= NULL;

        return NICKNAME_NEW;
        
    }

    if(strcmp(send, "/who") == null){

        msg->pld_len = 0;
        strcpy(msg->nick_sender, name);
        msg->type = NICKNAME_LIST;
        strcpy(msg->infos, "");

        *donnee = NULL;

        return NICKNAME_LIST;

    }

    if(strncmp(send, "/whois ", start_whois) == null){
        msg->pld_len = 0;
        strcpy(msg->nick_sender, name);
        msg->type = NICKNAME_INFOS;
        strcpy(msg->infos, send+start_whois);

       *donnee = NULL;

        return NICKNAME_INFOS;
    }

    if(strncmp(send, "/msgall ", start_msgall) == 0){

        msg->pld_len = (strlen(send+start_msgall)+1)*sizeof(char);
        strcpy(msg->nick_sender, name);
        msg->type = BROADCAST_SEND;
        strcpy(msg->infos, "");

        *donnee = malloc(msg->pld_len);
        strcpy(*donnee, send+start_msgall);
        
        return BROADCAST_SEND;
    }

    if(strncmp(send, "/msg ",  start_msg_all) == null){

       int start_msg_all_cmp = start_msg_all;

        while(send[start_msg_all_cmp] != ' '){
            if(send[start_msg_all_cmp++] == '\0'){
                *donnee = NULL;
                return UNICAST_SEND;
            }
        }
  int intial_size=strlen(send+start_msg_all_cmp)+1;
        msg->pld_len = (intial_size)*sizeof(char);
        strcpy(msg->nick_sender, name);
        msg->type = UNICAST_SEND;
        strncpy(msg->infos, send+start_msg_all, start_msg_all_cmp-start_msg_all);
        msg->infos[start_msg_all_cmp-start_msg_all] = '\0';

        *donnee = malloc(msg->pld_len);
        strcpy(*donnee, send+start_msg_all_cmp );
        
        return UNICAST_SEND;
    }

    if(strncmp(send, "/create ", start_create) == null){

        msg->pld_len = null;
        strcpy(msg->nick_sender, name);
        msg->type = MULTICAST_CREATE;
        strcpy(msg->infos, send+start_create);

        *donnee = NULL;

        return MULTICAST_CREATE;
        
    }

    if(strcmp(send, "/channel_list") == null){

        msg->pld_len = null;
        strcpy(msg->nick_sender, name);
       msg->type = MULTICAST_LIST;
        strcpy(msg->infos, "");

        *donnee = NULL;

        return MULTICAST_LIST;
    }

    if(strncmp(send, "/join ", start_join) == null){

       msg->pld_len = 0;
        strcpy(msg->nick_sender, name);
        msg->type = MULTICAST_JOIN;
        strcpy(msg->infos, send+6);

        *donnee = NULL;
        
        return MULTICAST_JOIN;
    }

    if(strncmp(send, "/quit ", start_quit) == 0){

        *donnee = NULL;
        msg->pld_len = 0;
        strcpy(msg->nick_sender, name);
        msg->type = MULTICAST_QUIT;
        strcpy(msg->infos, send+6);
        return MULTICAST_QUIT;
    }
}
    

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "wr.h"
#include <unistd.h>
#include "struct_msg.h"
#define max_att 10 

void sending_mesage(int socket, struct message *msg, void *donnee){
   
    
   int env;
    env = 0;
   char* ch = (char *) msg;
   int erreur;
   
    while (env != sizeof(struct message)){
        erreur = write(socket, ch+env, sizeof(struct message)-env);
        if(erreur == -1){
            perror(" problem write");
            exit(EXIT_FAILURE);
        }else{
             env += erreur;
        }
    }

    if(msg->pld_len > 0){
        ch= (char *) donnee;
        env= 0;
        while (send != msg->pld_len){
            erreur = write(socket, ch+env, msg->pld_len-env);
            if(erreur == -1){
                perror("write");
                exit(EXIT_FAILURE);
            }else{
                env+= erreur;
            }
        }
    }
}

enum msg_type recevoir_msg(int socket, struct message *msg, void **donnee){


    int nbr;
    char *ch;
    nbr = 0;
int rec;
rec = 0;
int erreur;
    ch = (char *) msg;
    rec = 0;
   nbr = 0;
    while (rec != sizeof(struct message)){
        erreur = read(socket, ch+rec, sizeof(struct message)-rec);
        if(erreur == -1){
            printf("il ya une eurreur en write");
            *donnee = NULL;
            return MULTICAST_QUIT;
        }else if(erreur == 0){
            if(nbr++ < max_att){
                fprintf(stderr, "\treceive_msg : max read attempt reachted.\n");
                *donnee = NULL;
                return MULTICAST_QUIT;
            }
        }else{
            rec += erreur;
        }
    }

    if(msg->pld_len > 0){
        char* ch= (char *) malloc(msg->pld_len);
        if(ch == NULL){
            perror(" problem in malloc:");
            exit(EXIT_FAILURE);
        }

        rec = 0;
        nbr = 0;
        while (rec != msg->pld_len){
            erreur = read(socket, ch+rec, msg->pld_len-rec);
            if(erreur == -1){
                perror(" problems  of writing");
                free(ch);
                *donnee = NULL;
                return MULTICAST_QUIT;
            }else if(erreur == 0){
                if(nbr++ < max_att){
                    fprintf(stderr, "receive_msg : max read attempt reachted.\n");
                    free(ch);
                    *donnee = NULL;
                    return MULTICAST_QUIT;
                }
            }else{
                rec += erreur;
            }
        }

        *donnee = (void *) ch;
    }else{
        *donnee = NULL;
    }

    return msg->type;

}

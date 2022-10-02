#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define Chaine_Size_Maxim 255
#include "inser_free1.h"



struct client_toinsert *create_client(int accept){
    struct client_toinsert *cl= NULL;
    cl=malloc(sizeof(struct client_toinsert));
    if(cl==NULL){exit(1);
    }

 
    (cl->portn) = malloc(sizeof(unsigned short));
     (cl->fd) = malloc(sizeof(int));
    
    (cl->namemach) = malloc( sizeof(char)* Chaine_Size_Maxim );
  
    cl->suivant = NULL;
    struct sockaddr_in *client_tobeadded ;
				*(cl->fd) = accept;
                char *ip_adress = inet_ntoa(client_tobeadded->sin_addr);;//convertir de unsigned char à string  
				*(cl->portn) = htons(client_tobeadded ->sin_port);
				strcpy( cl->namemach,ip_adress);


    return cl;
}
struct liste_des_clients* new_list(){
   struct liste_des_clients* element_client=malloc(sizeof(struct liste_des_clients));
 if(element_client==NULL){
 fprintf(stderr,"probleme d'allocation dynamique.\n");
 exit(EXIT_FAILURE);
 }
 int intial=0;
 element_client->client = NULL;
 element_client->nombre_des_clients= intial;


    return element_client;
}
void client_list_insert( struct liste_des_clients *cli,struct client_toinsert *cl){
struct liste_des_clients *element_client;


 cl->suivant=cli->client;
 cli->client=cl;
 cli->nombre_des_clients++;



}
void free_list (struct liste_des_clients *cl) {
    
    struct client_toinsert *c = cl->client;
    struct client_toinsert *c_prev;
    while (c != NULL) {

       if(c->fd != NULL) free(c->fd);
       if(c->portn != NULL) free(c->portn);
       if(c->namemach != NULL) free(c->namemach) ;
       c_prev = c;
       c = c->suivant;
       free(c_prev);
    
    }
    free(cl);
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include <unistd.h>
#include <poll.h>
#define timeout 5000
#define msg_length 256
#include "wr.h"
#define MAXimum 100
#include "struct_msg.h"
#define false  0 
#include "enum.h"
#define true  1
#define leng 500
#include"common.h"

int validation_nom(char *nk_name){
int longeur_nickname = 0;
	
	char ca =nk_name[0];
	while(ca != '\0'){
        if(longeur_nickname > NICK_LEN-1){
			printf("vous avez entrer un  nom  trés long \n");
			return false;
		}
		if(!(('A' <= ca && ca <= 'Z') || ('a' <= ca && ca <= 'z') || ('0' <= ca && ca <= '9'))){
			printf("tu dois pas entrer des caractéres  spéciaux .\n");
			return false;
		}
        longeur_nickname=longeur_nickname+1;
		ca= nk_name[ longeur_nickname];
		
	}


	if(longeur_nickname ==0){
		printf("Tle nom ne doit  pas contenir  une chaine de  caractére vide.\n");
		return false;
	}

	return true;
}

void exchange(int sock_fd_client)
{
    char buffer[MAXimum];
    int cmpt;
    for (;;) {
        bzero(buffer, sizeof(buffer));
        
        printf("please client enter your  message  : ");
        cmpt=0;
        while ((buffer[cmpt++] = getchar()) != '\n')
            ;
        
        
        write(sock_fd_client ,buffer, sizeof(buffer));
        memset(buffer,'=', sizeof(buffer));
        read(sock_fd_client, buffer, sizeof(buffer));
        printf(" what you  received From Server : ");
        puts(buffer);
        if ((strcmp(buffer, "quit")) == 0) {
            printf("tu va te deconnecter...\n");
            break;
        }
    }
}
				
void intialiser_nom(int socket_client){

	 int i=0;
 char tab[msg_length];
char ch;
void *donnee;
	
struct message *msg;
printf("donner  votre nickname\n");
				ch = getchar();
				while(ch != '\n'){
					tab[i++] = ch;
					ch = getchar();
				}
				tab[i++] = '\0';
				puts(tab);
	
	
	
	while(1){
		while(demande(tab, &msg, &donnee) != NICKNAME_NEW){
			if(donnee != NULL){
				free(donnee);
				donnee = NULL;
			}
			printf("tu dois choisir un nom svp!!");
			ch = getchar();
			i = 0;
			do
			{
				tab[i++] = ch;
			} while (ch != '\n')
			{
				ch = getchar();
			}
			tab[i++] = '\0';
		}
		if(validation_nom(msg->infos)){
			break;
			sending_mesage(socket_client,&msg,donnee);
		}else{
			ch = getchar();
			int i=0;
				while(ch != '\n'){
					tab[i++] = ch;
					ch = getchar();
				}
				tab[i++] = '\0';
				
		}

	}
}


 int connect_socket_client(char *machine, char *numport){

   struct addrinfo info;
    memset(&info, 0, sizeof(struct addrinfo));
    info.ai_family = AF_INET;        
    info.ai_socktype = SOCK_STREAM;  
    info.ai_protocol=IPPROTO_TCP;
    info.ai_flags = AI_PASSIVE;// le  numéro de port sera  sous  forme numérique  obligatoirement
    struct addrinfo *resu, *tmp;

     int  errcode=0; 
     int client_Socket;
    if(0 != (errcode=getaddrinfo(machine,numport, &info, &resu))){
        fprintf(stderr, "on va  avoir  l'eurreur: %s \n", gai_strerror(errcode));
        exit(EXIT_FAILURE);

    }
     for (tmp = resu; tmp != NULL; tmp=tmp->ai_next)
    {   if (tmp->ai_family == AF_UNSPEC) {
       int client_Socket=socket(tmp->ai_family,tmp->ai_socktype,tmp->ai_protocol);
        if (client_Socket==-1)continue;
        if(connect(client_Socket,tmp->ai_addr,tmp->ai_addrlen)!=-1) break;
      
       
    }}
    if(tmp==NULL){
        perror("On n'a pas pu ni créer ni bind serveur_Socket");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(resu);
	return client_Socket;
}
 
/*Lorsque des paramètres sont entrés après le nom du programme, ces paramètres sont passés dans
Principaux paramètres fonctionnels */
//nbr =nombres d'arguments utilisé 
//argp=les arguments passés en paramétres
//les arguments doivents êtres égale à  2 
int main(int nbr, char *argp[]){
    
    if(nbr!=3 ){
        perror("Oops!!vous avez des arguments qui manquent ");
        exit(-1);//on va sortir dans ce cas.
    }
     char ch;
 int i=0;
 char tab[msg_length];
   
int client_Socket=connect_socket_client(argp[1],argp[2]);

    struct pollfd fds[0];
    memset(fds,0, sizeof(struct pollfd));
   fds[0].fd = client_Socket;
    fds[0].events= POLLIN;// monitorer  l'activité  suivante qu'il ya d'autre donnée et on peut les  lire sans  bloquer polup erevent cad la socket  et  fermer   et on va  psser 
    fds[0].revents= 0 ;
   
     int pos=1;
    while(pos){
    
     int ready=poll(fds,0,timeout);
    if(ready==0){
        printf("timeout \n ");
    }
    else if (ready==-1){
        perror("poll_problem");
    }
    if(fds[0].revents & POLLIN){
    	 int i=0;
 char tab[msg_length];
char ch;
void *donnee;
	
struct message *msg;
printf("donner  votre nickname\n");
				ch = getchar();
				while(ch != '\n'){
					tab[i++] = ch;
					ch = getchar();
				}
				tab[i++] = '\0';
				puts(tab);
    r = demande(tab, &msg, &donnee);

				if (r==ECHO_SEND)
				{
					if (strlen((char *)data) > 0)
					{
						sending_msg(client_Socket, &msg, donnee);
						
					}
					if (r==NICKNAME_NEW)
					{
						if (name_validate(struct_msg.infos))
						{
							sending_msg(client_Socket, &msg, donnee);
						}
						break;
					}
					if (r==NICKNAME_LIST)
					{
						sending_msg(client_Socket, &msg, donnee);
					}

					if (r==NICKNAME_INFOS)
					{
						sending_msg(client_Socket, &stmsg, donnee);
					}
					if (r==BROADCAST_SEND)
					{
						sending_msg(client_Socket, &msg, donnee);
						
					}
					if (r==UNICAST_SEND)
					{
						if (daonnee == NULL)
						{
							printf("eurreur\n");
						}
						else
						{
							
							sending_msg(client_Socket, &msg, donnee);
						}
					}
					if (r==MULTICAST_CREATE)
					{
						if (validation_nom(msg.infos))
						{
							sending_msg(client_Socket, &msg, donnee);
						}
					}
					if (r==MULTICAST_LIST)
					{
						sending_msg(client_Socket, &msg, donnee);
					}
					if (r==MULTICAST_JOIN)
					{
						send_msg(client_Socket, &msg, donnee);
						printf("Joining channel : %s\n", struct_msg.infos);
					}
					if (r==MULTICAST_QUIT)
					{
						
							sending_msg(client_Socket, &msg, donnee);
							printf("bye: %s\n", msg.infos);
							
						
					}
					if (r==MULTICAST_SEND)
					{
						if (strlen((char *)donnee) > 0)
						{
							sending_msg(client_Socket, &msg, donnee);
							
						}
					}
					
       exchange(fds[0].fd);

  
                
    }
    if(fds[0].revents & POLLHUP){
			close(client_Socket);
			printf(" Deconnected\n");
			break;
		}
    }

  
    printf("la connection a été bien établie \n");
   
close(client_Socket);
    return 0;
    
}

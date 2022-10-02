#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>
#define BACKLOG 30
#define maxi_client 12
#define timeout 5000
#include "inser_free1.h"
#include "wr.h"
#define MAXimum 100
void exchange_server(int sock_ser)
{
    int cmpt;
    char buffer[MAXimum];
    cmpt= 0;
    
    for (;;) {
         memset( buffer, '=', MAXimum );
    buffer[MAXimum-1] = '\0';
       
   
        read(sock_ser, buffer, sizeof(buffer));
       
        printf(" message received from client: %s\t  me ssage to be send To client : ", buffer);


       bzero(buffer, MAXimum);
       
       
       printf("be aware you have  to resend  the same  msg you received ");
        while ((buffer[cmpt++] = getchar()) != '\n')
            ;
   
        write(sock_ser, buffer, sizeof(buffer));
   
         if ((strcmp(buffer, "quit")) == 0) {
            printf("tu va te deconnecter...\n");
            break;

        }
         
    }
}

int connect_socket( char *numport){

   struct addrinfo info;
    memset(&info, 0, sizeof(struct addrinfo));
    info.ai_family = AF_INET;        
    info.ai_socktype = SOCK_STREAM;  
    info.ai_flags = AI_PASSIVE;// le  numéro de port sera  sous  forme numérique  obligatoirement
    struct addrinfo *resu, *tmp;

     int  errcode=0; 
     int serveur_Socket;

     if(0 != (errcode=getaddrinfo(NULL,numport, &info, &resu))){   
        fprintf(stderr, "on va  avoir  l'eurreur: %s \n", gai_strerror(errcode));
        exit(EXIT_FAILURE);

    }
    for (tmp = resu; tmp != NULL; tmp=tmp->ai_next)
    {
        if (tmp->ai_family == AF_INET) {
        serveur_Socket=socket(tmp->ai_family,tmp->ai_socktype,tmp->ai_protocol);
        int value = 1;
	    //if (-1 == setsockopt(serveur_Socket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)))
		//perror("Setsockopt:");
        if (serveur_Socket==-1)continue;
        if(bind(serveur_Socket,tmp->ai_addr,tmp->ai_addrlen)==0) break;
            if(-1 == listen(serveur_Socket, BACKLOG))break;

        close(serveur_Socket);
    }
    
    }
    if(tmp==NULL){
        perror("On n'a pas pu ni créer ni bind serveur_Socket");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(resu);
	return serveur_Socket;
}
 
int main(int nbr, char **argp){
    
    if(nbr!=2 ){
        perror("Oops!!vous avez des arguments qui manquent ");
        exit(-1);//on va sortir dans ce cas.
    }
   
int serveur_Socket=connect_socket(argp[1]);

    struct pollfd fds[maxi_client];
    memset(fds,0, sizeof(struct pollfd)+maxi_client);
   struct liste_des_clients* new_liste=new_list();

fds[0].fd = serveur_Socket;
fds[0].events= POLLIN;// monitorer  l'activité  suivante qu'il ya d'autre donnée et on peut les  lire sans  bloquer polup erevent cad la socket  et  fermer   et on va  psser 
fds[0].revents= 0 ;

for(int i=1; i<maxi_client; i++){
	fds[i].fd = -1;
	fds[i].events = 0;
	fds[i].revents = 0;
}





    
int pos=1;
while(pos){

    

    int ready=poll(fds,maxi_client,timeout);
    /*if(ready==0){
        printf("timeout \n ");
    }*/
    if (ready==-1){
        perror("poll_problem");
    }
    for(int i =0;i<maxi_client;i++){
        if (fds[i].fd ==  serveur_Socket && fds[i].revents & POLLIN) {

    struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	printf("Waiting server ...\n");
	int new_fd = accept(serveur_Socket, (struct sockaddr *)&client_addr, &addr_len);
	if (new_fd <0){
		perror("Accept:");
        exit(EXIT_FAILURE);
    }
   
             for(int j = 0; j<maxi_client; j++){
					if(fds[j].fd == -1){
						fds[j].fd = new_fd;
						fds[j].events = POLLIN;
						fds[j].revents = 0;
						break;}
					
				}
struct client_toinsert* create= create_client(new_fd);
 client_list_insert(new_liste,create);
      fds[i].revents = 0;
     
            }
            
            else if (fds[i].fd !=  serveur_Socket && fds[i].revents & POLLIN){
                exchange_server(fds[i].fd);
                fds[i].revents = 0;
                
            }
            else if(fds[i].fd != serveur_Socket&& fds[i].revents & POLLHUP){
                printf("sorry you are deconnected  now");
                close(fds[i].fd);
                fds[i].fd = -1;
				fds[i].events = 0;
				fds[i].revents = 0;
            }
        }


    
     
       
    
    //}
    }
    close(serveur_Socket);
    free_list(new_liste);
  

    return 0;
}

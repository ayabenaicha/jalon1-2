#ifndef __inser_free_H__
#define __inser_free_H__
typedef struct client_toinsert{

 
    int *fd;
    unsigned short *portn;
     char *namemach;
    struct client_toinsert *suivant;
    
}client_toinsert;


struct liste_des_clients{
    struct client_toinsert *client;
     int nombre_des_clients ;
};
struct client_toinsert* create_client(int accept);
struct liste_des_clients* new_list();
void client_list_insert(struct liste_des_clients *cli, struct client_toinsert *cl);
void free_list (struct liste_des_clients *cl) ;

#endif
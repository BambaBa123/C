#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

                        /*Strucutres*/
struct machine{
    int numero_machine;
    char* nom_machine;
    char* adresseMAC;
    char* adresseIP;
    int connected;
    struct machine *suivant; 
    struct machine *precedent;
};
typedef struct machine Machine;

struct liste{
    Machine *premier;
};
typedef struct liste Liste;

                /***********************************/

            /* Initialisation de fonctions*/
char* macadress();/*Allouer directement une adresse MAC*/
char* ipadress();/*Allouer directement une adresse IP*/
char* enregistrer_fic(int num,char*adresse);/*Enregistrer dans le fichier*/
void supprimer_fic(char* adresse);/*Supprimer fichier de sauvegarde*/
char* con(int i);/*Statut de connexion*/
void connecte(Liste*liste,int choice);/*connexion au réseau*/
void deconnecte(Liste*liste,int choice);/*deconnexion du réseau*/
void ping(Liste* liste,int p);
char* dhcp_client(int num);
void dhcp_serveur();

        /***********************************/

int main(int argc, char* argv[]){
            /*déclarations de variables*/
    int continuer=1,continuer1=1,continuer2=1,n,z,num_machine,choice,p;
    char ficname[7];
    char lettre[1];
    lettre[1]='O';
    char* a;
    Machine *machine1,* nv,* aafficher,* aafficher2, * aafficher3,* aafficher4,* aafficher5,* aafficher6,* aafficher7;
    Liste *maliste;
    FILE *fp1;
    fpos_t position1;
        /***********************************/
    maliste = malloc(sizeof(*maliste));
    machine1= malloc(sizeof(*machine1));
    fp1=fopen("Serveur DHCP","w");
                            /*Initialisation*/
                if(maliste==NULL || machine1==NULL){
                    exit(EXIT_FAILURE);
                }else{
                    machine1->numero_machine=1;
                    machine1->connected=0;
                    machine1->adresseIP="192.168.1.1";
                    machine1->adresseMAC="08:07:20:00:20:12";
                    machine1->nom_machine="Serveur DHCP";
                    machine1->suivant=NULL;
                    machine1->precedent=NULL;
                    maliste->premier=machine1;
                }
                fprintf(fp1,"Machine %d\n",machine1->numero_machine);
                fgetpos(fp1,&position1);
                fsetpos(fp1,&position1);
                fputs(machine1->adresseMAC,fp1);
                fgetpos(fp1,&position1);
                fsetpos(fp1,&position1);
                fputs(machine1->adresseIP,fp1);
                fgetpos(fp1,&position1);
                fsetpos(fp1,&position1);
                fputs("\n",fp1);
                fgetpos(fp1,&position1);
                fsetpos(fp1,&position1);
                fputs(machine1->nom_machine,fp1);
                fgetpos(fp1,&position1);
                fsetpos(fp1,&position1);
                    /***********************************/  
                    dhcp_serveur();
                    sleep(5);
                while(continuer2==1){

                    printf("\n***********************************************************************\n");
                    printf("\n");
                    printf("\t\t\tPARC DE MACHINES\n");
                    printf("\n");
                    printf("\n***********************************************************************\n");
                    printf("\n");
                    printf("\t1.Ajouter une machine\n\t2.Ajouter une machine au réseau (Connexion) \n\t3.Lister les machines\n\t4.Lister les machines connectés au réseau\n\t5.Supprimer une machine\n\t6.Supprimer une machine du réseau (Déconnexion)\n\t7.Vider le parc\n\t8.Ping\n\t9.Quitter\n\n");
                                        printf("Reponse:");
                    scanf("%d",&n);

                    switch(n){
                        case 1: /*Ajout d'une machine dans le parc*/                          
                            nv =malloc(sizeof(*nv));
                            if(nv==NULL){
                                exit(EXIT_FAILURE);
                            }else{
                                nv->numero_machine= maliste->premier->numero_machine +1;
                                nv->connected=0;
                                nv->adresseMAC=macadress();
                                nv->adresseIP=NULL;                                
                                nv->suivant=maliste->premier;
                                nv->precedent=NULL;
                                maliste->premier->precedent=NULL;
                                maliste->premier=nv;
                            }
                            nv->nom_machine =enregistrer_fic(nv->numero_machine,nv->adresseMAC);
                                printf("Vous voulez connecté la machine au réseau ? O/N \n");
                                scanf("%s",lettre);
                            if(strcmp(lettre,"O")==0){
                                sleep(2);
                                printf("->En cours de connexion\n\n");
                                nv->connected=1 ;
                                nv->adresseIP=dhcp_client(nv->numero_machine);
                                sleep(1);
                                printf("\n\t\n->Connecté\n");
                            }else if(strcmp(lettre,"N")==0){
                                sleep(2);
                                printf("\tLa machine ne sera pas connecté au réseau! \n \tVous pourrez la connecter au réseau ultérieurement\n");
                            }else{
                                printf("Vous devriez entrerO ou N ,de ce fait, la machine n'a pas été connecté au réseau! \n \t -> Vous pourrez le connecter au réseau ultérieurement\n");
                            }
                            
                            aafficher= maliste->premier;
                            while(aafficher->suivant!=NULL ){
                                aafficher=aafficher->suivant;
                            }
                                sleep(3);
                            break;


                        case 2:/*Ajout d'une machine au réseau*/
                        printf("\t\t*******************AJOUT D'UNE MACHINE AU RESEAU*******************\n\n");
                            aafficher2= maliste->premier;
                            if(maliste==NULL){
                                exit(EXIT_FAILURE);
                            }else{
                                while(aafficher2!=NULL && aafficher2->suivant!=NULL){
                                    if(aafficher2->connected==0){
                                        printf("Non connecté %d %s %d\n",aafficher2->numero_machine,aafficher2->nom_machine,aafficher2->connected);
                                    }
                                    if(aafficher2->connected==1){                                       
                                        printf("Déjà connecté %d %s %d\n",aafficher2->numero_machine,aafficher2->nom_machine,aafficher2->connected);
                                    }
                                    aafficher2=aafficher2->suivant;   
                                }
                                printf("Déjà connecté %d %s %d\n",machine1->numero_machine,machine1->nom_machine,machine1->connected);
                            }
                            sleep(3);
                            printf("Entrer le numéro de la machine à ajouter au réseau\n");
                            scanf("%d",&choice); 
                            if(choice!=1){
                                printf("->En cours de connexion\n\n");
                                connecte(maliste,choice);
                                sleep(1);
                            }else{
                                sleep(1);
                                printf("La machine 1 ne peut pas être ajoutée au réseau!\n");
                            }                              
                            break;

                        case 3:/*Afficher la liste des machines du parc*/
                            printf("\t\t*******************LISTE DES MACHINES*******************\n\n"); 
                            sleep(1);
                            aafficher= maliste->premier;
                            if(maliste==NULL){
                                exit(EXIT_FAILURE);
                            }else{
                                while(aafficher !=NULL && aafficher->suivant!=NULL){
                                    printf("\t\t\t %d- mac=%s (%s) - Status:%s => ip= %s\n\n" ,aafficher->numero_machine,aafficher->adresseMAC,aafficher->nom_machine,con(aafficher->connected),aafficher->adresseIP);
                                    aafficher=aafficher->suivant;
                                }
                                if(aafficher->suivant==NULL ){
                                    printf("\t\t\t %d- %s (%s) => ip= %s\n\n" ,aafficher->numero_machine,aafficher->adresseMAC,aafficher->nom_machine,aafficher->adresseIP);
                                }
                                sleep(3);                            
                            }
                            break;     
                        case 4:/*Afficher les machine, du réseau*/
                        printf("\t**********LES MACHINES CONNECTES AU RESEAU**********\n");
                            sleep(2);
                            aafficher5= maliste->premier;
                            if(maliste==NULL){
                                exit(EXIT_FAILURE);
                            }else{
                                while(aafficher5->suivant!=NULL ){
                                    if(aafficher5->connected==1){
                                        printf("\t\t\t %d: %s (%s): %d\n\n" ,aafficher5->numero_machine,aafficher5->adresseMAC,aafficher5->nom_machine,aafficher5->connected);
                                    }
                                    aafficher5=aafficher5->suivant;
                                }
                                sleep(3);
                            }
                            break;
                        case 5: /*Supression d'une machine*/
                            aafficher3= maliste->premier;
                            aafficher7=maliste->premier;
                            ficname[0]='M';
                            ficname[1]='a';
                            ficname[2]='c';
                            ficname[3]='h';
                            ficname[4]='i';
                            ficname[5]='n';
                            ficname[6]='e';
                            printf("\t\t*******************SUPPRESSION D'UNE MACHINE*******************\n\n"); 
                            sleep(1);
                            printf("Entrer le numéro de la machine à supprimer\n");
                            scanf("%d",&num_machine);
                            sleep(2);
                            if(num_machine!=1){
                                printf("\t\t\t->La machine n°%d va être supprimée\n\n",num_machine);
                            }else{
                                printf("\t\t\t->La machine n°%d ne peut pas être supprimée\n\n",num_machine);
                            }
                            while(aafficher3!=NULL){
                                if(aafficher3->numero_machine==num_machine && aafficher->numero_machine==1){
                                    if(aafficher3==maliste->premier){  
                                        maliste->premier=aafficher3->suivant;
                                        free(aafficher3);
                                        aafficher3=maliste->premier;
                                    }else{
                                        aafficher7->suivant =aafficher3->suivant;
                                        free(aafficher3);
                                        aafficher3=aafficher7->suivant;
                                    }
                                }else{
                                    aafficher7=aafficher3;            
                                    aafficher3=aafficher3->suivant;
                                }
                            }
                            sleep(3);
                            break;
                        case 6:/*Supprimer une machine du réseau (Déconnexion)*/
                            aafficher6= maliste->premier;
                            if(maliste==NULL){
                                exit(EXIT_FAILURE);
                            }else{
                                printf("\t***********LISTE DES MACHINES CONNECTES AU RESEAU**********\n\n");
                                sleep(1);
                                while(aafficher6->suivant!=NULL){
                                    if(aafficher6->connected==1){
                                        printf("\t\t\t %d: %s (%s): %d\n\n" ,aafficher6->numero_machine,aafficher6->adresseMAC,aafficher6->nom_machine,aafficher6->connected);
                                    }
                                    aafficher6=aafficher6->suivant;
                                } 
                                sleep(2);
                                printf("Entrer le numéro de la machine à déconnecter\n");
                                scanf("%d",&choice);
                                if(choice!=1){
                                    deconnecte(maliste,choice);
                                }else{
                                    printf("La machine 1 n'est pas dans le réseau!\n");
                            }
                                sleep(3);
                            }
                            break;
                        case 7:/*Vider le parc(Suppression de toutes les machines*/
                            printf("\t\t*******************VIDER LE PARC*******************\n\n"); 
                            aafficher4= maliste->premier;
                            ficname[0]='M';
                            ficname[1]='a';
                            ficname[2]='c';
                            ficname[3]='h';
                            ficname[4]='i';
                            ficname[5]='n';
                            ficname[6]='e';
                            while(aafficher4->suivant!=NULL){
                                maliste->premier=aafficher4->suivant;
                                a=strcat(ficname,aafficher4->adresseMAC);
                                remove(a);   
                                free(aafficher4);
                                aafficher4=aafficher4->suivant;
                                a=NULL;
                            }
                            sleep(1);
                            printf("\t\t\tIl nous reste que la machine n°1\n\n");
                            sleep(3);
                            break;
                        case 8:/*Ping*/
                        printf("\t\t*******************PING*******************\n\n");
                            sleep(1);
                            printf("Choisisser votre machine!\n");
                            scanf("%d",&p);
                            ping(maliste,p);
                            sleep(3);
                            break;
                        case 9:/*Quitter*/
                            return EXIT_SUCCESS;
                            sleep(3);
                            break;
                        
                        default:
                            printf("Veuillez choisir les chiffres de la liste ci-dessus");
                            break;
                    }
                } 

}
                    /*Corps des fonctions*/
/*1*/char *macadress(){
	const char alphabet[] = "ABCDEF0123456789";
	char adresseMAC[17];
	int indice,i;
	srand(time(NULL));
	for(i=0;i<17;i++){
		indice = rand() % (16);
		adresseMAC[i]=alphabet[indice];
	}
	adresseMAC[17]='\0';
	for(i=0;i<16;i++){
	switch(i){
		case 2 : adresseMAC[2]=':';
		case 5 : adresseMAC[5]=':';
		case 8 : adresseMAC[8]=':';
		case 11 : adresseMAC[11]=':';
		case 14: adresseMAC[14]=':';
		default:
			break;
		}
	}
	char *copie=NULL;
	copie=malloc(strlen(adresseMAC)+1*sizeof(char));
	strcpy(copie,adresseMAC);
	return copie;
}
/*2*/char* enregistrer_fic(int num,char* adresse){
    char ficname[7];
    char nom[20];
    char nombre[2];
    char lettre[1];
    lettre[1]='O';
    ficname[0]='M';
    ficname[1]='a';
    ficname[2]='c';
    ficname[3]='h';
    ficname[4]='i';
    ficname[5]='n';
    ficname[6]='e';
    fpos_t position;
    FILE *fp=fopen(ficname,"w");
    printf("\t\t*******************AJOUT D'UNE MACHINE*******************\n");  
    do{  
        printf("Entrer le nom de votre machine \n");
        scanf("%s",nom);
        sleep(1);
        printf("Votre machine s'appelera: %s \n",nom);
        sleep(1);
        printf("Vous confirmez? O/N \n");
        scanf("%s",lettre);
    }while(strcmp(lettre,"O")); 
    fprintf(fp,"Machine %d\n",num);
    fgetpos(fp,&position);
    fsetpos(fp,&position);
    fputs(adresse,fp);
    fgetpos(fp,&position);
    fsetpos(fp,&position);
    fputs("\n",fp);
    fgetpos(fp,&position);
    fsetpos(fp,&position);
    fputs(nom,fp);
    fgetpos(fp,&position);
    fsetpos(fp,&position);
    char *copie=NULL;
	copie=malloc(strlen(nom)+1*sizeof(char));
	strcpy(copie,nom);
    return copie;
}
/*3*/void deconnecte(Liste* liste,int choice){
    Machine *aafficher=liste->premier;
    while(aafficher->suivant!=NULL){
        if(aafficher->numero_machine==choice){
            aafficher->connected=0;
            aafficher->adresseIP=NULL;
        }
        aafficher=aafficher->suivant;
    }
    sleep(2);
    printf("En cours de déconnexion\n");
    sleep(1);
    printf("Déconnecté\n");

}
/*4*/char* con(int i){
    char* a;
    if(i==0){
        a="Non Connecté";
    }else{
        a=" Connecté";
    }
    return a;
}
/*5*/char* ipadress(){
    	srand(time(NULL));
	char adresse[13],s[]=" ";
	int indice;
	char first[]="0123";
	char second[]="0123456789";
	indice = (rand() % 255)+1;
	adresse[0]='1';
	adresse[1]='9';
	adresse[2]='2';
	adresse[3]='.';
	adresse[4]='1';
	adresse[5]='6';
	adresse[6]='8';
	adresse[7]='.';
	adresse[8]='1';
	adresse[9]='.';
	sprintf(s,"%d",indice);
	indice = (rand() % (3))+1;
	adresse[10]=first[indice];
	for(int i=11;i<12;i++){
		indice = (rand() % (10))+1;
		adresse[i]=second[indice];
	}
	char *copie=NULL;
	copie=malloc(strlen(adresse)+1*sizeof(char));
	strcpy(copie,adresse);
    return copie;
}
/*6*/void ping(Liste* liste,int p){
    Machine *aafficher=liste->premier;
    Machine *aaffiche=liste->premier;
    Machine *temp;
    char addr[12];
    int ok;
    if(p==1){
        printf("Impossible d'utiliser cette machine\n");
    }
    while(aafficher->suivant!=NULL && p!=1){
        if(aafficher->numero_machine==p){
            printf("Vous allez utilisez la machine n°%d:\n",aafficher->numero_machine);
            sleep(1);
            printf("\tNom: %s\n",aafficher->nom_machine);
            sleep(1);
            printf("\tAdresse MAC:%s\n",aafficher->adresseMAC);
            sleep(1);
            if(aafficher->connected==1){
                printf("La machine est déjà connectée au réseau. \n");
            }
            if(aafficher->connected==0){
                printf("La machine n'est pas connectée au réseau\n");
                printf("\t->Nous allons d'abord connecté la machine au réseau.\n\n");
                aafficher->connected=1;
            }
            sleep(1);
            printf("\tAdresseIP: %s\n",aafficher->adresseIP);
        }
        temp=aafficher;
        aafficher=aafficher->suivant;
    }
    printf("Qu'elle machine voulez vous pinger?(Entrer l'adressse IP de la machine!)\n ");
    sleep(1);
    printf("<Machine %d> ping  ",temp->numero_machine);
    scanf("%s",addr);
    while(aaffiche->suivant!=NULL){
        int a=strcmp(addr,aaffiche->adresseIP);
        if(a==0){
            ok=1;
        }
        if(a!=0){
            ok=0;
        }

        aaffiche=aaffiche->suivant;
    }
    if(ok==1){
        printf("\nPING %s (%s) 56(84) bytes of data.\n",temp->adresseIP,temp->adresseIP);
        for(int i=1;i<=10;i++){
                printf("64 bytes from %s icmp_seq=i ttl=64 time=%d ms\n",temp->adresseIP,i);
                sleep(1);
            }
        sleep(3);
        printf("---%s ping statistics ---\n10 packets transmitted, 10 received, 0 loss packets, time 10ms\nrtt min/avg/max/mdev = 1/5/10/0 ms\n",temp->adresseIP);
        sleep(5);
    }
    if(ok==0){
        printf("\nPING %s (%s) 56(84) bytes of data.\n",temp->adresseIP,temp->adresseIP);
        for(int i=1;i<=10;i++){
                printf("Request timed out.\n");
                sleep(1);
            }
        sleep(3);
        printf("---%s ping statistics ---\n10 packets transmitted, 0 received, 10 loss packets, time 1ms\nrtt min/avg/max/mdev = 0/0.5/1/0 ms\n",temp->adresseIP);
        sleep(5);
    }
}
/*7*/void connecte(Liste* liste,int choice){
    Machine *aafficher=liste->premier;
    while(aafficher->suivant!=NULL){
        if(aafficher->numero_machine==choice){
            aafficher->connected=1;
            aafficher->adresseIP=dhcp_client(choice);
        }
        aafficher=aafficher->suivant;
    }
    sleep(2);
    printf("->Connecté\n\n");
    sleep(2);
}
/*8*/void dhcp_serveur(){
    sleep(1);
    printf("\tDémarrage du serveur DHCP\n");
    sleep(1);
    printf("\t\t<DHCP Server>\n");    
    sleep(1);
    printf("Listening on LPF/eth1/08:00:27::17:65:0a\n");
    sleep(1);
    printf("Sending on LPF/eth1/08:00:27::17:65:0a\n");
    sleep(1);
    printf("Listening on socket/fallback\n");
    sleep(1);
    printf("DHCP RELEASE on eth1 to 192.168.1.1 port 67\n\n");
}
/*9*/char* dhcp_client(int num){
    sleep(1);
    printf("\t\t<Machine %d>\n",num);
    sleep(1);
    printf("Listening on LPF/eth1/08:00:27::17:65:0a\n");
    sleep(1);
    printf("Sending on LPF/eth1/08:00:27::17:65:0a\n");
    sleep(1);
    printf("Listening on socket/fallback\n");
    sleep(1);
    printf("DHCP DISCOVER on eth1 to 255.255.255.255 port 67 interval 3\n");
    sleep(1);
    printf("DHCP OFFER from 192.168.1.1\n");
    sleep(1);
    printf("DHCP REQUEST on eth1 to 255.255.255.255 port 67\n");
    sleep(1);
    printf("DHCP PACK from 192.168.1.1\n");
    char *copie=NULL;
	copie=malloc(strlen(ipadress())+1*sizeof(char));
	strcpy(copie,ipadress());
    printf("bound to %s -- renewal in 32768 seconds\n",copie);
    return copie;
}

            /***********************************/
                    
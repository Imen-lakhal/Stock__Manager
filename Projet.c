#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct DATE {
    int JOUR;
    int MOIS;
    int ANNEE;
} date;
typedef struct PRODUIT{
    int ID; //the unique identifier of a product must consist of 6 digits between 100000 and 999999
    char NOM[20]; //the name of a product must not contain any numbers
    float PRIX;//the price of a product must be positive
    char DESC[30];//the description of a product is a  string without spaces
    date DE,DS;
} produit ;

void Ajouter(){
    produit p;
    FILE *f=fopen("stock.txt","a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    printf("\nAjout d\'un nouveau produit \n\n");

    do{
            printf("Donnez l\'identifiant du produit a ajouter(6 chiffres): ");
            fflush(stdin);
            scanf("%d", &p.ID);
    }while(p.ID<100000 || p.ID>999999);


    do{
            printf("Donnez le nom du produit a ajouter (string without digits) : ");
            fflush(stdin);
            gets(p.NOM);
    }while(chaine_sans_chiffre(p.NOM)==0);

    do {
            printf("Donnez le prix du produit a ajouter(prix > 0) : ");
            fflush(stdin);
            scanf("%f", &p.PRIX);
    }while(p.PRIX<0);


    do {
        printf("Donnez la description du produit a ajouter (string without spaces) : ");
        fflush(stdin);
        gets(p.DESC);
    }while(sans_epace(p.DESC)==0);

    do {
            printf("Donnez date d\'entree du produit a ajouter (JJ MM AAAA) :");
            scanf("%d%d%d",&p.DE.JOUR,&p.DE.MOIS,&p.DE.ANNEE);
    }while((p.DE.JOUR<0 || p.DE.JOUR>31 || p.DE.MOIS <0 || p.DE.MOIS>12 || p.DE.ANNEE<1000 || p.DE.ANNEE>9999 ) ||((p.DE.MOIS==2)&& p.DE.JOUR>28));
    do{
            printf("Donnez date de sortie du produit a ajouter (JJ MM AAAA) : ");
            scanf("%d%d%d",&p.DS.JOUR,&p.DS.MOIS,&p.DS.ANNEE);

    }while((p.DS.JOUR<0 || p.DS.JOUR>31 || p.DS.MOIS <0 || p.DS.MOIS>12 || p.DS.ANNEE<1000 || p.DS.ANNEE>9999)||((p.DS.MOIS==2)&& p.DS.JOUR>28));
    fprintf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",p.ID,p.NOM,p.PRIX,p.DESC,p.DE.JOUR,p.DE.MOIS,p.DE.ANNEE,p.DS.JOUR,p.DS.MOIS,p.DS.ANNEE);
    fclose(f);
    printf("L\' operation d\'ajout effectuee avec succes !\n\n");
    application();
    return 0;
}
void Supprimer(){
    int x,test=1;
    FILE *f;
    FILE *nf;
  	f=fopen("stock.txt","a+");
  	nf=fopen("tmpfile.txt","w");
    if (f == NULL || nf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
  	do{
            printf("Donner l'identifiant de produit a supprimer (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    produit p;
  	while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&p.ID,p.NOM,&p.PRIX,&p.DESC,&p.DE.JOUR,&p.DE.MOIS,&p.DE.ANNEE,&p.DS.JOUR,&p.DS.MOIS,&p.DS.ANNEE)!=EOF){

		if(p.ID!=x){
            fprintf(nf,"%d %s %f %s %d/%d/%d %d/%d/%d\n",p.ID,p.NOM,p.PRIX,p.DESC,p.DE.JOUR,p.DE.MOIS,p.DE.ANNEE,p.DS.JOUR,p.DS.MOIS,p.DS.ANNEE);
            test=0;
		}
		else {
            test=1;
		}
    }
    if (test==0){
               	printf("Identifiant introuvable !");
    }
	fclose(nf);
	fclose(f);
	f=fopen("stock.txt","w");
	nf=fopen("tmpfile.txt","r");
	while (fscanf(nf,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&p.ID,p.NOM,&p.PRIX,&p.DESC,&p.DE.JOUR,&p.DE.MOIS,&p.DE.ANNEE,&p.DS.JOUR,&p.DS.MOIS,&p.DS.ANNEE)!=EOF){
            fprintf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",p.ID,p.NOM,p.PRIX,p.DESC,p.DE.JOUR,p.DE.MOIS,p.DE.ANNEE,p.DS.JOUR,p.DS.MOIS,p.DS.ANNEE);

	}
	fclose(nf);
	fclose(f);
	if(test==1){
            printf("L\' operation de suppression effectuee avec succes !\n\n");

	}
	application();

}


void AfficherDesc(){
    int x;
    int test=0;
    produit prod;
    do {
            printf("Donner l'identifiant de produit pour voir son description (6 chiffres):");
            scanf("%d",&x);
    }while(x<100000 || x>999999);

    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
        if(prod.ID==x){
            printf("\nLa description de produit d\'identifiant %d est : %s\n",x,prod.DESC);
            test=1;
         }
    }
    if(test==0){
        printf("Aucun produit avec ce identifiant !\n\n");
    }
    fclose(f);
    application();
    return 0;

}
void AfficherStock(){
    char line[256];

    printf("\nLes produits actuellement en stock sont :\n\n");


    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier");
    exit(1) ;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
    printf("%s", line);
    }
    fclose(f);
    application();

  return 0;
}
void modifierProduit( ){
    int choix,x,test=0;
  	do{
            printf("Donner l'identifiant de produit a modifier (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    FILE *f=fopen("stock.txt","r");
    FILE *nf=fopen("tmpfile.txt","w+");
    if (f == NULL  || nf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    produit prod;

	while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
            if(prod.ID==x){
                printf("Produit avant modification :\n");
                printf("(1) nom :%s\n",prod.NOM);
                printf("(2) prix :%f\n",prod.PRIX);
                printf("(3) description :%s\n",prod.DESC);
                printf("(4) date entree :%d/%d/%d\n",prod.DE.JOUR,prod.DE.MOIS,prod.DE.ANNEE);
                printf("(5) date sortie :%d/%d/%d\n",prod.DS.JOUR,prod.DS.MOIS,prod.DS.ANNEE);
                test=1;

                do{
                        printf("Merci de choisir le choix de modification: ");
                        scanf("%d",&choix);
                        printf("\n");
                }while(choix<0 || choix >6);
                switch(choix){
                        case 1:
                            do{
                                printf("Saisir le nouveau nom :");
                                fflush(stdin);
                                gets(prod.NOM);
                            }while(chaine_sans_chiffre(prod.NOM)==0);
                            break;
                        case 2:
                            do{
                                printf("Saisir le nouveau prix :");
                                fflush(stdin);
                                scanf("%f", &prod.PRIX);
                            }while(prod.PRIX<0);
                            break;
                        case 3:
                            do {
                                    printf("Saisir la nouvelle description (string without spaces) : ");
                                    fflush(stdin);
                                    gets(prod.DESC);
                            }while(sans_epace(prod.DESC)==0);
                            break;
                        case 4:
                            do{
                                    printf("Saisir la nouvelle date d'entrée (JJ MM AAAA) :");
                                    fflush(stdin);
                                    scanf("%d",&prod.DE.JOUR);
                                    scanf("%d",&prod.DE.MOIS);
                                    scanf("%d",&prod.DE.ANNEE);
                            }while((prod.DE.JOUR<0 || prod.DE.JOUR>31 || prod.DE.MOIS <0 || prod.DE.MOIS>12 || prod.DE.ANNEE<1000 || prod.DE.ANNEE>9999 ) ||((prod.DE.MOIS==2)&& prod.DE.JOUR>28));
                            break;
                        case 5:
                            do{
                                    printf("Saisir la nouvelle date de sortie (JJ MM AAAA) :");
                                    fflush(stdin);
                                    scanf("%d",&prod.DS.JOUR);
                                    scanf("%d",&prod.DS.MOIS);
                                    scanf("%d",&prod.DS.ANNEE);
                            }while((prod.DS.JOUR<0 || prod.DS.JOUR>31 || prod.DS.MOIS <0 || prod.DS.MOIS>12 || prod.DS.ANNEE<1000 || prod.DS.ANNEE>9999)||((prod.DS.MOIS==2)&& prod.DS.JOUR>28));
                            break;
                        case 0:
                            exit(1);
                        }
            }
            fprintf(nf,"%d %s %f %s %d/%d/%d %d/%d/%d\n",prod.ID,prod.NOM, prod.PRIX,prod.DESC,prod.DE.JOUR,prod.DE.MOIS,prod.DE.ANNEE,prod.DS.JOUR,prod.DS.MOIS,prod.DS.ANNEE);
    }
    if(test==0){
        printf("Aucun produit avec ce identifiant !\n\n");
    }

	fclose(nf);
	fclose(f);
    f=fopen("stock.txt","w+");
	nf=fopen("tmpfile.txt","r");
	if(f==NULL || nf ==NULL){
	    printf("Erreur lors de l'ouverture du fichier");
		exit(1);
	}
	while (fscanf(nf,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE, &prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
            fprintf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",prod.ID,prod.NOM,prod.PRIX,prod.DESC,prod.DE.JOUR,prod.DE.MOIS,prod.DE.ANNEE,prod.DS.JOUR,prod.DS.MOIS,prod.DS.ANNEE);
    }
	fclose(nf);
	fclose(f);
	if(test==1){
            printf("L\' operation de modification effectuee avec succes !\n\n");

	}

	application();
}

void Recherche(){
    int x,test=0;
  	do{
            printf("Donner l'identifiant de produit a chercher (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    produit prod;
    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){

			if(prod.ID==x){
                printf("Identifiant : %d\nNom : %s\nPrix : %f\nDescription : %s\nDate de entree : %d/%d/%d\nDate de sortie : %d/%d/%d\n ",prod.ID,prod.NOM,prod.PRIX,prod.DESC,prod.DE.JOUR,prod.DE.MOIS,prod.DE.ANNEE,prod.DS.JOUR,prod.DS.MOIS,prod.DS.ANNEE);
                test=1;
	   	   }
    }
    if(test==0){
        printf("Aucun produit avec ce identifiant !\n\n");
    }
	fclose(f);
	application();
}


void hestoriqueEntree(){
    int jour, mois,testjour=0,testmois=0;
    produit prod;
    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    do{
            printf("Donner le jour d\'entree : ");
            scanf("%d", &jour);
    }while(jour<0 || jour>31);
    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
        if(prod.DE.JOUR==jour){
            printf("C'est le jour l\'entree du produit : %s\n",prod.NOM);
            testjour=1;

        }
    }
    if(testjour==0){
            printf("Aucun produit dans ce jour !\n ");
        }
    fclose(f);
    f=fopen("stock.txt","r");
    do{
            printf("Donner le mois d\'entree : ");
            scanf("%d", &mois);
    }while(mois <0 || mois>12 );

    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
        if(prod.DE.MOIS==mois){
            printf("C'est le mois d\'entree du produit : %s\n",prod.NOM);
            testmois=1;
        }
    }
    if(testmois==0){
            printf("Aucun produit dans ce mois !\n ");
        }
    	fclose(f);
    	application();

}

void hestoriqueSortie(){
    int jour, mois,testjour=0,testmois=0;
    produit prod;
    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    do {
            printf("Donner le jour d\'sortie : ");
            scanf("%d", &jour);
    }while(jour<0 || jour>31);


    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
        if(prod.DS.JOUR==jour){
            printf("C'est le jour de sortie du produit : %s\n",prod.NOM);
            testjour=1;
        }
    }
    if(testjour==0){
            printf("Aucun produit dans ce jour!\n");
        }
    fclose(f);
    f=fopen("stock.txt","r");
    do {
            printf("Donner le mois de sortie :");
            scanf("%d", &mois);
        }while(mois <0 || mois>12 );


    while (fscanf(f,"%d %s %f %s %d/%d/%d %d/%d/%d\n",&prod.ID,prod.NOM,&prod.PRIX,&prod.DESC,&prod.DE.JOUR,&prod.DE.MOIS,&prod.DE.ANNEE,&prod.DS.JOUR,&prod.DS.MOIS,&prod.DS.ANNEE)!=EOF){
        if(prod.DS.MOIS==mois){
            printf("C'est le mois de sortie du produit : %s\n",prod.NOM);
            testmois=1;

        }
    }
        if(testmois==0){
            printf("Aucun produit dans ce mois !\n ");
        }
    	fclose(f);
    	application();
}

int main(int argc, char *argv[]) {
    application();
    return 0;

}
void application(){
		printf("\t\t\t\t __________________________________________________\n");
		printf("\t\t\t\t|        -------- Bienvenue --------               | \n");
		printf("\t\t\t\t| 1  : Gestion du produit.                         | \n");
		printf("\t\t\t\t| 2  : Afficher le stock .                         | \n");
		printf("\t\t\t\t| 3  : Afficher l'historique d'entree du produit.  | \n");
		printf("\t\t\t\t| 4  : Afficher l'historique de sortie du produit. | \n");
		printf("\t\t\t\t| 0  : Quitter .                                   | \n");
		printf("\t\t\t\t|__________________________________________________| \n");
		printf("\n");
        int c;
		do {
                printf("Merci de choisir votre commande : ");
                scanf("%d",&c);
        }while(c<0 || c>4);
        commande(c);

}




void commande(int x){

	switch(x){
			case 1:
				GestionProduit();
				break;
			case 2:
				AfficherStock();
				break;
			case 3:
			    hestoriqueEntree();
				break;
			case 4:
			    hestoriqueSortie();
				break;
			case 0:
			    exit(1);
            default :
                printf("Erreur");
                return 0;
		}
	}
	void GestionProduit(){
	    int x;
		printf("\t\t\t\t _______________________________________________  \n");
		printf("\t\t\t\t|        -------- Bienvenue --------            | \n");
		printf("\t\t\t\t| 1  : Ajouter un produit.                      | \n");
		printf("\t\t\t\t| 2  : Afficher la description d\'un produit.    | \n");
		printf("\t\t\t\t| 3  : Supprimer un produit.                    | \n");
		printf("\t\t\t\t| 4  : Modifier un produit.                     | \n");
		printf("\t\t\t\t| 5  : Recherche d\'un produit dans le stock.    | \n");
		printf("\t\t\t\t| 0  : Retour .                                 | \n");
		printf("\t\t\t\t|_______________________________________________| \n");
		printf("\n");
	    do{
		printf("Merci de choisir votre choix : ");
		scanf("%d",&x);
		}while(x<0 || x>5);
        choix(x);
		return 0;
	}



void choix(int x ){
	switch(x){
			case 1:
				Ajouter();
				break;
			case 2:
				AfficherDesc();
				break;
			case 3:
				Supprimer();
				break;
			case 4:
				modifierProduit();
				break;
			case 5:
				Recherche();
				break;
			case 0:
				application();
            default :
                printf("erreur");
                return 0;
		}
		return 0;
}
int sans_epace(char ch[30]){
    int i;
    int l=strlen(ch);
    for (i=0 ;i<l ;i++){
        if (ch[i]==' '){
            return 0;
        }
    }
    return 1;
}
int  chaine_sans_chiffre(char ch[20]){
    if (strpbrk(ch, "0123456789")){
            return 0;
    }
    else{
        return 1;
    }
    return 0;
}

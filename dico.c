
// Fonction générant le dictionnaire

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico.h"



void lecture(char* filename,char** L,int s)
{

	FILE* f=fopen(filename,"rb");
	if (f==NULL)
	{
		printf("Impossible d'ouvrir le fichier");
	}
	L[0]=malloc(sizeof(char*));
	char buffer[50];
    fscanf(f,"%s",buffer);
	strcpy(L[0],buffer);
    for (int i=1;i<s;i++)
	{
        L[i]=malloc(sizeof(char*));
		fscanf(f,"%s",buffer);
		strcpy(L[i],buffer);
	}
	
    fclose(f);

}

char* mot_aleatoire(int l,char* filename,char** L,int s)
{
	char* liste_mots[s];
	if (L==NULL)
	{
		printf("L'allocation a échoué");
		return NULL;
	}
	lecture(filename,L,s);
	int j=0;
	for (int i=0; i<s; i++) 
	{		
		if (strlen(L[i])==l) 
		{
			liste_mots[j]=L[i];
			j++;
		}
	}
	srand(time(NULL));
	int r = rand()%j;
	char* mot = liste_mots[r];
	return mot;

}

/*

int main ()
{
	int longueur;
	char** L=malloc(386264*sizeof(char*));
	printf("Rentrez une longueur de mot :\n");
	scanf("%d",&longueur);
	char* mot = mot_aleatoire(longueur,"meilleur.txt",L,386264);
	printf("le mot est : %s\n", mot);
	return 0;	
}

*/


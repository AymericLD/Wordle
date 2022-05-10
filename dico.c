
// Fonction générant le dictionnaire

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lecture(char* filename,char** L)
{

	FILE* f=fopen(filename,"rb");
	int length=239185;
	if (f==NULL)
	{
		printf("Impossible d'ouvrir le fichier");
	}
	L[0]=malloc(sizeof(char*));
    fscanf(f,"%s",L[0]); 
    for (int i=1;i<length;i++)
	{
        L[i]=malloc(sizeof(char*));
		fscanf(f,"%s",L[i]);
	}
	L[length]="\0";
	
    fclose(f);

}

char* mot_aleatoire(int l,char* filename)
{
	int length=239185;
	char* liste_mots[length];
	char** L=malloc((length+1)*sizeof(char*));
	if (L==NULL)
	{
		printf("L'allocation a échoué");
		return NULL;
	}
	lecture(filename,L);
	int j=0;
	for (int i=0; i<length; i++) 
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
	free(L);
	return mot;

}



int main ()
{
	int longueur;
	printf("Rentrez une longueur de mot :\n");
	scanf("%d",&longueur);
	char* mot = mot_aleatoire(longueur,"french.txt");
	printf("le mot est : %s\n", mot);
    return 0;
	
}
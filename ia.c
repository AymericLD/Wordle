#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "dico.h"


//TAILLE 5 UNIQUEMENT POUR L'INSTANT

//Les quelques programmes suivants (avant la ligne de slash) sont ceux qui permettront de trouver
// le mot le plus "entropique" 




struct information {

	double* data;
	char* mot_associe;

};

struct entropies { //ensemble des mots avec leurs informations respectives

	double entropie;
	char* mot;
	struct entropies* next;

};

//void push(struct information* mot, double information) {

	//if(mot->sp == TAILLE_MAX) printf("Erreur, pile pleine\n");
	//mot->data[mot->sp] = information;
	//sp++;

//}

//fonctions du wordle précédent

// Mémoire sur les lettres recontrées : structure de file

    struct file
    {
        int first;
        int cur_nb;
        int max_nb;
        int* data;
    };


    // Fonction pour ajouter un élément à la file
    
    void enqueue(struct file* file,int val)
    {
       if (file->cur_nb==file->max_nb)
       {
           return;
       }
       file->data[(file->first + file->cur_nb)%file->max_nb]=val;
       file->cur_nb++;
    }

    // Fonction pour retirer un élément de la file

    void take (struct file* file)
    {
        if (file->cur_nb==0)
        {
            return;
        }
        file->first=(file->first +1)%file->max_nb;
        file->cur_nb--;
    }


// Fonction qui recherche une valeur dans un tableau


bool search(int* data,int val,int length)
{
   for(int i=0;i<length;i++)
   {
       if(data[i]==val)
       {
           return true;
       }
   }
   return false;
}

// Fonction qui retourne le nombre d'occurences d'une lettre dans une chaîne de caractères

int occurence(char letter,char* word,int longueur)
{
    int k=0;
    for(int i=0;i<longueur;i++)
    {
      if(word[i]==letter)
      {
        k++;
      }
    }
  return k;
}


////////////////////////////////



char conversion(int n) {
	char c;
	if(n==0) {
		c = 'O';
	} if(n==1) {
		c='~';
	} else {
		c = 'X';
	}
	return c;
}


// Création d'une liste des combinaisons de *O~ sur 5 emplacements
void possibilites(char** possibles) {

	char** combi = malloc(sizeof(char**)*243); //combi est une liste de 3^5 charactères
	for(int i=0;i<=242;i++) {
		combi[i] = malloc(sizeof(char*));
	}
	
	for(int n=0;n<=242;n++) { //passage en écriture ternaire
		char cb[5];

		cb[0] = conversion(floor(n/(pow(3,4))));
		cb[1] = conversion(floor((n-cb[0]*pow(3,4))/(pow(3,3))));
		cb[2] = conversion(floor((n-cb[0]*pow(3,4)-cb[1]*pow(3,3))/pow(3,2)));
		cb[3] = conversion(floor((n-cb[0]*pow(3,4)-cb[1]*pow(3,3)-cb[2]*pow(3,2))/(3^1)));
		cb[4] = conversion(floor((n-cb[0]*pow(3,4)-cb[1]*pow(3,3)-cb[2]*pow(3,2)-cb[3]*pow(3,1))/1));

		
		combi[n] = cb; // le k-ème élément de combi contient une combinaison unique
	}
	possibles = combi;

}

int taille(char** L) {
	int j;
	while(L[j] != NULL) {
		j+=1;
	}
	return j;
}

int occ(char lettre_dico, char* mot_info) { //Nous donne le nombre de fois qu'un mot contient un caractère donné (lettre_dico)

	int compteur;
	for(int i=0;i<strlen(mot_info);i++) {
		if(mot_info[i] == lettre_dico) {
			compteur++;
		}
	}
	return compteur;

} //à remplacer

bool lettres_interdites(char* combi, char* mot_info, char* mot_dico) { //nous dit si un mot contient une lettre interdite

	int k;
	for(k=0;k<5;k++) {
		for(int j=0;j<5;j++) {
			if(combi[k] == 'X' && mot_info[j] == mot_dico[k] && occ(mot_dico[k],mot_info) == 1) { //nombre d'occurence !
				return true;
			}
		}
	} return false;

}

bool mauvaise_lettre(char* combi, char* info, char* mot_dico) {

	int k;
	for(k=0;k<5;k++) {
		if(combi[k] == 'O' && info[k] != mot_dico[k]) {
			return true;
		}
	} return false;

}

bool lettres_misplace(char* combi, char* mot_info, char* mot_dico) {

	int k;
	for(k=0;k<=4;k++) {
		if(combi[k] == '~') { //mot_dico ne devra donc pas contenir la lettre mot_info[k] à la position k+1
			if(mot_info[k] == mot_dico[k]) {
				return true;
			}
		}
	} return false;

}

//COMPLETER LE TEST POUR LE COMPTEUR AVEC NB D'OCCURENCES SI ASSEZ DE TEMPS

//ensemble mots devra tenir compte des résultats précédents
struct information* information_mot(char** ensemble_mots, char* mot) { //renvoie la structure d'information d'UN SEUL MOT dans le dictionnaire
	
	char** combinaisons = malloc(sizeof(char*)*243);
	for(int i=0;i<243;i++) {
		combinaisons[i] = malloc(sizeof(char*));
	}
   
    possibilites(combinaisons); //combinaisons contient tout les arrangements possibles de *~O
    struct information* inf = malloc(sizeof(struct information*));
    inf->mot_associe = mot;
    int size = taille(ensemble_mots);
    double* pos = malloc(sizeof(double)*243); // une correction
    
    
    for(int i=0;i<=242;i++) { //Pour un i fixe on va regarder l'info associée
    	
    	//pos [i] = j/size 
    	char* une_combi = combinaisons[i];
    	
    	int compteur;

    	for(int j=0;j<size;j++) { //LES ELEMENTS DU DICO SONT SUPPOSES DEJA DE LA BONNE TAILLE
    		char* mot_dico = ensemble_mots[j];

    		if(lettres_interdites(une_combi,mot,mot_dico) == false && lettres_misplace(une_combi,mot,mot_dico) == false && mauvaise_lettre(une_combi,mot,mot_dico) == false) { //rajouter éventuellement des tests
    			compteur++;
    		}
    	
    	}
    	if(compteur!=0) {
    		pos[i] = compteur/size;
    	} else {
    		pos[i] = 0;
    	}
    inf->data = pos;
    
    }
    return inf;
}

//penser à initialiser ensemble mots (recalculer l'ensemble des mots possibles à chaque tour)

double log2(double x) {
	double l;
	l = log10(x)/log10(2);
	return l;
}

double calcul_entropie(char** ensemble_mots, char* word) { //calcul de l'entropie d'un mot

	struct information* info;
	info = information_mot(ensemble_mots,word);
	double entropie;
	int i;
	for(i=0;i<=242;i++) {
		if(info->data[i] !=0) {
			entropie = entropie + info->data[i]*log2(1/(info->data[i]));
			i++;
		} else {
			entropie = entropie + 0;
			i++;
		}
	}
	return(entropie);
}

struct entropies* entropie_vide(int size) {

	struct entropies* vide = malloc(sizeof(struct entropies));
	int i = 0;
	while(i<=size) {
		struct entropies* ajout = malloc(sizeof(struct entropies));
		vide->next=ajout;
		vide = vide->next;
	}
	return vide;
}

void liste_information(char** ensemble_mots, struct entropies* liste_entropies) { //renvoie la liste des 
    
    int size = taille(ensemble_mots);
    struct entropies* liste_entr = entropie_vide(size);
    int i = 0;
    while(i<size) {
    	char* word;
    	word = ensemble_mots[i];
    	double entropie_valeur;
    	entropie_valeur = calcul_entropie(ensemble_mots,word);
    	liste_entropies->entropie = entropie_valeur;
    	liste_entropies->mot = word;
    	liste_entropies = liste_entropies->next;
    }
    liste_entropies = liste_entr;

}


double maximum(double* tableau) {

	double max;
	max = tableau[0];
	int i = 1;
	while(tableau[i] != 0) { //Un mot d'entropie nulle n'existe pas
		if(max < tableau[i]) {
			max = tableau[i];
			i++;
		} i++;
	}
	return max;
}

char* max_entropie(char** ensemble_mots) {

	struct entropies* liste_entrop = malloc(sizeof(struct entropies));
	liste_information(ensemble_mots,liste_entrop);
	double max;
	int size = taille(ensemble_mots);
	double* toutes_les_entropies = malloc(sizeof(double*)*size);
	int i = 0;
	while(liste_entrop->mot != NULL) {
		toutes_les_entropies[i] = liste_entrop->entropie;
		liste_entrop = liste_entrop->next;
	}

	max = maximum(toutes_les_entropies);
	char* bon_mot; //On suppose qu'à chaque entropie on associe un unique mot correspondant
	struct entropies* trouver_max = malloc(sizeof(struct entropies*));
	liste_information(ensemble_mots, trouver_max);
	while(trouver_max->entropie != max) {
		trouver_max = trouver_max->next;
	}
	bon_mot = trouver_max->mot;
	return bon_mot;

}

///////////////////////////////////////////////////////////////////////////////////

//fonction pas très optimisée :
char** nouvel_ensemble(char** ancien, char* resultat, char* ancien_max_entrop) { //on détermine le nouvel ensemble de mots possibles en fonction du résultat (en terme de 0*~)


	int size = taille(ancien);
	int nouv_taille = 0;
	for(int i = 0; i<size; i++) {
		char* mot = ancien[i];
		if(lettres_interdites(resultat,ancien_max_entrop,mot) == false && lettres_misplace(resultat,ancien_max_entrop,mot) == false) {
			nouv_taille ++;
		}
	
	}

	char** nouveau = malloc(nouv_taille*sizeof(char*));
    if (nouveau == NULL)
    {
      printf("Erreur d'allocation");  // INITIALISATION DE LA NOUVELLE LISTE DE MOTS
    }
    for(int j = 0; j<nouv_taille; j++) {
    	nouveau[j] = malloc(sizeof(char*));
    }
    int j = 0;
    for(int i = 0; i<size; i++) {
		char* mot = ancien[i];
		if(lettres_interdites(resultat,ancien_max_entrop,mot) == false && lettres_misplace(resultat,ancien_max_entrop,mot) == false) {
			nouveau[j] = mot;
			j++;
		}
	
	}
	return nouveau;
}

//Il reste à prendre le code du wordle précédent, et faire comme si ce que joue l'ia est l'entrée utilisateur. Il faudra recalculer l'ensemble des mots possibles

int main() {

	int longueur = 5;

	char* resultat = malloc(longueur*sizeof(char*)); //futur pb de type ?

	char perfect_word[longueur];

    for(int i=0;i<longueur;i++)
    {
      perfect_word[i]='O';
    }

   	
    char** L=malloc((835+1)*sizeof(char*));
    if (L==NULL)
    {
      printf("Erreur d'allocation");
      return -1;
    }


	char* mot_cherche = mot_aleatoire(longueur,"dico.txt",L, 835); //mot que l'IA doit trouver
	

	int size=386264; 
    char** dico = malloc(size*sizeof(char*));
    if (dico == NULL)
    {
      printf("Erreur d'allocation");
      return -1;
    }
    lecture("meilleur.txt",dico,size);
    int nb_essais = 5;
    int compteur = 1;
    while(compteur <= nb_essais) {

    	char* mot_maxim = max_entropie(dico);
    	printf("%s\n",mot_maxim);
    	for(int j=0;j<longueur;j++) 
       {
          // Utilisation d'une structure de file pour stocker les occurences d'une lettre

          struct file* Memoire=malloc(sizeof(struct file));
          int* memoire=malloc(longueur*sizeof(int));
          int first=0;
          Memoire->data=memoire;
          Memoire->first=first;
          Memoire->cur_nb=0;
          Memoire->max_nb=longueur;
          
      
          int k=0;
          for(int p=0;p<longueur;p++)  // Parcours du mot à trouver
          {
              if (mot_maxim[j]==mot_cherche[p])
              {
                enqueue(Memoire,p);
                k++;
              } 
          }
          if(k!=0)
          {
             if(search(Memoire->data,j,Memoire->cur_nb)) // On regarde si l'indice de la lettre considérée a été gardée en mémoire
             {
               resultat[j]='O';
               k=0;
             }
             else
             {
               /* Si la lettre considérée n'est pas bien placée et apparaît plus de fois dans le mot saisi par le joueur que dans le mot cherché, 
               alors nécessairement cette lettre n'est pas dans le mot */

               if(occurence(mot_maxim[j],mot_maxim,longueur)>occurence(mot_maxim[j],mot_cherche,longueur))
               {
                 resultat[j]='X';
               }
               else
               {
                 resultat[j]='~';
               }
             } 
          }
          else
          {
            resultat[j]='X';
          }  
        free(Memoire);
        free(memoire);              
        }
    printf("%s\n",resultat);

    if (strcmp(resultat,perfect_word)==0)
    {
      printf("Gagné !");
      return 0;
    }

    dico = nouvel_ensemble(dico,resultat,mot_maxim);

    compteur ++;

    }

  printf("Game Over!");
  free(resultat);
  free(dico);
  free(L);
  return 0;

}
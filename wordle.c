// Wordle 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dico.h"
#include "verify.h"



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



int main()
{
    // Mot d'accueil 

    printf("Bienvenue dans Wordle !\nLa légende du jeu est la suivante : une lettre bien placée sera signalée par 'O', une lettre mal placée par '~',\nune lettre qui n'est pas dans le mot sera signalée par 'X'.");

    // Définition de la longueur du mot à deviner

    int longueur;
    printf("\nChoisis la longueur du mot à deviner\n");
    scanf("%d",&longueur);


    // Définition du nombre de tentatives

    int nb_tentatives = 6;

    // Mot Parfait

    char perfect_word[longueur];

    for(int i=0;i<longueur;i++)
    {
      perfect_word[i]='O';
    }

    /* On utilise deux dictionnaires : le premier de 835 mots courants contient les mots à trouver, le deuxième de 239185 mots permet la vérification 
    de la validité du mot saisi par le joueur.
    */

   int size=27740; 
   char** dico=malloc(27740*sizeof(char*));
   lecture("liste_francais.txt",dico);
   char** L=malloc((length+1)*sizeof(char*));


    // Algorithme d'évaluation du mot

    char* resultat=malloc(longueur*sizeof(int));


    for(int i=0;i<nb_tentatives;i++)
    {
       char mot_joueur[256];
       printf("Entrez un mot de %d lettres\n",longueur);
       scanf("%s",mot_joueur);

       while (strlen(mot_joueur)!=longueur)
       {
         printf("La longueur du mot entré n'est pas correcte\n");
         printf("Entrez un mot de %d lettres\n",longueur);
         scanf("%s",mot_joueur);
       }

       // Vérifcation que le mot saisi est bien dans le dictionnaire

       while(!dichotomie(dico,size,0,mot_joueur))
       {
         printf("Le mot que tu as entré n'est pas dans le dictionnaire, saisis un autre mot.\n");
         printf("Entrez un mot de %d lettres\n",longueur);
         scanf("%s",mot_joueur);
       }


       // Choix aléatoire du mot dans le dictionnaire

       char* mot_cherche=mot_aleatoire(longueur,"dico.txt",L);

       
       // Parcours du mot donné donné par l'utilisateur

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
              if (mot_joueur[j]==mot_cherche[p])
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

               if(occurence(mot_joueur[j],mot_joueur,longueur)>occurence(mot_joueur[j],mot_cherche,longueur))
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
  }
  printf("Game Over, retente ta chance !");
  free(resultat);
  free(dico);
  free(L);
  return 0;

}


/* A ajouter :

-Affichage graphique plus joli
-Gérer les accents

*/





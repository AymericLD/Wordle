/* Fonction vérifiant que le mot est bien dans le dictionnaire 

Pour ce faire, on va effectuer une recherche dichotomique du mot dans le dictionnaire

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "dico.h"


/* Fonction effectuant la recherche dichotomique */



bool dichotomie(char** file,int size,int debut,char* word)
{
   if ((size-1)>=debut)
   {
      int m=floor((size-1+debut)/2);
      if (strcmp(file[m],word)==0)
      {
         return true;  
      }
      if(strcmp(file[m],word)>0)
      {
         size=m;
      }
      if (strcmp(file[m],word)<0)
      {
         debut=m+1;
      }
      return (dichotomie(file,size,debut,word));  
   }
   return false;
}


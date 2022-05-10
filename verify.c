/* Fonction vérifiant que le mot est bien dans le dictionnaire 

Pour ce faire, on va effectuer une recherche dichotomique du mot dans le dictionnaire

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* Fonction effectuant la recherche dichotomique */

bool dichotomie(char** file,unsigned int size,int debut,int fin_1,char* word)
{
   if (fin_1>=debut)
   {
      int m=floor(fin_1+debut/2);
      if (strcmp(file[m],word)==0)
      {
         printf("Mot trouvé !");
         return true;   
      }
      if(strcmp(file[m],word)>0)
      {
         fin_1=m-1;
      }
      if (strcmp(file[m],word)<0)
      {
         debut=m+1;
      }
      return (dichotomie(file,size,debut,fin_1,word));  
   }
   printf("Mot non trouvé");
   return false;
}



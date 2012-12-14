#include "declaration.h"
#include "analyseur.h"
#include "tablsymb.h"
#include "error.h"





      
int main(){
	system("clear");
	system("rm -f parametre variable fonction.inVar fonction.inParam variable.bin param.bin  fonction.bin");
	
	int PositionVar;
	printf("\n\n\n\t\t\t\t******************** COMPILATEUR VOICE PROGRAMMING ********************\n\n\n");
	token = lire_token();
	if (prog())  
	{

	  printf ("\t\t\t\t\t*********** %d erreurs semantique ********** \n\n",nombre_error());
	  afficher_liste_error();
	  printf("\n\t\t\t\t\tCompilation terminee:syntaxe  correcte \n\n\n");	
	}
	else 
	{
	  printf("\t\t\t\tCompilation terminee :syntaxe incorrecte\n");
	}
return 0;
}
	

	   
	  
	  
	
	
  

  
      
      
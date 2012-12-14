#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tablsymb.h"
#define NBS 100
static int PositionVariable = 0;
static int level = 0;

//TABLEAU QUI CONTIENDRA LES INFO SUR LES VARIABLES + FONCTIONS +PARAMETRE 
static Symbole TableSymbole[NBS];

// AJOUTER UNE VARIABLE DANS LA TABLE DES SYMBOLES
void  ajouterVar(Symbole newvar)
{
  FILE *fonction = fopen("fonction.inVar","a+");
  FILE *variable = fopen("variable","a+");
  TableSymbole[PositionVariable].typeSymb=VARIABLE;
  TableSymbole[PositionVariable].ligneSymb=newvar.ligneSymb;
  strcpy(TableSymbole[PositionVariable].nomSymb,newvar.nomSymb);
  TableSymbole[PositionVariable].u.var.nbredeclVar = newvar.u.var.nbredeclVar; 
  TableSymbole[PositionVariable].u.var.boolInit = newvar.u.var.boolInit; 
  TableSymbole[PositionVariable].u.var.varInit = newvar.u.var.varInit;
  TableSymbole[PositionVariable].u.var.typeVar = newvar.u.var.typeVar;
  fprintf(fonction,"Var:%s\n",newvar.nomSymb);
  fprintf(variable,"%s  %d\n",newvar.nomSymb,level-1);
  fclose(fonction);
  fclose(variable);
  
  PositionVariable ++;
}


int ajouterVar2(symbolVar *newvar)
{
  FILE *fichier = fopen ("variable.bin","ab");
  if(fichier == NULL) return -1;
  else 
    fwrite(newvar,sizeof(symbolVar),1,fichier);
  fclose(fichier);
  return 1;
}

int ajouterFonc2(symbolFonc *newvar)
{
  FILE *fichier = fopen ("fonction.bin","ab");
  if(fichier == NULL) return -1;
  else 
    fwrite(newvar,sizeof(symbolFonc),1,fichier);
  fclose(fichier);
  return 1;
}

int ajouterParam2(symbolParam *newvar)
{
  FILE *fichier = fopen ("param.bin","ab");
  if(fichier == NULL) return -1;
  else 
    fwrite(newvar,sizeof(symbolParam),1,fichier);
  fclose(fichier);
  return 1;
}

int recherchervar(char *nomrech,int level)
{
  FILE *fichier = fopen ("variable.bin","a+");
  int trouve = 0;
  symbolVar *rech = (symbolVar*)malloc(sizeof(symbolVar));
   while (fread(rech,sizeof(symbolVar),1,fichier) != 0)
   {
     if(strcmp(nomrech,rech->nomvar)==0 && level == rech->level)
     {
       trouve = 1;
       break;
     }
   }
   return trouve;
  fclose(fichier);
}
int rechercherparam(char *nomrech,int level)
{
  FILE *fichier = fopen ("param.bin","a+");
  int trouve = 0;
  symbolParam *rech = (symbolParam*)malloc(sizeof(symbolParam));
   while (fread(rech,sizeof(symbolParam),1,fichier) != 0)
   {
     if(strcmp(nomrech,rech->nomparam)==0 && level == rech->level)
     {
       trouve = 1;
       break;
     }
   }
   return trouve;
  fclose(fichier);
}
//-----
//-------------------------------------------------------------- 
//ajout d'une nouvelle fonction dans la table des symboles
//--------------------------------------------------------------

void  ajouterFonc(Symbole newfonc)
{
  FILE *fonctionVar = fopen("fonction.inVar","a+");
  FILE *fonctionParam = fopen("fonction.inParam","a+");
  TableSymbole[PositionVariable].typeSymb=FONCTION;
  TableSymbole[PositionVariable].ligneSymb=newfonc.ligneSymb;
  strcpy(TableSymbole[PositionVariable].nomSymb,newfonc.nomSymb);
  TableSymbole[PositionVariable].u.fonc.typeRetourFonc = newfonc.u.fonc.typeRetourFonc; 
  PositionVariable ++;
  fprintf(fonctionVar,"fonction%d:%s  level %d\n",level,newfonc.nomSymb,level);
  fprintf(fonctionParam,"fonction%d:%s  level %d\n",level,newfonc.nomSymb,level);
  level++;
  fclose(fonctionVar);
  fclose(fonctionParam);
}

//-------------------------------------------------------------- 
//-------------------------------------------------------------- 
void  ajouterParam(Symbole newparam)
{
  FILE *fonction = fopen("fonction.inParam","a+");
  FILE *parametre= fopen("parametre","a+");
  TableSymbole[PositionVariable].typeSymb=PARAMETRE;
  TableSymbole[PositionVariable].ligneSymb=newparam.ligneSymb;
  strcpy(TableSymbole[PositionVariable].nomSymb,newparam.nomSymb);
  TableSymbole[PositionVariable].u.param.nbredeclparam = newparam.u.param.nbredeclparam; // nbre de declaration 
  TableSymbole[PositionVariable].u.param.typeVar =newparam.u.param.typeVar;
  fprintf(fonction,"Param:%s\n",newparam.nomSymb);
  fprintf(parametre,"%s %d\n",newparam.nomSymb,level-1);
  PositionVariable ++;
  fclose(fonction);
  fclose(parametre);
}

int checkVar(char *nom,int *level_t)
{
  FILE *variable = fopen("variable","a+");
  char nom_rech[40];
  int level_rech;
  if (variable == NULL) return -1;
  else 
    while(feof(variable)!= 0)
    {
      fscanf(variable,"%s  %d ",nom_rech,&level_rech);
      if(strcmp (nom,nom_rech)== 0 && (*level_t) == level_rech)
      {
	return 1;
      }
    }
    return -1;
  fclose(variable);
}

//PREDICAT  DE RECHERCHE
boolean dansTableSymbole(char * nom, int* PositionVar)
{
  int i= 0;
  
  while( (i < NBS) && strcmp(TableSymbole[i].nomSymb,nom) != 0) i++;
   
    if(i == NBS) return false;
    else
    {
      (*PositionVar) = i;
      return true;
    }
}
boolean Verifier_main(char *nom)
{
  int i= 0;
  while((i < NBS) && strcmp(TableSymbole[i].nomSymb,nom) != 0) i++;
  if(i == NBS) return false;
  else return true;
}

//LA VALEUR D'INITIALISATION  
double ValeurInitVar(int positionVar)
{
  return TableSymbole[positionVar].u.var.varInit;
}

//LA VALEUR D'INITIALISATION D'UN BOOLEAN
boolean valeurBoolVar(int positionVar)
{
  return  TableSymbole[positionVar].u.var.boolInit;
}

//TYPE D'UNE VARIABLE DANS LA TABLE DES SYMBOLES
data_type typeVariableVar(int positionVar)
{
  return TableSymbole[positionVar].u.var.typeVar;
}



//TYPE D'UN PARAMETRE DANS LA TABLE DES SYMBOLES
data_type typeVariableParam(int positionVar)
{
  return TableSymbole[positionVar].u.param.typeVar;
}
//-------------------------------------------------------------- 

//RETOURNE LE NOM DE LA VARIABLE
char *nom (int positionVar)
{
  return TableSymbole[positionVar].nomSymb;
}
//--------------------------------------------------------------
/* reverse: reverse string s in place */
//-------------------------------------------------------------- 

void reverse(char s[]){
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
//-------------------------------------------------------------- 

//-------------------------------------------------------------- 
char * itoa(int n){
  int i = 0;
  char s[100];
  char * result;
  do { /* generate digits in reverse order */
    s[i++] = n % 10 + '0'; /* get next digit */
  } while ((n /= 10) > 0); /* delete it */
  s[i] = '\0';
  reverse(s);
  result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}
//-------------------------------------------------------------- 
//-------------------------------------------------------------- 
void afficherTableSymbole(){
			int i = 0;
           while (i< NBS)
   {
		printf("  nom:%s \n",TableSymbole[i].nomSymb);
		i++;
	}

}

void afficherVar()
{
  FILE *fichier = fopen("variable.bin","r+");
  symbolVar *temp= (symbolVar*)malloc(sizeof(symbolVar));
  while(fread(temp,sizeof(symbolVar),1,fichier)!=0)
    {
       printf("Nom : %s  level:%d\n",temp->nomvar,temp->level);
    }
    fclose(fichier);
}

/////////////////////////////////////////////////////////////////


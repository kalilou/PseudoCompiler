#ifndef TABLSYMB_H
#define TABLSYMB_H
#include "type.h"
#define Malloc(type) (type *)malloc(sizeof(type))


 

#include "type.h"


//extern void incrementerNbreDeclVar(int positionVar);
//extern void incrementerNbreDeclFonc(int positionfonc);
//extern void incrementerNbreDeclParam(int positionparm);
extern void  ajouterVar(Symbole newvar);
extern void  ajouterFonc(Symbole newfonc);
extern void  ajouterParam(Symbole newparam);
extern double ValeurInitVar(int positionVar);
extern boolean valeurBoolVar(int positionVar);
extern data_type typeVariable(int positionVar);
extern char *nom (int positionVar);
extern void reverse(char s[]);
extern boolean dansTableSymbole(char * nom, int* positionVar);
extern data_type typeVariableParam(int positionVar);
extern char * itoa(int n);
extern void afficherTableSymbole();
extern boolean Verifier_main();
extern int checkVar(char *nom,int *level_t);
extern int ajouterVar2(symbolVar *newvar);
extern int ajouterFonc2(symbolFonc *newvar);
extern int ajouterparam2(symbolParam *newvar);
extern int recherchervar(char *nomrech,int level);
extern int rechercherparam(char *nomrech,int level);
extern void afficherVar();
extern data_type rechTypefonction(int *level_t);

typedef struct FONC
{
  data_type  typeRetour;
}type_fonc;
  



#endif
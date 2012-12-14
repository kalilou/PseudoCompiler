#ifndef ERROR_H
#define ERROR_H
#include "type.h"
//LES DIFFERENTS TYPE D'ERREUR 

typedef enum
{
  dejaDeclarerVar,	
  dejaDeclarerFonc,
  dejaDeclarerParam,
  nonDeclarerVar,
  incompatibleAssignTypeVar,
  incompatibleCompTypeVar,
  incompatibleReturnFonc,
  incompatibleOperationTypeVar,
  initVarError
}errorType;

//LES INFO SUR LES ERREURS
typedef struct 
{
  char nomError[20];
  int ligneError;
  errorType erreur;
}error;

//ERREUR D'INSTRUCTION
extern void create_error_inst(errorType e, int ligne,char *name);

//ERREUR DECLARATION
extern void create_error_decl(errorType e, int ligne,char *name);

// AFFICHER L'ERREUR
extern void affiche_errors();

 //FONCTION AFFICHER LA LISTE DES ERREURS 
extern void afficher_liste_error();

//NOMBRE D'ERREUR
extern int nbre_errors();

// FONCTION QUI LIT LA LISTE DES ERREURS DE COMPILATION
extern void lireErreur() ;



#endif
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define NMAXERR  200
//DECLARATION DES VAR GLOBALE 
static int NBERRDECL = 0;    //COMPTEUR POUR LES DECLARATIONS
static int NBERRINST = 0;	//COMPTEUR POUR LES INSTRUCTIONS

static error *ERDECL[NMAXERR];// LISTE CONTIENT L'ENSEMBLE DES ERREURS DE DECLARATION  
static error *ERINST[NMAXERR];// LISTE CONTIENT L'ENSEMBLE DES ERREURS D'INSTRUCTION


//FONCTION CREER LES ERREURS 
error  *create_error(errorType er,int ligne,char *nom)
{
  error *e = (error*)malloc(sizeof(error));
  strcpy(e->nomError,nom);
  e->ligneError = ligne;
  e->erreur = er;
  return e;
}

//FONCTION AFFICHER LES ERREURS
void afficher_error(errorType er,int ligne ,char *nom)
{
  FILE *erreurFile;
  erreurFile=fopen("erreur.vc","a+");
  printf("ligne  %d:  %s: ",ligne,nom);
  fprintf(erreurFile,"ligne  %d:  %s: ",ligne,nom);
  switch (er)
  {
    case dejaDeclarerVar: printf("Variable deja declare\n");fprintf(erreurFile,"Variable deja declare\n");break;
    case dejaDeclarerFonc:printf("Conflit de fonction\n");fprintf(erreurFile,"Conflit de fonction\n");break;
    case dejaDeclarerParam:printf("argument deja declarer\n");fprintf(erreurFile,"argument deja declarer\n");break;
    case nonDeclarerVar:printf("Variable non declare\n");fprintf(erreurFile,"Variable non declare\n");break;
    case incompatibleAssignTypeVar:printf("incompatible avec la valeur d'affectation\n");fprintf(erreurFile,"incompatible avec la valeur d'affectation\n");break;
    case incompatibleCompTypeVar:printf("incompatible avec la valeur de comparaison\n");fprintf(erreurFile,"incompatible avec la valeur de comparaison\n");break;
    case incompatibleReturnFonc:printf("incompatible avec la valeur de return\n");fprintf(erreurFile,"incompatible avec la valeur de return\n");break;
    case incompatibleOperationTypeVar:printf("incomptible avec l'operation\n");fprintf(erreurFile,"incomptible avec l'operation\n");break;
    case initVarError:printf("Variable mal initialise\n");fprintf(erreurFile,"Variable mal initialise\n");break;
  }
  fclose(erreurFile);
}
 
 //FONCTION AFFICHER LA LISTE DES ERREURS 
void afficher_liste_error(){
  int idecl = 0;
  int iinst = 0;
  FILE *erreurFile;
  erreurFile=fopen("erreur.vc","a");
  if(Verifier_main("main") == true)
  {
  while (idecl < NBERRDECL) { // AFFICHER LES ERREURS_DECLARATIONS
   afficher_error(ERDECL[idecl]->erreur, ERDECL[idecl]->ligneError, ERDECL[idecl]->nomError);
    idecl++;
  }

 while (iinst < NBERRINST) { // AFFICHER LES ERREURS_INSTRUCTIONS  
   afficher_error(ERINST[iinst]->erreur, ERINST[iinst]->ligneError, ERINST[iinst]->nomError);
    iinst++;  
							}
 fprintf(erreurFile,"%d erreurs de compilation au totals.",(iinst+idecl));
 fclose(erreurFile);
  }
  else 
  {
    printf("Erreur la fonction main n'existe pas \n");
  }
// lireErreur();
}
  
  // FONCTION QUI LIT LA LISTE DES ERREURS DE COMPILATION
  void lireErreur() {
    system("./lecteurVoiceC erreur.vc");
  }
  
  // FONCTION RETURN LE NOMBRE GLOBALE DES ERREURS :
  int nombre_error(){
  return  NBERRDECL + NBERRINST;
}

// FONCTION PERMET DE STOCKER  LES ERREUR D'INSTRUCTION DANS LE TB ERINST[NBRERRORINST]
void creer_erreur_instruction(errorType er,int ligne ,char *nom){
    ERINST[NBERRINST++]= create_error(er, ligne, nom);   
}

// FONCTION PERMET DE STOCKER  LES ERREUR DE DECLARATION DANS LE TB ERDECL[NBRERRORDECL]
void creer_erreur_declaration(errorType er,int ligne ,char *nom){
   ERDECL[NBERRDECL++]= create_error(er, ligne, nom); 
}
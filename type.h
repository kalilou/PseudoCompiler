#ifndef TYPE_H
#define TYPE_H
#include "analyseur.h"
#include "ast.h"
#define NULL ((void *)0)
#define Malloc(type) (type *)malloc(sizeof(type))
/*...................................*//*...................................*//*...................................*/
typedef struct Symbole symbole;

//ENUMERATION DES TYPES D'INSTRUCTION 
typedef enum {PrintfIdf, PrintfText, AssignArith, IfInst, IfElseInst, WhileInst, DoInst } type_inst;
//ENUMERATION DES TYPES DE SYMBOLES A STOCKES
typedef enum { FONCTION, PARAMETRE, VARIABLE } type_symb; 
//ENUMERATION DES TYPES DIFFERENTS QUE PEUX PRENDRE LES SYMBOLES
typedef enum {INT_TYPE, CHAR_TYPE, FLOAT_TYPE ,BOOL_TYPE,DOUBLE_TYPE} data_type;



/*...................................*//*...................................*//*...................................*/
//STRUCTURE  VARIABLE
typedef struct
{
  data_type typeVar;// le type de la variable
  int nbredeclVar ;//nombre de declaration
  double varInit;//la valeur d'initialisation de la variable
  boolean boolInit;// boolean initialisation; 
  int level;
  char nomvar[30];
 
}symbolVar;
/*...................................*/
//STRUCTURE FONCTION
typedef struct 
{
  int ariteFonc;
  char nomfonc[30];
  data_type  typeRetourFonc;	   //type de retour de la fonction
  int defined;	
  int level;
}symbolFonc;
/*...................................*/
//STRUCTURE PARAMETRE
typedef struct 
{
  char nomparam[30];
  data_type typeVar;// le type de la variable
  int nbredeclparam ;//nombre de declaration
  int level;
}symbolParam  ; 
/*...................................*/
typedef struct 
{
  char nomSymb[20];
  type_symb  typeSymb;
  int ligneSymb;
 
  union
  {
    symbolFonc	fonc;
    symbolVar 	var;
    symbolParam	param;
  }u;
}Symbole;


/*...................................*/    
// typename d'un data 
  
typedef struct
{
  data_type typename;
}constypeValue;

/*...................................*/
// constance value 
typedef struct {
  data_type typename;    // CONST_IB.typename
  double valinit;   // CONST_IB.valinit
} valueType;
/*...................................*//*...................................*//*...................................*/


struct INST;//STOCKAGE DES INSTRUCTIONS

struct LIST_INST;//STOCKAGE DES LISTES D'INSTRUCTION

//STRUCTURE POUR LES INSTRUCTIONS
typedef struct INST {
  type_inst typeinst;
  union  {
    struct  {
      int positionVar; // INDICE DE L'IDF, DANS LA TABLE DES SYMBOLES
    } printnode;
    struct  {
      int positionVar; // INDICE DE L'IDF, OU IL FAUT AFFECTER, DANS LA TABLE DES SYMBOLES
      AST right; 
    } assignnode;
    // IF ... THEN 
    struct  {
      int positionVar; // indice de l'idf � comparer, dans la table des symbole
      //double right; // la valeur de comparaison
      AST right; // l'expression � comparer
      struct LIST_INST * thenlinst; // then list of instructions
      struct LIST_INST * elselinst; // else list of instructions
    } ifnode;
    struct {
      int positionVar;
      AST right;
      struct LIST_INST *whileliste;
    }whilenode;
    struct {
      int positionVar;
      AST right;
      struct LIST_INST *dowhileliste;
    }dowhilenode;
  } node;
} instvalueType;

//STRUCTURE POUR LA LISTE DES INSTRUCTIONS
typedef struct LIST_INST {
  struct INST first;
  struct LIST_INST * next;
} listinstvalueType;


typedef union {
  Symbole varattribute;           	     //SYMB.varattribute
  valueType constattribute;        // CONST_IB.constattribute
  data_type typename;                        // TYPE.typename
  instvalueType instattribute;          // INST.instattribute
  listinstvalueType listinstattribute;  // LIST_INST.listinstattribute
  //AST expattribute;                     // EXP.expattribute
} svalueType;



#define YYSTYPE svalueType

extern instvalueType* creer_instruction_print(int positionVar);
extern instvalueType* creer_instruction_affectation(int positionVar, AST * past);
extern instvalueType* creer_instruction_if(int positionVar, AST * past, listinstvalueType * plistthen, listinstvalueType * plistelse);
extern instvalueType* creer_instruction_while(int positionVar,AST *past,listinstvalueType *plist);
extern instvalueType* creer_instruction_dowhile(int positionVar,AST *past,listinstvalueType *plist);

extern void inserer_inst_en_queue(listinstvalueType * listinstattribute, instvalueType instattribute);

extern void inserer_inst_en_tete(listinstvalueType ** listinstattribute, instvalueType instattribute);

extern void afficher_inst(instvalueType instattribute);

extern void afficher_list_inst(listinstvalueType * plistinstattribute);











#endif
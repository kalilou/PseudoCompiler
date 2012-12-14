#ifndef AST_H
#define AST_H
#include "type.h"

typedef enum {NB=0,_IDF = 1, BOOLEAN = 2, OP=3} Type_Exp ;


typedef enum {Plus, Moins, Mult, Div} Type_Op;


typedef struct  Exp *AST;

typedef union {
  double nombre ;
  char *idf;
  boolean bool;
  struct {
    Type_Op top;
    AST expression_gauche ;
    AST expression_droite ;
  } op;
}NoeudArbre;


typedef struct Exp {
  Type_Exp typexp ; // NB ou IDF ou OP
  //data_type    typename; // Int ou Bool ou Double ou Float ou Char
  NoeudArbre noeud ;
}expvalueType;

double value(char *idf);


AST arbre_gauche(AST a);

AST arbre_droit(AST a);

Type_Op top(AST a);

//data_type     type(AST a);

boolean est_feuille(AST a);


AST creer_feuille_booleen(boolean b);

//AST creer_feuille_nombre(double n, data_type type);

//AST creer_feuille_idf(char *idf,data_type type);

//AST creer_noeud_operation(char op, AST arbre_g, AST arbre_d, data_type type);


void afficher_infixe_arbre (AST ast);

void afficher_postfixe_arbre (AST ast);


double evaluer (AST ast);
#endif
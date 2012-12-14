#include "ast.h"
#include "tablesymb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int positionVar;
double value(char *idf){
  boolean ilyest= dansTableSymbole(idf, &positionVar);
  if (debug){
    if (ilyest != true) printf("bug(%s) n'est pas dans la TS\n",idf);
    else{
      printf("RANG == %d", positionVar);
      printf("( %s ) == %s", idf, name(positionVar));
      printf(" est dans la TS de valeur = %f\n", valinit(positionVar));
      printf(" 0  dans la TS de valeur = %f\n", valinit(0));
      printf(" 1  dans la TS de valeur = %f\n", valinit(1));
      printf(" 2  dans la TS de valeur = %f\n", valinit(2));

     // afficherTS();
    }
  }
  return valinit(positionVar);
}

AST arbre_gauche(AST a){
  return a->noeud.op.expression_gauche;
}


AST arbre_droit(AST a){
  return a->noeud.op.expression_droite;
}


Type_Op top(AST a){
  return a->noeud.op.top;
}

data_type  type(AST a){
return a->typename;
}


boolean est_feuille(AST a){
  return (a->typexp != OP) ;
}


AST creer_feuille_booleen(boolean b){
  if (debug) printf("creer_feuille_boolean()\n");
  AST result = (AST) malloc (sizeof(struct Exp));
  result->typexp=BOOLEAN;
  result->noeud.bool = b;
  result->typename = Bool;

  if (debug) printf("out of creer_feuille_boolean()\n");
  return result;
}

AST creer_feuille_nombre(double n, data_type type){
  if (debug) printf("creer_feuille_nombre()\n");
  AST result = (AST) malloc (sizeof(struct Exp));
  result->typexp=NB;
  result->noeud.nombre = n;
  result->typename = type;

  if (debug) printf("out creer_feuille_nombre()\n");

  return result;
}

AST creer_feuille_idf(char *idf, data_type type){
  if (debug) printf("creer_feuille_idf()\n");

  AST result = (AST) malloc (sizeof(struct Exp));
  result->typexp=_IDF;
  result->typename = type; // Bool ou Int
  result->noeud.idf = (char*) malloc (sizeof(char)*(strlen(idf)+1));
  strcpy(result->noeud.idf, idf);

  if (debug) printf("out of creer_feuille_idf()\n");

  return result;
}

AST creer_noeud_operation(char op, AST arbre_g, AST arbre_d, data_type type){
  if (debug) printf("creer_noeud_operation()\n");

  AST result= (AST) malloc (sizeof(struct Exp));
  result->typexp=OP;
  result->typename = type;
  result->noeud.op.top = ((op=='+')?Plus:((op=='-')?Moins:((op=='*')?Mult:Div)));
  result->noeud.op.expression_gauche = arbre_g;
  result->noeud.op.expression_droite = arbre_d;

  if (debug) printf("out of creer_noeud_operation()\n");

  return result;
}

void afficher_infixe_arbre (AST ast){
  // if (est_feuille(ast)){
  switch(ast->typexp) {
  case BOOLEAN : printf(" %s",(ast->noeud.bool==true)?"true":"false"); break;
  case NB : printf(" %lf",ast->noeud.nombre); break;
  case _IDF :  printf(" %s",ast->noeud.idf); break;
  case OP :
    afficher_infixe_arbre(arbre_gauche(ast));
    switch(ast->noeud.op.top){
    case Plus : printf(" + "); break;
    case Moins : printf(" - "); break;
    case Mult : printf(" * "); break;
    case Div : printf(" / "); break;
    }
    afficher_infixe_arbre(arbre_droit(ast));
    break;
  }
}

void afficher_postfixe_arbre (AST ast){
  // if (est_feuille(ast)){
  switch(ast->typeexp) {
  case BOOLEAN : printf(" %s",(ast->noeud.bool==true)?"true":"false"); break;
  case NB : printf(" %lf",ast->noeud.nombre); break;
  case _IDF :  printf(" %s",ast->noeud.idf); break;
  case OP :
    afficher_postfixe_arbre(arbre_gauche(ast));
    afficher_postfixe_arbre(arbre_droit(ast));
    switch(ast->noeud.op.top){
    case Plus : printf(" + "); break;
    case Moins : printf(" - "); break;
    case Mult : printf(" * "); break;
    case Div : printf(" / "); break;
    }
    break;
  }
  
  
  
  double evaluer (AST ast){
  double valg, vald;
  //if (est_feuille(ast)){
  switch(ast->typexp) {
  case NB : return ast->noeud.nombre; break;
  case _IDF : if (debug) printf("idf == %s de valeur %lf", ast->noeud.idf, value(ast->noeud.idf));
    return value(ast->noeud.idf); break;
  case OP :
    valg = evaluer(arbre_gauche(ast));
    vald = evaluer(arbre_droit(ast));
    switch(ast->noeud.op.top){
    case Plus : if (debug) printf("%lf + %lf == %lf\n",valg, vald, valg + vald);return valg + vald; break;
    case Moins : if (debug) printf("%lf - %lf == %lf\n",valg, vald, valg - vald);return valg - vald; break;
    case Mult : if (debug) printf("%lf * %lf == %lf\n",valg, vald, valg * vald);return valg * vald; break;
    case Div : if (debug) printf("%lf / %lf == %lf\n",valg, vald, valg / vald);return valg / vald; break;
    }
    break;
  }
}
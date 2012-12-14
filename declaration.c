#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include"analyseur.h"
#include "declaration.h"
#include "type.h"
#include "error.h"
#include "tablsymb.h"
#include "uthash.h"

static int level = -1;

//////////////////////////////////////////////  LA GRAMMAIRE /////////////////////////////////////////////////////

/*

PROG: LISTE_PREPROC LISTE_FONCT 
LISTE_PREPROC : PREPROC LISTE_PREPROCAUX
LISTE_PREPROCAUX : LISTE_PREPROC | EPSILONE
PREPROC : DIEZ PREPROCAUX  
PREPROCAUX : INCLUDE SIGGA IDF POINT IDF SIGDR | DEFINE IDF CONST
LISTE_FONCT : FONCT LISTE_FONTCAUX
LISTE_FONCTAUX : LISTE_FONCT | EPSILONE
FONC : ENTETE ACCO CORPS ACCF
ENTETE: TYPE IDF POPEN SUITE_PARAM PCLOSE
SUITE_PARAM : VOID | LISTE_PARAM
LISTE_PARAM : PARAM LISTE_PARAMAUX
PARAM : TYPE PARAMAUX
PARAMAUX : IDF PARAMAUX1 | FOIS PARAMAUX2
PARAMAUX1 : CROG CROD | EPSILONE
PARAMAUX2 : FOIS IDF | IDF 
CORPS : LISTE_DECL LISTE_INST 
LISTE_DECL: DECL LISTE_DECLAUX
LISTE_DECLAUX : LISTE_DECL  | EPSILONE
DECL:TYPE IDF  DECLAUX
DECLAUX: EQ CONST PVIRG | PVIRG | CROG ENTIER CROD PVIRG
LISTE_INST : INST LISTE_INSTAUX
LISTE_INSTAUX : LISTE_INST | EPSILONE
INST :IDF EQ ADDSUB PVIRG | IF POPEN LISTE_COND PCLOSE ACCO LISTE_INST ACCF IFAUX 
      | WHILE POPEN LISTE_COND PCLOSE ACCO LISTE_INST ACCF
      | DO ACCO LISTE_INST ACCF WHILE POPEN LISTE_COND PCLOSE PVIRG
      | PRINTF PRINTFAUX
PRINTFAUX : STRING | LIST_IDF
LISTE_IDF : IDF LISTE_IDFAUX 
LISTE_IDFAUX : , LISTE_IDF | EPSILONE



IFAUX : ELSE ACCO LISTE_INST ACCF | EPSILONE
LISTE_COND : COND LISTE_CONDAUX
LISTE_CONDAUX : LOGIQ LISTE_COND | EPSILONE
COND :IDF CONDAUX
CONDAUX : SIGDR CONST | SIGGA CONST | SIGDREQ CONST | SIGGAEQ | EQEQ CONST | NOTEQ CONST
ADDSUB : MULT ADDSUBAUX
ADDSUBAUX: PLUS MULT ADDSUBAUX | MOINS MULT ADDSUBAUX | EPSILONE
MULT : AUX MULTAUX
MULTAUX : FOIS AUX MULTAUX | DIV AUX MULTAUX | EPSILONE 
AUX : IDF | ENTIER | REELLLE | POPEN ADDSUB PCLOSE

CONST: ENTIER | REELLE | TRUE | FALSE 
TYPE: INT | FLOAT | DOUBLE | CHAR   
LOGIQ : OU | ET      
      
      
*/ 

Symbole symbol;
type_fonc typeFonc;
constypeValue typeattribute;// type de la variable
valueType typattribute;//type de la constante d'initialisation
int positionVar;

//////////////////////////////////////////////  LE PROGRAMME /////////////////////////////////////////////////////

//PROG: LISTE_PREPROC LISTE_FONCT 

boolean prog()
{
  if(liste_preproc())
  {
     token = lire_token();
      if(liste_fonct()) 
      {
	token = lire_token();
        if (token == END_OF_FILE) return true;
        else return false;
      }
      else return false;
    }
    else return false;
}


//////////////////////////////////////////////  CONSTANTE  /////////////////////////////////////////////////////

// CONST: ENTIER | REELLE | TRUE | FALSE 
boolean Const() {
	if 	(token == ENTIER || token == REELLE )  
	  {
	  typattribute.typename = FLOAT_TYPE;
	  return true;
	}
	else if (token == TRUE  ) 
	  {
	  typattribute.typename = BOOL_TYPE;
	  return true;
	}
	else if (token == FALSE ) 
	  {
	  typattribute.typename = BOOL_TYPE;
	  return true;
	}
	else return false;
}

//////////////////////////////////////////////  TYPE  /////////////////////////////////////////////////////

//TYPE: INT | FLOAT | DOUBLE | CHAR | BOOL
boolean type()
{
	if 	(token == DOUBLE ) 
	{
	  typeattribute.typename = FLOAT_TYPE;
	  return true;
	}
	else if (token == FLOAT  )  
	  {
	  typeattribute.typename = FLOAT_TYPE;
	  return true;
	}
	else if (token == INT    ) 
	  {
	  typeattribute.typename = FLOAT_TYPE;
	  return true;
	}
	else if (token == CHAR   )
	  {
	  typeattribute.typename = CHAR_TYPE;
	  return true;
	}
	else if (token == BOOL)
	{
	  typeattribute.typename = BOOL_TYPE;
	  return true;
	}
	else return false;
}

//////////////////////////////////////////////  LISTE DES DECLARATION /////////////////////////////////////////////////////

//DECL:TYPE IDF DECLAUX 
boolean decl()
{
  if(type())
  {   
     token = lire_token();
     if(token == IDF)
     {
       token = lire_token();
       if(declaux())
       {
	 //RECHERCHER POUR VERIFIER L'EXISTANCE DE LA VARIABLE
	if(recherchervar(symbol.nomSymb,level) == 1 && dansTableSymbole(symbol.nomSymb,&positionVar)== true)
	{
	   creer_erreur_declaration(dejaDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
	}
	
	 else 
	 {
	   Symbole newvar;
	   strcpy(newvar.nomSymb,symbol.nomSymb);
	   newvar.ligneSymb = symbol.ligneSymb;
	   newvar.u.var.nbredeclVar = 1;
	   newvar.u.var.typeVar = typeattribute.typename;
	   newvar.u.var.varInit = typattribute.valinit;
	   newvar.u.var.boolInit = symbol.u.var.boolInit;
	   newvar.u.var.level = level;
	   ajouterVar(newvar);  
	   symbolVar *newvar2 = (symbolVar*)malloc(sizeof(symbolVar));
	   strcpy(newvar2->nomvar,symbol.nomSymb);
	   newvar2->level = level;
	   ajouterVar2(newvar2);
	   
	 } 
	 //VARIABLE MAL INITIALISEE
	 if(symbol.u.var.boolInit == true)
	 {
	    if(typeattribute.typename != typattribute.typename )
	      creer_erreur_declaration(initVarError,symbol.ligneSymb,symbol.nomSymb);
	 }
	 return true;
       }
       else return false;
     }
     else return false;
  }
  else return false;
}


//DECLAUX: EQ CONST PVIRG | PVIRG | CROG ENTIER CROD PVIRG
boolean declaux()
{
  if (token == PVIRG) 
  {
    symbol.u.var.boolInit = false;
    return true;
  }
  else if(token == EQ)  
  {
    token = lire_token();
    if(Const())
    {
      token = lire_token();
      if(token == PVIRG) 
      {
	symbol.u.var.boolInit = true;
	return true;
      }
      else return false;
    }
    else return false;
  } 
  else if(token == CROG)
  {
      token = lire_token();
      if(token == ENTIER)
      {
	  token = lire_token();
	  if(token == CROD)
	  {
	      token = lire_token();
	      if(token == PVIRG) 
	      {
		symbol.u.var.boolInit = false;
		return true;
	      }
	      else return false;
	  }
	  else return false;
      }
      else return false;
  }
		
 else return false;
}


//LISTE_DECL: DECL LISTE_DECLAUX
boolean liste_decl()
{
  if(decl())
  {
    token = lire_token();
    return liste_declaux();
  }
    else return false;
}

//LISTE_DECLAUX : LISTE_DECL  | EPSILONE
boolean liste_declaux()
{
  
 if(liste_decl()) return true;
  notread_token = true;
  return true;
}
      
      


//////////////////////////////////////////////  LISTE DES PREPROCESSEURS /////////////////////////////////////////////////////


//LISTE_PREPROC : PREPROC LISTE_PREPROCAUX
boolean liste_preproc()
{
  if(preproc())
  {
    token = (typetoken)yylex();
    return liste_preprocaux();
  }
  else return false;
}

//LISTE_PREPROCAUX : LISTE_PREPROC | EPSILONE
boolean liste_preprocaux()
{
  if(liste_preproc()) return true;
  notread_token = true;
  return true;
}
   
 //PREPROC : DIEZ PREPROCAUX   
boolean preproc()
{
  if (token == DIEZ) 
  {
   token = (typetoken)yylex();
   return preprocaux();
  }
  else return false;
}

//PREPROCAUX : INCLUDE SIGGA IDF POINT IDF SIGDR | DEFINE IDF CONST
boolean preprocaux()
{
    if(token == INCLUDE)
    {	
      token = (typetoken)yylex();
      if(token == SIGGA)
      {
	token = lire_token();
	if(token == IDF)
	{
	  token = lire_token();
	  if(token == POINT)
	  {
	    token = lire_token();
	    if(token == IDF)
	    {
	      token = lire_token();
	      if(token == SIGDR) return true;
	      else return false;
	    }
	      else return false;
	  }
	    else return false;
	}
	  else return false;
      }
	else return false;
   }
   
  else if (token == DEFINE )
  {
    token = lire_token();
    if(token == IDF)
    {
      token = lire_token();
      if(Const()) return true;
      else return false;
    }
    else return false;
  }
  else return false;
} 
      

      
///////////////////////////////////////////////  LISTE DES FONCTIONS /////////////////////////////////////////////////////

//LISTE_FONCT : FONCT LISTE_FONTCAUX
boolean liste_fonct()
{
  if(fonct())
  {
     token = lire_token();
     return liste_fonctaux();
  }
  else  return false;
}

//LISTE_FONCTAUX : LISTE_FONCT | EPSILONE
boolean liste_fonctaux()
{
  if(liste_fonct()) return true;
  notread_token =true;
  return true;
}

//FONC : ENTETE ACCO CORPS ACCF
boolean fonct()
{
  if(entete())
   {
        token = lire_token();
	if(token == ACCO)
	{
	   token = lire_token();
	   if(corps())
	   {
	      token = lire_token();
	      if(token == ACCF) return true; 
	      else  return true;
	   }
           else return false;
	}   
        else return false;
   }
   else return false;
}
    
//ENTETE: TYPE IDF POPEN SUITE_PARAM PCLOSE
boolean entete()
{
 if(type())
 {
   token = (typetoken)yylex();
   if(token == IDF)
   {
      token = (typetoken)yylex();
      if(token == POPEN)
      {
	if(dansTableSymbole(symbol.nomSymb,&positionVar) == true)
	{
	  creer_erreur_declaration(dejaDeclarerFonc,symbol.ligneSymb,symbol.nomSymb);
	}
	else 
	{
	  Symbole newfonc;
	  strcpy(newfonc.nomSymb,symbol.nomSymb);
	  newfonc.ligneSymb = symbol.ligneSymb;
	  newfonc.u.fonc.defined = 1;
	  newfonc.u.fonc.typeRetourFonc = typeattribute.typename;
	  typeFonc.typeRetour = typeattribute.typename; //typeFonc.typeRetour est une structure qui memorise le type de la fonction
	  ajouterFonc(newfonc);
	  level ++;//le niveau de la fonction
	}
	 token = lire_token();
	 if(suite_param())
	 {
	     token = lire_token();
	     if(token ==  PCLOSE) return true;
	     else return false;
	 }
	 else return false;
      }
      else return false;
   }
   else return false;
 }
 else return false;
}

//SUITE_PARAM : VOID | LISTE_PARAM
boolean suite_param()
{
  if	   (token == VOID) 	return true;
  else if  (liste_param())      return true;
  else return false;
}
		  	      
//LISTE_PARAM : PARAM LISTE_PARAMAUX
boolean liste_param()
{
  if(param())
  {
     token = lire_token();
     return liste_paramaux();
  }
  else return false;
}
//LISTE_PARAMAUX : VIRG LISTE_PARAM | EPSILONE
boolean liste_paramaux()
{
  if(token == VIRG)
  {
  token = lire_token();
  if(liste_param()) return true;
  else return false;
  }
  notread_token = true;
  return true;
}
//PARAM : TYPE PARAMAUX
boolean param()
{
  if(type())
  {
     token = lire_token();
     if(paramaux()) return true;
     else return false;
  }
  else return false;
}

//PARAMAUX : IDF PARAMAUX1 | FOIS PARAMAUX2
boolean paramaux()
{
  if(token == IDF)
  {
    
     token = lire_token();
     if(paramaux1()) 
     {
       if (rechercherparam(symbol.nomSymb,level)==1 && dansTableSymbole(symbol.nomSymb,&positionVar) == true)
       {
        creer_erreur_declaration(dejaDeclarerParam,symbol.ligneSymb,symbol.nomSymb);
       }
       //ajouter parametre dans la table des symboles
	 else 
	 {
	   Symbole newparam;
	   strcpy(newparam.nomSymb,symbol.nomSymb);
	   newparam.ligneSymb = symbol.ligneSymb;
	   newparam.u.param.nbredeclparam = 1;
	   newparam.u.param.typeVar = typattribute.typename;
	   ajouterParam(newparam);  
	   symbolParam *newparam2 = (symbolParam*)malloc(sizeof(symbolParam));
	   strcpy(newparam2->nomparam,symbol.nomSymb);
	   newparam2->level = level;
	   ajouterParam2(newparam2);
	 }
       return true;
     }
     else return false;
  }
  else if (token == FOIS)
  {
     token = lire_token();
     if(paramaux2()) return true;
     else return false;
  }
  else return false;
}

//PARAMAUX1 : CROG CROD | EPSILONE 
boolean paramaux1()
{
  if(token == CROG)
  {
     token = lire_token();
     if(token == CROD) return true;
     else return false;
  }
  notread_token = true;
  return true;
}
//PARAMAUX2 : FOIS IDF | IDF 
boolean paramaux2()
{
  if(token == IDF) 
  {
   if (rechercherparam(symbol.nomSymb,level)==1 && dansTableSymbole(symbol.nomSymb,&positionVar) == true)
       {
      creer_erreur_declaration(dejaDeclarerParam,symbol.ligneSymb,symbol.nomSymb);
       }
       //AJOUTER PARAMETRE DANS LA TABLE DES SYMBOLEs
	 else 
	 {
	   Symbole newparam;
	   strcpy(newparam.nomSymb,symbol.nomSymb);
	   newparam.ligneSymb = symbol.ligneSymb;
	   newparam.u.param.nbredeclparam = 1;
	   newparam.u.param.typeVar = typeattribute.typename;
	   ajouterParam(newparam);  
	   symbolParam *newparam2 = (symbolParam*)malloc(sizeof(symbolParam));
	   strcpy(newparam2->nomparam,symbol.nomSymb);
	   newparam2->level = level;
	   ajouterParam2(newparam2);
	 }
    return true;
  }
  else if(token == FOIS)
  {
     token = lire_token();
     if(token == IDF) 
     {
        if (rechercherparam(symbol.nomSymb,level)==1 && dansTableSymbole(symbol.nomSymb,&positionVar) == true)
       {
      creer_erreur_declaration(dejaDeclarerParam,symbol.ligneSymb,symbol.nomSymb);
       }
       //AJOUTER PARAMETRE DANS LA TABLE DES SYMBOLES
	 else 
	 {
	   Symbole newparam;
	   strcpy(newparam.nomSymb,symbol.nomSymb);
	   newparam.ligneSymb = symbol.ligneSymb;
	   newparam.u.param.nbredeclparam = 1;
	   newparam.u.param.typeVar = typeattribute.typename;
	   ajouterParam(newparam);  
	   symbolParam *newparam2 = (symbolParam*)malloc(sizeof(symbolParam));
	   strcpy(newparam2->nomparam,symbol.nomSymb);
	   newparam2->level = level;
	   ajouterParam2(newparam2);  
	 }
       return true;
     }
     else return true;
  }
  else return true;
}
       
    
/////////////////////////////////////////////////////// LE CORPS DE LA FONCTION ////////////////////////////////////////

//CORPS : LISTE_DECL LISTE_INST RETOUR 
boolean corps()
{
    if (liste_decl())
    {
        token = lire_token();
	if(liste_inst())
	{
	   token = lire_token();
	   if(retour())  
	   {
	     token = lire_token();
	     if(token == PVIRG) return true;
	     else return false;
	   }
	   else return false;
	}
	else return false;
    }
    else  return false;
}

//RETOUR : RETOUR RETOURAUX
boolean retour()
{
  if(token == RETURN)
  {
     token = lire_token();
     if(retouraux()) return true;
     else return false;
  }
  else return false;
}

//RETOURAUX: IDF | ENTIER | REELLE
boolean retouraux()
{
  if(token == IDF) 
  {
    if(recherchervar(symbol.nomSymb,level) != 1 && rechercherparam(symbol.nomSymb,level) != 1 )
        creer_erreur_instruction(nonDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
    else 
    {
      if(typeFonc.typeRetour != typeattribute.typename)
	creer_erreur_instruction(incompatibleReturnFonc,symbol.ligneSymb,symbol.nomSymb);
    }
	
	
    return true;
  }
  else if(token == ENTIER) return true;
  else if(token == REELLE) return true;
  else return false;
}
       
/////////////////////////////////////////////////////// LISTE INSTRUCTION ////////////////////////////////////////

//LISTE_INST : INST LISTE_INSTAUX
boolean liste_inst()
{
  if(inst())
  {
     token = lire_token();
     return liste_instaux();
  }
  else return false;
}
//LISTE_INSTAUX : LISTE_INST | EPSILONE
boolean liste_instaux()
{
  if(liste_inst()) return true;
  notread_token = true;
  return true;
}
//INST :IDF EQ ADDSUB PVIRG | IF POPEN LISTE_COND PCLOSE ACCO LISTE_INST ACCF IFAUX 
    //  | WHILE POPEN LISTE_COND PCLOSE ACCO LISTE_INST ACCF
    //  | DO ACCO LISTE_INST ACCF WHILE POPEN LISTE_COND PCLOSE PVIRG
    //  | PRINTF PRINTFAUX


boolean inst()
{
  if(token == IDF)
  {
    if(dansTableSymbole(symbol.nomSymb,&positionVar) == false)
      creer_erreur_instruction(nonDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
    else
    {
      if(typeVariableVar(positionVar) != FLOAT_TYPE && typeVariableVar(positionVar) != INT_TYPE && typeVariableVar(positionVar) != DOUBLE_TYPE)
	 creer_erreur_instruction(incompatibleAssignTypeVar,symbol.ligneSymb,symbol.nomSymb);
    }
    token = lire_token();
    if(token == EQ)
    {
      token = lire_token();
      if(addsub())
      {
	token = lire_token();
	if(token == PVIRG) 	
	  return true;
	else return false;
      }
      else return false;
    }
    else return false;
  }
  
  else if(token == IF)
  {
     token = lire_token();
     if(token == POPEN)
     {
        token = lire_token();
	if(liste_cond())
	{
	  token = lire_token();
	  if(token == PCLOSE)
	  {
	     token = lire_token();
	     if(token == ACCO)
	     {
	        token = lire_token();
		if(liste_inst())
		{
		  token = lire_token();
		  if(token == ACCF)
		  {
		     token = lire_token();
		     if(ifaux()) return true;
		     else return false;
		  }
		  else return false;
		}
		else return false;
	     }
	     else return false;
	  }
	  else return false;
	}
	else return false;
     }
     else return false;
  }
  
  else if(token == WHILE)
  {
     token = lire_token();
     if(token == POPEN)
     {
        token = lire_token();
	if(liste_cond())
	{
	   token = lire_token();
	   if(token == PCLOSE)
	   {
	      token = lire_token();
	      if(token == ACCO)
	      {
		 token = lire_token();
		 if(liste_inst())
		 {
		    token = lire_token();
		    if(token == ACCF) return true;
		    else return false;
		 }
		 else return false;
	      }
	      else return false;
	   }
	   else return false;
	}
	else return false;
     }
     else return false;
  }
  
  else if(token == DO)
  {
     token = lire_token();
     if(token == ACCO)
     {
        token = lire_token();
	if(liste_inst())
	{
	   token = lire_token();
	   if(token == ACCF)
	   {
	      token = lire_token();
	      if(token == WHILE)
	      { 
		 token = lire_token();
		 if(token == POPEN)
		 {
		    token = lire_token();
		    if(liste_cond())
		    {
		       token = lire_token();
		       if(token == PCLOSE) 
		       {
			  token = lire_token();
			  if(token == PVIRG) return true;
			  else return false;
		       }
		        else return false;
		    }
		     else return false;
		 }
		  else return false;
	      }
	       else return false;
	   }
	    else return false;
	}
	else return false;
     }
      else return false;
  } 
  else if(token == PRINTF)
  {
     token = lire_token();
     if(printfaux()) return true;
     else return false;
  }
    

  else return false;
}


//PRINTFAUX : STRING | LISTE_IDF 
boolean printfaux()
{
  if (token == STRING) return true;
  else if(liste_idf()) return true;
  else return false;
}



    
//IFAUX : ELSE ACCO LISTE_INST ACCF | EPSILONE
boolean ifaux()
{
  if(token == ELSE)
  {
    token = lire_token();
    if(token == ACCO)
    {
      token = lire_token();
      if(liste_inst())
      {
	token = lire_token();
	if(token == ACCF) return true;
	else return false;
      }
      else return false;
    }
    else return false;
  }
  notread_token = true;
  return true;
}
/////////////////////////////////////////////////////// LISTE_IDF ////////////////////////////////////////  

//LISTE_IDF : IDF LISTE_IDFAUX
boolean liste_idf()
{
  if(token == IDF)
  {
    if(dansTableSymbole(symbol.nomSymb,&positionVar) == false)
      creer_erreur_instruction(nonDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
        token = lire_token();
	if(liste_idfaux()) return true;
	else return false;
  }
  else return false;
}

//LISTE_IDFAUX : VIRG LISTE_IDF | EPSILONE
boolean liste_idfaux()
{
  if(token == VIRG)
  {
        token = lire_token();
	if(liste_idf()) return true;
	else return false;
  }
  notread_token = true;
  return true;
}
	  
	  
    

/////////////////////////////////////////////////////// LISTE CONDITION ////////////////////////////////////////  

//LISTE_COND : COND LISTE_CONDAUX
boolean liste_cond()
{
  if(cond())
  {
    token = lire_token();
    return liste_condaux();
  }
  else return false;
}
    
//LISTE_CONDAUX : LOGIQ LISTE_COND | EPSILONE
boolean liste_condaux()
{
  if(logiq())
  {
    token = lire_token();
    if(liste_cond()) return true;
    else return false;
  }
  notread_token = true;
  return true;
}


//LOGIQ : OU | ET
boolean logiq()
{
  if(token == OU) return true;
  else if(token == ET) return true;
  else return false;
}
    
//COND :IDF CONDAUX
boolean cond()
{
  if(token == IDF)
  {
    if(dansTableSymbole(symbol.nomSymb,&positionVar) == false)
    creer_erreur_instruction(nonDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
     token = lire_token();
     return  condaux();
  }
  else return false;
}

//CONDAUX : SIGDR CONST | SIGGA CONST | SIGDREQ CONST | SIGGAEQ | EQEQ CONST | NOTEQ CONST
boolean condaux()
{
  if(token == SIGDR)
  {
     token = lire_token();
     if(Const())
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
	 creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else if(token == SIGGA)
  {
     token = lire_token();
     if(Const()) 
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
            creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else if(token == SIGDREQ)
  {
     token = lire_token();
     if(Const()) 
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
	 creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else if(token == SIGGAEQ)
  {
     token = lire_token();
     if(Const())
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
	 creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else if(token == EQEQ)
  {
     token = lire_token();
     if(Const())
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
	 creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else if(token == NOTEQ)
  {
     token = lire_token();
     if(Const())
     {
       if(typeVariableVar(positionVar) != typeattribute.typename)
	 creer_erreur_instruction(incompatibleCompTypeVar,symbol.ligneSymb,symbol.nomSymb);
       return true;
     }
     else return false;
  }
  else return false;
}
     
    
    



/////////////////////////////////////////////////////// ADDSUB ////////////////////////////////////////  

// ADDSUB : MULT ADDSUBAUX
boolean addsub()
{
  if(mult())
  {
    token = lire_token();
    if(addsubaux()) return true;
    else return false;
  }
  else return false;
}

//ADDSUBAUX: PLUS MULT ADDSUBAUX | MOINS MULT ADDSUBAUX | EPSILONE
boolean addsubaux()
{
  if(token == PLUS)
  {
    token = lire_token();
    if(mult())
    {
      token = lire_token();
      if(addsubaux()) return true;
      else return false;
    }
    else return false;
  }
  else if(token == MOINS)
  {
    token = lire_token();
    if(mult())
    {
      token = lire_token();
      if(addsubaux()) return true;
      else return false;
    }
    else return false;
  }
  notread_token = true;
  return true;
}

//MULT : AUX MULTAUX
boolean mult()
{
  if(aux())
  {
    token = lire_token(); 
    if(multaux()) return true;
    else return false;
  }
  else return false;
}

//MULTAUX : FOIS AUX MULTAUX | DIV AUX MULTAUX | EPSILONE 
boolean multaux()
{
  if(token == FOIS)
  {
    token = lire_token();
    if(aux())
    {
      token = lire_token();
      if(multaux()) return true;
      else return false;
    }
    else return false;
  }
  
  else if(token == DIV)
  {
    token = lire_token();
    if(aux())
    {
      token = lire_token();
      if(multaux()) return true;
      else return false;
    }
    else return false;
  } 
  notread_token = true;
  return true;
}
    
      

    
    


//AUX : IDF | ENTIER | REELLLE | POPEN ADDSUB PCLOSE
boolean aux()
{
  if(token == IDF)
  {
    if(dansTableSymbole(symbol.nomSymb,&positionVar) == false)
      creer_erreur_instruction(nonDeclarerVar,symbol.ligneSymb,symbol.nomSymb);
    else
    {
      if(typeVariableVar(positionVar) != FLOAT_TYPE)
      creer_erreur_instruction(incompatibleOperationTypeVar,symbol.ligneSymb,symbol.nomSymb);
    }
    return true;
  }
  else if(token == ENTIER) return true;
  else if(token == REELLE) return true;
  else if(token == TRUE)   return true;
  else if(token == FALSE)  return true;
  else if(token == POPEN)
  {
    token = lire_token();
    if(addsub())
    {
      token = lire_token();
      if(token == PCLOSE) return true;
      else return false;
    }
    else return false;
  }
	
    
  else return false;
}
	
      
  
//FONCTION LIRE TOKEN 
typetoken lire_token()
{
  if(notread_token) notread_token = false;
  else
  token = (typetoken) yylex();
  
  return token;
}
    
void set_idf_attributes(char *name, int linenumber)
{
	strcpy(symbol.nomSymb, name);
	symbol.ligneSymb = linenumber;
}

void set_number_attributes(int value)
{
	typattribute.valinit = value;
}
  
    

      
	
      
    
    
    
    
    
    
   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
       

		    
    

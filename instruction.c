  // ================================ LA PARTIE POUR LA LISTE D'INSTRUCTION=======================================//
  

//liste_instruction====>inst instaux
boolean liste_instruction()
{
  if(inst())
  {
    token = (typetoken) yylex();
    if(instaux())
      return true;
      else return false;
  }
  else return false;
}

//==========================================================================================================================>

//instaux====>inst instaux | espsilone
boolean instaux()
{
  if(inst())
  {
    token = (typetoken) yylex();
    if(instaux()) return true;
    return false ;
  }
  
    notread = true;
    return true ;
}
//===========================================================================================================================>

//inst====> idf=constante; | if(idf==constante) then list_instruction ifaux
boolean inst()
{
  if(token == IDF)
  {
    token = (typetoken) yylex();
      if(token == EQUAL)
      {
	 token = (typetoken) yylex();
	 if(constante())
	 {
	 token = (typetoken) yylex();
	 if(token == PVIRG) return true;
	 else return false;
         }
         else return false;
      }
      else return false;
  }
  else if(token == IF)
  {
     token = (typetoken) yylex();
     if(token == PG)
     {
       token = (typetoken) yylex();
       if(token== IDF)
       {
        token = (typetoken) yylex();
	if(token == D_EQUAL)
	{
	   token = (typetoken) yylex();
	   if(constante())
	   {
	      token = (typetoken) yylex();
	      if(token == PD)
	      {
		 token = (typetoken) yylex();
		 if(token == THEN)
		 {
		    token = (typetoken) yylex();
		    if(liste_instruction())
		    {
		      if(notread) notread = false ;
                      else token = (typetoken) yylex();
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
     else return false;
  }
  
  else return false;
}
//===============================================================================================================>
//ifaux ====> endif | else instruction endif

boolean ifaux()
{
  if(token == ENDIF) return true;
  else if(token == ELSE)
  {
    token = (typetoken) yylex();
    if(liste_instruction())
    {
      if(notread) notread = false ;
      else token = (typetoken) yylex();
      if(token == ENDIF) return true;
      else return false;
    }
    else return false;
  }
  else return false;
}
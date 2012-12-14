%{
#include "analyseur.h"
%}
%option noyywrap

%%
"#"			{if (debug) printf ("#");		 return DIEZ;}
"||"			{if (debug) printf ("OU");		 return OU;}
"&&"			{if (debug) printf ("ET");		 return ET;}
"printf"		{if (debug) printf ("PRINTF");		 return PRINTF;}
"\""			{if (debug) printf ("GUILL");		 return GUILL;}
"corps"			{if (debug) printf ("CORPS\n");          return CORPS;}
"include"		{if (debug) printf ("INCLUDE"); 	 return INCLUDE;}
"define" 		{if (debug) printf ("DEFINE"); 		 return DEFINE;}
";" 			{if (debug) printf (";\n");  		 return PVIRG;}
"return"		{if (debug) printf ("RETURN ");		 return RETURN;}
"," 			{if (debug) printf (","); 		 return VIRG;}
"do"			{if (debug) printf ("DO\n");             return DO;}
"while"			{if (debug) printf ("WHILE\n");          return WHILE;}
"int" 			{if (debug) printf ("INT "); 		 return INT;}
"bool" 			{if (debug) printf ("BOOL ");    	 return BOOL;}
"double" 		{if (debug) printf ("DOUBLE "); 	 return DOUBLE;}
"float" 		{if (debug) printf ("FLOAT ");  	 return FLOAT;}
"true" 			{if (debug) printf ("TRUE ");  	 	 return TRUE;}
"char" 		        {if (debug) printf ("CHAR "); 		 return CHAR;}
"void" 		        {if (debug) printf ("VOID "); 		 return VOID;}
"false" 		{if (debug) printf ("FALSE ");  	 return FALSE;}
"if"			{if (debug) printf ("IF ");  		 return IF;}
"else"			{if (debug) printf ("ELSE\n");  	 return ELSE;}
"("			{if (debug) printf ("(");  		 return POPEN;}
")"			{if (debug) printf (")");  		 return PCLOSE;}
"["			{if (debug) printf ("["); 		 return CROG;}
"]"			{if (debug) printf ("]");  		 return CROD;}
"{"			{if (debug) printf ("{\n"); 		 return ACCO;}
"}"			{if (debug) printf ("}\n"); 		 return ACCF;}
[a-zA-Z_][a-zA-Z0-9_]* 	{if (debug) printf ("IDF(%s)",yytext); 	set_idf_attributes(yytext, yylineno); return IDF;}
[(]["][^\n]*["][)][;]	{if (debug) printf ("STRING(%s)\n",yytext);return STRING;}
[0-9]+			{if (debug) printf ("ENTIER(%s)",yytext); set_number_attributes(atoi(yytext)); return ENTIER;}
[0-9]+"."[0-9]+		{if (debug) printf ("REELLE(%s)",yytext); set_number_attributes(atoi(yytext)); return REELLE;} 
"=="			{if (debug) printf ("==");  		 return EQEQ;}
"!="			{if (debug) printf ("NOTEQ");  		 return NOTEQ;}
">="			{if (debug) printf ("SIGDREQ");          return SIGDREQ;}
"<="			{if (debug) printf ("SIGGAEQ");  	 return SIGGAEQ;}
">"			{if (debug) printf (">");  		 return SIGDR;}
"<"			{if (debug) printf ("<");  		 return SIGGA;}
"="			{if (debug) printf ("=");  		 return EQ;}
"+"			{if (debug) printf ("+");   		 return PLUS;}
"-"			{if (debug) printf ("-");   		 return MOINS;}
"*"			{if (debug) printf ("*");   		 return FOIS;}
"/"			{if (debug) printf ("/"); 		 return DIV;}
"."			{if (debug) printf (".");   		 return POINT;}
<<EOF>>			{if (debug) printf ("FIN");		 return END_OF_FILE;}
[ \t\n]		/* caractère vide */
%%

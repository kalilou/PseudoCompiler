flex --yylineno analyseur.l
gcc analyseur.c lex.yy.c declaration.c error.c tablsymb.c  -o a.out

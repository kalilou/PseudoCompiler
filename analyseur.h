#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include <stdio.h>
#include <stdlib.h>
#define debug false
#define Malloc(type) (type *)malloc(sizeof(type))


typedef enum {false=0, true=1} boolean;

typedef enum {
ENTIER= 1000,
IDF = 1001,
INT = 1002,
BOOL = 1003,
TRUE = 1004,
FALSE = 1005,
PVIRG = 1006,
SIGGA = 1007,
POINT = 1010,
IF = 1009,
EQ = 1010,
SIGDR = 1011,
ELSE = 1012,
DIEZ = 1013,
POPEN = 1014,
PCLOSE = 1015,
EQEQ = 1016,
PLUS = 1017,
MOINS = 1018,
FOIS = 1019,
DIV = 1020,
INCLUDE = 1021,
CHAR = 1022,
H = 1023,
DOUBLE = 1024,
FLOAT = 1025,
DEFINE = 1026,
CROD = 1027,
CROG = 1028,
REELLE = 1029,
CORPS = 1030,
RETURN  = 1031,
VIRG = 1032,
ACCO = 1033,
ACCF = 1034,
VOID = 1035,
END_OF_FILE = 1036,
ET = 1037,
OU = 1038,
SIGGAEQ = 1039,
SIGDREQ = 1040,
NOTEQ = 1041,
WHILE = 1042,
DO = 1043,
PRINTF = 1044,
GUILL = 1045,
STRING = 1046

} typetoken;
typetoken token;


#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "instance.h"
#include "parseur.h"




int stringToInt(char * s)
{
    return strtol(s,NULL,10);
}


void sautLigne(FILE * fp)
{
    char * s = (char *) malloc(sizeof(char)* 100);
    fgets(s,100,fp);
    free(s);
}

int main(int argc, char *argv[])
{
// data/MKP-Instances/_mknapcb1_res.txt
parseur(argv[1]);
}

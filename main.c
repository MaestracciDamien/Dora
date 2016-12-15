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
    char buf[1024];
    getcwd(buf,1024);
    printf("SALOPE %s",buf);
/*int i;

for (i=0; i<argc; i++)
{
    printf("Param %d: %s\n",i, argv[i]);
}
*/

printf("chemin fichier %s", argv[1]);
// data/MKP-Instances/_mknapcb1_res.txt
parseur(argv[1]);
}

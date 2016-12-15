#include <stdio.h>
void parseur(char* chemin)
{
    FILE * fp;

    fp = fopen( chemin, "rt" );
    if (fp == NULL)
        exit(-1);

    char * s = (char *) malloc (sizeof(char)* 100);
    fgets (s, 100, fp );
    sautLigne( fp );
    sautLigne( fp );
    sautLigne( fp );
    free(s);
    creerInstance(fp);
}

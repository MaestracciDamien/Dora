#include "parseur.h"
void parseur(char* chemin)
{
    FILE * fp;

    fp = fopen( chemin, "rt" );
    if (fp == NULL)
        exit(-1);

    char * s = (char *) malloc (sizeof(char)* 100);
    char * split;
    int nbInstances;
    int i =0;
    fgets (s, 100, fp );
    sautLigne( fp );

    split = strtok(s, " ");
    nbInstances = stringToInt(split);
    free(s);
    while (i < nbInstances)
    {
        sautLigne( fp );
        sautLigne( fp );
        creerInstance(fp);
        i++;
    }

}

#include "sortie.h"

FILE * openSortie(char * chemin)
{
    FILE * fp = fopen (chemin,"w+");
    if (fp == NULL)
    {
        exit(-1);
    }
    return fp;
}
void fermerSortie(FILE * fp)
{
    fclose(fp);
}


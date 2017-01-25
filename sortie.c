#include "sortie.h"

void openSortie(char * chemin)
{
    FILE *fp = fopen (chemin,"w+");
    if (fp == NULL)
    {
        exit(-1);
    }
}
void fermerSortie()
{
    fclose(fp);
}


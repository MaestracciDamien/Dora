#include "sortie.h"

<<<<<<< HEAD
FILE * openSortie(char * chemin)
{
    FILE * fp = fopen (chemin,"w+");
=======
void openSortie(char * chemin)
{
    FILE *fp = fopen (chemin,"w+");
>>>>>>> 6dcbf3d8ad46a2f8e18bb0a8343d484c3689dc3b
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


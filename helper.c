#include "helper.h"


// retourne un entier a partir d'une chaine de caracteres
int stringToInt(char * s)
{
    return strtol(s,NULL,10);
}

// saute le pointeur d'une ligne dans un fichier
void sautLigne(FILE * fp)
{
    char * s = (char *) malloc(sizeof(char)* 100);
    fgets(s,100,fp);
    free(s);
}

#include "helper.h"


// retourne un entier a partir d'une chaine de caracteres
int stringToInt(char * s)
{
    int retour = atoi(s);
    return retour;
}

// saute le pointeur d'une ligne dans un fichier fp
void sautLigne(FILE * fp)
{
    char * s = (char *) malloc(sizeof(char)* 100);
    fgets(s,100,fp);
    free(s);
}

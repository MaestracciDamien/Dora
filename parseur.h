#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heuristiques.h"
#include "metaheuristiques.h"
typedef struct
{
    FILE * fp;
    int nbInstances;
    int pInstance;
}parseur;
parseur * initParseur(char* chemin);
instance * nextInstance();


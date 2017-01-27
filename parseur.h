#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "instance.h"
typedef struct
{
    FILE * fp;
    int nbInstances;
    int pInstance;
}parseur;
parseur * initParseur(char* chemin);
instance * nextInstance();


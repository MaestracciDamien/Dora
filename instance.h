#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef INSTANCE
#define INSTANCE
typedef struct
{
    int nbObjet;
    int nbDim;
    int * valeurObj;
    int ** poidObj;
    int * capaciteSac;
}instance;
#endif
instance * creerInstance(FILE *fp);
void instToString(instance* inst);

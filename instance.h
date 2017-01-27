#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
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
instance * initInstance(FILE *fp);
void printInst(instance* inst);

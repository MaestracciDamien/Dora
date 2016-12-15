#include <stdio.h>
typedef struct
{
    int nbObjet;
    int nbDim;
    int * valeurObj;
    int ** poidObj;
    int * capaciteSac;
}instance;

instance * creerInstance(FILE *fp);
void instToString(instance* inst);

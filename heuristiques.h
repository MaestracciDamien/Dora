# include "codage.h"
#include "helper.h"
#ifndef FUNCTION
#define FUNCTION
typedef int * (*functionSort)(instance * inst);
#endif


int * sortRandom(instance * inst);
int * sortValue(instance *inst);
int * sortRatioValueSum(instance *inst);
int * sortRatioValueDimCrit(instance *inst);
int * sortValuePoids(instance *inst);
solution * heuristique(instance * inst, functionSort fun, int typeCodage);
int isItemFitting(int * item, int * roomBag, int nbDim);
void addItemToBag(int * item, int * roomBag, int nbDim);


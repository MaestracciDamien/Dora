# include "codage.h"


typedef int * (*functionSort)(instance * inst);
int * sortRandom(instance * inst);
int * sortValue(instance *inst);
int * sortRatioValueSum(instance *inst);
int * sortRatioValueDimCrit(instance *inst);
solution * heuristique(instance * inst, functionSort fun, int typeCodage);
int isItemFitting(int * item, int * roomBag, int nbDim);
void addItemToBag(int * item, int * roomBag, int nbDim);


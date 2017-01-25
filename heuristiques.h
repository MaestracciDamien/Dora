# include "codage.h"


typedef int * (*functionSort)(instance * inst);
void sortRandom(instance * inst);
solution * heuristique(instance * inst, functionSort fun, int typeCodage);
int isItemFitting(int * item, int * roomBag, int nbDim);
void addItemToBag(int * item, int * roomBag, int nbDim);


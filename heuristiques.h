# include "instance.h"
# include "codage.h"


typedef int * (*functionSort)(instance * inst);
void sortRandom(ins);
solution * heuristique(instance * inst, functionSort fun);
int isItemFitting(int * item, int * roomBag, int nbDim);
void addItemToBag(int * item, int * roomBag, int nbDim);


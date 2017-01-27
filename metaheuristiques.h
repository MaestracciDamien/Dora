#include "heuristiques.h"
# include "codage.h"

solution * localSearch(instance * inst,functionSort fun, int typeCodage);
solution * tabooSearch(int nbIter, int tabooSize, int asp, instance * inst,functionSort fun, int typeCodage);
solution * geneticAlgo(int sizePopu, int nbIterMax, int pMut, instance * inst);



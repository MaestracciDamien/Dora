#include "heuristiques.h"
# include "codage.h"
#include "helper.h"
#ifndef MOVE
#define MOVE
typedef struct{
int a;
int b;
}mouvement;
#endif // MOVE
solution * localSearch(instance * inst,functionSort fun, int typeCodage);
solution * tabooSearch(int nbIter, int tabooSize, int asp, instance * inst,functionSort fun, int typeCodage);
solution * geneticAlgo(int sizePopu, int nbIterMax, int pMut, instance * inst);
int isInTable(int nombre, int * tab, int nb);
void reparation(solution * sol);
solution ** croisementEnfants(solution * parent1, solution * parent2);



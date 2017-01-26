#include <stdio.h>
#include "instance.h"
#ifndef SOLUTION
#define SOLUTION
typedef struct
{
    int typeCodage;
    instance * inst;
    int * codageDirect;
    int * codageIndirect;
    FILE * fileSolution;
}solution;
#endif

void initSolution(solution * sol,instance * inst, int type);
void decodeur(solution * sol);
int evalSolution(solution * sol);
int isSolutionPossible(solution * sol);
void printSolution(solution * sol);
void solution2File(solution * sol);


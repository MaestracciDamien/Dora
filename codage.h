#include <stdio.h>
#include "instance.h"

typedef struct
{
    int typeCodage;
    instance * inst;
    int * codageDirect;
    int * codageIndirect;
    FILE * fileSolution;
}solution;


void decodeur(solution * sol);
int evalSolution(solution * sol);
int isSolutionPossible(solution * sol);
void printSolution(solution * sol);
void solution2File(solution * sol);


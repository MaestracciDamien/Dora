#include "codage.h"



solution * initSolution(instance * inst, int type)
{
    int i;
    solution * sol;
    sol->typeCodage = type;
    sol->inst = inst;
    sol->codageDirect = (int *) malloc (sizeof(int) * inst->nbObjet);
    for (i =0; i < inst->nbObjet; i++)
    {
        sol->codageDirect[i] = 0;
    }
    sol->codageIndirect = (int *) malloc (sizeof(int) * inst->nbObjet);
    for (i =0; i < inst->nbObjet; i++)
    {
        sol->codageIndirect[i] = i;
    }
    sol->fileSolution = NULL;

    return sol;
}
void decodeur(solution * sol)
{
    int i =0;
    int j;
    int * valDimension;
    int nbDim = sol->inst->nbDim;
    int p;
    int test;
    valDimension = (int *) malloc (sizeof(int) * nbDim);
    for(p =0; p< nbDim; p++)
    {
        valDimension[p] = sol->inst->capaciteSac[p];
    }

    while (i != (sol->inst->nbObjet-1))
    {
        test =1;
        p =0;
        j = sol->codageIndirect[i];
        while ( (p< nbDim) && test)
        {
            test = valDimension[p] - sol->inst->poidObj[p][i];
            test = (test < 0)  ?  0  : 1;
            p++;
        }
        if (test ==1)
        {
         for (p=0; p <nbDim; p++)
            {
                valDimension[p] -= sol->inst->poidObj[p][i];
            }
            sol->codageDirect[i] =1;
        }
        i++;

    }


}

int evalSolution(solution * sol)
{
    int i;
    int retour = 0;
    if (sol->typeCodage == 1)
    {
        decodeur(sol);
    }
    for (i= 0; i< sol->inst->nbObjet; i++)
    {
        if ( sol->codageDirect[i] == 1) retour += sol->inst->valeurObj[i];
    }
    return retour;
}

int isSolutionPossible(solution * sol)
{
    int retour =1;
    int * valDimension;
    int nbDim = sol->inst->nbDim;
    int i;
    valDimension = (int *) malloc (sizeof(int) * nbDim);
    for(i =0; i< nbDim; i++)
    {
        valDimension[i] = sol->inst->capaciteSac[i];
    }
    if (sol->typeCodage == 1)
    {
        decodeur(sol);
    }
    while (retour  && i< sol->inst->nbObjet)
    {
        int j;
         if ( sol->codageDirect[i] == 1)
         {
            for (j=0; j <nbDim; j++)
            {
                valDimension[j] -= sol->inst->poidObj[j][i];
                if (valDimension[j] < 0) retour =0;
                j++;
            }

         }
         i++;
    }


}
void printSolution(solution * sol);
void solution2File(solution * sol);

#include "codage.h"



void initSolution(solution * sol,instance * inst, int type)
{
    int i;
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
}
void decodeur(solution * sol)
{
    int i =0;
    int val;
    int * valDimension;
    int nbDim = sol->inst->nbDim;
    int p;
    int test;
    valDimension = (int *) malloc (sizeof(int) * nbDim);
    for(p =0; p< nbDim; p++)
    {
        valDimension[p] = sol->inst->capaciteSac[p];
    }

    while (i  < (sol->inst->nbObjet))
    {
        val = sol->codageIndirect[i];
        test =1;
        p =0;
        while ( (p< nbDim) && test)
        {
            test = valDimension[p] - sol->inst->poidObj[p][val];
            test = (test < 0)  ?  0  : 1;
            p++;
        }
        if (test ==1)
        {
         for (p=0; p <nbDim; p++)
            {
                valDimension[p] -= sol->inst->poidObj[p][val];
            }
            sol->codageDirect[val] =1;
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
         if ( sol->codageDirect[i] >= 1)
         {
            for (j=0; j <nbDim; j++)
            {
                valDimension[j] -= sol->inst->poidObj[j][i];
                if (valDimension[j] < 0) retour =0;
            }

         }
         i++;
    }

    return retour;
}
void printSolution(solution * sol){
    int i;
    printf("%s","[ ");
    if (sol->typeCodage == 0){
        for (i =0; i < sol->inst->nbObjet; i++){
            printf("%d , ", sol->codageDirect[i]);
        }
        printf("%d", sol->codageDirect[i]);
    }
    else {
        for (i =0; i < sol->inst->nbObjet; i++){
            printf("%d ,", sol->codageIndirect[i]);
        }
    }
    printf("%s\n"," ]" );
};

void solution2File(solution * sol){
    FILE *f = fopen("solution.txt", "w");
    if (f == NULL){
        printf("Error opening file!\n");
    }
    int i;
    fprintf(f,"%s","[ ");
    if (sol->typeCodage == 0){
        for (i =0; i < sol->inst->nbObjet-1; i++){
            fprintf(f,"%d , ", sol->codageDirect[i]);
        }
        fprintf(f,"%d", sol->codageDirect[i]);
    }
    else {
        for (i =0; i < sol->inst->nbObjet; i++){
            fprintf(f,"%d", sol->codageIndirect[i] = i);
        }
        fprintf(f,"%d", sol->codageIndirect[i]);
    }
    fprintf(f,"%s\n"," ]" );
    fclose(f);
}


solution * copySolution(solution * sol)
{
    solution * retour = (solution *) malloc(sizeof(solution));
    retour->typeCodage = sol->typeCodage;
    retour->inst = sol->inst;
    retour->fileSolution = sol->fileSolution;
    retour->codageDirect = (int *) malloc(sizeof(int)*retour->inst->nbObjet);
    retour->codageIndirect = (int *) malloc(sizeof(int)*retour->inst->nbObjet);
    for (int i=0; i<retour->inst->nbObjet; i++)
    {
        retour->codageDirect[i] = sol->codageDirect[i];
        retour->codageIndirect[i] = sol->codageIndirect[i];
    }
    return retour;

}

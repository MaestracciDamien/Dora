#include "codage.h"


//initialise une solution à partir d'une instance
// /!\ c'est à l'utilisateur de liberer la solution alloue
solution * initSolution(instance * inst, int type)
{
    solution * sol =(solution *) malloc(sizeof(solution));
    if (sol == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    int i;
    sol->typeCodage = type;
    sol->inst = inst;
    sol->codageDirect = (int *) malloc (sizeof(int) * inst->nbObjet);
    if (sol->codageDirect == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for (i =0; i < inst->nbObjet; i++)
    {
        sol->codageDirect[i] = 0;
    }
    sol->codageIndirect = (int *) malloc (sizeof(int) * inst->nbObjet);
    if (sol->codageIndirect == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for (i =0; i < inst->nbObjet; i++)
    {
        sol->codageIndirect[i] = i;
    }
    sol->fileSolution = NULL;
    return sol;
}

/* si la solution est coder de façon indirect on a besoin de cette fonction
pour arriver à une solution concrete (codage direct)
*/
void decodeur(solution * sol)
{
    int i =0;
    int val;
    int * valDimension;
    int nbDim = sol->inst->nbDim;
    int p;
    int test;
    valDimension = (int *) malloc (sizeof(int) * nbDim);
    if (valDimension == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    // on initialise le sac comme étant vide (chaque dimensions est à sa capacite maximale)
    for(p =0; p< nbDim; p++)
    {
        valDimension[p] = sol->inst->capaciteSac[p];
    }
    // pour chaque objet
    while (i  < (sol->inst->nbObjet))
    {
        val = sol->codageIndirect[i];
        test =1;
        p =0;
        // on va essayer d'ajouter en priorite dans l'ordre indirect des objets
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

//evalue une solution, c.a.d renvoie la valeur objective associe a cette solution
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


// teste si une solution est réalisable, renvoie 1 si oui 0 sinon
int isSolutionPossible(solution * sol)
{
    int retour =1;
    int * valDimension;
    int nbDim = sol->inst->nbDim;
    int i;
    valDimension = (int *) malloc (sizeof(int) * nbDim);
    if (valDimension == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    // on instancie le sac à dos comme étant (toutes les dimensions ont au maximum
    for(i =0; i< nbDim; i++)
    {
        valDimension[i] = sol->inst->capaciteSac[i];
    }
    //si l'on se trouve en codage indirect on passe en codage direct qui est plus simple à utiliser
    if (sol->typeCodage == 1)
    {
        decodeur(sol);
    }
    // on teste pour chaque objet qui doit se trouver dans le sac à dos, si l'ajout de celui ne fait pas déborder le sac dans l'une de ses dimensions
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

// affiche la solution dans le terminal
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

//
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

// cree une copie d'une solution, en memoire
// /!\ c'est à l'utilisateur de liberer la nouvelle solution alloue
solution * copySolution(solution * sol)
{
    solution * retour = (solution *) malloc(sizeof(solution));
    if (retour
         == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    retour->typeCodage = sol->typeCodage;
    retour->inst = sol->inst;
    retour->fileSolution = sol->fileSolution;
    retour->codageDirect = (int *) malloc(sizeof(int)*retour->inst->nbObjet);
    if (retour->codageDirect == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    retour->codageIndirect = (int *) malloc(sizeof(int)*retour->inst->nbObjet);
    if (retour->codageIndirect == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for (int i=0; i<retour->inst->nbObjet; i++)
    {
        retour->codageDirect[i] = sol->codageDirect[i];
        retour->codageIndirect[i] = sol->codageIndirect[i];
    }
    return retour;

}

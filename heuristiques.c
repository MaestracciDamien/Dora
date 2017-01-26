# include "heuristiques.h"

int * sortRandom(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb -1; i++){
            size_t j = i +rand() / (RAND_MAX/(nb-i)+1);
            int t = sortedList[j];
            sortedList[j]=sortedList[i];
            sortedList[i]=t;
        }
    }
    return sortedList;
};

int * sortValue(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            for (int j =0; j< nb ;j++){
                if (inst->valeurObj[i] < inst->valeurObj[j]){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

int * sortRatioValueSum(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            int dimI =0;
            for (int dim=0;dim<inst->nbDim;dim++){
                dimI+= inst->poidObj[dim][i];
            }
            for (int j =0; j< nb ;j++){
                int dimJ=0;
                for (int dim=0;dim<inst->nbDim;dim++){
                    dimJ+=inst->poidObj[dim][j];
                }
                if ((inst->valeurObj[i]/dimI) < (inst->valeurObj[j]/dimJ)){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

int * sortRatioValueDimCrit(instance *inst){
    int nb = inst->nbObjet;
    int dimCrit= 0;
    for (int dim=1; dim< inst->nbDim; dim++){
        if (inst->capaciteSac[dim]< inst->capaciteSac[dimCrit]){
            dimCrit = dim;
        }
    }
    int * sortedList = malloc (sizeof(int)*nb);
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            for (int j =0; j< nb ;j++){
                if ((inst->valeurObj[i]/inst->poidObj[dimCrit][i]) < (inst->valeurObj[j]/inst->poidObj[dimCrit][j])){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

int * sortValuePoids(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            int poidsI =0;
            for (int dim=0;dim<inst->nbDim;dim++){
                poidsI+= inst->poidObj[dim][i];
            }
            for (int j =0; j< nb ;j++){
                int poidsJ=0;
                for (int dim=0;dim<inst->nbDim;dim++){
                    poidsJ+=inst->poidObj[dim][j];
                }
                if (poidsI > poidsJ){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};
solution * heuristique(instance * inst, functionSort fun, int typeCodage)
{
    int l = 0;
    int j;
    int * poidObjet;
    int nb = inst->nbObjet;
    int nbD = inst->nbDim;
    int * sac= (int *) malloc (sizeof(int)* nb);
    for(int p =0; p< nbD; p ++)
        {
            sac[p] = inst->capaciteSac[p];
        }
    solution * retour = (solution *) malloc (sizeof(solution));
    initSolution(retour,inst, typeCodage);
    int * tab = (*fun)(inst);
    printSolution(retour);
    while (l < nb)
    {
        j = tab[l];
        poidObjet = (int *) malloc (sizeof(int)* nbD);
        for(int p =0; p< nbD; p ++)
        {
            poidObjet[p] = inst->poidObj[p][j];
        }
        if (isItemFitting(poidObjet,sac,nbD))
        {
            addItemToBag(poidObjet,sac,nbD);
            retour->codageDirect[j] = 1;
        }
        l++;

    }
    return retour;
}

int isItemFitting(int * item, int * roomBag, int nbDim)
{
    int test =1;
    int val;
    int i= 0;
    while (test && (i < nbDim) )
    {
        val = roomBag[i] -  item[i];
        i++;
        if (val < 0)
        {
            test = 0;
        }
    }
    return test;
}

void addItemToBag(int * item, int * roomBag, int nbDim)
{

    int i;
    for (i=0; i< nbDim; i++)
    {
        roomBag[i] -=  item[i];
    }

}

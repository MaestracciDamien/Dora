# include "heuristiques.h"

void sortRandom(instance *inst);
solution * heuristique(instance * inst, functionSort fun, int typeCodage)
{
    int l = 0;
    int j;
    int * poidObjet;
    int nb = inst->nbObjet;
    int * sac= (int *) malloc (sizeof(int)* nb);
    for(int p =0; p< nb; p ++)
        {
            sac[p] = inst->capaciteSac[p];
        }
    solution * retour = initSolution(inst, typeCodage);
    int * tab = (*fun)(inst);
    while (l < nb)
    {
        poidObjet = (int *) malloc (sizeof(int)* nb);
        for(int p =0; p< nb; p ++)
        {
            poidObjet[p] = inst->poidObj[p][l];
        }
        if (isItemFitting(poidObjet,sac,nb))
        {
            addItemToBag(poidObjet,sac,nb);
            retour->codageDirect[l] = 1;
        }
        l++;

    }
    return retour;
}

int isItemFitting(int * item, int * roomBag, int nbDim)
{
    int test =1;
    int val;
    int i;
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

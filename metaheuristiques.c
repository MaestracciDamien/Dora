#include "metaheuristiques.h"

solution * localSearch(instance * inst,functionSort fun, int typeCodage)
{
    int continuer = 1;
    int fBest;
    int fCourant;
    int fPrec;
    solution * solutionBest;
    solution * solutionCourante = (solution *) malloc (sizeof(solution));
    solutionCourante = heuristique (inst,fun, typeCodage);
    solutionBest = solutionCourante;
    fBest = evalSolution(solutionBest);
    fCourant = evalSolution(solutionCourante);
    fPrec = fCourant;
    int temp;
    int fBestVoisin;
    solution * solutionVoisine;
    solution * solutionBestVoisine;
    while (continuer)
    {
        fBestVoisin = 0;
            if (typeCodage == 0)
            {
                for (int j=0; j < inst->nbObjet; j++)
                {
                    if (solutionCourante->codageDirect[j] == 0)
                    {
                        solutionVoisine = copySolution(solutionCourante);
                        solutionVoisine->codageDirect[j] =1;
                        if(isSolutionPossible(solutionVoisine))
                        {
                            if(evalSolution(solutionVoisine)>fBestVoisin)
                            {
                                solutionBestVoisine = solutionVoisine;
                                fBestVoisin = evalSolution(solutionVoisine);
                            }
                        }
                    }
                }
            }
            else
            {
                for (int i=0; i <inst->nbObjet;i++)
                {
                    for(int j =0; j<(inst->nbObjet/2);j++)
                    {
                        solutionVoisine = copySolution(solutionCourante);
                        temp = solutionVoisine->codageIndirect[i];
                        solutionVoisine->codageIndirect[i] = solutionVoisine->codageIndirect[j];
                        solutionVoisine->codageIndirect[j] = temp;
                        if(isSolutionPossible(solutionVoisine))
                        {
                            if(evalSolution(solutionVoisine)>fBestVoisin)
                            {
                                solutionBestVoisine = solutionVoisine;
                                fBestVoisin = evalSolution(solutionVoisine);
                            }
                        }
                    }
                }
            }
            fCourant = fBestVoisin;
            solutionCourante = solutionBestVoisine;

            if (fCourant> fBest)
            {
                fBest = fCourant;
                solutionBest = solutionCourante;
            }
            else
            {
                if (fCourant <= fPrec)
                {
                    continuer =0;
                }
            }
            fPrec = fCourant;

    }
    return solutionBest;

}


solution * tabooSearch(int nbIter, int tabooSize, int aspi, instance * inst,functionSort fun, int typeCodage)
{
    solution * solutionBest;
    int fBest;
    int fCourant;
    int fBestVoisin;
    int nbTaboo =0;
    int isTaboo;
    int mouvUtil;
    int * tabooTable = (int *) malloc (sizeof(int)*tabooSize);
    int i= 0;
    solution * solutionCourante = (solution *) malloc (sizeof(solution));
    solutionCourante = heuristique (inst,fun, typeCodage);
    solutionBest = solutionCourante;
    fCourant = evalSolution(solutionCourante);
    fBest = evalSolution(solutionCourante);

    solution * solutionVoisine;
    solution * solutionBestVoisine;
    while (i < nbIter)
    {
        fBestVoisin = 0;
        if (typeCodage == 0)
            {
                for (int j=0; j < inst->nbObjet; j++)
                {
                    if (solutionCourante->codageDirect[j] == 0)
                    {
                        isTaboo = isInTable(j,tabooTable,nbTaboo);
                        if ((!isTaboo)|| aspi)
                        {
                            solutionVoisine = copySolution(solutionCourante);
                            solutionVoisine->codageDirect[j] =1;
                            if((!isTaboo))
                            {
                                if(isSolutionPossible(solutionVoisine))
                                {
                                    if(evalSolution(solutionVoisine)>fBestVoisin)
                                    {
                                    solutionBestVoisine = solutionVoisine;
                                    fBestVoisin = evalSolution(solutionVoisine);
                                    mouvUtil = j;
                                    }
                                }
                            }
                            else
                            {
                                if(isSolutionPossible(solutionVoisine))
                                {
                                    if(evalSolution(solutionVoisine)>fBest)
                                    {
                                    solutionBestVoisine = solutionVoisine;
                                    fBestVoisin = evalSolution(solutionVoisine);
                                    mouvUtil = j;
                                    }
                                }
                            }
                        }
                    }
                }
            }
                fCourant = fBestVoisin;
                solutionCourante = solutionBestVoisine;
                nbTaboo ++;
                if(nbTaboo== tabooSize)
                {
                    int temp = tabooTable[0];
                    for (int p =nbTaboo; p>0; p--)
                    {
                        tabooTable[p] = tabooTable[p-1];
                    }
                    tabooTable[0] = mouvUtil;
                    nbTaboo--;
                }
                else
                {
                    int temp = tabooTable[0];
                    for (int p =nbTaboo; p>0; p--)
                    {
                        tabooTable[p] = tabooTable[p-1];
                    }
                    tabooTable[0] = mouvUtil;
                }
                if(fCourant>fBest)
                {
                    fBest = fCourant;
                    solutionBest=solutionCourante;
                    i =0;
                }
                i++;
    }
    return solutionBest;

}

int isInTable(int nombre, int * tab, int nb)
{
    int i=0;
    int retour =0;
    while (i < nb && !retour)
    {
        if(tab[i] == nombre) retour=1;
        i++;
    }
    return retour;
}

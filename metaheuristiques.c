#include "metaheuristiques.h"
#include <time.h>
#include <stdlib.h>



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

void reparation(solution * sol)
{
    int test = isSolutionPossible(sol);
    int posChangement;
    int found =0;
    int i=0;
    while(!test)
    {
        while (!found && i <sol->inst->nbObjet)
        {
            if (sol->codageDirect[i] == 1)
            {
                found =1;
                posChangement = i;
            }
            i++;
        }
        if (!found)
        {
            i =0;
            while (!found && i <sol->inst->nbObjet)
            {
                if (sol->codageDirect[i] == 2)
                {
                    found =1;
                    posChangement = i;
                }
                i++;
            }
        }
        sol->codageDirect[posChangement] =0;
        test = isSolutionPossible(sol);

        found =0;
    }
    for (int j=0; j < sol->inst->nbObjet; j++)
    {
        if (sol->codageDirect[j] == 2)
        {
            sol->codageDirect[j]=1;
        }
    }
}
solution ** croisementEnfants(solution * parent1, solution * parent2)
{
    solution ** retour = (solution **) malloc (sizeof(solution *) *2);
    retour[0]= (solution *) malloc (sizeof(solution));
    retour[1]= (solution *) malloc (sizeof(solution));
    int nb = parent1->inst->nbObjet;
    initSolution(retour[0],parent1->inst,0);
    initSolution(retour[1],parent1->inst,0);
    for (int i =0; i<nb; i++)
    {
        retour[0]->codageDirect[i] = parent1->codageDirect[i] + parent2->codageDirect[i];
        retour[1]->codageDirect[i] = parent1->codageDirect[i] + parent2->codageDirect[i];
    }
    reparation(retour[0]);
    reparation(retour[1]);
    return retour;
}

void mutation (solution * sol)
{
    int nb = rand() % sol->inst->nbObjet;
    if (sol->codageDirect[nb]== 0)
    {
        sol->codageDirect[nb]=1;
    }
    else
    {
        sol->codageDirect[nb] =0;
    }
}

solution * geneticAlgo(int sizePopu, int nbIterMax, int pMut, instance * inst)
{
    solution ** populationCourante = (solution **) malloc (sizeof(solution *)* sizePopu );
    solution ** populationEnfant ;
    functionSort fun = &sortRandom;
    solution * solutionBest;
    int fBest =0;
    int i=0;
    srand(time(NULL));
    int r;
    for(int j=0; j <sizePopu;j++)
    {
        populationCourante[j] =heuristique(inst,fun, 0);
        if(evalSolution(populationCourante[j])>fBest)
        {
            fBest =evalSolution(populationCourante[j]);
            solutionBest = populationCourante[j];
        }

    }
    while (i < nbIterMax)
    {
          populationEnfant  = (solution **) malloc (sizeof(solution *)* sizePopu );
          for (int j =0; j <(sizePopu); j+=2)
          {
                solution ** enfants = croisementEnfants(populationCourante[j], populationCourante[j+1]);
                populationEnfant[j] = (solution *) malloc (sizeof(solution));
                populationEnfant[j+1] = (solution *) malloc (sizeof(solution));
                populationEnfant[j] = enfants[0];
                populationEnfant[j+1] = enfants[1];
          }
          for (int j=0; j <sizePopu; j++)
          {
              if (evalSolution(populationEnfant[j])>fBest)
              {
                  fBest =evalSolution(populationEnfant[j]);
                  solutionBest = populationEnfant[j];
              }
                r = rand()%100;
                if (r <= pMut)
                {
                    mutation(populationEnfant[j]);
                    if(isSolutionPossible(populationEnfant[j]))
                    {
                        if (evalSolution(populationEnfant[j])>fBest)
                        {
                            fBest =evalSolution(populationEnfant[j]);
                            solutionBest = populationEnfant[j];
                        }
                    }
                }
          }
          populationCourante = populationEnfant;
          i++;
    }
    return solutionBest;
 }

#include "metaheuristiques.h"
#include <time.h>
#include <stdlib.h>



solution * localSearch(instance * inst,functionSort fun, int typeCodage)
{
    int continuer = 1;
    int fBest; // meilleur valeur de la fonction objective
    int fCourant; // valeur de la solution courante
    int fPrec;  // valeur de la solution precedente
    solution * solutionBest; // meilleur solution
    solution * solutionCourante = (solution *) malloc (sizeof(solution));
    solutionCourante = heuristique (inst,fun, typeCodage); // on calcule la premiere solution a partir d'une heuristique
    solutionBest = solutionCourante;
    fBest = evalSolution(solutionBest);
    fCourant = evalSolution(solutionCourante);
    fPrec = fCourant;
    int temp;
    int fBestVoisin; // valeur du meilleur voisin
    solution * solutionVoisine;
    solution * solutionBestVoisine;

    while (continuer)
    {
        fBestVoisin = 0;
            if (typeCodage == 0) // dans le cas du codage direct
            {
                for (int j=0; j < inst->nbObjet; j++)
                {
                    if (solutionCourante->codageDirect[j] == 0) // si  a l'emplacement j la solution comporte un 0
                    {
                        solutionVoisine = copySolution(solutionCourante); // on copie la solution courante
                        solutionVoisine->codageDirect[j] =1; // et on change la valeur de j afin de creer un voisin avec un objet en plus dans le sac
                        if(isSolutionPossible(solutionVoisine)) // si la nouvelle solution est possible
                        {
                            if(evalSolution(solutionVoisine)>fBestVoisin) // et si la nouvelle valeur objective est meilleur que celle du meilleur voisin
                            {
                                solutionBestVoisine = solutionVoisine; // meilleur voisin devient voisin courant, de meme pour la valeur objective
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
                        if (i !=j)
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
    int temp;
    int fCourant;
    int fBestVoisin;
    int nbTaboo =0;
    int isTaboo;
    int mouvUtil;
    mouvement mouvUtilIndirect;
    int * tabooTable = (int *) malloc (sizeof(int)*tabooSize);
    mouvement * tabooTableIndirect = (mouvement *) malloc (sizeof(mouvement)*tabooSize);
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
            else
            {
                for(int i =0; i<(inst->nbObjet/2);i++)
                {
                    for (int j=0; j < inst->nbObjet; j++)
                    {
                            mouvement mouvCourant = {i,j};
                            isTaboo = isInTableIndirect(mouvCourant,tabooTable,nbTaboo);
                            if ((!isTaboo)|| aspi)
                            {
                                solutionVoisine = copySolution(solutionCourante);
                                temp = solutionVoisine->codageIndirect[i];
                                solutionVoisine->codageIndirect[i] = solutionVoisine->codageIndirect[j];
                                solutionVoisine->codageIndirect[j] = temp;
                                if((!isTaboo))
                                {
                                    if(isSolutionPossible(solutionVoisine))
                                    {
                                        if(evalSolution(solutionVoisine)>fBestVoisin)
                                        {
                                        solutionBestVoisine = solutionVoisine;
                                        fBestVoisin = evalSolution(solutionVoisine);
                                        mouvUtilIndirect = mouvCourant;
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
                                        mouvUtilIndirect = mouvCourant;
                                        }
                                    }
                                }
                            }
                        }

                }
            }
                if (typeCodage == 0)
                {
                    nbTaboo = addIntToTab(mouvUtil,tabooTable,tabooSize,nbTaboo);
                }
                else
                {
                    nbTaboo = addIntToTabIndirect(mouvUtilIndirect,tabooTableIndirect,tabooSize,nbTaboo);
                }
                fCourant = fBestVoisin;
                solutionCourante = solutionBestVoisine;

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
int addIntToTab(int i, int * tab, int size, int nb)
{
                nb ++;
                if(nb== size)
                {
                    for (int p =nb; p>0; p--)
                    {
                        tab[p] = tab[p-1];
                    }
                    tab[0] = i;
                    nb--;
                }
                else
                {
                    for (int p =nb; p>0; p--)
                    {
                        tab[p] = tab[p-1];
                    }
                    tab[0] = i;
                }
                return nb;
}

int addIntToTabIndirect(mouvement i, mouvement * tab, int size, int nb)
{
                nb ++;
                if(nb== size)
                {
                    for (int p =nb; p>0; p--)
                    {
                        tab[p] = tab[p-1];
                    }
                    tab[0] = i;
                    nb--;
                }
                else
                {
                    for (int p =nb; p>0; p--)
                    {
                        tab[p] = tab[p-1];
                    }
                    tab[0] = i;
                }
                return nb;
}

int equalMove(mouvement mouvA, mouvement mouvB)
{
    if (((mouvA.a==mouvB.a) && (mouvA.b==mouvB.b)) || ((mouvA.a==mouvB.b) && (mouvA.b==mouvB.a)) ) return 1;
    else return 0;
}

int isInTableIndirect(mouvement mouv, mouvement * tab, int nb)
{
    int i=0;
    int retour =0;
    while (i < nb && !retour)
    {
        if(equalMove(mouv,tab[i])) retour=1;
        i++;
    }
    return retour;
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
    if (retour == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    retour[0]= initSolution(parent1->inst,0);
    retour[1]= initSolution(parent1->inst,0);
    int nb = parent1->inst->nbObjet;
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
    if (populationCourante == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
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
        if (populationEnfant == NULL)
        {
            puts("error memory allocation");
            exit(-1);
        }
          for (int j =0; j <(sizePopu); j+=2)
          {
                solution ** enfants = croisementEnfants(populationCourante[j], populationCourante[j+1]);
                populationEnfant[j] = (solution *) malloc (sizeof(solution));
                if (populationEnfant[j] == NULL)
                {
                    puts("error memory allocation");
                    exit(-1);
                }
                populationEnfant[j+1] = (solution *) malloc (sizeof(solution));
                if (populationEnfant[j+1] == NULL)
                {
                    puts("error memory allocation");
                    exit(-1);
                }
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

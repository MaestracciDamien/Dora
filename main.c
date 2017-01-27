#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "instance.h"
#include "parseur.h"
#include "codage.h"
#include "heuristiques.h"
#include "instance.h"


int stringToInt(char * s)
{
    return strtol(s,NULL,10);
}

functionSort wichSort(int i )
{
    functionSort retour;
    switch(i)
    {
    case 0:
        retour = &sortRandom;
        break;
    case 1:
        retour = &sortValue;
        break;
    case 2:
        retour = &sortRatioValueSum;
        break;
    case 3:
        retour = &sortRatioValueDimCrit;
        break;
    case 4:
        retour = &sortValuePoids;
        break;
    }
    return retour;
}
void sautLigne(FILE * fp)
{
    char * s = (char *) malloc(sizeof(char)* 100);
    fgets(s,100,fp);
    free(s);
}

int main(int argc, char *argv[])
{
// data/MKP-Instances/_mknapcb1_res.txt
int typeCodage = stringToInt(argv[2]);
int choixMethode = stringToInt(argv[3]);
printf("codage :%d, methode :%d\n", typeCodage, choixMethode);
instance * instCour;
solution * sol;
parseur * pars = initParseur(argv[1]);
while (pars->pInstance < pars->nbInstances)
{
    instCour = nextInstance(pars);
    switch(choixMethode)
    {
    case 1:
        {
        int choixSort = stringToInt(argv[4]);
        functionSort fun = wichSort(choixSort);
        sol = heuristique(instCour,fun,typeCodage);
        break;
        }
    case 2: // metaheuristique recherche locale
        {
            int choixSort = stringToInt(argv[4]);
            functionSort fun = wichSort(choixSort);
            sol = localSearch(instCour,fun,typeCodage);
            break;
        }
    case 3: // metaheuristique recherche tabou
        {
            int choixSort = stringToInt(argv[4]);
            int nbIter = stringToInt(argv[5]);
            int tabooSize = stringToInt(argv[6]);
            int asp = stringToInt(argv[7]);
            functionSort fun = wichSort(choixSort);
            sol =tabooSearch(nbIter,tabooSize,asp,instCour,fun,typeCodage);
            break;
        }
    case 4: // metaheuristique algo genetique
        {
            functionSort fun= &sortRandom;
            int taille =stringToInt(argv[4]);
            int nbIte =stringToInt(argv[5]);
            int pMut = stringToInt(argv[6]); // probabilite de mutation en % [1..100]
            sol = geneticAlgo(taille,nbIte,pMut,instCour);
            break;
        }

    }
    if (isSolutionPossible(sol))
        {
            printf("Instance %d:la solution est realisable et sa valeur objective est: %d\n",pars->pInstance,evalSolution(sol));
        }
        else
        {
            puts ("la solution n'est pas realisable\n");
        }

}
}

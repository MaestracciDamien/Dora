#include "parseur.h"
void parseur(char* chemin)
{
    FILE * fp;

    fp = fopen( chemin, "rt" );
    if (fp == NULL)
        exit(-1);

    char * s = (char *) malloc (sizeof(char)* 100);
    char * split;
    int nbInstances;
    int i =0;
    fgets (s, 100, fp );
    sautLigne( fp );
    functionSort function = &sortRatioValueDimCrit;
    split = strtok(s, " ");
    nbInstances = stringToInt(split);
    free(s);
    while (i < nbInstances)
    {
        sautLigne( fp );
        sautLigne( fp );
        instance * inst = (instance *) malloc (sizeof(instance));
        initInstance(inst,fp);
        //solution * sol = heuristique(inst,function,0);
        //printf("Direct: %d,",evalSolution(sol));
        //printSolution(sol);
        //sol = heuristique(inst,function,1);
        //printSolution(sol);
        //decodeur(sol);
        //sol->typeCodage = 0;
        //printSolution(sol);
        //solution * sol = localSearch(inst, function,1);
        solution * sol = tabooSearch(10,10,1,inst,function,0);
        if (isSolutionPossible(sol))
        {
            printf("la solution est realisable et sa valeur objective est: %d",evalSolution(sol));
        }
        else
        {
            puts ("la solution n'est pas realisable");
        }
        i++;
    }

}

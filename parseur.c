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
    functionSort function = &sortRandom;
    split = strtok(s, " ");
    nbInstances = stringToInt(split);
    free(s);
    while (i < nbInstances)
    {
        sautLigne( fp );
        sautLigne( fp );
        instance * inst = (instance *) malloc (sizeof(instance));
        initInstance(inst,fp);
        solution * sol = heuristique(inst,function,0);
        printSolution(sol);
        if (isSolutionPossible(sol))
        {
            printf("la solution est rŽalisable et sa valeur objective est: %d",evalSolution(sol));
        }
        else
        {
            puts ("la solution n'est pas rŽalisable");
        }
        i++;
    }

}

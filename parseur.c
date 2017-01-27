#include "parseur.h"
parseur * initParseur(char* chemin)
{
    FILE * fp;
    parseur * retour = (parseur *) malloc(sizeof(parseur));
    fp = fopen( chemin, "rt" );
    if (fp == NULL)
        exit(-1);
    retour->fp = fp;


    char * s = (char *) malloc (sizeof(char)* 100);
    char * split;

    int i =0;
    fgets (s, 100, fp );
    sautLigne( fp );
    split = strtok(s, " ");
    retour->nbInstances = stringToInt(split);
    retour->pInstance =0;
    free(s);
    return retour;
}

instance * nextInstance(parseur * pars)
{
        sautLigne( pars->fp );
        sautLigne( pars->fp );
        instance * inst = (instance *) malloc (sizeof(instance));
        initInstance(inst,pars->fp);
        pars->pInstance++;
        return inst;


}

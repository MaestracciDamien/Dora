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
    fgets (s, 100, fp );
    sautLigne( fp );
    split = strtok(s, " ");
    retour->nbInstances = stringToInt(split);
    retour->pInstance =0;
    free(s);
    return retour;
}

// retourne la prochaine instance à partir d'un parseur
instance * nextInstance(parseur * pars)
{
        sautLigne( pars->fp );
        sautLigne( pars->fp );
        instance * inst = initInstance(pars->fp);
        if(inst == NULL)
        {
            puts("error memory allocation");
            exit(-1);
        }

        pars->pInstance++;
        return inst;
}

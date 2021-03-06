#define STRING_BUFFER 20000
#include "instance.h"


// affichage d'une instance sur le terminal
void printInst(instance* inst)
{
    int i,j;
    printf("\n nbObjet: %d", inst->nbObjet);
    printf("\n nbDim: %d", inst->nbDim);
    printf("\n valeurObjet[");
    for (i=0; i< inst->nbObjet; i++)
    {
        printf(" %d,",inst->valeurObj[i]);
    }
    puts("]");

    for (i =0; i<inst->nbDim; i++)
    {
        printf("Poid Dimension %d [",i+1);
        for (j =0; j< inst->nbObjet; j++)
        {
            printf(" %d,", inst->poidObj[i][j]);
        }
        puts("]");

    }
    printf("\n capacite Sac[");
    for (i=0; i< inst->nbDim; i++)
    {
        printf(" %d,",inst->capaciteSac[i]);
    }
    puts("]");
}

//instancie une instance a partir des donnes contenue dans le fichier fp
// /!\ la liberation de l'instance renvoye est a la charge de l'utilisateur de la fonction
instance * initInstance(FILE *fp)
{
    int i,j;
    instance * inst = (instance *) malloc (sizeof(instance));
    char * s = (char *) malloc (sizeof(char)* STRING_BUFFER);
    if(s ==NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    fgets (s, STRING_BUFFER, fp );
    char *split = strtok(s, " ");
    inst->nbObjet = stringToInt(split);
    split = strtok(NULL, " ");
    inst->nbDim = stringToInt(split);

    fgets (s, STRING_BUFFER, fp );
    fgets (s, STRING_BUFFER, fp );
    fgets (s, STRING_BUFFER, fp );
    inst->valeurObj = (int *) malloc (sizeof(int) * inst->nbObjet);
    if (inst->valeurObj == NULL) exit(-1);
    split= strtok(s, " ");
    for (i =0; i< inst->nbObjet; i++)
    {
        inst->valeurObj[i] = stringToInt(split);
        split = strtok(NULL, " ");
    }
    fgets (s, STRING_BUFFER, fp );
    inst->poidObj = (int **) malloc (sizeof(int *) * inst->nbDim);
    if (inst->poidObj == NULL) exit(-1);
    for (i =0; i<inst->nbDim; i++)
    {
        inst->poidObj[i] = (int *) malloc (sizeof(int) * inst->nbObjet);
        if (inst->poidObj[i] == NULL) exit(-1);
        fgets (s, STRING_BUFFER, fp );
        split= strtok(s, " ");
        for (j =0; j< inst->nbObjet; j++)
        {
            inst->poidObj[i][j] = stringToInt(split);
            split = strtok(NULL, " ");
        }

    }
    fgets (s, STRING_BUFFER, fp );
    fgets (s, STRING_BUFFER, fp );
    inst->capaciteSac = (int *) malloc (sizeof(int)* inst->nbDim);
    if (inst->capaciteSac == NULL) exit(-1);
    split= strtok(s, " ");
    for (i =0; i< inst->nbDim; i++)
    {
        inst->capaciteSac[i] = stringToInt(split);
        split = strtok(NULL, " ");
    }
    return inst;
}

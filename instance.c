#define STRING_BUFFER 2000
#include "instance.h"

void instToString(instance* inst)
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
    printf("\n capacitée Sac[");
    for (i=0; i< inst->nbDim; i++)
    {
        printf(" %d,",inst->capaciteSac[i]);
    }
    puts("]");
}


instance * creerInstance(FILE *fp)
{
    instance inst;
    int i,j;
    char * s = (char *) malloc (sizeof(char)* STRING_BUFFER);

    fgets (s, STRING_BUFFER, fp );
    char *split = strtok(s, " ");
    inst.nbObjet = stringToInt(split);
    split = strtok(NULL, " ");
    inst.nbDim = stringToInt(split);

    //sautLigne(fp );
   // fscanf(fp,"\n");
    fgets (s, STRING_BUFFER, fp );
    fgets (s, STRING_BUFFER, fp );

    //sautLigne(fp );
    fgets (s, STRING_BUFFER, fp );
    inst.valeurObj = (int *) malloc (sizeof(int) * inst.nbObjet);
    if (inst.valeurObj == NULL) exit(-1);
    split= strtok(s, " ");
    for (i =0; i< inst.nbObjet; i++)
    {
        inst.valeurObj[i] = stringToInt(split);
        split = strtok(NULL, " ");
    }
    fgets (s, STRING_BUFFER, fp );
    //sautLigne( fp );
    inst.poidObj = (int **) malloc (sizeof(int *) * inst.nbDim);
    if (inst.poidObj == NULL) exit(-1);
    for (i =0; i<inst.nbDim; i++)
    {
        inst.poidObj[i] = (int *) malloc (sizeof(int) * inst.nbObjet);
        if (inst.poidObj[i] == NULL) exit(-1);
        fgets (s, STRING_BUFFER, fp );
        split= strtok(s, " ");
        for (j =0; j< inst.nbObjet; j++)
        {
            inst.poidObj[i][j] = stringToInt(split);
            split = strtok(NULL, " ");
        }

    }
    fgets (s, STRING_BUFFER, fp );

    //sautLigne( fp );
    fgets (s, STRING_BUFFER, fp );
    inst.capaciteSac = (int *) malloc (sizeof(int)* inst.nbDim);
    if (inst.capaciteSac == NULL) exit(-1);
    split= strtok(s, " ");
    for (i =0; i< inst.nbDim; i++)
    {
        inst.capaciteSac[i] = stringToInt(split);
        split = strtok(NULL, " ");
    }

    instToString(&inst);
}

void deleteInstance(instance*  inst)
{

}

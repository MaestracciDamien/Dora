# include "heuristiques.h"

// retourne un tableau d'entier des objets d'une instance triŽ de faon alŽatoire
// /!\ il revient a l'utilisateur de liberer le tableau d'entier retournŽ
int * sortRandom(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    if (sortedList == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb -1; i++){
            size_t j = i +rand() / (RAND_MAX/(nb-i)+1);
            int t = sortedList[j];
            sortedList[j]=sortedList[i];
            sortedList[i]=t;
        }
    }
    return sortedList;
};

// retourne un tableau d'entier des objets d'une instance triŽ selon leur valeur (par ordre decroissant)
// /!\ il revient a l'utilisateur de liberer le tableau d'entier retournŽ
int * sortValue(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    if (sortedList == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            for (int j =0; j< nb ;j++){
                if (inst->valeurObj[i] < inst->valeurObj[j]){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

// retourne un tableau d'entier des objets d'une instance triŽ de facon decroissante suivant un ratio ( Valeur/(poid dimension 1+ poid dimension 2 + ...))
// /!\ il revient a l'utilisateur de liberer le tableau d'entier retournŽ
int * sortRatioValueSum(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    if (sortedList == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            int dimI =0;
            for (int dim=0;dim<inst->nbDim;dim++){
                dimI+= inst->poidObj[dim][i];
            }
            for (int j =0; j< nb ;j++){
                int dimJ=0;
                for (int dim=0;dim<inst->nbDim;dim++){
                    dimJ+=inst->poidObj[dim][j];
                }
                if ((inst->valeurObj[i]/dimI) < (inst->valeurObj[j]/dimJ)){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

// retourne un tableau d'entier des objets d'une instance triŽ de facon decroissante suivant un ratio ( valeur / poid de l'objet dans la dimension critique)
// /!\ il revient a l'utilisateur de liberer le tableau d'entier retournŽ
int * sortRatioValueDimCrit(instance *inst){
    int nb = inst->nbObjet;
    int dimCrit= 0;
    for (int dim=1; dim< inst->nbDim; dim++){
        if (inst->capaciteSac[dim]< inst->capaciteSac[dimCrit]){
            dimCrit = dim;
        }
    }
    int * sortedList = malloc (sizeof(int)*nb);
    if (sortedList == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            for (int j =0; j< nb ;j++){
                if ((inst->valeurObj[i]/inst->poidObj[dimCrit][i]) < (inst->valeurObj[j]/inst->poidObj[dimCrit][j])){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};

// retourne un tableau d'entier des objets d'une instance triŽ de facon croissante par la somme des poids de l'objet dans toute les dimensions
// /!\ il revient a l'utilisateur de liberer le tableau d'entier retournŽ
int * sortValuePoids(instance *inst){
    int nb = inst->nbObjet;
    int * sortedList = malloc (sizeof(int)*nb);
    if (sortedList == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for( int i=0;i<nb;i++){
        sortedList[i]=i;
    }
    if (nb>1){
        size_t i;
        for (i=0; i< nb; i++){
            int poidsI =0;
            for (int dim=0;dim<inst->nbDim;dim++){
                poidsI+= inst->poidObj[dim][i];
            }
            for (int j =0; j< nb ;j++){
                int poidsJ=0;
                for (int dim=0;dim<inst->nbDim;dim++){
                    poidsJ+=inst->poidObj[dim][j];
                }
                if (poidsI > poidsJ){
                    int t = sortedList[j];
                    sortedList[j]=sortedList[i];
                    sortedList[i]=t;
                }
            }
        }
    }
    return sortedList;
};


solution * heuristique(instance * inst, functionSort fun, int typeCodage)
{
    int l = 0; //emplacement dans la table des priorites
    int j;
    int idInd =0;
    int temp;
    int * poidObjet; // sac
    int nb = inst->nbObjet;
    int nbD = inst->nbDim;
    int * sac= (int *) malloc (sizeof(int)* nb);
    if (sac == NULL)
    {
        puts("error memory allocation");
        exit(-1);
    }
    for(int p =0; p< nbD; p ++) //on initialise le sac avec ses capacites dans chaque dimension
        {
            sac[p] = inst->capaciteSac[p];
        }
    solution * retour = initSolution(inst, typeCodage);
    int * tab = (*fun)(inst);
    while (l < nb)
    {
        j = tab[l]; //on prend l'objet correspondant
        poidObjet = (int *) malloc (sizeof(int)* nbD);
        if (poidObjet == NULL)
        {
            puts("error memory allocation");
            exit(-1);
        }
        for(int p =0; p< nbD; p ++)
        {
            poidObjet[p] = inst->poidObj[p][j];
        }
        if (isItemFitting(poidObjet,sac,nbD)) // on regarde si l'objet peut rentrer dans le sac
        {
            addItemToBag(poidObjet,sac,nbD); // si il peut on ajoute l'objet
            if (retour->typeCodage == 0) // on change le codage de la solution pour representer l'ajout de l'objet
            {
                retour->codageDirect[j] = 1;
            }
            else // meme chose pour le codage indirecte
            {
                temp = retour->codageIndirect[idInd];
                retour->codageIndirect[idInd] =j;
                retour->codageIndirect[j] = temp;
                idInd++;
            }

        }
        l++;

    }
    return retour;
}


// regarde si un objet peut aller dans un sac, si il y a assez de place pour accueillir l'objet
int isItemFitting(int * item, int * roomBag, int nbDim)
{
    int test =1;
    int val;
    int i= 0;
    // on regarde dans chaque dimension du sac, si celle ci peut accueillir le poid de l'objet dans la dimension
    while (test && (i < nbDim) )
    {
        val = roomBag[i] -  item[i];
        i++;
        if (val < 0)
        {
            test = 0;
        }
    }
    return test;
}

// ajoute le poid d'un objet pour chaque dimension dans un sac
// /!\ il revient ˆ l'utilisateur de verifier que le peut accueillir l'objet (cf isItemFitting)
void addItemToBag(int * item, int * roomBag, int nbDim)
{

    int i;
    for (i=0; i< nbDim; i++)
    {
        roomBag[i] -=  item[i];
    }

}

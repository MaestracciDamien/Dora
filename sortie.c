void openSortie(char * chemin)
{
    fp = fopen (chemin,"w+");
    if (fp == NULL)
    {
        exit(-1);
    }
}
void fermerSortie()
{
    fclose(fp);
}


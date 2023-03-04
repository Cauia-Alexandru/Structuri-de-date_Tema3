//Cauia_Alexandru_314CB
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct carte
{
    char *titlu;
    char *autor;
    int rating;
    int nr_pagini;
} Tcarte, *Adr_carte;

typedef struct TitluCarte
{
    struct TitluCarte *copii[68];
    Adr_carte Calea_Carte;
    int sfarsit;

} T1;

typedef struct Autor_Carte
{
    struct Autor_Carte *copii[68];
    T1 *Cartile_autorului;
    int final;
} T2;

int poz_litera(const char litera)
{
    const char *litere = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";

    return strchr(litere, litera) - litere;
}

T1 *nod_nou(void)
{
    T1 *creeaza_nod = (T1 *)malloc(sizeof(T1));
    if (creeaza_nod)
    {
        creeaza_nod->Calea_Carte = NULL;
        creeaza_nod->sfarsit = 0;
        int i;
        for (i = 0; i < 68; i++)     //setez la NULL campurile structurii
        {
            creeaza_nod->copii[i] = NULL;
        }
    }
    return creeaza_nod;
}
T2 *nod_nou_2(void)
{
    T2 *creeaza_nod = (T2 *)malloc(sizeof(T2));
    if (creeaza_nod)
    {
        creeaza_nod->Cartile_autorului = NULL;
        creeaza_nod->final = 0;
        int i;
        for (i = 0; i < 68; i++)
        {
            creeaza_nod->copii[i] = NULL;
        }
    }
    return creeaza_nod;
}

void add_book_T1(T1 *radacina, char *cheie, Adr_carte info_carte)
{
    T1 *parg_node = radacina;
    int nivel, index;
    int lungime = strlen(cheie); //lungimea cheii
    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = poz_litera(cheie[nivel]);
        if (!parg_node->copii[index]) //daca nu exista in arbore litera ii aloc un nod nou
        {
            parg_node->copii[index] = nod_nou();
        }
        parg_node = parg_node->copii[index]; //daca exista parcurg mai departe
    }
    if (parg_node->sfarsit)
        return;

    parg_node->sfarsit = 1;
    parg_node->Calea_Carte = info_carte; // ajung la nodul frunza si setez un pointer catre structura cu informatii
}

void add_book_T2(T2 *radacina, char *cheie, T1 *cartileLui, Adr_carte str_info)
{
    char *denumire = str_info->titlu;
    T2 *parg_node = radacina;
    int nivel, index;
    int lungime = strlen(cheie);

    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = poz_litera(cheie[nivel]);
        if (!parg_node->copii[index])
        {
            parg_node->copii[index] = nod_nou_2();
        }
        parg_node = parg_node->copii[index];
    }
    parg_node->final = 1;
    if (!parg_node->Cartile_autorului)
        parg_node->Cartile_autorului = cartileLui; //daca in strucura T2 nu exista T1 o egalez cu cea primita ca parametru
    else
    {
        add_book_T1(parg_node->Cartile_autorului, denumire, str_info); //daca exista, adaug mai departe cartile
    }
}

Adr_carte search(T1 *root, char *cheie)
{
    T1 *parg_node = root;
    int nivel, index;
    int lungime = strlen(cheie);

    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = poz_litera(cheie[nivel]);
        if (!parg_node->copii[index])
        {
            return NULL;
        }
        parg_node = parg_node->copii[index];
    }
    if (parg_node->sfarsit)
    {
        return parg_node->Calea_Carte; //returnez informatiile despre carte ca sa le pot afisa
    }
    else
    {
        return NULL;
    }

}

int nod_terminal(T1 *root)
{
    return root->sfarsit;
}
void afisare_T1(T1 *root, FILE *fwrite)
{
    if (nod_terminal(root)) //verific daca am ajuns la nodul frunza
    {
        fprintf(fwrite, "%s\n", root->Calea_Carte->titlu); //printez titlu
    }
    int i;
    for (i = 0; i < 68; i++)
    {
        if (root->copii[i])
        {
           
            afisare_T1(root->copii[i], fwrite); //parcurg recursiv pana ajung la nodul frunza
        }
    }
}

void list_autor(T2 *root2, char *cheie, FILE *fwrite, int a, char *nume) //daca a=1, functia e apelata pentru "list_author", daca a=0, e apelata pentru search_by_author
{
    T2 *parc_node = root2;
    int lungime = strlen(cheie);
    int nivel, index;

    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = poz_litera(cheie[nivel]);
        if (!parc_node->copii[index]) //caut autorul, daca nu gasesc, afisez mesajul
        {
            fprintf(fwrite, "Autorul %s nu face parte din recomandarile tale.\n", cheie);
            return;
        }
        parc_node = parc_node->copii[index];
    }
    if (parc_node->final && a) // afisarea pentru "list_author"
    {
        afisare_T1(parc_node->Cartile_autorului, fwrite); 
        return;
    }
    else if (parc_node->final) //afisarea pentru functia search_by_author
    {
        Adr_carte carte_cautata = search(parc_node->Cartile_autorului, nume);
        if (carte_cautata == NULL)
        {
            fprintf(fwrite, "Cartea %s nu exista in recomandarile tale.\n", nume);
        }
        else
        {
            fprintf(fwrite, "Informatii recomandare: %s, %s, %i, %i\n", carte_cautata->titlu, carte_cautata->autor, carte_cautata->rating, carte_cautata->nr_pagini);
        }
        return;
    }
    
}

void citesteTabla(char *numeFisier, char *numeFisierIesire, T1 *root, T2 *root2)
{
    FILE *f;
    FILE *fwrite;
    char *line = NULL;
    size_t len = 0;

    f = fopen(numeFisier, "rt");
    fwrite = fopen(numeFisierIesire, "wt");
    if (f == NULL)
        return;
    
    while (getline(&line, &len, f) != -1)
    {
        char *functie = strtok(line, " ");
        if (strcmp(functie, "add_book") == 0)
        {

            char *titlu = strtok(NULL, ":");
            char *autor = strtok(NULL, ":");
            char *rating_char = strtok(NULL, ":");
            int rating = atoi(rating_char);
            char *pagini = strtok(NULL, ":");
            int nr_pagini = atoi(pagini);
            Tcarte *info_carte = malloc(sizeof(Tcarte)); //aloc spatiu pentru carte, apoi o formez
            if (info_carte == NULL)
                return;
            info_carte->autor = (char *)malloc((strlen(autor) + 1) * sizeof(char));
            strcpy(info_carte->autor, autor);
            info_carte->titlu = (char *)malloc((strlen(titlu) + 1) * sizeof(char));
            strcpy(info_carte->titlu, titlu);
            info_carte->rating = rating;
            info_carte->nr_pagini = nr_pagini;

            add_book_T1(root, titlu, info_carte);
            T1 *aux = nod_nou();
            add_book_T1(aux, titlu, info_carte);
            add_book_T2(root2, autor, aux, info_carte);
        }
        else if (strcmp(functie, "search_book") == 0)
        {
            char *titlu = strtok(NULL, "\n");
            Adr_carte carte_cautata = search(root, titlu);
            if (carte_cautata == NULL)
            {
                fprintf(fwrite, "Cartea %s nu exista in recomandarile tale.\n", titlu);
            }
            else
            {
                fprintf(fwrite, "Informatii recomandare: %s, %s, %i, %i\n", carte_cautata->titlu, carte_cautata->autor, carte_cautata->rating, carte_cautata->nr_pagini);
            }
        }
        else if (strcmp(functie, "list_author") == 0)
        {
            char *autor = strtok(NULL, "\n");
            list_autor(root2, autor, fwrite, 1, NULL);
        }
        else if (strcmp(functie, "search_by_author") == 0)
        {
            char *autor = strtok(NULL, ":");
            char *titlu = strtok(NULL, "\n");

            list_autor(root2, autor, fwrite, 0, titlu);
            
        }
    }
}

int main(int argc, char *argv[])
{
    T1 *root = nod_nou();
    T2 *root2 = nod_nou_2();
    citesteTabla(argv[1], argv[2], root, root2);
}
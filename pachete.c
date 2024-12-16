#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura pentru cartier
typedef struct
{
    int id;
    char *nume;
} Cartier;

// structura pentru pachet
typedef struct
{
    int id;
    int adresa[18];
    int id_cartier;
    int strada;
    int numar;
    int prioritate;
    float greutate;
    char *mesaj;
    int codif_mesaj;
} Pachet;

// structura pentru postas
typedef struct
{
    int id;
    int nr_pachete;
    Pachet pachete[50];
} Postas;

// structura pentru postasul sef
typedef struct
{
    Postas postasi[32];
} PostasSef;

// -----------------------------  Cerinta I  ---------------------------------

//  functia care citeste datele
void citire(int *task, int *nrC, Cartier **cartiere, int *nrP, Pachet **pachete)
{
    int i, j;
    scanf("%d", task); // nr cerintei
    scanf("%d", nrC);  // nr de cartiere si postasi

    // alocare pentru cartier
    *cartiere = (Cartier *)malloc(*nrC * sizeof(Cartier));

    // numele cartierelor
    for (i = 0; i < *nrC; i++)
    {
        char aux[100]; // citesc cu un auxiliar (local)
        scanf("%s", aux);

        (*cartiere)[i].id = i;
        (*cartiere)[i].nume = (char *)malloc(strlen(aux) * sizeof(char) + 1); // alocare pentru numele cartierului
        strcpy((*cartiere)[i].nume, aux);                                     // numele devine aux
    }

    scanf("%d", nrP); // nr de pachete

    // alocare pentru pachet
    *pachete = (Pachet *)malloc(*nrP * sizeof(Pachet));

    //  detaliile fiecarui pachet
    for (i = 0; i < *nrP; i++)
    {
        // adresa pachetului (18 valori 0 sau 1)
        for (j = 0; j < 18; j++)
            scanf("%d", &(*pachete)[i].adresa[j]);

        // prioritatea pachetului
        scanf("%d", &(*pachete)[i].prioritate);

        // greutatea pachetului
        scanf("%f", &(*pachete)[i].greutate);

        // mesajul pachetului
        char aux[100];
        getchar(); // citesc un newline pentru ca anterior am avut o valoare intreaga
                   // iar daca nu procedez astfel aux va fi = '\n'

        fgets(aux, sizeof(aux), stdin); // citesc linia de la tastatura cu fgets

        // elimin caracterul '\n' adaugat de fgets cu '\0' (termen de sir) daca exista
        aux[strcspn(aux, "\n")] = '\0';

        (*pachete)[i].mesaj = (char *)malloc(strlen(aux) + 1); // aloc memorie pentru mesaj
        strcpy((*pachete)[i].mesaj, aux);                      // copiez mesajul in structura pachetului

        // Fiecare pachet are o adresa reprezentata printr un vector de 18 pozitii ce retine doar valori 0 sau 1
        // deci id ul cartierului este setat pe baza adresei pachetului
        (*pachete)[i].id = i;
    }
}

// functia care afiseaza datele corepunzatoare cerintei 1
void afisare_cerinta_1(int nrC, Cartier *cartiere, int nrP, Pachet *pachete)
{
    int i, j;
    // afisarea id ului si numelui cartierelor
    for (i = 0; i < nrC; i++)
        printf("%d %s\n", cartiere[i].id, cartiere[i].nume);

    // afisarea pachetelor
    for (i = 0; i < nrP; i++)
    {
        // id ul pachetului
        printf("%d\n", pachete[i].id);

        // adresa pachetului
        for (j = 0; j < 18; j++)
        {
            printf("%d", pachete[i].adresa[j]);
            if (j < 17)
                printf(" ");
        }

        printf("\n");

        // prioritatea si greutatea cu 3 zecimale
        printf("%d %.3f\n", pachete[i].prioritate, pachete[i].greutate);

        // mesajul pachetului
        printf("%s\n", pachete[i].mesaj);
    }
}

// -----------------------------  Cerinta II  ---------------------------------

// functie pentru a extrage cartierul strada si nr din adresa pachetului
void extrage_din_adresa(Pachet **pachete, int nrP)
{
    int i;
    for (i = 0; i < nrP; i++)
    {
        // primele 5 pozitii = id cartier
        (*pachete)[i].id_cartier = (*pachete)[i].adresa[0] * 16 + (*pachete)[i].adresa[1] * 8 + // 16 = 2^4, 8 = 2^3
                                   (*pachete)[i].adresa[2] * 4 + (*pachete)[i].adresa[3] * 2 +  // 4 = 2^2 , 2 = 2^1
                                   (*pachete)[i].adresa[4] * 1;                                 // 1 = 2^0

        // urmatoarele 5 = strada
        (*pachete)[i].strada = (*pachete)[i].adresa[5] * 16 + (*pachete)[i].adresa[6] * 8 + // 16 = 2^4, 8 = 2^3
                               (*pachete)[i].adresa[7] * 4 + (*pachete)[i].adresa[8] * 2 +  // 4 = 2^2 , 2 = 2^1
                               (*pachete)[i].adresa[9] * 1;                                 // 1 = 2^0

        // urmatoarele 8 = nr
        (*pachete)[i].numar = (*pachete)[i].adresa[10] * 128 + (*pachete)[i].adresa[11] * 64 + // 128 = 2^7, 8 = 2^6
                              (*pachete)[i].adresa[12] * 32 + (*pachete)[i].adresa[13] * 16 +  // 32 = 2^5, 16 = 2^4
                              (*pachete)[i].adresa[14] * 8 + (*pachete)[i].adresa[15] * 4 +    // 8 = 2^3, 4 = 2^2
                              (*pachete)[i].adresa[16] * 2 + (*pachete)[i].adresa[17] * 1;     // 2 = 2^1, 1 = 2^0
    }
}

// functia care afiseaza datele corepunzatoare cerintei 2
void afisare_cerinta_2(Pachet *pachete, int nrP)
{
    int i;
    for (i = 0; i < nrP; i++)
    {
        // afisez id ul pachetului
        printf("%d\n", pachete[i].id);

        // afisez id_cartier strada si nr
        printf("%d %d %d\n", pachete[i].id_cartier, pachete[i].strada, pachete[i].numar);
    }
}

// -----------------------------  Cerinta III  ---------------------------------

// functie pentru a distribui pachetele postasilor
void distribuire_pachete(int nrC, int nrP, Pachet *pachete, Postas **postasi)
{
    int i;
    // aloc memorie pentru vectorul de ppostasi
    *postasi = (Postas *)malloc(nrC * sizeof(Postas));

    // initializez structurile de postasi
    for (i = 0; i < nrC; i++)
    {
        (*postasi)[i].id = i;         // id postas = id cartier
        (*postasi)[i].nr_pachete = 0; // 0 pachete initial
    }

    // distribui pachetele catre postasi
    for (i = 0; i < nrP; i++)
    {
        (*postasi)[pachete[i].id_cartier].pachete[(*postasi)[pachete[i].id_cartier].nr_pachete] = pachete[i]; // adaug pachet
        (*postasi)[pachete[i].id_cartier].nr_pachete++;                                                       // incrementez nr de pachete
    }
}

// functia care afiseaza datele corepunzatoare cerintei 3
void afisare_cerinta_3(int nrC, Postas *postasi)
{
    int i, j;
    for (i = 0; i < nrC; i++)
    {
        // id postas si nr de pachete
        printf("%d %d\n", postasi[i].id, postasi[i].nr_pachete);

        // id urile pachetelor
        for (j = 0; j < postasi[i].nr_pachete; j++)
        {
            printf("%d", postasi[i].pachete[j].id);
            if (j < postasi[i].nr_pachete - 1)
                printf(" ");
        }

        if (postasi[i].nr_pachete != 0)
            printf("\n");
    }
}
// -----------------------------  Cerinta IV  ---------------------------------

// functia care sorteaza pachetele
void sorteaza_pachete(Postas *postasi, int nrC)
{
    int i, j, k;
    for (i = 0; i < nrC; i++)
    {
        // folosesc Bubble Sort
        for (j = 0; j < postasi[i].nr_pachete - 1; j++)
        {
            int gata = 1;

            for (k = 0; k < postasi[i].nr_pachete - j - 1; k++)
            {
                // compar prioritatea si greutatea direct
                if (postasi[i].pachete[k].prioritate < postasi[i].pachete[k + 1].prioritate ||
                    (postasi[i].pachete[k].prioritate == postasi[i].pachete[k + 1].prioritate &&
                     postasi[i].pachete[k].greutate < postasi[i].pachete[k + 1].greutate))
                {
                    // iterschimb pachetele
                    Pachet aux = postasi[i].pachete[k];
                    postasi[i].pachete[k] = postasi[i].pachete[k + 1];
                    postasi[i].pachete[k + 1] = aux;

                    gata = 0; // lista nu e sortata complet
                }
            }

            // lista era deja sortata
            if (gata)
                break;
        }
    }
}

// functia care afiseaza datele corepunzatoare cerintei 4
void afisare_cerinta_4(Postas *postasi, int nrC)
{
    int i, j;
    for (i = 0; i < nrC; i++)
    {
        // id postas si nr de pachete
        printf("%d %d\n", postasi[i].id, postasi[i].nr_pachete);

        // id urile pachetelor
        for (j = 0; j < postasi[i].nr_pachete; j++)
        {
            printf("%d", postasi[i].pachete[j].id);
            if (j < postasi[i].nr_pachete - 1)
                printf(" ");
        }

        if (postasi[i].nr_pachete != 0)
            printf("\n");
    }
}

// -----------------------------  Cerinta V  ---------------------------------

// functie de prelucrare a mesajului

void prelucrare_mesaj(const char *mesaj_original, char *mesaj_final)
{
    char copie_mesaj[101];
    strcpy(copie_mesaj, mesaj_original); // salvez mesajul original intr o copie deoarece acesta
                                         // va fi distrus dupa utilizarea strtok

    char *cuvinte[100];
    int nr_cuvinte = 0;

    // elimin semnele de punctuatie si impart in cuvinte
    char *p = strtok(copie_mesaj, " ,.!?:;\n");
    while (p != NULL)
    {
        cuvinte[nr_cuvinte] = (char *)malloc(strlen(p) + 1); // alocare pentru cuvant
        strcpy(cuvinte[nr_cuvinte], p);
        nr_cuvinte++;
        p = strtok(NULL, " ,.!?:;\n");
    }

    // construiesc mesajul inversat concatenand la mesaj_final fiecare cuvand in parte invers dpdv al aparitiei
    mesaj_final[0] = '\0';
    int i;
    for (i = nr_cuvinte - 1; i >= 0; i--)
    {
        strcat(mesaj_final, cuvinte[i]);
        free(cuvinte[i]); // eliberez memoria alocata pentru fiecare cuvant
    }
}

// functie de calcul al codului unui mesaj procesat
int calculare_cod(const char *mesaj_procesat, int strada, int numar)
{
    int cod = 0, i, impartitor;

    // calculez suma produselor (ASCII * pozitie)
    for (i = 0; mesaj_procesat[i] != '\0'; i++)
        cod = cod + mesaj_procesat[i] * i;

    // aplic formula finala
    impartitor = strada * numar + 1;
    return cod % impartitor;
}

// functie care codifica mesajul
void codifica_mesaje(Postas *postasi, int nrC)
{
    int i, j;
    for (i = 0; i < nrC; i++)
    {
        for (j = 0; j < postasi[i].nr_pachete; j++)
        {
            // prelucrare mesaj
            char mesaj_procesat[101];
            prelucrare_mesaj(postasi[i].pachete[j].mesaj, mesaj_procesat);

            // calculare cod final
            postasi[i].pachete[j].codif_mesaj = calculare_cod(mesaj_procesat,
                                                              postasi[i].pachete[j].strada, postasi[i].pachete[j].numar);
        }
    }
}

// functia care afiseaza datele corepunzatoare cerintei 5
void afisare_cerinta_5(Postas *postasi, int nrC)
{
    int i, j;
    for (i = 0; i < nrC; i++)
    {

        // afisez id ul postasului si nr de pachete
        printf("%d %d\n", postasi[i].id, postasi[i].nr_pachete);

        // afisez id ul pachetului si codul mesajului
        for (j = 0; j < postasi[i].nr_pachete; j++)
        {
            printf("%d %d\n", postasi[i].pachete[j].id, postasi[i].pachete[j].codif_mesaj);
        }
    }
}

// -----------------------------  Cerinta VI  ---------------------------------

// functie care verifica daca codul contine o cifra din id
int contine_cifra(int cod, int id)
{
    int copie_id;
    while (cod > 0)
    {
        copie_id = id;
        while (copie_id > 0)
        {
            if (copie_id % 10 == cod % 10) // se compara fiecare cifra din cod cu fiecare din id
                return 1;
            copie_id = copie_id / 10;
        }
        cod = cod / 10;
    }
    return 0;
}

//  functie auxiliara care sa altereze (modifice) codul unui mesaj
int alterare_cod(int cod, int id)
{
    // id = 0 inversez bit ul de pe pozitia 0 => tot codul
    if (id == 0)
    {
        cod = ~cod & 1;
        return cod;
    }

    // descopun id in factori primi si ii retin intr un vector
    int factori[32] = {0}, nr_factori = 0, d = 2; // vectorul este de maximum 32 (4(int)*8)

    if (id == 1)
        factori[nr_factori++] = 1;

    // descompunere in factori primi
    while (id > 1)
    {
        while (id % d == 0)
        {
            factori[nr_factori++] = d;
            id = id / d;
        }
        if (d == 2)
            d++;
        else
            d = d + 2;
    }

    // ma folosesc de o masca pentru a inversa bitii
    int masca = 0, i;
    for (i = 0; i < nr_factori; i++)
        masca = masca | (1 << factori[i]); // creare masca

    // inversez bitii
    return cod = cod ^ masca;

    return cod;
}

// functie care altereaza doar acele coduri care au cel putin o cifra care se regaseste in id ul postasului
void modifica_coduri_postasi(Postas **postasi, int nrC)
{

    int i, j;
    for (i = 0; i < nrC; i++)
        for (j = 0; j < (*postasi)[i].nr_pachete; j++)
            if (contine_cifra((*postasi)[i].pachete[j].codif_mesaj, (*postasi)[i].id)) // verific daca codul contine o cifra din id
                (*postasi)[i].pachete[j].codif_mesaj = alterare_cod((*postasi)[i].pachete[j].codif_mesaj, (*postasi)[i].id);
}

// functia care afiseaza datele corepunzatoare cerintei 6 == functia care afiseaza datele corepunzatoare cerintei 5

// -----------------------------  Cerinta VII  ---------------------------------

// functia care calculeaza scorul fiecarui postas
void calculare_scor(Postas *postasi, int nrC)
{
    int i, j;
    for (i = 0; i < nrC; i++)
    {
        int nr_pachete_corecte = 0;

        for (j = 0; j < postasi[i].nr_pachete; j++)
        {
            // recalculez codul mesajului original
            char mesaj_procesat[101];
            prelucrare_mesaj(postasi[i].pachete[j].mesaj, mesaj_procesat);
            int cod_original = calculare_cod(mesaj_procesat, postasi[i].pachete[j].strada, postasi[i].pachete[j].numar);

            // compar codul original cu codul nou
            if (postasi[i].pachete[j].codif_mesaj == cod_original)
                nr_pachete_corecte++;
        }

        // calculez scorul
        float scor;
        if (postasi[i].nr_pachete > 0)
            scor = (float)nr_pachete_corecte / postasi[i].nr_pachete;
        else
            scor = 0.0;

        // afisez cu 3 zecimale
        printf("%d %.3f\n", postasi[i].id, scor);
    }
}

int main()
{
    int nrC, nrP, task, i;
    Cartier *cartiere = NULL;
    Pachet *pachete = NULL;
    Postas *postasi = NULL;

    // citesc datele de la tastatura
    citire(&task, &nrC, &cartiere, &nrP, &pachete);

    // functia de afisare pentru cerinta 1
    if (task == 1)
        afisare_cerinta_1(nrC, cartiere, nrP, pachete);

    // extrag cartierul, strada si nr din adresa pachetului
    extrage_din_adresa(&pachete, nrP);

    // functia de afisare pentru cerinta 2
    if (task == 2)
        afisare_cerinta_2(pachete, nrP);

    // functie care distribuie pachetele postasilor
    distribuire_pachete(nrC, nrP, pachete, &postasi);

    // functia de afisare pentru cerinta 3
    if (task == 3)
        afisare_cerinta_3(nrC, postasi);

    // functie care sorteaza pachete
    sorteaza_pachete(postasi, nrC);

    // functia de afisare pentru cerinta 4
    if (task == 4)
        afisare_cerinta_4(postasi, nrC);

    // functie care codifica mesaje
    codifica_mesaje(postasi, nrC);

    // functia de afisare pentru cerinta 5
    if (task == 5)
        afisare_cerinta_5(postasi, nrC);

    // functia care altereaza codurile care au o cifra comuna cu id ul postasului
    modifica_coduri_postasi(&postasi, nrC);

    // functia de afisare pentru cerinta 6 == aceeasi ca la 5
    if (task == 6)
        afisare_cerinta_5(postasi, nrC);

    // functia de calculare scor + afisare
    if (task == 7)
        calculare_scor(postasi, nrC);

    // eliberez memoria alocata
    for (i = 0; i < nrC; i++)
        free(cartiere[i].nume);
    free(cartiere);

    for (i = 0; i < nrP; i++)
        free(pachete[i].mesaj);
    free(pachete);

    free(postasi);

    return 0;
}
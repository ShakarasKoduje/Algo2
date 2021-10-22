#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Rekord rekord_t;

struct Rekord{
    int wartosc;
    char znak;
    float zmiennoprzecinkowa;
    
};

//Funkcje
void WczytajDane(unsigned int *, char *);

rekord_t **Losowanie(const unsigned int);
void SortowanieB(rekord_t **, const unsigned int);
//int ZliczanieZnakow(rekord_t **, const unsigned int *, const char *);
void ZliczanieZnakow(rekord_t **, const unsigned int *, const char *);

void Kasowanie(rekord_t **, const unsigned int);

int main(){
    clock_t begin, end; double time_spend;
    

    unsigned int N = 7; char X = 'R'; //unsigned int wystapieniaX;

    WczytajDane(&N, &X);
    begin = clock();
    rekord_t **tablica = Losowanie(N);

    SortowanieB(tablica, N);
    for(int i = 0; i < 20; i++){
        printf("%d | ID: [ %.1f ] wartosc: %d, znak: %c",i, tablica[i]->zmiennoprzecinkowa, tablica[i]->wartosc, tablica[i]->znak);
        puts("");
        free(tablica[i]);
    }
    //wystapieniaX = 
    ZliczanieZnakow(tablica, &N, &X);
    //printf("%d \n", wystapieniaX);
    Kasowanie(tablica,N);    

    puts("");



    printf("SUKCES\n");
    end = clock();
    time_spend = (double)(end - begin)/(CLOCKS_PER_SEC/1000);
    printf("Czas jaki uplynal: %.5lf ms", time_spend);
    return 0;
}


rekord_t **Losowanie(const unsigned int N){
    rekord_t **tablica = (rekord_t**)malloc(N * sizeof(rekord_t));
    for(int i = 0; i < N; i++){
        tablica[i] = (rekord_t*)malloc(sizeof(rekord_t));
        //int numerlitery = rand()%18+66;
        
        //char litera = numerlitery;
        tablica[i]->wartosc = rand() % 10001 + (-1000);
        tablica[i]->znak = rand()%18+66;//litera;
        tablica[i]->zmiennoprzecinkowa = 1001+i;
    }
    return tablica;
}

void SortowanieB(rekord_t **tab, const unsigned int N){
    char zmiana; //zmienna kontrolująca czy doszło do zamiany miejsc.
    unsigned int nieposortowanych = N; //liczba nieposortowanych struktur.
    rekord_t *tmp = (rekord_t*)malloc(sizeof(rekord_t));
    do{
        zmiana = 0;

        for(int i =0; i < nieposortowanych-1; ++i){
            if((*tab[i]).wartosc > (*tab[i+1]).wartosc){               
                tmp = tab[i+1];
                tab[i+1] = tab[i];
                tab[i] = tmp;
                zmiana = 1;
            }
            zmiana = 1;
            
        }
        

        --nieposortowanych;
    }while(zmiana);
   free(tmp);
}

void Kasowanie(rekord_t **tab, const unsigned int N){
    for(int i = 0; i < N; i++){
        free(tab[i]);
    }
    free(tab);
}
void ZliczanieZnakow(rekord_t **tab, const unsigned int *N, const char *X){
    unsigned int zliczoneX = 0;

    for(int i = 0; i < *N; i++){
        if(tab[i]->znak == *X){
            zliczoneX++;
        }
    }
    printf("ZNAK : %c, wystapil %d razy \n", *X, zliczoneX);
 
}

void WczytajDane(unsigned int *n, char *x){
    FILE *f;
    f = fopen("inlab01.txt", "r");
    fscanf(f, "%d %c", n, x);
    
    fclose(f);
}
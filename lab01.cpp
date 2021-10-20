#include <iostream>
#include <fstream>
#include <random>
#include <ctime>


using namespace std;

//Struktura z danymi
struct Rekord{
    int wartosc;
    char znak;
    float zmiennoprzecinkowa;
};

//Funkcje
void WczytajDane(int &, char &);
Rekord **Losowanie(const int);
void SortowanieB(Rekord *[], const int);
int ZliczanieZnakow(Rekord **, const int, char);
void Kasowanie(Rekord **, const int);

int main(){
    int N = 0;
    char X = 0;

    //Wczytanie danych z pliku.
    WczytajDane(N,X);
   

    srand(time(NULL));    
    clock_t begin, end; double time_spend;
    begin = clock();

    //Losowanie struktur do tablicy.
    Rekord **tablica = Losowanie(N);

    //Sortowanie tablicy (porządek rosnący).
    SortowanieB(tablica, N);
    //Wypisanie pierwszych 20 struktur (porządek rosnący).
    for(auto i = 0; i < 20; i++) cout<<"Posortowane struktury danych Rekord według pola 'wartosc': "<<tablica[i]->wartosc<<endl;
    
    //zliczanie wystąpień znaków.
    auto znaki = ZliczanieZnakow(tablica, N, X);
    cout<<"ZNAK "<< X << " wystąpił: " << znaki <<" razy."<<endl;

    //Zwalnianie pamięci.
    Kasowanie(tablica, N);


    end = clock();
    
    time_spend = (double)(end - begin)/ CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << time_spend << endl;
    return 0;
}

void WczytajDane(int &N, char &X){
    ifstream plik;
    plik.open("inlab01.txt");
    if(!plik) {
        cout<<"Nie można odczytać pliku. Awaryjnie tworzy 200 struktur, z szukanym znakiem 'F'."<<endl;
        N = 200;
        X = 'F';
    }
    else{
        cout<<"Pomyślne załadowanie pliku"<<endl;
        plik>>N;
        plik>>X;
    }
    plik.close();
}

Rekord **Losowanie(const int N){
    Rekord **tablica = new Rekord*[N];
    for(int i = 0; i < N; i++){
        tablica[i] = new  Rekord;
        int numerlitery = rand()%18+66;
        char litera = numerlitery;
        tablica[i]->wartosc = rand() % 10001 + (-1000);
        tablica[i]->znak = litera;
        tablica[i]->zmiennoprzecinkowa = 1001+i;
    }
    return tablica;
}

void SortowanieB(Rekord *tablica[], const int N){
    bool zmiana; //zmienna kontrolująca czy doszło do zamiany miejsc.
    auto nieposortowanych = N; //liczba nieposortowanych struktur.
    do{
        zmiana = 0;
        for(int i =0; i < nieposortowanych-1; ++i){
            if(tablica[i]->wartosc > tablica[i+1]->wartosc){               
                swap(tablica[i], tablica[i+1]);
                zmiana = 1;
            }
        }
        --nieposortowanych;
    }while(zmiana);
   
}

void Kasowanie(Rekord **tab, const int N){
    for(int i = 0; i < N; i++) {        
        delete []tab[i];
        tab[i] = nullptr;        
    }    
    delete []tab;
    tab=nullptr;    
}

int ZliczanieZnakow(Rekord **tab, const int N, char X){
    int wystapienia = 0;
    for(int i = 0; i < N; i++){
        if(tab[i]->znak == X) ++wystapienia;
    }
    return wystapienia;
}
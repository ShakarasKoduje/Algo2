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
Rekord **Losowanie2(const int, int [],int&);

void SortowanieB(Rekord *[], const int);
void Sortowanie(Rekord *[], const int);
void ZliczanieZnakow(Rekord **, const int, char);
void Kasowanie(Rekord **, const int);

int *StworzyZakresINT(const int);
int *UsunZZakresu(int *, int &, int);


int main(){
    int N = 0; char X = 0; int rozmiar = 10001;
    srand(time(NULL));    
    clock_t begin, end; double time_spend; 
    // tablica z intami od -1000 do 9000.
    int *zakresINT = StworzyZakresINT(rozmiar);

    //Pobranie danych z pliku inlab01.txt
    WczytajDane(N,X);
   
    begin = clock();

    //Losowanie struktur do tablicy. Bez powtarzania dla wartosci int.
    Rekord ** tablica = Losowanie2(N, zakresINT, rozmiar);

    //Sortowanie Bąbelkowe
    Sortowanie(tablica, N);

    //Wypisanie pierwszych 20 struktur (porządek rosnący).
    for(auto i = 0; i < 20; i++) cout<<"Posortowane struktury danych Rekord według pola [id] 'wartosc': "<< "["<< tablica[i]->zmiennoprzecinkowa<<"] "<<tablica[i]->wartosc<<endl;
    
    ZliczanieZnakow(tablica, N, X);

    //Zwalnianie pamięci.
    Kasowanie(tablica, N);


    end = clock();
    
    time_spend = (double)(end - begin)/ (CLOCKS_PER_SEC/1000);
    cout << "Czas wykonania: " << time_spend <<"ms" << endl;
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

//Losowanie sturktur bez ominiecia powtarzania dla wartosci int
Rekord **Losowanie(const int N){
    Rekord **tablica = new Rekord*[N];
    for(int i = 0; i < N; i++){
        tablica[i] = new  Rekord;
        tablica[i]->wartosc = rand() % 10001 + (-1000);
        tablica[i]->znak = rand()%18+66;
        tablica[i]->zmiennoprzecinkowa = 1001+i;
    }
    return tablica;
}
//Losowanie sturkturz ominieciem powtarzania dla wartosci int
Rekord **Losowanie2(const int N, int zakres[], int &rozmiarZakresu){
    Rekord **tablica = new Rekord*[N];
    
    int los;
    for(int i = 0; i < N; i++){
        tablica[i] = new  Rekord;
       
        los = rand() % rozmiarZakresu;
        tablica[i]->wartosc = zakres[los];
        zakres = UsunZZakresu(zakres, rozmiarZakresu, los);
        tablica[i]->znak = rand()%18+66;
        tablica[i]->zmiennoprzecinkowa = 1001+i;
    }
    return tablica;
}

void SortowanieB(Rekord *tablica[], const int N){
    bool zmiana; //zmienna kontrolująca czy doszło do zamiany miejsc.
    auto nieposortowanych = N; //liczba nieposortowanych struktur.
    
    do{
        zmiana = 0;
        for(auto i =0; i < nieposortowanych-1; ++i){
            if(tablica[i]->wartosc > tablica[i+1]->wartosc){               
                swap(tablica[i], tablica[i+1]);
                zmiana = 1;
            }
        }
        --nieposortowanych;
    }while(zmiana);
   
}

void Sortowanie(Rekord *tablica[], const int N){
    bool zmiana; //zmienna kontrolująca czy doszło do zamiany miejsc.
    auto nieposortowanych = N; //liczba nieposortowanych struktur.
    Rekord * tmp = new Rekord;
    do{
        zmiana = 0;
        for(auto i =0; i < nieposortowanych-1; ++i){
            if(tablica[i]->wartosc > tablica[i+1]->wartosc){               
                tmp = tablica[i];
                tablica[i] = tablica[i+1];
                tablica[i+1] = tmp;
                zmiana = 1;
            }
        }
        --nieposortowanych;
    }while(zmiana);
   
}


void Kasowanie(Rekord **tab, const int N){
    for(auto i = 0; i < N; i++) {        
        delete []tab[i];
        tab[i] = nullptr;        
    }    
    delete []tab;
    tab=nullptr;    
}

void ZliczanieZnakow(Rekord **tab, const int N,const char X){
    int wystapienia = 0;
    for(auto i = 0; i < N; i++){
        if(tab[i]->znak == X) ++wystapienia;
    }
    cout<<"ZNAK "<< X << " wystąpił: " << wystapienia<<" razy."<<endl;
    //return wystapienia;
}

int *StworzyZakresINT(const int rozmiar){
    
    int *intydolosowania = new int[rozmiar];
    for(auto i = 0; i < 10001; i++){
        int wartosc = i-1000;
        if(i%100 == 0) cout << "Wartość: "<< wartosc <<endl;
        intydolosowania[i] = wartosc;
    }
    return  intydolosowania;
}

int * UsunZZakresu(int * zakres, int &rozmiar, int index){
    int *tmp = new int[rozmiar-1]; int j = 0;
    for(auto i = 0; i < rozmiar; i++){
        if(i == index) continue;
        tmp[j] = zakres[i];
        ++j;
    } 
    delete zakres;
    zakres = tmp;
    --rozmiar;
    return zakres;
}


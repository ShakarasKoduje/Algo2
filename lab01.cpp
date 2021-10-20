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
/*

Zdefiniuj typ strukturalny (odpowiednik abstrakcyjnego typu rekordowego) zawierający 3 pola,
odpowiednio: int, char, float. Następnie zaimplementuj funkcje do obsługi zdefiniowanego typu:

 losowanie – funkcja:
o pobiera jako argument liczbę N struktur, które mają zostać utworzone;
o dynamicznie alokuje pamięć na tablicę N wskaźników na struktury;
o następnie alokuje kolejno N struktur, przypisując uzyskane adresy do kolejnych komórek
utworzonej wcześniej tablicy;
o pole typu int jest ustawiane na wartość losową pomiędzy -1000 a 9000; pole typu char
jest ustawiane na losową literę z zakresu od B do S; zaś pole typu float jest ustawiane na
wartość 1000 + numer kolejny struktury (od 1 do N);
o funkcja zwraca adres tablicy.
UWAGA: Zadbaj o to, by w każdym kolejnym uruchomieniu programu wartości losowe były
odmienne (np. wykorzystując funkcję biblioteczną srand()), oraz o to, by każda spośród N
struktur miała inną wartość pola typu int.

 kasowanie – funkcja:
o pobiera wskaźnik na tablicę struktur i jej wielkość (liczba przechowywanych wskaźników
na struktury);
o zwalniana jest najpierw kolejno pamięć zajęta przez wszystkie przechowywane struktury;
o następnie zwalniana jest również pamięć zajęta przez samą tablicę wskaźników na
struktury.

 sortowanie – funkcja:
o pobiera wskaźnik na tablicę struktur i jej wielkość;
o elementy tablicy (wskaźniki na struktury) sortowane są zgodnie z algorytmem sortowania
bąbelkowego/pęcherzykowego według pola zawierającego składową typu int w porządku
rosnącym, przy czym algorytm sortowania musi być zaimplementowany w wersji z
iteracjami ograniczonymi (pętle for) oraz mechanizmem kończącym sortowanie po
stwierdzeniu, że tablica już jest posortowana.

 zliczanie znaków – funkcja:
o pobiera wskaźnik na tablicę struktur oraz jej wielkość oraz znak, którego liczbę wystąpień
należy wyznaczyć;
o przeszukuje kolejno struktury w poszukiwaniu zadanego znaku i w przypadku jego
znalezienia zwiększa licznik wystąpień o 1.
o zwraca liczbę wystąpień znaku.

Program po uruchomieniu wczytuje plik wejściowy inlab01.txt

Plik inlab01.txt zawiera kolejno (rozdzielone spacją): liczbę struktur N do wylosowania z
zakresu od 1 do 10000 i znak X do wyszukania i wyznaczenia liczby jego wystąpień.
Następnie wywoływana jest sekwencja funkcji (dalej w funkcji main())

 czas start;
 losowanie N elementów;
 sortowanie;
 zliczanie znaków X;
 kasowanie;
 czas stop.
Program wypisuje na konsoli listę pierwszych 20-tu posortowanych struktur, liczbę wyszukanych
znaków X oraz czas wykonania całego programu. 
*/
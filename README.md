# Algo2
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

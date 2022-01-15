// ALGO2 IN1 20A LAB04
// Marcin Ficek
// fm09107@zut.edu.pl 


#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;

template<typename T>
class Node{
    public:
        int Index;
        int Key;
        int Height;
        T data;
        Node<T> *Left;
        Node<T> *Right;
        Node<T> *Parent;
};

template<typename T>
class BSTree{
    public:
        BSTree();
        int Size;
        void Insert(int, T&);
        void PrintInOrder();
        bool Search(int);
        int FindMax();
        int FindMin();
        int Succesor(int);
        void Remove(int);
        //wyswietlanie drzewa
        void SetHeight();
        int FindHeight();

    protected:
        Node<T> *Insert(Node<T>*, int, T&);
        void PrintInOrder(Node<T> *);
        Node<T> *Search(Node<T> *, int);
        int FindMax(Node<T> *);
        int FindMin(Node<T> *);
        int Succesor(Node<T> *);
        Node<T> * Remove(Node<T> *, int);
        //wyswietlanie drzewa
        void SetHeight(Node<T> *, int);
        int FindHeight(Node<T> *);

    private:
        Node<T> * root;

};


int main(){

//drzewo musi zawierać wskaznik na korzeń oraz aktualny rozmiar.
    srand(time(NULL));   
    clock_t begin, end; double time_spend;

    BSTree<char> * bst = new BSTree<char>();
   
    const int MAX_ORDER = 4;
    for(int o = 1; o < MAX_ORDER; o++){
        const int n = pow(10, o); int i = 0;
        begin = clock();
        for(; i < n; i++){
            int k = rand()%100+1;
            char d = rand()%18+66;
            bst->Insert(k, d);
        }

        bst->SetHeight();
        end = clock();
        time_spend = (double)(end - begin)/ (CLOCKS_PER_SEC/1000);
        cout<<"Czas utworzenia "<< n<<" węzłów w drzewie BTS, wyniosl w ms: "<<time_spend<<endl;
        cout<<"Poszukiwanie klucza o wartości 31"<<endl;
        cout<<"Rozmiar drzewa BST: "<<bst->Size<<endl;
        bst->SetHeight();
        begin = clock();
        bool searchResult; int hits = 0;
        const int m = pow(10, MAX_ORDER/2);
        for(int i = 0; i < m; i++){
            searchResult = bst->Search(31);
            if(searchResult) {
                hits++;
                bst->Remove(31);
            }
        }
        end = clock();
        time_spend = (double)(end - begin)/ (CLOCKS_PER_SEC/1000);
        cout<<"Liczba trafien: "<<hits<<endl;
        cout<<"Czas wyszukiwania wyniosl w ms: "<<time_spend<<endl;
    }

    cout<<"Największy klucz w drzewie: " << bst->FindMax()<<endl;
    cout<<"Najmniejszy klucz w drzewie: " << bst->FindMin()<<endl;
    cout<<"Rozmiar drzewa BST: "<<bst->Size<<endl;
    bst->SetHeight();

    //bst->PrintInOrder(); //<- odkomentować dla małych drzew.
    cout<<"Wysokość drzewa BST: "<< bst->FindHeight()<<endl;
    //Kończenie programu.


 
    delete bst;
    cout<<"Koniec programu."<<endl;
    return EXIT_SUCCESS;
}


/*
    Metody klas

*/

//Metody wstawiania węzła do drzewa BST.
template<typename T>
Node<T> * BSTree<T>::Insert(Node<T> * node, int key, T& data){

    if(node == NULL){
        node = new Node<T>();
        Size++;
        node->Key = key;
        node->data = data;
        node->Left = NULL;
        node->Right = NULL;
        node->Parent = NULL;

    }
    else if(node->Key < key){
        node->Right = Insert(node->Right, key, data);
        node->Right->Parent = node;

    }
    else{
        node->Left = Insert(node->Left, key, data);
        node->Left->Parent = node;   

     
    }
    
    return node;
}

template<typename T>
void BSTree<T>::Insert(int key, T& data){
    root = Insert(root, key, data);

}

//Wyznaczenie wysokości węzłów.
template<typename T>
void BSTree<T>::SetHeight(){
    int counter = 0;
    SetHeight(root, counter);
}

template<typename T>
void BSTree<T>::SetHeight(Node<T> * node, int counter){
    if(node == NULL) return;
    int left,right;
    left = counter +1;
    right = counter +1;
    SetHeight(node->Left, left);
    node->Height = counter;
    SetHeight(node->Right, right);

}

template<typename T>
int BSTree<T>::FindHeight(Node<T> *node){
    if(node == NULL) return 0;
    else{
        int left = FindHeight(node->Left);
        int right = FindHeight(node->Right);
        return max(left,right)+1;
    }
}

template<typename T>
int BSTree<T>::FindHeight(){
     return FindHeight(root);
}

//Wypisywanie drzewa w porządku.

template<typename T>
void BSTree<T>::PrintInOrder(){

    cout<<"Drzewo BST:\nsize: "<<Size<<"\n{\n";
    PrintInOrder(root);
    cout<<"}"<<endl;
}

template<typename T>
void BSTree<T>::PrintInOrder(Node<T> *node){
    if(node == NULL) return;
    PrintInOrder(node->Left);
    //node->Height = counter;
    cout<<"\n"<<node->Height<<" [Key: "<<node->Key<< " data: "<<node->data<<" ]";
    if(node->Parent != NULL) cout<<" p:("<<node->Parent->Key<<", "<<node->Parent->data<<")";
    else cout<<" p:(NULL, NULL)";
    if(node->Right != NULL) cout<<" r:("<<node->Right->Key<<", "<<node->Right->data<<")";
    else cout<<" r:(NULL, NULL)";
    if(node->Left != NULL) cout<<" l:("<<node->Left->Key<<", "<<node->Left->data<<")";
    else cout<<" l:(NULL, NULL)";
    cout<<endl;

    PrintInOrder(node->Right);
}

//Wyszukiwanie węzła z poszukiwanym kluczem

template<typename T>
Node<T> * BSTree<T>::Search(Node<T> * node, int key){
    if (node == NULL) return NULL;
    else if(node->Key == key) return node;
    else if(node->Key < key) return Search(node->Right, key);
    else return Search(node->Left, key);    
}

template<typename T>
bool BSTree<T>::Search(int key){
    Node<T> * node = Search(root, key);

    return node == NULL ? false : true;
}

//Wynajdywanie Maksimum i Minimum

template<typename T>
int BSTree<T>::FindMax(Node<T> *node){
    if(node == NULL) return -1;
    else if(node->Right == NULL) return node->Key;
    else return FindMax(node->Right);
}

template<typename T>
int BSTree<T>::FindMax(){
     return FindMax(root);
}

template<typename T>
int BSTree<T>::FindMin(Node<T> *node){
    if(node == NULL) return -1;
    else if(node->Left == NULL) return node->Key;
    else return FindMin(node->Left);
}

template<typename T>
int BSTree<T>::FindMin(){
     return FindMin(root);
}

//Wskazywanie Nastepnika
template<typename T>
int BSTree<T>::Succesor(Node<T> *node){
    if(node->Right != NULL) return FindMin(node->Right);
    else{
        Node<T> *current = node;
        Node<T> *parent = node->Parent;

        while((parent != NULL) && (current == parent->Right)){
            current = parent;
            parent = current->Parent;

        }
        return parent == NULL ? -1 : parent->Key;
    }
}

template<typename T>
int BSTree<T>::Succesor(int key){
    Node<T> *node = Search(root, key);
    return node == NULL ? -1 : Succesor(node);
}

//Usuwanie z drzewa
template<typename T>
Node<T> *BSTree<T>::Remove(Node<T> *node, int key){
    if(node==NULL) return NULL;

    if(node->Key == key){
        if(node->Left == NULL && node->Right == NULL) node = NULL;
        else if(node->Left == NULL && node->Right !=NULL){
            node->Right->Parent = node->Parent;
            node = node->Right;
        }
        else if(node->Left != NULL && node->Right ==NULL){
            node->Left->Parent = node->Parent;
            node = node->Left;
        }
        else{
            int succesorKey = Succesor(key);
            node->Key = succesorKey;
            node->Right = Remove(node->Right,succesorKey);
        }
    }
    else if(node->Key < key) node->Right = Remove(node->Right, key);
    else node->Left = Remove(node->Left,key);
    
    return node;


}

template<typename T>
void BSTree<T>::Remove(int key){
    Size--;
    root = Remove(root, key);
}

//Konstruktor drzewa.
template<typename T>
BSTree<T>::BSTree()
{
    root = NULL;
    Size = 0;
    cout<<"Utworzono drzewo BST."<<endl;
}
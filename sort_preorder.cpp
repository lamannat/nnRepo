#include <cassert>
#include <vector>
#include <iostream>

template<class T>
void swap(T&a, T&b){
    T aux = a;
    a = b;
    b = aux;
}

template<class T>
int ubicar_pivote(std::vector<T> &pre, int inicio, int final)
{
    int pos_piv = inicio;
    while(pos_piv < final && pre[pos_piv] > pre[pos_piv+1]){
        swap(pre[pos_piv],pre[pos_piv+1]);
        pos_piv++;
    }
    return pos_piv;
}

template<class T>
void sort_preorder(std::vector<T> &pre, int inicio, int final)
{
    if(inicio<final){

        int pos_piv = ubicar_pivote(pre, inicio, final);
        sort_preorder(pre, inicio, pos_piv-1);
        sort_preorder(pre, pos_piv+1, final);
    }
}

template<class T>
void sort_preorder(std::vector<T> &pre)
{
    int inicio = 0;
    int final = pre.size()-1;
    sort_preorder(pre, inicio, final);
}


template<class T>
void test_array_sorted(std::vector<T> &P, int test_no)
{
    std::cout << "Test #" << test_no << "... ";

    sort_preorder(P);

    for(std::size_t i = 0; i < P.size()-1; ++i)
        assert(P[i] < P[i+1]);



    std::cout << "OK." << std::endl;
    std::cout.flush();
}

void run_tests()
{
    std::vector<int>
        P1   {5},
        P2_1 {5,3},
        P2_2 {5,7},
        P3   {5,3,7},
        Pn   {13,7,5,6,10,9,20,15,14,16,22,23};

    test_array_sorted(P1,1);
    test_array_sorted(P2_1,2);
    test_array_sorted(P2_2,3);
    test_array_sorted(Pn,4);
}

int main()
{
    run_tests();
    return 0;
}

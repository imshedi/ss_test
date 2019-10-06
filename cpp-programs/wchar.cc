// An example C++ program to demonstrate use of wchar_t
#include <iostream>

using namespace std;

int main(void)
{
    wchar_t w  = L'A';
    cout << "Wide character value:: " << w << endl ;
    cout << "Size of the wide char is:: " << sizeof(w) << endl;

    return 0;
}

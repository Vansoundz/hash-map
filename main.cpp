#include <iostream>
#include "source files/include/map.h"
using namespace std;

int hash_key(string s, int size);

int main()
{
    Map<string, int> m;

    for (int i = 0; i < 150; i++)
    {
        m.add_item(to_string(i), i);
    }

    cout << m.get_item("105") << endl;
    cout << m.size << endl;

    return 0;
}

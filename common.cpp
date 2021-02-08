#include <iostream>
using namespace std;

int hash_key(string s, int size)
{
    unsigned int h = 17;
    string::iterator it;
    for (it = s.begin(); it != s.end(); it++)
    {
        h *= (int)(*it);
    }
    return h % size;
}

template <class K>
void print(vector<K> vec)
{
    cout << "Size: " << vec.size() << endl;
    typename vector<K>::iterator it;
    cout << "[";
    for (it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << (it < (vec.end() - 1) ? ", " : "");
    }
    cout << "]" << endl;
}
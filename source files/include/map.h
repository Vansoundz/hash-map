#ifndef MAP_H
#define MAP_H
#include <vector>
#include "../../common.cpp"

template <class K, class V>
struct Item
{
    K key;
    V value;

    Item(){};

    Item(K k, V v)
    {
        key = k;
        value = v;
    }
};

template <class K, class V>
class Map
{
public:
    int size = 100;
    int length;
    void add_item(K k, V v);
    V get_item(K k);
    void resize();
    vector<K> keys();
    vector<V> values();
    void clear();
    Map()
    {
        table = new vector<Item<K, V>>[size];
        length = 0;
    };

private:
    vector<Item<K, V>> *table;
};

template <class K, class V>
vector<K> Map<K, V>::keys()
{
    vector<K> keys;

    for (int i = 0; i < size; i++)
    {
        if (table[i].size() > 0)
        {
            typename vector<Item<K, V>>::iterator it;
            for (it = table[i].begin(); it != table[i].end(); it++)
            {
                keys.push_back(it->key);
            }
        }
    }

    return keys;
}

template <class K, class V>
vector<V> Map<K, V>::values()
{
    vector<V> values;
    typename vector<Item<K, V>>::iterator it;

    for (int i = 0; i < size; i++)
    {
        if (table[i].size() > 0)
        {
            for (it = table[i].begin(); it != table[i].end(); it++)
            {
                values.push_back(it->value);
            }
        }
    }

    return values;
}

template <class K, class V>
void Map<K, V>::clear()
{
    length = 0;
    delete[] table;
    size = 100;
    table = new vector<Item<K, V>>[size];
}

template <class K, class V>
V Map<K, V>::get_item(K k)
{
    int i = hash_key(k, size);

    typename vector<Item<K, V>>::iterator it;
    Item<K, V> item;

    for (it = table[i].begin(); it != table[i].end(); it++)
    {
        if (it->key == k)
        {
            item = *it;
            break;
        }
    }

    return item.value;
}

template <class K, class V>
void Map<K, V>::resize()
{
    size *= 3;
    length = 0;
    vector<Item<K, V>> *tbl = new vector<Item<K, V>>[size * 3];

    for (int i = 0; i < size / 3; i++)
    {
        if (table[i].size() > 0)
        {
            typename vector<Item<K, V>>::iterator it;

            for (it = table[i].begin(); it != table[i].end(); it++)
            {
                int idx = hash_key(it->key, size);

                if (tbl[idx].size() == 0)
                {
                    tbl[i] = {*it};
                }
                else
                {
                    tbl[i].push_back(*it);
                }
                length++;
            }
        }
    }

    delete[] table;
    table = tbl;
}

template <class K, class V>
void Map<K, V>::add_item(K k, V v)
{
    if ((length * 1.0) / size >= 0.75)
    {
        resize();
    }

    int i = hash_key(k, size);
    Item<K, V> item(k, v);

    if (table[i].size() == 0)
    {
        length++;
        table[i] = {item};
    }
    else
    {
        typename vector<Item<K, V>>::iterator it;
        bool inserted = false;
        int index = 0;
        for (it = table[i].begin(); it != table[i].end(); it++)
        {
            if (it->key == k)
            {
                it->value = v;
                inserted = true;
                break;
            }
            index++;
        }

        if (!inserted)
        {
            table[i].push_back(item);
            length++;
        }
    }
}

#endif
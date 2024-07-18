#include "LRU.hpp"


void test_LRU()
{
    LRUCache *obj = new LRUCache(2);

    obj->put(1, 1);
    obj->put(2, 2);
    int ret = obj->get(1);
    obj->put(3, 3);
    ret = obj->get(2);
    obj->put(4, 4);
    ret = obj->get(1);
    ret = obj->get(3);
    ret = obj->get(4);
}

int main(void)
{
    LRUCache Joker(3);

    test_LRU();


    // Joker.put(20, 1);
    // Joker.put(0, 1);
    // Joker.put(2, 4);
    // Joker.put(2, 3);
    // Joker.put(1, 2);
    // Joker.put(3, 4);
    // Joker.put(2, 22);
    // Joker.put(3, 99);

    // cout << Joker.get(20) << endl;
    // cout << Joker.get(3) << endl;
    // cout << Joker.get(2) << endl;
    // cout << Joker.get(1) << endl;
    // cout << Joker.get(0) << endl;

    return 0;
}
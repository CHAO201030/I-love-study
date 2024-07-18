#ifndef __LRU_HPP__
#define __LRU_HPP__

#include <cpp58.hpp>

class LRUCache
{
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);

private:
    void updateCacheOrder(int key);
    bool noSwapOut(int key);
private:
    int _capacity;
    unordered_map<int, int> _cache;
    list<int> _erase_order_list;
    size_t _list_size;
    size_t _cache_size;
};

#endif
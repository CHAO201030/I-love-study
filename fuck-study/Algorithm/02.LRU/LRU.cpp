#include "LRU.hpp"

LRUCache::LRUCache(int capacity)
:_capacity(capacity), _list_size(0), _cache_size(0)
{

}

int LRUCache::get(int key)
{
    auto it = _cache.find(key);
    if(it == _cache.end())
    {
        return -1;
    }
    else
    {
        int ret = it->second;
        
        noSwapOut(key);

        return ret;
    }
}

void LRUCache::put(int key, int value)
{
    if(_cache_size < size_t(_capacity))
    {
        auto it = _cache.find(key);
        if(it == _cache.end())
        {
            _cache.insert({key, value});
            _cache_size++;
        }
        else
        {
            it->second = value;
        }
    }
    else
    {
        auto it = _cache.find(key);
        if(it == _cache.end())
        {
            _cache.erase(_erase_order_list.back());
            _cache.insert({key, value});
        }
        else
        {
            it->second = value;
        }
    }

    updateCacheOrder(key);
}

bool LRUCache::noSwapOut(int key)
{
    auto it = _erase_order_list.begin();

    for(;it != _erase_order_list.end(); ++it)
    {
        if(*it == key)
        {
            _erase_order_list.splice(_erase_order_list.begin(), _erase_order_list, it);
            return true;
        }
    }

    return false;
}

void LRUCache::updateCacheOrder(int key)
{
    if(_list_size < size_t(_capacity))
    {
        if(!noSwapOut(key))
        {
            _erase_order_list.push_front(key);
            _list_size++;
        }
    }
    else
    {
        if(!noSwapOut(key))
        {
            _erase_order_list.pop_back();
            _erase_order_list.push_front(key);
        }
    }
}
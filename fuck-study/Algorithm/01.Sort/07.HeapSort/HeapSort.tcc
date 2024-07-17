#include "My_HeapSort"

template<typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size, Compare cmp)
:_vec(arr, arr + size), _cmp(cmp)
{

}

template<typename T, typename Compare>
void HeapSort<T, Compare>::build_heap()
{
    for(size_t i = (_vec.size() - 2) >> 1; i > 0; i--)
    {
        heapAdjust(i, _vec.size());
    }
    heapAdjust(0, _vec.size());
}

template<typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t parent, size_t size)
{
    while(parent < size)
    {
        size_t lchild = 2 * parent + 1;
        size_t rchild = 2 * parent + 2;
    
        size_t pos_idx = parent;
        if(lchild < size && _cmp(_vec[pos_idx], _vec[lchild]))
        {
            pos_idx = lchild;
        }
        if(rchild < size && _cmp(_vec[pos_idx], _vec[rchild]))
        {
            pos_idx = rchild;
        }
        if(pos_idx == parent) break;

        std::swap(_vec[parent], _vec[pos_idx]);
        parent = pos_idx;
    }
}

template<typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
    build_heap();
    // printResult();

    size_t len = _vec.size();

    while (len > 1)
    {
        std::swap(_vec[0], _vec[len - 1]);
        len--;
        heapAdjust(0, len);
        // printResult();
    }
    
}

template<typename T, typename Compare>
void HeapSort<T, Compare>::printResult()
{
    for(auto & it : _vec)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

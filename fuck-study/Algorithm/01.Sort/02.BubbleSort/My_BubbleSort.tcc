#include "My_BubbleSort"

template <typename T, typename Compare>
BubbleSort<T, Compare>::BubbleSort(T *arr, size_t size, Compare cmp)
:_vec(arr, arr + size), _cmp(cmp)
{

}

template <typename T, typename Compare>
void BubbleSort<T, Compare>::sort()
{
    bool swap_flag = false;
    for(size_t i = 0; i < _vec.size(); i++)
    {
        for(size_t j = i + 1; j < _vec.size(); j++)
        {
            if(_cmp(_vec[j], _vec[i]))
            {
                std::swap(_vec[j], _vec[i]);
                swap_flag = true;
            }
        }
        
        if(!swap_flag)
        {
            break;
        }
    }
}

template <typename T, typename Compare>
void BubbleSort<T, Compare>::printResult()
{
    for(auto & it : _vec)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}
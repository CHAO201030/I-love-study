#include "My_SelectSort"

template <typename T, typename Compare>
SelectSort<T, Compare>::SelectSort(T* arr, size_t size, Compare cmp)
:_vec(arr, arr + size), _cmp(cmp)
{

}

template <typename T, typename Compare>
void SelectSort<T, Compare>::sort()
{

    for(size_t i = 0; i < _vec.size(); i++)
    {
        size_t pos = i;

        for(size_t j = i + 1; j < _vec.size(); j++)
        {
            if(_cmp(_vec[j], _vec[pos]))
            {
                pos = j;
            }
        }
        std::swap(_vec[pos], _vec[i]);
    }
}

template <typename T, typename Compare>
void SelectSort<T, Compare>::printResult()
{
    for(auto & it : _vec)
    {
        std::cout << it << " ";
    }

    std::cout << std::endl;
}
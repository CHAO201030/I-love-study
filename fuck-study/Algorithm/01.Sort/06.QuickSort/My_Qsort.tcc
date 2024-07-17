#include "My_Qsort"

template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T* arr, size_t size, Compare com)
:_vec(arr, arr + size), _com(com)
{

}

template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right)
{
    if(left < right)
    {
        int pos = partition(left, right);
        quick(left, pos - 1);
        quick(pos + 1, right);        
    }
}

template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right)
{
    auto pivot = _vec[left];

    int low = left, high = right;

    while(low < high)
    {
        while(low < high && _com(pivot, _vec[high]))
        {
            --high;
        }

        _vec[low] = _vec[high];

        while(low < high && _com(_vec[low], pivot))
        {
            ++low;
        }

        _vec[high] = _vec[low];
    }
    _vec[low] = pivot;

    return low;
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::printResult()
{
    for(auto i : _vec)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

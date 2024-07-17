#include "My_Vector"

template <typename _Tp> Vector<_Tp>::Vector()
{
    _M_start = nullptr;
    _M_finish = nullptr;
    _M_end_of_storage = nullptr;
}

template <typename _Tp> Vector<_Tp>::Vector(_Tp data)
{
    _M_start = new _Tp[2]();
    _M_start[0] = data;
    _M_finish = _M_end_of_storage = _M_start + 1;
}

template <typename _Tp> Vector<_Tp>::Vector(size_t n, const _Tp & data)
{
    _M_start = new _Tp[n + 1]();
    for(size_t i = 0; i < n; i++)
    {
        _M_start[i] = data;
    }
    _M_finish = _M_end_of_storage = _M_start + n;
}

template <typename _Tp> Vector<_Tp>::~Vector()
{
    if(_M_start)
    {
        delete [] _M_start;
        _M_start = nullptr;
        _M_finish = nullptr;
        _M_end_of_storage = nullptr;
    }
}

template <typename _Tp> typename Vector<_Tp>::Iterator Vector<_Tp>::begin()
{
    return _M_start;
}

template <typename _Tp> typename Vector<_Tp>::Const_Iterator Vector<_Tp>::begin() const
{
    return _M_start;
}

template <typename _Tp> typename Vector<_Tp>::Iterator Vector<_Tp>::end()
{
    return _M_finish;
}

template <typename _Tp> typename Vector<_Tp>::Const_Iterator Vector<_Tp>::end() const
{
    return _M_finish;
}

template <typename _Tp> size_t Vector<_Tp>::max_size() const
{
    return size_t(-1) / sizeof(_Tp);
}

template <typename _Tp> size_t Vector<_Tp>::size() const
{
    return size_t(_M_finish - _M_start);
}

template <typename _Tp> size_t Vector<_Tp>::capacity() const
{
    return size_t(_M_end_of_storage - _M_start);
}

template <typename _Tp> bool Vector<_Tp>::empty() const
{
    return _M_start == nullptr;
}

template <typename _Tp> _Tp Vector<_Tp>::operator[](size_t n)
{
    return _M_start[n];
}

template <typename _Tp> void Vector<_Tp>::push_back(const _Tp & data)
{
    if(_M_start == nullptr)
    {
        _M_start = new _Tp[2]();
        *_M_start = data;
        _M_finish = _M_end_of_storage = _M_start + 1;
        return;
    }

    if(_M_finish == _M_end_of_storage)
    {
        _Tp *pTemp = new _Tp[2 * this->size() + 1]();
        
        for(size_t i = 0; i < this->size(); i++)
        {
            pTemp[i] = _M_start[i];
        }
        pTemp[this->size()] = data;

        _M_end_of_storage = pTemp + 2 * this->size();
        _M_finish = pTemp + this->size() + 1;
        
        delete [] _M_start;
        _M_start = pTemp;
    }
    else
    {
        *_M_finish = data;
        ++_M_finish;
    }
}

template <typename _Tp> void Vector<_Tp>::pop_back()
{
    if(_M_start == nullptr)return;

    --_M_finish;
    
    if(_M_start == _M_finish)
    {
        delete [] _M_start;
        _M_start = _M_finish = _M_end_of_storage = nullptr;
    }
}

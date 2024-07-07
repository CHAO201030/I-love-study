#include "String.hpp"

String::String()
{
    // std::cout << "String()" << std::endl;

    _pstr = nullptr;
    _size = 0;
}

String::String(const char *str)
{
    // std::cout << "String(const char *)" << std::endl;

    _size = strlen(str);
    _pstr = new char[_size + 1]();
    strcpy(_pstr, str);
}

String::String(const String & rhs)
{
    // std::cout << "String(const String & rhs)" << std::endl;
    
    _size = rhs._size;
    _pstr = new char[_size + 1]();
    strcpy(_pstr, rhs._pstr);
}

String::~String()
{
    // std::cout << "~String()" << std::endl;

    if(_pstr)
    {
        delete [] _pstr;
        _pstr = nullptr;
    }
}

size_t String::size() const
{
    // std::cout << "String::size()" << std::endl;

    return this->_size;
}

const char* String::c_str() const
{
    return this->_pstr;
}

String & String::operator=(const String & rhs)
{
    // std::cout << "String::operator=(const String & rhs)" << std::endl;

    if(this != &rhs)
    {
        if(this->_pstr)
        {
            delete [] _pstr;
        }
        this->_size = rhs._size;
        this->_pstr = new char[this->_size + 1]();
        strcpy(this->_pstr, rhs._pstr);
    }

    return *this;
}

String & String::operator=(const char *str)
{
    // std::cout << "String::operator=(const char *str)" << std::endl;

    if(this->_pstr)
    {
        delete [] this->_pstr;
    }
    this->_size = strlen(str);
    this->_pstr = new char[this->_size + 1]();
    strcpy(this->_pstr, str);
    
    return *this;
}

String & String::operator+=(const String & rhs)
{
    // std::cout << "String::operator+=(const String & rhs)" << std::endl;
    
    char *old = nullptr;

    if(this->_pstr)old = this->_pstr;
    
    this->_pstr = new char[this->_size + rhs._size + 1]();

    if(old == nullptr)
    {
        if(rhs._pstr)
        {
            strcpy(this->_pstr, rhs._pstr);
        }
    }
    else
    {
        if(rhs._pstr)
        {
            strncpy(this->_pstr, old, this->_size);
            strncpy(this->_pstr + this->_size, rhs._pstr, rhs._size);
            delete [] old;
        }
    }

    this->_size = strlen(this->_pstr);
    
    if(this->_size == 0)
    {
        // 一个字节的空间我都不多给！
        delete [] this->_pstr;
        this->_pstr = nullptr;
    }

    return *this;
}

String & String::operator+=(const char *str)
{
    // std::cout << "String::operator+=(const char *str)" << std::endl;
    
    char *old = nullptr;

    if(this->_pstr)old = this->_pstr;
    
    this->_pstr = new char[this->_size + strlen(str) + 1]();

    if(old == nullptr)
    {
        strcpy(this->_pstr, str);
    }
    else
    {
        strncpy(this->_pstr, old, this->_size);
        strncpy(this->_pstr + this->_size, str, strlen(str));
        delete [] old;
    }

    this->_size = strlen(this->_pstr);
    
    if(this->_size == 0)
    {
        // 一个字节的空间我都不多给！
        delete [] this->_pstr;
        this->_pstr = nullptr;
    }

    return *this;
}

char & String::operator[](size_t index)
{
    // std::cout << "String::operator[](size_t index)" << std::endl;

    if(index < 0 || index >= this->_size)
    {
        std::cout << "Out of range ";
        static char error_char = '\0';
        return error_char;
    }
    else
    {
        return this->_pstr[index];
    }
}

const char & String::operator[](size_t index) const
{
    // std::cout << "String::operator[](size_t index) const" << std::endl;

    if(index < 0 || index >= this->_size)
    {
        std::cout << "Out of range ";
        static char error_char = '\0';
        return error_char;
    }
    else
    {
        return this->_pstr[index];
    }
}

bool operator==(const String & lhs, const String & rhs)
{
    /*
    if(lhs._size != rhs._size)return false;

    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] != rhs._pstr[i])return false;
    }

    return true;
    */

    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String & lhs, const String & rhs)
{
    /*
    if(lhs._size != rhs._size)return true;

    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] != rhs._pstr[i])return true;
    }

    return false;
    */

    return strcmp(lhs._pstr, rhs._pstr) != 0;
}

bool operator<(const String & lhs, const String & rhs)
{   
    /*
    if(lhs._size < rhs._size)return true;
    if(lhs._size > rhs._size)return false;
    
    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] < rhs._pstr[i])return true;
    }

    return false;
    */

    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String & lhs, const String & rhs)
{
    /*
    if(lhs._size > rhs._size)return true;
    if(lhs._size < rhs._size)return false;

    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] > rhs._pstr[i])return true;
    }

    return false;
    */

    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String & lhs, const String & rhs)
{   
    /*
    if(lhs._size < rhs._size)return true;
    if(lhs._size > rhs._size)return false;

    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] > rhs._pstr[i])return false;
    }

    return true;
    */

    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String & lhs, const String & rhs)
{
    /*
    if(lhs._size < rhs._size)return false;
    if(lhs._size > rhs._size)return true;

    for(size_t i = 0; i < lhs._size; i++)
    {
        if(lhs._pstr[i] < rhs._pstr[i])return false;
    }

    return true;
    */
    
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

std::ostream & operator<<(std::ostream & os, const String & rhs)
{
    os << rhs._pstr;

    return os;
}

std::istream & operator>>(std::istream & is, String & rhs)
{
    /*
    std::cout << "Input a string (less than 1024) : ";
    
    char temp[1024] = {0};
    
    is >> temp;

    rhs += temp;

    return is;
    */

    if(rhs._pstr)
    {
        delete [] rhs._pstr;
        rhs._pstr = nullptr;
    }

    std::vector<char> buf;
    char ch;

    while((ch = is.get())!= '\n')
    {
        buf.push_back(ch);
    }

    rhs._size = buf.size();
    rhs._pstr = new char[rhs._size + 1]();
    strncpy(rhs._pstr, &buf[0], rhs._size);

    return is;
}

String operator+(const String & lhs, const String & rhs)
{
    size_t size = lhs.size() + rhs.size();

    char temp[size + 1] = {0};

    strncpy(temp, lhs.c_str(), lhs.size());
    strncpy(temp + lhs.size(), rhs.c_str(), rhs.size());

    return String(temp);
}

String operator+(const String & lhs, const char *str)
{
    size_t size = lhs.size() + strlen(str);

    char temp[size + 1] = {0};
    
    strncpy(temp, lhs.c_str(), lhs.size());
    strncpy(temp + lhs.size(), str, strlen(str));

    return String(temp);    
}

String operator+(const char *str, const String & rhs)
{
    size_t size = rhs.size() + strlen(str);

    char temp[size + 1] = {0};

    strncpy(temp, str, strlen(str));
    
    strncpy(temp + strlen(str), rhs.c_str(), rhs.size());

    return String(temp);    
}
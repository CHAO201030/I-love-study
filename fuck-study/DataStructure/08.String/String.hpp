#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include <string.h>
#include <limits>

class String
{
public:
    String();
    String(const char *str);
    String(const String & rhs);
    ~String();

    size_t size() const;
    const char* c_str() const;

    String & operator=(const String & rhs);
    String & operator=(const char *str);
    
    String & operator+=(const String & rhs);
    String & operator+=(const char *str);

    char & operator[](size_t index);
    const char & operator[](size_t index)const;

    friend bool operator==(const String & lhs, const String & rhs);
    friend bool operator!=(const String & lhs, const String & rhs);
    friend bool operator<(const String & lhs, const String & rhs);
    friend bool operator>(const String & lhs, const String & rhs);
    friend bool operator<=(const String & lhs, const String & rhs);
    friend bool operator>=(const String & lhs, const String & rhs);

    friend std::ostream & operator<<(std::ostream & os, const String & rhs);
    friend std::istream & operator>>(std::istream & is, String & rhs);

private:
    char *_pstr;
    size_t _size;
};

String operator+(const String & lhs, const String & rhs);

String operator+(const String & lhs, const char *str);

String operator+(const char *str, const String & rhs);

#endif
#include "String.h"

# include <cstring>
# include <cstdlib>
# include <iostream>

String::String()
{
    len = 0;
    str = NULL;
}

String::~String()
{
    if (str != NULL && len > 0) {
        delete[] str;
    }
}

String::String(const char* c_str) {
    len = strlen(c_str);
    str = new char[len + 1];
    strncpy(str, c_str, len);
    str[len] = '\0';
}

String::String(const String& old_str) {
    len = old_str.len;
    str = new char[len + 1];
    strncpy(str, old_str.str, len);
    str[len] = '\0';
}

String::operator char*() const {
    return str;
}

char& String::operator[](int index) {
    if (index >= len && len < 0) throw "Illegal index";
    return str[index];
}

String& String::operator=(const String& old_str) {
    if (str != NULL && len > 0) {
        delete[] str;
    }

    len = old_str.len;
    str = new char[len + 1];
    strncpy(str, old_str.str, len);
    str[len] = '\0';

    return *this;
}

String operator+(const String& left, const String& right) {
    String str;

    str.len = left.len + right.len;
    str.str = new char[str.len + 1];

    strncpy(str.str, left.str, left.len);
    strncpy(str.str + left.len, right.str, right.len);
    str.str[str.len] = '\0';

    return str;
}

String& operator+=(String& left, const String& right) {
    int len = left.len + right.len;

    if (len == left.len)
        return left;

    char* str = new char[len + 1];

    if (left.len > 0) {
        strncpy(str, left.str, left.len);
    }

    strncpy(str + left.len, right.str, right.len);

    str[len] = '\0';

    if (left.str != NULL && left.len > 0) {
        delete[] left.str;
    }

    left.len = len;
    left.str = str;

    return left;
}

int String::length() const {
    return len;
}

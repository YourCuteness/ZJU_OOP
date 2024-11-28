#include "String.h"

void UCObject::decr()
{
    m_refCount--;
    if (m_refCount == 0)
        delete this;
};

template <class T>
UCPointer<T>::UCPointer(const UCPointer<T> &p)
{
    m_pObj = p.m_pObj;
    increment();
};

template <class T>
UCPointer<T> &UCPointer<T>::operator=(const UCPointer<T> &p)
{
    if (this != &p)
    {
        decrement();
        m_pObj = p.m_pObj;
        increment();
    }
    return *this;
};

// 放在模板定义后
template class UCPointer<StringRep>;

StringRep::StringRep(const char *s)
{
    if (s)
    {
        int len = strlen(s) + 1;
        m_pChars = new char[len];
        strcpy(m_pChars, s);
    }
    else
    {
        m_pChars = new char[1];
        *m_pChars = '\0';
    }
};

StringRep::~StringRep()
{
    delete[] m_pChars;
}

StringRep::StringRep(const StringRep &s)
{
    int len = strlen(s.m_pChars) + 1;
    m_pChars = new char[len];
    strcpy(m_pChars, s.m_pChars);
};

void StringRep::operator=(const StringRep &s)
{
    if (this != &s)
    {
        delete[] m_pChars;
        int len = strlen(s.m_pChars) + 1;
        m_pChars = new char[len];
        strcpy(m_pChars, s.m_pChars);
    }
};

int StringRep::equal(const StringRep &s) const
{
    return strcmp(m_pChars, s.m_pChars) == 0;
};

String::String(const char *s)
{
    m_rep = new StringRep(s);
};

String::~String(){};

String::String(const String &s) : m_rep(s.m_rep){};

String &String::operator=(const String &s)
{
    m_rep = s.m_rep;
    return *this;
};

int String::operator==(const String &s) const
{
    return m_rep->equal(*s.m_rep);
};

bool String::operator==(const char *s) const
{
    return strcmp(m_rep->m_pChars, s) == 0;
}

String String::operator+(const String &s) const
{
    char *newStr = new char[length() + s.length() + 1];
    strcpy(newStr, m_rep->m_pChars);
    strcat(newStr, s.m_rep->m_pChars);
    String result(newStr);
    delete[] newStr;
    return result;
};

int String::length() const
{
    return m_rep->length();
};

String::operator const char *() const
{
    return m_rep->m_pChars;
};

int String::refCount() const
{
    return m_rep->references();
}

const char *String::getRaw() const
{
    return m_rep->m_pChars;
};

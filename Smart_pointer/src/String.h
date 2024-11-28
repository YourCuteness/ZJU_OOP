#ifndef _String_h
#define _String_h

#include <assert.h>
#include <string.h>

size_t strlen(const char *s);

class UCObject
{
public:
    UCObject() : m_refCount(0){};
    virtual ~UCObject() { assert(m_refCount == 0); };
    UCObject(const UCObject &rhs) : m_refCount(0){};
    void incr() { m_refCount++; };
    void decr();
    int references() { return m_refCount; };

private:
    int m_refCount;
};

template <class T>
class UCPointer
{
private:
    T *m_pObj;
    void increment()
    {
        if (m_pObj)
            m_pObj->incr();
    }
    void decrement()
    {
        if (m_pObj)
            m_pObj->decr();
    }

public:
    UCPointer(T *r = 0) : m_pObj(r)
    {
        increment();
    }
    ~UCPointer()
    {
        decrement();
    }
    UCPointer(const UCPointer<T> &p);
    UCPointer<T> &operator=(const UCPointer<T> &p);
    T *operator->() const { return m_pObj; };
    T &operator*() const { return *m_pObj; };
};

class StringRep : public UCObject
{
private:
    char *m_pChars;
    void operator=(const StringRep &);

    friend class String;

public:
    StringRep(const char *);
    ~StringRep();
    StringRep(const StringRep &);
    int length() const { return strlen(m_pChars); };
    int equal(const StringRep &) const;
};

class String
{
public:
    String(const char *);
    ~String();
    String(const String &);
    String &operator=(const String &);
    int operator==(const String &) const;
    bool operator==(const char *) const; // 新增
    String operator+(const String &) const;
    int length() const;
    operator const char *() const;
    const char *getRaw() const;
    int refCount() const;

private:
    UCPointer<StringRep> m_rep;
};

#endif

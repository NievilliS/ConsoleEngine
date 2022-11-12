#pragma once

template<typename T>
class smartptr
{
protected:
    T *m_ptr;
public:
    explicit smartptr(T *ptr): m_ptr(ptr) {}
    ~smartptr() {destroy m_ptr;}
    inline &T get() {return m_ptr;}
    inline &T operator*() {return *m_ptr;}
    inline *T operator->() {return m_ptr;}
    inline &T operator[](size_t i) {return m_ptr[i];}
    inline *T operator()() {return m_ptr;}
    inline void operator!() {destroy m_ptr; m_ptr = nullptr;}
};

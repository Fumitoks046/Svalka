#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

template <class T>
class MFV
{
    private:
        int _capacity;
        int _size;
        T *_memory;
    public:
        MFV();
        MFV(int,T);
        MFV(MFV const &);
        ~MFV();
        void resize(int);
        T & operator[](int);
        T operator[](int) const;
        int size();
        MFV operator= (MFV);
        void push_back(T);
};

template <class T>
MFV<T>::MFV()
{
    _capacity = 0;
    _size = 0;
    _memory = new T[_capacity];
}

template <class T>
MFV <T> :: MFV(int a,T b = T())
{
    int i,s = 4;
    while (s < a)
    {
        s = s << 1;
    }
    _capacity = s;
    _size = a;
    _memory = new T[_capacity];
    for (i = 0;i < a;++i)
    {
        _memory[i] = b;
    }
}

template <class T>
MFV <T> :: MFV(MFV const & A)
{
    int i;
    _memory = new T[A._capacity];
    for (i = 0;i < A._size;++i)
    {
        _memory[i] = A[i];
    }
    _capacity = A._capacity;
    _size = A._size;
}

template <class T>
MFV <T> :: ~MFV()
{
    int i = 0;
    for (i = 0;i < _size;++i)
    {
        _memory[i].~T();
    }
    delete [] _memory;
}

template <class T>
void MFV <T> :: resize(int a)
{
    int i,s;
    if (a > _size)
    {
        if (a > _capacity)
        {
            s = _capacity;
            if (s == 0)
            {
                s = 4;
            }
            while (s < a)
            {
                s = s << 1;
            }
            T * temp = _memory;
            _memory = new T[s];
            for (i = 0;i < _size;++i)
            {
                _memory[i] = temp [i];
                temp[i].~T();
            }
            for (i = _size;i < a;++i)
            {
                _memory[i] = T();
            }
            _capacity = s;
            _size = a;
        }
        else
        {
            for (i = _size;i < a;++i)
            {
                _memory[i] = T();
            }
            _size = a;
        }
    }
    else
    {
        s = _capacity;
        while (s > a)
        {
            s = s >> 1;
        }
        s = s << 1;
        if (s < 4)
        {
            s = 4;
        }
        for (i = s;i < _capacity;++i)
        {
            _memory[i].~T();
        }
        _capacity = s;
        _size = a;
    }
}

template <class T>
T & MFV<T> :: operator[](int i)
{
    if ((i >= _size) || (i < 0))
    {
        cout<<"Exit out of vector"<<endl;
        exit(-1);
    }
    return _memory[i];
}

template <class T>
T MFV<T> :: operator[](int i) const
{
    if ((i >= _size) || (i < 0))
    {
        cout<<"Exit out of vector"<<endl;
        exit(-1);
    }
    return _memory[i];
}

template <class T>
int MFV<T> :: size()
{
    return _size;
}

template <class T>
MFV<T> MFV<T> :: operator= (MFV<T> a)
{
    int i;
    MFV<T> temp;
    temp._memory = new T[a._capacity];
    for (i = 0;i < a._size;++i)
    {
        temp._memory[i] = a[i];
    }
    for (i = 0;i < _capacity;++i)
    {
        _memory[i].~T();
    }
    _memory = temp._memory;
    _capacity = a._capacity;
    _size = a._size;
}

template <class T>
void MFV<T> :: push_back(T a)
{
    resize(_size+1);
    _memory[_size-1] = a;
}

int main()
{
    MFV <int> asdf;
    MFV <int> qwer(10);
    MFV <int> asd(qwer);
    MFV <double> as(5);
    MFV <bool> asf(1000,false);
    asdf.resize(1000);
    qwer.resize(1000);
    asdf[1] = 56;
    qwer.push_back(1100);
    asdf.push_back(900);
    qwer.resize(2000);
    cout<<asdf[1000]<<endl;
    cout<<qwer[1000]<<endl;
    qwer = asdf;
    cout<<qwer[1000]<<endl;
    return 0;
}

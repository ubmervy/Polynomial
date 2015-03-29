#include "Polynomial.h"
#include <initializer_list>

Polynomial<T>::Polynomial(std::initializer_list<T> il)
{
    //ctor
}

Polynomial<T>::~Polynomial()
{
    //dtor
}

Polynomial& Polynomial<T>::operator=(const Polynomial& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

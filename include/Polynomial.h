#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <initializer_list>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
class Polynomial
{
public:

    //ctor for zero polinomial
    Polynomial<T>()
    {
        this->coefs.push_back(T());
    };

    //ctor with initialization list
    Polynomial<T>(std::initializer_list<T> il) : coefs(il)
    {

    };

    //dtor
    ~Polynomial<T>()
    {
        //clean up the coefficient vector
        this->coefs.resize(0);
        this->coefs.shrink_to_fit();
    };

    std::vector<T> coefs; //polynomial coefficients;

    //polinomial at position <index>
    struct proxy
    {
        Polynomial* polynomial; //pointer to this
        int position;// index of this

        //ctor
        proxy(Polynomial* pln, int index)
            : polynomial(pln), position(index)
        {

        }

        // Invoked when proxy is used to modify coefficient at i-position
        void operator = (const T& i) const
        {
            //resize polinomial to fit new position
            if (position >= polynomial->coefs.size())
                polynomial->coefs.resize(position+1);
            //set new value to position
            polynomial->coefs[position] = i;
            //delete zeros in the end of coefs vector
            polynomial->delete_zeros();
        }

        // Invoked when proxy is used to compare coefficient at position with compared_value
        bool operator == (const T& compared_value)
        {
            return polynomial->coefs[position] == compared_value;
        }

        //assign a coefficient at polinomial's index
        operator T() const
        {
            return polynomial->coefs[position];
        }

    };

    //return polynomial at position <index> (lvalue)
    proxy operator[](const int index)
    {
        if(index > this->degree())
            this->coefs.resize(index+1);
        proxy prx (this, index);
        return prx;
    }

    //get coefficient by index (rvalue)
    const T operator[](const int index) const
    {
        T val = T();
        if (index < this->coefs.size())
            val = this->coefs[index];
        return val;
    }

    //assign polinomial to polinomial
    Polynomial<T>&  operator=(const Polynomial<T>& assigned_pln)
    {
        if (this == &assigned_pln)
            return *this; // handle self assignment
        //assignment operator
        return *this;
    }

    //get max degree of polinomial
    int degree()
    {
        return (coefs.size() - 1);
    }

    //get max degree of polinomial
    int degree() const
    {
        return (coefs.size() - 1);
    }

    //equality operator for polinomials
    friend bool operator==(const Polynomial<T> left_pln, const Polynomial<T>& right_pln)
    {
        return (left_pln.coefs == right_pln.coefs);
    }

    //addition operator for polinomials
    friend Polynomial<T> operator+(const Polynomial<T>& left_pln, const Polynomial<T>& right_pln)
    {
        Polynomial<T> sum;
        int n = left_pln.coefs.size();
        int m = right_pln.coefs.size();
        int i = 0;

        sum.coefs.resize(std::max(n, m));

        for (i = 0; i < std::max(n, m); ++i)
        {
            if (i<n)
                sum.coefs[i] += left_pln.coefs[i];
            if (i<m)
                sum.coefs[i] += right_pln.coefs[i];
        }

        sum.delete_zeros();

        return sum;
    }

    //substruction operator for polinomials
    friend Polynomial<T> operator-(const Polynomial<T>& left_pln, const Polynomial<T>& right_pln)
    {
        Polynomial<T> sub;
        int n = left_pln.coefs.size();
        int m = right_pln.coefs.size();
        int i = 0;

        sub.coefs.resize(std::max(n, m));

        for (i = 0; i < std::max(n, m); ++i)
        {
            if (i<n)
                sub.coefs[i] += left_pln.coefs[i];
            if (i<m)
                sub.coefs[i] -= right_pln.coefs[i];
        }

        sub.delete_zeros();

        return sub;
    }

    //miltiplication operator for polinomials
    friend Polynomial<T> operator*(const Polynomial<T>& left_pln, const Polynomial<T>& right_pln)
    {
        Polynomial<T> p_product;
        int m = left_pln.degree();
        int n = right_pln.degree();

        if ((left_pln.coefs == p_product.coefs) || (right_pln.coefs == p_product.coefs))
            return p_product;

        p_product.coefs.resize(m+n+1);

        for(int k = 0; k <= (n+m); ++k)
        {
            p_product.coefs[k] = T();
            for (int i = std::max(0, k-n); i <= (std::min(k, m)); ++i)
                p_product.coefs[k] += left_pln.coefs[i]*right_pln.coefs[k-i];
        }

        return p_product;
    }

    //miltiplication operator for polinomial and righthand scalar
    Polynomial<T> operator*(const T& scalar)
    {
        Polynomial<T> s_product;
        return s_product.multiplicate(scalar, *this);

    }

    //miltiplication operator for lefthand scalar and polinomial
    friend Polynomial<T> operator*(const T& scalar, const Polynomial<T>& left_pln)
    {
        Polynomial<T> s_product;
        return s_product.multiplicate(scalar, left_pln);
    }

protected:

    //polinomial-scalar miltiplication
    Polynomial<T> multiplicate(const T& scalar, const Polynomial<T>& left_pln)
    {
        int m = left_pln.degree();

        if ((left_pln.coefs[0]==T()) || (scalar==T()))
            return *this;

        this->coefs.resize(m+1);

        for (int i = 0; i <= m; ++i)
            this->coefs[i] = scalar*left_pln.coefs[i];

        return *this;
    }
    //delete zero coefficients of zero powers in the end of polinomial
    void delete_zeros()
    {
        while ((this->coefs.back() == T()) && (this->coefs.size() != 1))
            this->coefs.pop_back();
        this->coefs.shrink_to_fit();
    }
};



#endif // POLYNOMIAL_H

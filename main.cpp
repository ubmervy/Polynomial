#include <iostream>
#include <assert.h>
#include <complex.h>
#include "include/Polynomial.h"

void test_initialize()
{
    //Polynomial<int>
    Polynomial<int> p = {7, 2, 7, 5, 6}; //construct non-zero polynomial
    assert(p[5] == 0); //the coefficient of X^5 is 0
    p[5] = 7; // set X^5 coefficient to 7
    auto pk = p[5]; // assign k to X^5 as a coefficient
    assert(pk == 7); // check coefficient of X^5 is 7

    //Polynomial<double>
    Polynomial<double> d = {7.3, -2.0, 7.5, 5.1, 6.95}; //construct non-zero polynomial
    d[5] = 7; // set X^5 coefficient to 7.0
    auto dk = d[5]; // assign k to X^5 as a coefficient
    assert(dk == 7.0); // check coefficient of X^5 is 7.0

    //Polynomial<float>
    Polynomial<float> f = {7.3, 2.0, 7, 5, -6.95}; //construct non-zero polynomial
    f[5] = 7; // set X^5 coefficient to 7
    auto fk = d[5]; // assign k to X^5 as a coefficient
    assert(fk == 7.0f); // check coefficient of X^5 is 7.0f

    //Polynomial<complex<double>>
    Polynomial<std::complex<double>> c = {(1.0, 1.0)}; //construct non-zero polynomial
    c[1] = (5.0, 0.0); // set X coefficient to (5.0, 0.0)
    auto ck = c[1]; // assign k to X as a coefficient
    assert(ck == (5.0, 0.0)); // check coefficient of X is (5.0, 0.0)

    p = p; // polynomial self-assignement
    Polynomial<int> asgn = {0, 1, 2};
    assert(asgn.coefs != p.coefs);
    asgn = p; // assign other polynomial
    assert(asgn.coefs == p.coefs);
}

void test_degree()
{
    //Zero-polinomial degree
    Polynomial<int> p; //construct zero polynomial
    assert(p.degree() == 0); // degree of zero polynomial is 0
    assert(p[0] == 0); // the coefficient of X^0 is 0

    //Non-zero-polinomial degree
    Polynomial<int> q = {1};  // construct non-zero polynomial
    assert(q.degree() == 0); // finding degree of non-zero polynomial
    assert(q[0] == 1); // degree of non-zero polynomial is 1

    //Polinomial degree changes with respect to trailing zeros
    Polynomial<int> f = {1, 0, 0, 0, 0, 0, 0, 0, 1};
    assert(f.degree() == 8); //current degree is 8
    f[8] = 0; // set zero coefficient to the highest degree
    assert(f.degree() == 0); // now current degree is 0
    f[12] = 6; // set non-zero coefficient to X^12
    assert(f.degree() == 12); // now current degree is 12
}

void test_addition()
{
    //Addition of two polynomials (non-zero result)
    Polynomial<int> augend = {1, 5, 1}; // x^2 + 5*x + 1
    Polynomial<int> addend1 = {6, 0, 2, 3}; // 3*x^3 + 2*x^2 + 6
    Polynomial<int> sum = {7, 5, 3, 3}; // 3*x^3 + 3*x^2 + 5*x + 7
    assert(augend + addend1 == sum);
    auto var_sum = augend + addend1;
    assert(var_sum == sum);

    Polynomial<std::complex<double>> c1 = {(20.0,1.0)};
    Polynomial<std::complex<double>> c2 = {(1.0,3.0)};
    Polynomial<std::complex<double>> c_sum = {(21.0,4.0)};
    assert(c_sum == c1 + c2);

    //Addition of two polynomials (result degree less than max input degree)
    Polynomial<int> addend2 = {0, -5, -1};
    Polynomial<int> var_sum1 = {1};
    assert(augend + addend2 == var_sum1);

    //Addition of two polynomials (zero result)
    Polynomial<int> addend3 = {-1, -5, -1};
    Polynomial<int> var_zero_sum = {0};
    assert(var_zero_sum == augend + addend3);
}

void test_substruction()
{
    //Substruction of two polynomials (non-zero result)
    Polynomial<int> minuend = {0, 8, 0, 4, 0, 11}; // 11*x^5 + 4*x^3 + 8*x
    Polynomial<int> subtrahend1 = {6, 0, 2, 3}; // 3*x^3 + 2*x^2 + 6
    Polynomial<int> difference1 = {-6, 8, -2, 1, 0, 11}; // 11*x^5 + x^3 + 2*x^2 + 8*x + 6
    assert(minuend - subtrahend1 == difference1);
    auto var_dif = minuend - subtrahend1;
    assert(var_dif == difference1);

    //Substruction of two polynomials (complex coefficients)
    Polynomial<std::complex<double>> c1 = {(20.0,1.0)};
    Polynomial<std::complex<double>> c2 = {(1.0,3.0)};
    Polynomial<std::complex<double>> c_dif = {(19.0,-2.0)};
    assert(c_dif == c1 - c2);
    Polynomial<std::complex<double>> c3 = {(20.0,1.0)};
    assert((c1 - c3)[0] == (0.0,0.0));

    //Substruction of two polynomials (result degree differs from input degree)
    Polynomial<int> subtrahend2 = {0, 0, 0, 4, 0, 11};
    Polynomial<int> difference2 = {0, 8};
    auto dif_change = minuend - subtrahend2; // substruction diminishs input degree from 5 to 1
    assert(dif_change == difference2);
    assert((minuend - subtrahend2)[1] == 8);
    assert((minuend - subtrahend2)[5] == 0);
    auto dif_change_degree = (minuend - subtrahend2).degree(); //get result degree
    assert(dif_change_degree == 1); // result degree is 1

    //Addition of two polynomials (zero result)
    Polynomial<int> subtrahend3 = {0, 8, 0, 4, 0, 11};
    Polynomial<int> var_zero_dif;
    assert(var_zero_dif == minuend - subtrahend3); // substruction of identical polynomials gives zero polynomial
}

void test_pln_multiplication()
{
    //Multiplication of two polynomials (non-zero result)
    Polynomial<int> p_multiplier1 = {1, 5, 1}; // x^2 + 5*x + 1
    Polynomial<int> p_multiplier2 = {6, 0, 2, 3}; // 3*x^3 + 2*x^2 + 6
    Polynomial<int> p_product = {6, 30, 8, 13, 17, 3}; // 3*x^5 + 17*x^4 + 13*x^3 + 8*x^2 + 30*x + 6
    assert(p_multiplier1 * p_multiplier2 == p_product);
    auto var_product = p_multiplier1 * p_multiplier2; // assign multiplication result to variable
    assert(var_product == p_product);

    auto var_product_degree = (p_multiplier1 * p_multiplier2).degree(); //finding multiplication result degree
    assert(var_product_degree == 5); // multiplication result degree is 5

    //Multiplication of two polynomials (complex coefficients)
    Polynomial<std::complex<double>> c1 = {(20.0,1.0)};
    Polynomial<std::complex<double>> c2 = {(1.0,3.0)};
    Polynomial<std::complex<double>> c_mult = {(20.0,3.0)};
    assert(c_mult == c1 * c2);
    assert((c1 * c2)[0] == (20.0,3.0));

    //Multiplication of two polynomials (zero result)
    Polynomial<int> p_multiplier3; //zero polynomial
    auto zero_product = p_multiplier1 * p_multiplier3; // assign multiplication result to variable
    Polynomial<int> zero_result; //zero polynomial for checking result
    assert(zero_product == zero_result);

    auto var_zeroproduct_degree = (p_multiplier1 * p_multiplier3).degree(); //finding multiplication result degree
    assert(var_zeroproduct_degree == 0);  // multiplication result degree is 0
    assert((p_multiplier1 * p_multiplier3)[0] == 0); // the coefficient of X^0 is 0
}

void test_pln_scalar_multiplication()
{
    //Multiplication of scalar and polynomial (non-zero result)
    Polynomial<int> p_multiplier1 = {1, 5, 1}; // x^2 + 5*x + 1
    int s_value1 = 5;
    Polynomial<int> s_product = {5, 25, 5}; // 5*x^2 + 25*x + 5

    auto s_product_rhs = p_multiplier1 * s_value1; // righthand scalar multiplication
    auto s_product_lhs = s_value1 * p_multiplier1; // lefthand scalar multiplication

    assert(s_product_rhs == s_product); // result is true
    assert(s_product_rhs == s_product_lhs); //result doesn't depend on operands' order

    //Multiplication of scalar and polynomial (complex coefficients)
    Polynomial<std::complex<double>> c1 = {(20.0,1.0)};
    Polynomial<std::complex<double>> c_smult = {(100.0,5.0)};
    auto s_cproduct_rhs = c1 * s_value1;
    auto s_cproduct_lhs = s_value1 * c1;
    assert(c_smult == s_cproduct_lhs);
    assert(s_cproduct_rhs == s_cproduct_lhs);
    assert((s_value1 * c1)[0] == (100.0,5.0));

    //Multiplication of scalar and polynomial (zero result)
    Polynomial<int> p_multiplier2 = {6, 0, 2, 3};
    int s_value2 = 0;
    Polynomial<int> p_multiplier3;
    Polynomial<int> zero_sproduct = {0};
    assert(p_multiplier2 * s_value2 == zero_sproduct); // multiplication of zero scalar and non-zero polynomial gives zero polynomial
    assert(s_value1 * p_multiplier3 == zero_sproduct); // multiplication of non-zero scalar and zero polynomial also gives zero polynomial
}

void test()
{
    test_initialize();
    test_degree();
    test_addition();
    test_substruction();
    test_pln_multiplication();
    test_pln_scalar_multiplication();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
};

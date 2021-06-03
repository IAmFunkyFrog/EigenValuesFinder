#ifndef EIGENVALUESFINDER_MATRIXUTILS_H
#define EIGENVALUESFINDER_MATRIXUTILS_H

#include "../RationalNum/RationalNum.h"
#include <set>

typedef struct {
    unsigned int degree;
    RationalNum* coefficients;
} Polynomial;

Polynomial* getCharacteristicPolynomial(RationalNum** matrix, unsigned int size);
set<RationalNum> findRationalSolutions(Polynomial* polynomial);
RationalNum getPolynomialValue(Polynomial* polynomial, RationalNum x);

#endif //EIGENVALUESFINDER_MATRIXUTILS_H

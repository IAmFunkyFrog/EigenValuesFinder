#include "MatrixUtils.h"
#include "../RationalNum/RationalNum.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

RationalNum getMainMinor(RationalNum** matrix, vector<unsigned int>&rows) {
    if(rows.empty()) return 1ll;

    vector<unsigned int>permutation;
    for(int i = 0; i < rows.size(); i++) permutation.push_back(i);
    RationalNum sum = 0ll;
    do {
        unsigned int sign = 0;
        for(int i = 0; i < permutation.size() - 1; i++) {
            for(int j = i + 1; j < permutation.size(); j++) {
                if(permutation[j] < permutation[i]) sign++;
            }
        }
        RationalNum msum = 1ll;
        for(int i = 0; i < rows.size(); i++) msum *= matrix[rows[i]][rows[permutation[i]]];
        if(sign % 2 == 0) sum += msum;
        else sum -= msum;
    } while(next_permutation(permutation.begin(), permutation.end()));
    return sum;
}

Polynomial* getCharacteristicPolynomial(RationalNum** matrix, unsigned int size) {
    if(matrix == nullptr) return nullptr;

    Polynomial* polynomial = new Polynomial;
    polynomial->degree = size;
    polynomial->coefficients = new RationalNum [polynomial->degree + 1];

    for(unsigned int i = 0; i < pow(2, size); i++) {
        vector<unsigned int>rows;
        for(unsigned int j = 1, p = 0; j < pow(2, size + 1); j *= 2, p++) {
            if((i & j) != 0) rows.push_back(p);
        }
        polynomial->coefficients[size - rows.size()] += getMainMinor(matrix, rows);
    }
    for(unsigned int i = 1; i <= polynomial->degree; i += 2) polynomial->coefficients[i] *= -1ll;

    return polynomial;
}

set<long long int> getDivisors(long long int num) {
    set<long long int> divisors;
    for(int i = 1; i * i <= abs(num); i++) {
        if(num % i == 0) divisors.insert(i);
    }
    divisors.insert(abs(num));
    return divisors;
}

RationalNum getPolynomialValue(Polynomial* polynomial, RationalNum x) {
    RationalNum value = polynomial->coefficients[0];
    RationalNum m = x;
    for(int i = 1; i <= polynomial->degree; i++, m *= x) {
        value += polynomial->coefficients[i] * m;
    }
    return value;
}

//Находим решение многочлена как дробь p / q, где p - делитель коофицента с наименьшей степенью не равного 0, а q - делитель старшего коофицента
set<RationalNum> findRationalSolutions(Polynomial* polynomial) {
    long long int commonDenominator = 1;
    for(int i = 0; i <= polynomial->degree; i++) commonDenominator *= polynomial->coefficients[i].getDenominator();

    set<long long int> pValues;
    for(int i = 0; i <= polynomial->degree; i++) {
        if(polynomial->coefficients[i] != 0ll) {
            pValues = getDivisors(polynomial->coefficients[i].getNumerator() * (commonDenominator / polynomial->coefficients[0].getDenominator()));
            break;
        }
    }
    set<long long int> qValues = getDivisors(polynomial->coefficients[polynomial->degree].getNumerator() * (commonDenominator / polynomial->coefficients[polynomial->degree].getDenominator()));

    set<RationalNum> rationalSolutions;
    for(auto p : pValues) {
        for(auto q : qValues) {
            RationalNum x(p, q);
            if(getPolynomialValue(polynomial, x) == 0ll) rationalSolutions.insert(x);
            if(getPolynomialValue(polynomial, -x) == 0ll) rationalSolutions.insert(-x);
        }
    }
    if(getPolynomialValue(polynomial, 0ll) == 0ll) rationalSolutions.insert(0ll);

    return rationalSolutions;
}
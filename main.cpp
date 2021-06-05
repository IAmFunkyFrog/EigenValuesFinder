#include <iostream>
#include <iomanip>
#include <map>
#include "libs/InputParser/InputParser.h"
#include "libs/MatrixUtils/MatrixUtils.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "You must write filename" << endl;
        return -1;
    }

    ParsedInput *input = parseInput(argv[1]);

    if (input == nullptr) {
        cout << "Error while parsing filename" << endl;
        return -1;
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < input->n; i++) {
        for (int j = 0; j < input->n; j++) {
            cout  << setw(3) << input->matrix[i][j] << " ";
        }
        cout << endl;
    }

    Polynomial *polynomial = getCharacteristicPolynomial(input->matrix, input->n);

    cout << "Characteristics polynomial:" << endl;
    cout << "F(x) = ";
    for (int i = polynomial->degree; i >= 0; i--) {
        if(i > 0) {
            if(polynomial->coefficients[i] == 1ll) {
                cout << "x^" << i << " ";
            }
            else if(polynomial->coefficients[i] == -1ll) {
                cout << "- x^" << i << " ";
            }
            else {
                if(polynomial->coefficients[i] > 0ll) cout << "+ " << polynomial->coefficients[i] << " " << "x^" << i << " ";
                else if(polynomial->coefficients[i] < 0ll) cout << "- " << -polynomial->coefficients[i] << " " << "x^" << i << " ";
            }
        }
        else if(i == 0) {
            if(polynomial->coefficients[i] > 0ll) cout << "+ " << polynomial->coefficients[i];
            else if(polynomial->coefficients[i] < 0ll) cout << "- " << -polynomial->coefficients[i];
        }
    }
    cout << endl;

    cout << "Rational eigenvalues: " << endl;
    set<RationalNum> eigenValues = findRationalSolutions(polynomial);

    int m = 1;
    for(auto eigenValue : eigenValues) {
        cout << "x_" << m++ << " = " << eigenValue << endl;
    }

    map<RationalNum, set<vector<RationalNum>>> eigenSpaces;
    cout << "Eigenspaces: " << endl;
    for(auto eigenValue : eigenValues) {
        set<vector<RationalNum>> basis = getEigenSpaceBasis(input->matrix, input->n, eigenValue);
        eigenSpaces[eigenValue] = basis;
        cout << "L(" << eigenValue << ") = span ( ";
        for(const auto& vector : basis) {
            cout << "(";
            for(int i = 0; i < vector.size(); i++) {
                cout << vector[i];
                if(i < vector.size() - 1) cout << ", ";
            }
            cout << ") ";
        }
        cout << ")" << endl;
    }

    int basisVectorsCount = 0;
    for(const auto& space : eigenSpaces) basisVectorsCount += space.second.size();

    if(basisVectorsCount < input->n) {
        cout << "Not enough eigen vectors to make eigen basis" << endl;
        return 0;
    }

    RationalNum** D = new RationalNum* [input->n];
    RationalNum** C = new RationalNum* [input->n];
    for(int i = 0; i < input->n; i++) {
        D[i] = new RationalNum [input->n];
        C[i] = new RationalNum [input->n];
    }

    m = 0;
    for(const auto& space : eigenSpaces) {
        for(auto basisVector : space.second) {
            D[m][m] = space.first;
            for (int j = 0; j < input->n; j++) C[j][m] = basisVector[j];
            m++;
        }
    }

    RationalNum** C1 = getInverseMatrix(C, input->n);

    cout << "Matrix decomposition: " << endl;
    cout << "A = C D C^(-1)" << endl;
    cout << "C:" << endl;
    for(int i = 0; i < input->n; i++) {
        for(int j = 0; j < input->n; j++) cout << C[i][j] << " ";
        cout << endl;
    }
    cout << "D:" << endl;
    for(int i = 0; i < input->n; i++) {
        for(int j = 0; j < input->n; j++) cout << D[i][j] << " ";
        cout << endl;
    }
    cout << "C^(-1):" << endl;
    for(int i = 0; i < input->n; i++) {
        for(int j = 0; j < input->n; j++) cout << C1[i][j] << " ";
        cout << endl;
    }

    //Освобождение памяти
    for(int i =0 ; i < input->n; i++) {
        delete [] input->matrix[i];
        delete [] D[i];
        delete [] C[i];
        delete [] C1[i];
    }
    delete[] input->matrix;
    delete [] D;
    delete [] C;
    delete [] C1;

    return 0;
}

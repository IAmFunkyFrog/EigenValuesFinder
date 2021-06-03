#include <iostream>
#include <iomanip>
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
    for (int i = polynomial->degree; i >= 0; i--) {
        if(i > 0) {
            if(polynomial->coefficients[i] == 1) {
                cout << "x^" << i << " ";
            }
            if(polynomial->coefficients[i] == -1) {
                cout << "- x^" << i << " ";
            }
            else {
                if(polynomial->coefficients[i] > 0) cout << "+ " << polynomial->coefficients[i] << " " << "x^" << i << " ";
                else if(polynomial->coefficients[i] < 0) cout << "- " << -polynomial->coefficients[i] << " " << "x^" << i << " ";
            }
        }
        else if(i == 0) {
            if(polynomial->coefficients[i] > 0) cout << "+ " << polynomial->coefficients[i];
            else if(polynomial->coefficients[i] < 0) cout << "- " << -polynomial->coefficients[i];
        }
    }
    cout << endl;

    cout << "Rational eigenvalues: " << endl;
    int i = 1;
    for(auto solution : findRationalSolutions(polynomial)) {
        cout << "x_" << i++ << " = " << solution << endl;
    }

    return 0;
}

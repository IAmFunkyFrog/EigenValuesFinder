#ifndef EIGENVALUESFINDER_INPUTPARSER_H
#define EIGENVALUESFINDER_INPUTPARSER_H

#include "../RationalNum/RationalNum.h"

typedef struct {
    int n;
    RationalNum** matrix;
} ParsedInput;

ParsedInput* parseInput(string filename);

#endif //EIGENVALUESFINDER_INPUTPARSER_H

#ifndef EIGENVALUESFINDER_INPUTPARSER_H
#define EIGENVALUESFINDER_INPUTPARSER_H

#include "../RationalNum/RationalNum.h"

typedef struct {
    unsigned int n;
    RationalNum** matrix;
} ParsedInput;

ParsedInput* parseInput(string filename);
void freeParsedInput(ParsedInput* input);

#endif //EIGENVALUESFINDER_INPUTPARSER_H

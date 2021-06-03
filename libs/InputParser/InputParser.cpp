#include <fstream>
#include <regex>
#include "InputParser.h"

ParsedInput* parseInput(string filename) {
    ifstream stream(filename);

    ParsedInput* input = new ParsedInput;
    string buf;
    //Parsing of input->n param
    regex r(R"(\d+)");
    smatch m;

    getline(stream, buf);
    if(regex_search(buf, m, r)) {
        input->n = stoi(m[0].str());
    }
    else {
        delete input;
        return nullptr;
    }
    //Parsing of input->matrix param
    input->matrix = new RationalNum* [input->n];
    for(int i = 0; i < input->n; i++) {
        getline(stream, buf);
        istringstream iss(buf);
        input->matrix[i] = new RationalNum [input->n];
        for(int j = 0; j < input->n; j++) {
            if(iss.eof()) {
                for(int k = 0; k <= i; k++) delete[] input->matrix[i];
                delete input->matrix;
                delete input;
                return nullptr;
            }
            iss >> input->matrix[i][j];
        }
    }

    return input;
}

void freeParsedInput(ParsedInput* input) {
    for(int i = 0; i < input->n; i++) delete[] input->matrix[i];
    delete input->matrix;
}
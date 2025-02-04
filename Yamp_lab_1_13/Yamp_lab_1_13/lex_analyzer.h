#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <string>
#include "hash_table.h"
#include "tokens.h"

using namespace std;

class LexicalAnalyzer {
public:
    LexicalAnalyzer(const string& input, const string& output) {
        inputF.open(input);
        outputF.open(output);
    };
    ~LexicalAnalyzer() {};
    void analyzer();
    Token getNextLexeme();
    ifstream inputF;
    ofstream outputF;
    HashTable tokenList;
private:


    bool isOperator(char elem) const;
    bool isDelimiter(char elem) const;
    bool isWrongSymbol(char elem) const;


};

#endif


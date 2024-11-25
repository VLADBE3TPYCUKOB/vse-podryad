#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <iostream>
#include <fstream>
#include <string>
#include "HashTableClass.h"
#include "Token.h"

class LexicalAnalyzer {
public:
    LexicalAnalyzer(const std::string& input, const std::string& output, const std::string& error) {
        testTxtFile.open(input);
        outputFile.open(output);
        errorFile.open(error);
    };
    ~LexicalAnalyzer() {
        if (testTxtFile.is_open())
            testTxtFile.close();
        if (outputFile.is_open())
            outputFile.close();
        if (errorFile.is_open())
            errorFile.close();
    };
    void lexAnBeg();

private:
    std::ifstream testTxtFile;                                   // cin
    std::ofstream outputFile;                                 // out
    std::ofstream errorFile;                                  // out with error
    HashTable tokenList;                                    // Hash-table

    bool isOperator(char elem) const;                       // Checking whether the operator is
    bool isDelimiter(char elem) const;                      // Checking whether the character is a separator
    bool isDigit(const std::string& lexeme);                     // checking for exceptional numbers
    bool isValidIdentifier(const std::string& lexeme) const;     // checking for the exceptional presence of letters
    
    // checking the next token
    Token getNextLexeme();
    // checking for int, while, return
    Token isKeyWord(std::ifstream& testTxtFile, int index, int num, char c);
  };

#endif
#include "LexicalAnalyzer.h"
#include "Token.h"
#include <iostream>
#include <vector>


std::vector<std::string> words = { "INTEGER","PROGRAM","END", "COMPLEX"};

bool LexicalAnalyzer::isDigit(const std::string& lexeme) {
    for (char c : lexeme)
        if (!isdigit(c))
            return false;
    return true;
}

bool LexicalAnalyzer::isValidIdentifier(const std::string& lexeme) const {
    for (char elem : lexeme)
        if (!isalpha(elem))
            return false;
    return true;
}


bool LexicalAnalyzer::isOperator(char elem) const {
    return (elem == '+' || elem == '-' || elem == '=');
}

bool LexicalAnalyzer::isDelimiter(char elem) const {
    return (elem == '(' || elem == ')' || elem == ',');
}


Token LexicalAnalyzer::isKeyWord(std::ifstream& testTxtFile, int index, int num, char elem) {
    std::string lexeme;
    int count = 1;
    int indexKey = 1;
    bool flag = false;

    lexeme += elem;
    while (testTxtFile.get(elem) && !isspace(elem)) {
        if (isDelimiter(elem)) {
            testTxtFile.unget();
            break;
        }
        lexeme += elem;
        
        if (indexKey < words[num].size())
            if (elem == words[num][indexKey])
                count++;
            else
                flag = true;
        else
            flag = true;
        indexKey++;
    }

    if (count == indexKey && (!flag)) {
        if (num == 0)
            return Token(TokenType::TYPE, lexeme, index, 0);
        else if (num == 1)
            return Token(TokenType::BEGIN, lexeme, index, 0);
        else
            return Token(TokenType::END, lexeme, index, 0);
    }
    else {
        if (!isValidIdentifier(lexeme))
            return Token(TokenType::ERROR, lexeme, index, 0);
        else
            return Token(TokenType::ID_NAME, lexeme, index, 0);
    }
}

Token LexicalAnalyzer::getNextLexeme() {
    std::string lexeme;
    char elem;
    int index = 1;

    while (testTxtFile.get(elem)) 
    {
        if (isspace(elem)) {
            index++;
            continue;
        }
        // int
        if (elem == 'I') {
            Token result = isKeyWord(testTxtFile, index, 0, elem);
            return result;
        }
        // program
        else if (elem == 'P') {
            Token result = isKeyWord(testTxtFile, index, 1, elem);
            return result;
        }
        // end
        else if (elem == 'E') {
            Token result = isKeyWord(testTxtFile, index, 2, elem);
            return result;
        }
        //complex
        else if (elem == 'C')
        {
            Token result = isKeyWord(testTxtFile, index, 3, elem);
            return result;
        }
    


        if (isalpha(elem)) {
            lexeme.clear();
            lexeme += elem;
            while (testTxtFile.get(elem) && (isalnum(elem)))
                lexeme += elem;
            testTxtFile.unget();

            if (isValidIdentifier(lexeme))// a - z, A-Z
                return Token(TokenType::ID_NAME, lexeme, index, 0);
            else
                return Token(TokenType::ERROR, lexeme, index, 0);
        }

        else if (isdigit(elem)) { // 0-9
            lexeme.clear();
            lexeme += elem;
            while (testTxtFile.get(elem) && isdigit(elem))
                lexeme += elem;
            testTxtFile.unget();
            return Token(TokenType::CONST, lexeme, index, 0);
        }

        else if (isOperator(elem)) { // + - =
            return Token(TokenType::OP, std::string(1, elem), index, 0);
        }

        else if (elem == '(')
        {
            lexeme.clear;
            lexeme += elem;
            if (testTxtFile.get(elem) && isdigit(elem))
            {
                lexeme += elem;
            }
            else
            {
                testTxtFile.unget();
                testTxtFile.unget();
                return Token(TokenType::DELIMITER, std::string(1, elem), index, 0);
            }
            if (elem == ',') lexeme += elem;
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    testTxtFile.unget();
                }
                return Token(TokenType::DELIMITER, std::string(1, elem), index, 0);
            }
            if (testTxtFile.get(elem) && isdigit(elem))
            {
                lexeme += elem;
            }
            else
            {   
                for (int i = 0; i < 4; i++)
                {
                    testTxtFile.unget();
                }
                return Token(TokenType::DELIMITER, std::string(1, elem), index, 0);
            }
            if (elem == ')') lexeme += elem;
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    testTxtFile.unget();
                }
                return Token(TokenType::DELIMITER, std::string(1, elem), index, 0);
            }
            return Token(TokenType::CONST, lexeme, index, 0);
        }

        else if (isDelimiter(elem)) {// ( ) [ ] { }
            return Token(TokenType::DELIMITER, string(1, elem), index, 0);
        }

        else {
            // Additional verification
            lexeme.clear();
            lexeme += elem;
            while (testTxtFile.get(elem) && !isspace(elem) && !isDelimiter(elem))
                lexeme += elem;
            testTxtFile.unget(); 
            return Token(TokenType::ERROR, lexeme, index, 0);
        }
    }

    return Token(TokenType::UNKNOWN, "", index, 0); // Plug
}


void LexicalAnalyzer::lexAnBeg() {
    Token token;
    while ((token = getNextLexeme()).type != TokenType::UNKNOWN)
        tokenList.addToken(token);

    tokenList.printTokensToFiles(outputFile, errorFile);
    tokenList.printTokensToConsole();
}
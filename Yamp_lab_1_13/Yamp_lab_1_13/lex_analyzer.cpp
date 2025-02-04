#include "lex_analyzer.h"
#include "tokens.h"
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;


bool LexicalAnalyzer::isOperator(char elem) const {
    return (elem == '+' || elem == '-' || elem == '=');
}

bool LexicalAnalyzer::isDelimiter(char elem) const {
    return (elem == '(' || elem == ')' || elem == ',');
}

bool LexicalAnalyzer::isWrongSymbol(char elem) const
{
    bool isNum = (elem == '0' || elem == '1' || elem == '2' || elem == '3' || elem == '4' || elem == '5' ||
        elem == '6' || elem == '7' || elem == '8' || elem == '9');
    return (!isDelimiter(elem) && !isOperator(elem) && !isalpha(elem) && !isNum && elem != ' ');
}

Token LexicalAnalyzer::getNextLexeme() {
    string lexeme;
    char elem;
    int curstate = 1; //состояния 1=начало, 2=названия, 3=инты, 4=операторы, 5=разделители+комплексные, 6=ошибки
    int index = 1;

    while (inputF.get(elem)) {
        switch (curstate) {
        case 1:
            if (isspace(elem)) {
                index++;
                continue;
            }

            if (isalpha(elem)) {
                curstate = 2;
                lexeme += elem;
            }
            else if (isdigit(elem)) {
                curstate = 3;
                lexeme += elem;
            }
            else if (isOperator(elem)) {
                curstate = 4;
                lexeme += elem;
            }
            else if (isDelimiter(elem)) {
                
                curstate = 5;
                lexeme += elem;
            }
            else {
                curstate = 6;
                lexeme += elem;
            }
            break;

        case 2:
            if (isalpha(elem)) {
                lexeme += elem;
                //Распознавание "PROGRAM"
                if (elem == 'R' && lexeme.size() == 2) {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'O') {
                            curstate = 2;
                        }
                        else if (elem == 'O') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'G') {
                                    curstate = 2;
                                }
                                else if (elem == 'G') {
                                    inputF.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        curstate = 6;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        if (elem != 'R') {
                                            curstate = 2;
                                        }
                                        else if (elem == 'R') {
                                            inputF.get(elem);
                                            lexeme += elem;
                                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                                curstate = 6;
                                                break;
                                            }
                                            else if (isalpha(elem)) {
                                                if (elem != 'A') {
                                                    curstate = 2;
                                                }
                                                else if (elem == 'A') {
                                                    inputF.get(elem);
                                                    lexeme += elem;
                                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                                        curstate = 6;
                                                        break;
                                                    }
                                                    else if (isalpha(elem)) {
                                                        if (elem != 'M') {
                                                            curstate = 2;
                                                        }
                                                        else if (elem == 'M') {
                                                            inputF.get(elem);
                                                            lexeme += elem;
                                                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                                                curstate = 6;
                                                                break;
                                                            }
                                                            else if (isalpha(elem)) {
                                                                return Token(5, lexeme, index, 0);
                                                            }
                                                            else if (elem == ' ') {
                                                                inputF.unget();
                                                                lexeme.erase(lexeme.end() - 1);
                                                                return Token(1, lexeme, index, 0);
                                                            }
                                                        }
                                                    }
                                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                        inputF.unget();
                                                        return Token(5, lexeme, index, 0);
                                                    }
                                                }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputF.unget();
                                                return Token(5, lexeme, index, 0);
                                            }
                                        }
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputF.unget();
                                        return Token(5, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                return Token(5, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputF.unget();
                        return Token(5, lexeme, index, 0);
                    }

                }
                //Распознавание "INTEGER"
                else if (elem == 'N' && lexeme == "IN") {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'T') {
                            curstate = 2;
                        }
                        else if (elem == 'T') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'E') {
                                    curstate = 2;
                                }
                                else if (elem == 'E') {
                                    inputF.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        curstate = 6;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        if (elem != 'G') {
                                            curstate = 2;
                                        }
                                        else if (elem == 'G') {
                                            inputF.get(elem);
                                            lexeme += elem;
                                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                                curstate = 6;
                                                break;
                                            }
                                            else if (isalpha(elem)) {
                                                if (elem != 'E') {
                                                    curstate = 2;
                                                }
                                                else if (elem == 'E') {
                                                    inputF.get(elem);
                                                    lexeme += elem;
                                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                                        curstate = 6;
                                                        break;
                                                    }
                                                    else if (isalpha(elem)) {
                                                        if (elem != 'R') {
                                                            curstate = 2;
                                                        }
                                                        else if (elem == 'R') {
                                                            inputF.get(elem);
                                                            lexeme += elem;
                                                            if (isdigit(elem) || isWrongSymbol(elem) || isOperator(elem) || isDelimiter(elem)) {
                                                                curstate = 6;
                                                                break;
                                                            }
                                                            else if (isalpha(elem)) {
                                                                curstate = 2;
                                                            }
                                                            else if (elem == ' ') {
                                                                inputF.unget();
                                                                return Token(2, lexeme, index, 0);
                                                            }
                                                        }
                                                    }
                                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                        inputF.unget();
                                                        return Token(5, lexeme, index, 0);
                                                    }
                                                }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputF.unget();
                                                return Token(5, lexeme, index, 0);
                                            }
                                        }
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputF.unget();
                                        return Token(5, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                return Token(5, lexeme, index, 0);
                            }
                        }
                        else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                            inputF.unget();
                            return Token(5, lexeme, index, 0);
                        }
                    }
                }
                //Распознавание CABS
                else if (elem == 'A' && lexeme == "CA") {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'B') {
                            curstate = 2;
                        }
                        else if (elem == 'B') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'S') {
                                    curstate = 2;
                                }
                                else if (elem == 'S') {
                                    inputF.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        curstate = 6;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        curstate = 2;
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputF.unget();
                                        lexeme.erase(lexeme.end() - 1);
                                        return Token(10, lexeme, index, 0);
                                    }
                                }

                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                return Token(5, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputF.unget();
                        return Token(5, lexeme, index, 0);
                    }
                }
                //Распознавание COMPLEX
                else if (elem == 'O' && lexeme == "CO") {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'M') {
                            curstate = 2;
                        }
                        else if (elem == 'M') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'P') {
                                    curstate = 2;
                                }
                                else if (elem == 'P') {
                                    inputF.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        curstate = 6;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        if (elem != 'L') {
                                            curstate = 2;
                                        }
                                        else if (elem == 'L') {
                                            inputF.get(elem);
                                            lexeme += elem;
                                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                                curstate = 6;
                                                break;
                                            }
                                            else if (isalpha(elem)) {
                                                if (elem != 'E') {
                                                    curstate = 2;
                                                }
                                                else if (elem == 'E') {
                                                    inputF.get(elem);
                                                    lexeme += elem;
                                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                                        curstate = 6;
                                                        break;
                                                    }
                                                    else if (isalpha(elem)) {
                                                        if (elem != 'X') {
                                                            curstate = 2;
                                                        }
                                                        else if (elem == 'X') {
                                                            inputF.get(elem);
                                                            lexeme += elem;
                                                            if (isdigit(elem) || isWrongSymbol(elem) || isOperator(elem) || isDelimiter(elem)) {
                                                                curstate = 6;
                                                                break;
                                                            }
                                                            else if (isalpha(elem)) {
                                                                curstate = 2;
                                                            }
                                                            else if (elem == ' ') {
                                                                inputF.unget();
                                                                return Token(2, lexeme, index, 0);
                                                            }
                                                        }
                                                    }
                                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                        inputF.unget();
                                                        return Token(5, lexeme, index, 0);
                                                    }
                                                }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputF.unget();
                                                return Token(5, lexeme, index, 0);
                                            }
                                        }
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputF.unget();
                                        return Token(5, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                return Token(5, lexeme, index, 0);
                            }
                        }
                        else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                            inputF.unget();
                            return Token(5, lexeme, index, 0);
                        }
                    }
                }
                //Распознавание CMPLX
                else if (elem == 'M' && lexeme == "CM") {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'P') {
                            curstate = 2;
                        }
                        else if (elem == 'P') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'L') {
                                    curstate = 2;
                                }
                                else if (elem == 'L') {
                                    inputF.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        curstate = 6;
                                        break;
                                    }
                                    
                                       else if (isalpha(elem)) {
                                            if (elem != 'X') {
                                                    curstate = 2;
                                             }
                                                else if (elem == 'X') {
                                                inputF.get(elem);
                                                lexeme += elem;
                                                if (isdigit(elem) || isWrongSymbol(elem)) {
                                                    curstate = 6;
                                                    break;
                                                }
                                                else if (isalpha(elem)) {
                                                    curstate = 2;
                                                }
                                                else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                    inputF.unget();
                                                    lexeme.erase(lexeme.end() - 1);
                                                    return Token(10, lexeme, index, 0);
                                                }
                                            }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputF.unget();
                                                return Token(5, lexeme, index, 0);
                                            }
                                        }
                                    }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                return Token(5, lexeme, index, 0);
                            }
                        }
                        else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                            inputF.unget();
                            return Token(5, lexeme, index, 0);
                        }
                    }
                //Распознавание END
                else if (elem == 'N' && lexeme == "EN") {
                    inputF.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'D') {
                            curstate = 2;
                        }
                        else if (elem == 'D') {
                            inputF.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                curstate = 6;
                                break;
                            }
                            else if (isalpha(elem)) {
                                curstate = 2;
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputF.unget();
                                lexeme = "END";
                                return Token(4, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputF.unget();
                        return Token(5, lexeme, index, 0);
                    }
                }
                //Распознавание любых других лексем 
                else {
                    while (inputF.get(elem) && isalpha(elem)) {
                        lexeme += elem;
                    }
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        curstate = 6;
                        lexeme += elem;
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputF.unget();
                        return Token(5, lexeme, index, 0);
                    }
                }
            }
            else if (isdigit(elem) || isWrongSymbol(elem)) {
                curstate = 6;
                lexeme += elem;
            }
            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                inputF.unget();
                return Token(5, lexeme, index, 0);
            }
            break;

        case 3:
            if (isdigit(elem)) {
                lexeme += elem;
            }
            else if (isalpha(elem)) {
                lexeme += elem;
                curstate = 6;
            }
            else {
                inputF.unget();
                    return Token(6, lexeme, index, 0);
            }
            break;

        case 4:
            inputF.unget();
            return Token(8, lexeme, index, 0);

        case 5:
            while (isdigit(elem))
            {
                lexeme += elem;
                inputF.get(elem);
                if (elem == ',')
                {
                    lexeme += elem;
                    inputF.get(elem);
                    while (isdigit(elem))
                    {
                        lexeme += elem;
                        inputF.get(elem);
                        if (elem == ')')
                        {
                            lexeme += elem;
                            return Token(7, lexeme, index, 0);
                        }
                        else curstate = 6;
                    }
                }
                else curstate = 6;
            }
            if (lexeme.size() == 1)
            {
                inputF.unget();
                return Token(9, lexeme, index, 0);
            }
            else curstate = 6;

        case 6:
            if (isspace(elem) || isDelimiter(elem) || isOperator(elem)) {
                inputF.unget();
                return Token(11, lexeme, index, 0);
            }
            else {
                lexeme += elem;
            }
            break;
        }
    }

    return Token(12, "", index, 0);
}

void LexicalAnalyzer::analyzer() {
    Token token;
    while ((token = getNextLexeme()).type != 12) {
        tokenList.newToken(token);
    }
    tokenList.outTable(outputF);
}
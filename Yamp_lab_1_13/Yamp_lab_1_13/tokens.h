#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

class Token {
public:
    int type;  //1=program, 2=type, 3=begin, 4=end, 5=id_name, 6=integer, 7=complex, 8=op, 9=delimetr, 10=function, 11=error, 12=unknown
    string lexeme;
    int index;
    int hash;

    Token() : type(12), lexeme(""), index(-1), hash(0) {}

    Token(int t, const string& lex, int idx, int hsh)
        : type(t), lexeme(lex), index(idx), hash(hsh) {
    }

    int getIndex();
    string getType();
};

#endif TOKEN_H  
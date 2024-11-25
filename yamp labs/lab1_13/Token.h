#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <fstream>


enum class TokenType {
    PROGRAM,        // Program -> Begin Descriptions Operators End
    BEGIN,          // PROGRAM Id
    END,            // END Id
    DESCRIPTIONS,   // Descriptions -> Descr | Descr Descriptions
    DESCR,          // Descr -> Type VarList
    TYPE,           // INTEGER | COMPLEX
    VARLIST,        // Id | Id , VarList
    OP,             // Id = Expr
    OPERATORS,      // Op | Op Operators
    ID_NAME,        // a-z,A-Z
    CONST,          // 0-9,(0-9,0-9)
    OPERATOR,       // Op | Op Operators
    DELIMITER,      // ( ) [ ] { } 
    ERROR,          // Ошибки
    SIMPLEEXPR,     // Id | Const | ( Expr ) | CMPLX ( Expr , Expr ) | CABS ( Expr ) Expr → SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr
    UNKNOWN
};

class Token {
public:
    TokenType type;
    std::string lexeme;
    int index = -1;
    int hash;
    Token() : type(TokenType::UNKNOWN), lexeme(""), index(-1), hash(0) {}

    Token(TokenType t, const std::string& lex, int idx, int hsh) : type(t), lexeme(lex), index(idx), hash(hsh) {}

    int getIndex();   // print index
    std::string getType(); // Recognition of the type of token for information output
};


#endif 
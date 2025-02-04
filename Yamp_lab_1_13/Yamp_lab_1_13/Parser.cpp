#include "Parser.h"

int operatorsCount = 0;
int countLines = 1;

//1=program, 2=type, 3=begin, 4=end, 5=id_name, 6=integer, 7=complex, 8=op, 9=delimetr, 10=function, 11=error, 12=unknown

void Parser::getNextToken()
{
    currentToken = lexer.getNextLexeme(); 
    lexer.tokenList.newToken(currentToken);
    if (currentToken.type == 11) {
        throw runtime_error("Lexical error: invalid token '" + currentToken.lexeme + "'");
    }
}

void Parser::Start(Node& n) {
    n.addSon("Begin");
    Program(n.getSon(n.children.size() - 1)); 

    n.addSon("Descriptions");
    Descriptions(n.getSon(n.children.size() - 1));

    n.addSon("Operators");
    Operators(n.getSon(n.children.size() - 1));

    n.addSon("End");
    End(n.getSon(n.children.size() - 1));
}

int deskrNodeCount = 1;

void Parser::Program(Node& n) {
    getNextToken();
    countLines++;
    if (currentToken.type == 1 && currentToken.lexeme == "PROGRAM") {
        n.addSon(currentToken.lexeme);
        getNextToken(); 
        if (currentToken.type == 5) {
            n.addSon(currentToken.lexeme);

            getNextToken(); 
        }
        else {
            throw runtime_error("Syntax error: token of unexpected type after PROGRAM with number: " +
                to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
        }
        
    }
    else {
        throw runtime_error("Syntax error: expected 'PROGRAM' in token with number: " + to_string(lexer.tokenList.tokenCount) 
            + ", got: " + currentToken.lexeme + " in line " + to_string(countLines)) ;
    }
}


void Parser::Descriptions(Node& n) {
    while (currentToken.type == 2) { 
        n.addSon("deskrNode" + to_string(deskrNodeCount));
        deskrNodeCount++;
        Descr(n.getSon(n.children.size() - 1));
    }
}

void Parser::Descr(Node& n) {
    if (currentToken.type == 2) {
        n.addSon(currentToken.lexeme);
        countLines++;

        getNextToken(); 
        if (currentToken.type == 5) {
            n.addSon("VarList");
            VarList(n.getSon(n.children.size() - 1));
        }
        else {
            throw runtime_error("Syntax error: expected new variable in token " + to_string(lexer.tokenList.tokenCount) 
                + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));

        }
        

    }
    else {
        throw runtime_error("Syntax error: expected type in token " + to_string(lexer.tokenList.tokenCount) 
            + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));
    }
}

void Parser::VarList(Node& n) {
    if (currentToken.type == 5) {
        n.addSon(currentToken.lexeme); 
        getNextToken(); 

        while (currentToken.type == 9 && currentToken.lexeme == ",") {
            getNextToken(); 

            if (currentToken.type == 5) {
                n.addSon(currentToken.lexeme); 
                getNextToken();
            }
            else {
                throw runtime_error("Syntax error: expected variable name after ',' in token " + to_string(lexer.tokenList.tokenCount) 
                    + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));
            }
        }

        
    }
}


void Parser::Operators(Node& n) {
    while (currentToken.type == 5) {
        operatorsCount++;
        countLines++;

        n.addSon("OpLine " + to_string(operatorsCount));
        Op(n.getSon(n.children.size() - 1));

    }
}

void Parser::Op(Node& n) {
    n.addSon(currentToken.lexeme); 
    getNextToken();

    if (currentToken.type == 8 && currentToken.lexeme == "=") {
        n.addSon(currentToken.lexeme);
        getNextToken();

        if (currentToken.type == 8) {
            throw runtime_error("Syntax error: unexpected operator '" + currentToken.lexeme +
                "' after '=' in operator ¹" + to_string(operatorsCount) +
                " in line " + to_string(countLines));
        }

        Expr(n.getSon(n.children.size() - 1));
    }
    else {
        throw runtime_error("Syntax error: expected '=' as start of operator ¹" +
            to_string(operatorsCount) + ", got: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }
}

void Parser::Expr(Node& n) {
    if (currentToken.type == 10 ||
        currentToken.type == 5 ||
        currentToken.type == 6 ||
        currentToken.type == 7 ||
        currentToken.lexeme == "(") {
        n.addSon("SimpleExpr");
        SimpleExpr(n.getSon(n.children.size() - 1));
    }
    else {
        throw runtime_error("Syntax error: expected operand, got: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }

    if (currentToken.type == 8 && currentToken.lexeme != "=") {
        string operatorLexeme = currentToken.lexeme;
        n.addSon(operatorLexeme);
        getNextToken();

        if (currentToken.type == 10 ||
            currentToken.type == 5 ||
            currentToken.type == 6 ||
            currentToken.type == 7 ||
            currentToken.lexeme == "(") {
            Expr(n.getSon(n.children.size() - 1)); 
        }
        else {
            throw runtime_error("Syntax error: expected operand after operator '" + operatorLexeme +
                "', got: " + currentToken.lexeme + " in line " + to_string(countLines));
        }
    }
}


void Parser::SimpleExpr(Node& n) {
    if (currentToken.lexeme == "(") {
        n.addSon("(");
        getNextToken();
        Expr(n.getSon(n.children.size() - 1));

        if (currentToken.lexeme == ")") {
            n.addSon(")");
            getNextToken();
        }
        else {
            throw runtime_error("Syntax error: expected ')', got: " + currentToken.lexeme +
                " in line " + to_string(countLines));
        }
    }
    else if (currentToken.type == 6) {
        n.addSon("INT_NUM");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == 7) {
        n.addSon("COMPLEX_NUM");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == 5) {
        n.addSon("ID_NAME");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.lexeme == ",") {
        getNextToken();
    }
    else if (currentToken.type == 10) {
        n.addSon(currentToken.lexeme);
        getNextToken();

        if (currentToken.lexeme == "(") {
            n.addSon("(");
            getNextToken();
            Expr(n.getSon(n.children.size() - 1));

            if (currentToken.lexeme == ",") {
                n.addSon(",");
                getNextToken();
                Expr(n.getSon(n.children.size() - 1));
            }

            if (currentToken.lexeme == ")") {
                n.addSon(")");
                getNextToken();
            }
            else {
                throw runtime_error("Syntax error: expected ')', got: " + currentToken.lexeme +
                    " in line " + to_string(countLines));
            }
        }
        else {
            throw runtime_error("Syntax error: expected '(', got: " + currentToken.lexeme +
                " in line " + to_string(countLines));
        }
    }
    else {
        throw runtime_error("Syntax error: unexpected token in SimpleExpr: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }
}




void Parser::End(Node& n)
{
    if (currentToken.type == 4 && currentToken.lexeme == "END") {
        n.addSon(currentToken.lexeme);
        countLines++;
        getNextToken();
        if (currentToken.type == 5) {
            n.addSon(currentToken.lexeme);
            getNextToken();
            
        }
        else {
            throw runtime_error("Syntax error: token of unexpected type after END, got: " + currentToken.lexeme
                + " with number : " + to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
        }

    }
    else {
        throw runtime_error("Syntax error: expected 'END' , got: " + currentToken.lexeme
            + " with number : " + to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
    }
}

Parser::Parser(LexicalAnalyzer& lexer) : lexer(lexer) {
    currentToken = Token(12, "", 50000, 0);
}

Node Parser::parse() {
    Node root("Program");
    Start(root);     
    return root;
}

#include "tokens.h"

// Возвращаем индекс токена
int Token::getIndex() {
    return index;
}

// Возвращаем тип токена
string Token::getType() {
    switch (type) {
    case 1:
        return "PROGRAM";
    case 2:
        return "TYPE";
    case 3:
        return "BEGIN";
    case 4:
        return "END";
    case 5:
        return "ID_NAME";
    case 6:
        return "INTEGER";
    case 7:
        return "COMPLEX";
    case 8:
        return "OP";
    case 9:
        return "DELIMITER";
    case 10:
        return "FUNCTION";
    case 11:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
#include <iostream>
#include "hash_table.h"
using namespace std;

void SpaceViz(int a, ofstream& outputF) {
    while (a > 0) {
        outputF << " ";
        a--;
    }
}

int HashTable::hashFunction(const string& lexeme) const {
    int hash = 0;
    for (char elem : lexeme)
        hash = (hash * 31 + elem) % HASH_SIZE;
    return hash;
}
void HashTable::newToken(const Token& token) {
    int hash = hashFunction(token.lexeme);

    if (tokens[hash] == nullptr) {
        tokens[hash] = new Token(token.type, token.lexeme, tokenCount, hash);
        tokenCount++;
    }
    else {
        if (tokens[hash]->lexeme == token.lexeme)
            return;

        int newHash = (hash + 1) % HASH_SIZE;
        while (tokens[newHash] != nullptr) {
            newHash = (newHash + 1) % HASH_SIZE;
        }
        tokens[newHash] = new Token(token.type, token.lexeme, tokenCount, newHash);
        tokenCount++;
    }
}
void HashTable::outTable(ofstream& outputF) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Token* token = new Token();
        for (int j = 0; j < HASH_SIZE; j++) {
            if (tokens[j] == nullptr)
                continue;

            if (i == getIndex(j)) {
                token = tokens[j];
                break;
            }
        }
        if (token->type != 12 && token->type != 11) {
            string tokenType = token->getType();
            outputF << " " << tokenType;
            SpaceViz(10 - tokenType.size(), outputF);
            outputF << "|  " << token->lexeme;
            SpaceViz(10 - token->lexeme.size(), outputF);
            outputF << "| " << token->hash << endl;
        }
    }
    outputF << endl;
    for (int i = 0; i < HASH_SIZE; i++) {
        Token* token = tokens[i];
        if (tokens[i] != nullptr && token->type == 11) {
            outputF << " " << "ERROR";
            SpaceViz(5, outputF);
            outputF << "|  " << token->lexeme;
            SpaceViz(10 - token->lexeme.size(), outputF);
            outputF << "| " << token->hash << endl;
        }
    }
}
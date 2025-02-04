﻿#include <iostream>
#include <fstream>
#include "lex_analyzer.h"
#include "Parser.h"
#include "Node.h"
#include "SemanticAnalyzer.h"

using namespace std;

int main() 
{
    try {
        setlocale(LC_ALL, "rus");
        ifstream inputF("input.txt");
        if (!inputF.is_open()) {
            cerr << "Unable to open input file" << endl;
            return 1;
        }
        LexicalAnalyzer lexer("input.txt", "output.txt");
        //lexer.analyzer();
        Parser parser(lexer);
        Node parseTree = parser.parse();
        ofstream outTreeFile("ParsingTree.txt");
        if (outTreeFile.is_open()) {
            parseTree.print(0, outTreeFile); // Передаем корневой узел и уровень отступов (начиная с 0)
            outTreeFile.close();
        }
        else {
            cerr << "Failed to open file for writing." << endl;
        }

        ofstream outputFile("output.txt");
        if (!outputFile.is_open()) {
            cerr << "Error: Unable to open output file!" << endl;
        }
        lexer.tokenList.outTable(outputFile);
        SemanticAnalyzer sem_anal = SemanticAnalyzer(parseTree);
        ofstream outPostfixFile("PostfixRecord.txt");
        if (outPostfixFile.is_open()) {
            sem_anal.printSematicAnalyzer(outPostfixFile);
            outPostfixFile.close();
        }
        else {
            cerr << "Failed to open file for writing." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
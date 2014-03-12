/*
 * lexer.h
 *
 *  Created on: 10-Mar-2014
 *      Author: Mukul Anand
 *      Author: Abhishek Bansal
 */

#ifndef LEXER_H_
#define LEXER_H_
#include "constants.h"
#include "LexerDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *getStream(FILE *fp, Buffer B, buffersize k);
// to get the next buffer filled up from source file
tokenPtr getNextToken(FILE *fp);
// to get the next token (to be called by the parser routine)
void initialize_lookUpTable();
// to initialize the lookUpTable (to be called in the beginning before the parser starts to work)
FILE *initializeBuffer(FILE *fp);
//to initialize the buffer for the first time before the parser starts to work
tokenPtr findToken(FILE **fp);
//returns the next tokenizes token
FILE *skipToSemiColon(FILE **fp);
// skips the lexical scanner to jump to the next semicolon or eof whichever it finds first
tokenPtr tokenize(Token token[10], long linenumber , Lexeme lexeme[21], Value value);
//tokenizes a token based on the values passed to it by the caller
#endif /* LEXER_H_ */

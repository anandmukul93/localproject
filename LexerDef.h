/*
 * LexerDef.h
 *
 *  Created on: 10-Mar-2014
 *      Author: Mukul Anand
 *      Author: Abhishek Bansal
 */

#ifndef LEXERDEF_H_
#define LEXERDEF_H_
#include "constants.h"

typedef long buffersize;
typedef char* Buffer;
typedef char Token ;
typedef char Lexeme;
typedef double Value ;
typedef int State;
typedef struct tokenInfo* tokenPtr;

char bufferArray[2][CONST_BUFFER_SIZE];
char lookUpTable[2][NUMBER_OF_KEYWORDS][MAX_SIZE_OF_KEYWORD];  // to store the lexeme as well as token
// lookUpTable[0][i] stores the token and lookUpTable [1][i] stores the lexeme value corresponding

int scanner , forward;
int bufferNo;   // to keep track which buffer is in use
int linenumber;
int flag;				//flag associated with checking whether we need to bring in buffer or not
int previousindex, previousbufferno; // for storing a value if we need to backtrack in DFA
int state;
struct tokenInfo{
Token token[MAX_SIZE_OF_KEYWORD];	// to store the token name of the lexeme
long  linenumber ;   // to store the line no. corresponding to the lexeme
Lexeme lexeme[MAX_ID_SIZE];  //to store the lexeme pattern
Value value; // to store the value if it is
tokenPtr nextToken;
};

#endif /* LEXERDEF_H_ */

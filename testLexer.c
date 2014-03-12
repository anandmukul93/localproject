/*
 * testLexer.c
 *
 *  Created on: 11-Mar-2014
 *      Author: Mukul Anand
 *      Author: Abhishek Bansal
 */
#include"Lexer.h"
int main(){
	FILE *fp;
	fp=fopen("inputfile.txt","r+");
	initialize_lookUpTable();

	tokenPtr token=getNextToken(fp);
	while(strcmp(tokenPtr->token,"EOF"))
	{
		printf("%s   %ld   %s   %lf\n",tokenPtr->token,tokenPtr->linenumber,tokenPtr->lexeme,tokenPtr->value);
	}

	fclose(fp);
}

/*
 * Lexer.c
 *
 *  Created on: 10-Mar-2014
 *      Author: Mukul Anand
 *gcc      Author: Abhishek Bansal
 */

/*
 *  This function takes the  input from the file pointed to by 'fp'.
 *  This file is the source code written in the given language.
 *  The function uses efficient technique to bring the fixed sized piece (of size k)
 *  of source code into the buffer B  for processing so as to avoid intensive I/O operations
 *  mixed with CPU intensive tasks.
 *  The function also maintains the file pointer after every access so that it
 *  can get more data into the memory on demand.
 *
 */
#include "Lexer.h"
#include "LexerDef.h"
FILE *getStream(FILE *fp, Buffer B, buffersize k){

	fread(B,sizeof(char),k,fp);
	return fp;
}


gcc
/*
 * initializes the lookup table with the keywords
 * from the file
 * 			-KEYWORDS.txt
 *
 */
void initialize_lookUpTable(){
	int i =0;
	FILE *fp=fopen("KEYWORDS.txt","r+");
	while(fscanf(fp,"%s %s",lookUpTable[0][i],lookUpTable[1][i++]));

	fclose(fp);
}



/**
 * this function is used to initialize the values of global variables as well as initialize the
 * bufferArray[0] for the first time with the source file.
 *
 */
FILE *initializeBuffer(FILE *fp){
	bufferNo=0;
	forward=scanner=0;
	flag=0;
		fp=getStream(fp,bufferArray[bufferNo],CONST_BUFFER_SIZE);
	return fp;
}


/*[anand@anand localproject]$ 

 * This function reads the input character stream and uses efficient mechanism to recognize lexemes.
 *  The function tokenizes the lexeme appropriately and returns all relevant information
 *  it collects in this phase (lexical analysis phase) encapsulated as  tokenInfo.
 *  The function also displays lexical errors appropriately .
 *  The input parameters are made flexible and students can select appropriate input parameters.
 *   The function also takes care of ignoring the white spaces and comments.
 *
 * @param:
 * 		fp- file stream pointer to source code
 */
tokenPtr getNextToken(FILE **fp){
	return findToken(fp);

}




/*
 *precondition : state is set to zero and the buffer is allocated and scanner =forward
 *postcondition : token identified and state 0 again in the end and scanner = forward
 *
 */

tokenPtr findToken(FILE **fp){
	char temp;
	char lexeme[21];
	tokenPtr nextToken=NULL;
	int  idlength=0;
	double  value=0;
	long long divider=10;


while(nextToken==NULL){
								// this complex buffer fetching is because of handling = and =/= and =/others
									// type of case
		if(forward==CONST_BUFFER_SIZE -1 && flag!=1)
		{
			*fp=getStream(*fp,bufferArray[1-bufferNo],CONST_BUFFER_SIZE);
			forward=0;
		}
		else if(forward==CONST_BUFFER_SIZE-1 && flag==1)
		{
			bufferNo=1-bufferNo;
			forward=0;
			flag=0;
		}

		temp=bufferArray[bufferNo][forward];

		switch(state){			// to implement the dfa in the form of switch cases
		case 0:                                   // We are in the start state
				switch(temp){
				case ';':
							nextToken=tokenize("SEMICOLON",linenumber,";" , 0);// tokenizing the (
							forward++;
										break;
				case '[':
							nextToken=tokenize("SQO",linenumber,"[",0);// tokenizing the (
							forward++;
										break;
				case ']':
							nextToken=tokenize("SQO",linenumber,"]",0);// tokenizing the (
							forward++;
										break;
				case '(':
							nextToken=tokenize("OP",linenumber , "(",0);// tokenizing the (
							forward++;
										break;
				case ')':nextToken=tokenize("CL",linenumber,")",0); // tokenizing the (
							forward++;
										break;
				case ',':nextToken=tokenize("COMMA",linenumber,",",0);// tokenizing the (
						forward++;
										break;
				case '+':nextToken=tokenize("PLUS",linenumber,"+",0);// tokenizing the (
							forward++;
										break;
				case '-':nextToken=tokenize("MINUS",linenumber,"-",0);// tokenizing the (
							forward++;
										break;
				case '*':nextToken=tokenize("MUL",linenumber,"*",0);// tokenizing the (
							forward++;
										break;
				case '/':nextToken=tokenize("DIV",linenumber,"//",0);// tokenizing the (
							forward++;
										break;
				case '@':nextToken=tokenize("SIZE",linenumber,"@",0);// tokenizing the (
							forward++;
										break;
				case '#':state=34;					// state to capture comment
										break;
				case '\n ':linenumber++;
							scanner=++forward;
										break;
				case '.':state=22;
						forward++;			// this state is for .and./  .or. / .not. identification
										break;
				case ' ':scanner=++forward;						// if space do nothing in the dfa in the 0 the state
										break;
				case '"':state=36;
							forward++;						// string starts
										break;
				case '<':state=11;          // the token can be < or <= so corresponding state
							forward++;
										break;
				case '>':state=14;			// the token can be > or >= so corresponding state
							forward++;
										break;
				case '=':state=17 	;		// the state can be assignment or == operator or =/= operator
							forward++;
										break;
				case '_': state=44;// function identifier;
							lexeme[idlength++]='-';
							forward++;
										break;

				case EOF:nexttoken=tokenize("EOF",linenumber,"$",0);// tokenizing the (
										break;
				default : if(temp>='a' && temp <=z || temp>='A' && temp<='Z'){	// tokenize ids and real no.s
							state =50;	// and integers
							lexeme[idlength++]=temp;
							forward++;

						}
						else if(temp<='9' && temp>='0')					// here integers tokenized
						{
							state=39;
							forward++;
							value=value*10+('temp'-'0');
						}
						else{
								state=100;            //to  error state
						}
										break;
				}     // inner switch ends for start state

										break;

/*
 * dfa part capturing .and. / .or / .not.
 */


		case 22: if(temp=='a'){// for .and. .or. and .not. identification
				state=23;
				forward++;
			}
		else if(temp=='o'){
			state=26;
			forward++;
		}
		else if(temp=='n'){
			state=28;
			forward++;
		}
		else
			{state=100;}
										break;

/**
 * dfa part capturing .and.
 */

		case 23:if(temp=='n')				//detecting n of .and.
			{state=24;forward++;}
		else
			state=100;
									break;
		case 24:if(temp=='d'){				//detecting d of .and.
			state=25;forward++;
		}
		else
			state=100;
								break;
		case 25:if(temp=='.')				// detecting last '.' of .and.
		{
			nextToken=tokenize("AND",linenumber,".and.",0);
			forward++;
			state=0;
		}
		else
			state=100;
								break;


/**
 * dfa part detecting .or.
 */

		case 26:if(temp=='r'){    //detecting r of .or.
					state=27;
					forward++;
				}
				else
					state=100;
								break;

		case 27: if(temp=='.'){				//detecting last '.' of .or.
					nextToken=tokenize("OR",linenumber,".or.",0);
					state=0;
					forward++;
				}
				else
					state=100;
								break;


/**
 * dfa part capturing .not.
 */
		case 28:if(temp=='o'){        //detecting o of .not.
			state=29;
			forward++;
		}
		else
			state=100;
						break;

		case 29: if(temp=='t'){			//detecting t of .not.
					state=30;
					forward++;
				}
				else{
					state=100;
				}
							break;
		case 30: if(temp=='.'){
			nextToken=tokenize("NOT",linenumber,".not.",0);
			state=0;
			forward++;
		}
/**
 * dfa part capturing string constant
 */


		case 36:if(temp>='a' && temp <='z')//string constant capture
				{state=37;forward++;}
				else
					state=100;
										break;
		case 37: if(temp<='z' && temp>='a'){
					forward++;
				}
				else if(temp=='"')
				{
					nextToken=tokenize("STR",linenumber,"---",0);
					state=0;
					forward++;
				}
				else
					state=100;

										break;


/**dfa part for capturing comments
 *
 */


		case 34: if(temp=='\n'){					// comment found state
						linenumber++;
						scanner=++forward;
						state=0;
					}
				else if(temp==EOF)
					state=0;
				else
					forward++;

/**
 * dfa part for capturing < and <=
 */

										break;
		case 11:if(temp=='=') {   // the token can be < or <=
				nextToken=tokenize("LE",linenumber,"<=",0)
					forward++;
					state=0;
				}
				else{
					nextToken=tokenize("LT",linenumber,"<",0);
					state=0;
				}

/**
 * dfa part for capturing > or >=
 */

										break;
		case 14:	if(temp=='=') {   			// the token can be > or >=
			nextToken=tokenize("GE",linenumber,">=",0)
				forward++;
				state=0;
			}
			else{
				nextToken=tokenize("GT",linenumber,">",0);
				state=0;
			}						// the token can be > or >=
										break;


/**
 * dfa part for capturing = and == and =/=
 */

		case 17:if(temp=='/')		// the token can be = or == or =/= or   EQ  DIV
					{state=18;previousindex=forward;
							previousbufferno=bufferNo;
					forward++;}
				else if(temp=='='){
					nextToken=tokenize("EQ",linenumber,"==",0);
					state=0;
					forward++;
				}
				else
				{
					nextToken=tokenize("ASSIGNOP",linenumber,"=",0);
					state=0;
				}
										break;
		case 18:if(temp=='='){				// detecting the last = of =/
			nextToken=tokenize("NE",linenumber,"=/=");
			state=0;
			forward++;
		}
			else{				// handling the "=/others" case where there should be backtracking
				nextToken=tokenize("ASSIGNOP",linenumber,"=",0);
				state=0;
									forward=previousindex;
									if(bufferNo!=previousbufferno)
										flag=1;
									bufferNo=previousbufferno;

			}


/**
 * dfa for identifying real and integer no.s
 */
		case 39:if(temp<='9'&& temp>='0'){// identifying the real of integer no.
					value=value*10+(temp-'0');
					forward++;
				}
				else if(temp=='.'){			// handling the real no.s
					state=41;
					previousindex=forward;
					previousbufferno=bufferNo;
					forward++;
				}
				else{
					nextToken=tokenize("NUM",linenumber,"---",value);
					state=0;
				}

										break;

/**
 * capturing the case of real numbers and eg.-   1331313.and. which should be NUM AND
 */
		case 41:if(temp<='9'&& temp>='0'){
						forward++;
						value=value+(double)(temp-'0')/divider;
						divider*=10;
						state=42;
				}
				else if(temp=='a'||temp=='o' ||temp =='n')
				{
					nextToken=tokenize("NUM",linenumber,"---",value);
					forward=previousindex;
					if(bufferNo!=previousbufferno)
						flag=1;
					bufferNo=previousbufferno;
				}
				else
					state=100;
										break;


		case 42: if(temp<='9'&& temp>='0'){
					value=value+(double)(temp-'0')/divider;
					divider*=10;
					forward++;
				}
				else{
					nextToken=tokenize("RNUM",linenumber,"---",value);
					state=0;
				}
										break;


/**
 * dfa identifying the function identifiers
 *max length can be 20 characters
 *
 */

		case 44:if((temp>='a' && temp<='z') || (temp<='Z'&& temp>='A')){// identifying the function identifiers
					lexeme[idlength++]=temp;
					forward++;
					state=45;
				}
			else
				state=100;				//error no function type id found
										break;

		case 45: if((temp>='a'&& temp<='z')||(temp>='A'&& temp<='Z')||(temp>='0'&& temp<='9')){
					if(idlength<=19)
					{lexeme[idlength++]=temp;
					forward++;}
					else
						state=100;   // error state , function id name has more than 20 characters

				}
				else {
					if(strcmp(lexeme,"_main")==0)
					nextToken=tokenize("MAIN",linenumber,"_main",0);
					else
					nextToken=tokenize("FUNID",linenumber,lexeme,0);
					state=0;
				}
										break;


/**
 * dfa identifying the general identifiers a
 * max length can be 20 characters
 */
		case 50:if((temp>='a'&& temp<='z')||(temp<='Z'&& temp>='A'))	// ID capturing state
				{		if(idlength<MAX_ID_SIZE-1){
						lexeme[idlength++]=temp;
						forward++;
						}
						else{
							state=100;    //length of id >20  so error state(100)
						}
				}
				else if(temp>='0'&& temp<='9'){
					if(idlength<MAX_ID_SIZE-1){		// a digit can only be the last character and only
													// one digit at end allowed
						lexeme[idlength++]=temp;
						state=0;
						nextToken=tokenize("ID",linenumber,lexeme,0);
					}
					else
					{
						nextToken=tokenize("ID",linenumber,lexeme,0);
						state=0;
					}

				}
				else{
						state=0;
						int k;
						if(k=searchLookUpTable(lexeme)!=-1)// searching the lookup table if any keyword exist
															// with the same name
						nextToken=tokenize(lookUpTable[0][k],linenumber,lookUpTable[1][k],0);
						else
						nextToken=tokenizer("ID",linenumber,lexeme,0);
				}



										break;

/**
 * THIS is the ERROR state and this is encountered anywhere when the dfa is unable to proceed
 * so this will just make an ERROR token and send and fast forward the forward to the next
 * SEMICOLON
 * and send the error token to the syntax analyzer
 *
 *the syntax analyzer also pops its contents till it finds another semicolon in its stack ADT
 */

		case 100:
			nextToken=tokenize("ERROR",linenumber,"---",0);
			*fp=skipToSemicolon(*fp);    // lexical error detected so pushing to semicolon
			state=0;
										break;

		} //  outer switch ends


	}
	scanner=forward;
	return nextToken;


}



/**
 * In case of error this function is called to skip the scanner and the forward index
 * till the next semicolon is found
 *
 * A useful means is to not make the tokens till the next semicolon as they will not be used
 * as the syntax analyzer also skips to the next semicolon
 *
 *
 */
FILE *skipToSemicolon(FILE *fp){
	while(bufferArray[bufferNo][forward]!=';'&& bufferArray[bufferNo][forward]!=EOF){
		if(bufferArray[bufferNo][forward]=='\n')
			linenumber++;
		forward++;
		if(forward==CONST_BUFFER_SIZE){
			fp=getStream(fp,bufferArray[1-bufferNo],CONST_BUFFER_SIZE);
			forward=0;
		}
	}
	return fp;
}



/***
 *
 * this function is used to check if any ID matches the keywords stored in the lookup table
 *input: the ID's
 *output:the index in the corresponding symbol table to which it matches
 *output:-1 if it does not match any keyword
 *
 *
 */
int searchLookUpTable(const char *comparisonString){
	for(int i=0;i<NUMBER_OF_KEYWORDS;i++){
		if(strcmp(comparisonString,lookUpTable[1][i])==0) // 1 is the part of the lexeme table which stores
			return i;									// returns the token of keyword that matches if found
	}
	return -1;
}


/**
 *
 * this function is used to make a token of each lexeme
 * It allocates a memory in heap and assigns the different values to it
 * ans returns a pointer to it
 *
 * input : the parameters for the lexeme
 * returns: the pointer to the tokenInfo node allocated in heap
 *
 */
tokenPtr tokenize(Token token , long linenumber, Lexeme lexeme , Value value){
	tokenPtr tempptr;

	tempptr=(TokenPtr)malloc(sizeof(struct tokenInfo));
	strcpy(tempptr->token,token);
	tempptr->linenumber =linenumber;
	strcpy(tempptr->lexeme, lexeme);
	tempptr->value = value ;
	tempptr->nextToken=NULL;	// to be used if we maintain a list of these lexemes in the later stage
								// of implementation

return tempptr;
}

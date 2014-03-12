/*
*Actual implementations of the various functions required to 
* make the preprocessor for the compiler 
*
*Created by :- Anand Mukul 
*Date :- 24th july 2014 
*
*/

/*
* inputs :
*   input-the file name of  the input file.
*   output-the file name of  the output file  
*
* precondition - the input file contains the source code to 
* 			preprocess 
*postcondition - the output file contains comments free code 
*  
* 
*/
char line[10000];
void preprocessorControlFunction(char* input  ,char* output){
	FILE *inpt, *outpt ;	
	while(!eof(input)){
		inpt= fopen(input,"r");
		//take a line 
		//if blank remove the line but insert a line break in the output file as well
		// if contains some character preprocess till semicolon  or end of line 
		outpt=fopen(output, "w");
		fgets(inpt,line);
		lineProcessor(line);
	}

}

/*inputs: 
*		line - to take the pointer to the line to processed 
*
*precondition- unedited line 
*postcondition - edited line to be added to output file 
*
*
*/
void lineProcessor(char* line ){
	while(!eof(line)){
			
	
	}

}

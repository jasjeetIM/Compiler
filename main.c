/* 
 * File: P1/main.c
 * Desc: This file contains the entry point to P1.
 * Author: Jasjeet Dhaliwal
 * Date: 01/10/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "Env.h"
#include "Node.h"
#include "y.tab.h"


/* Buffer to read from stdin to a file -- needed for forking CPP, and then the parser */ 
#define BUFFER 1024

/* Pointer used as input stream by lex.yy.c */
extern FILE * yyin; 

/* Requiredglobal namespace/environment */
Env * top = NULL;  

/* Required global root of the AST */ 
Node * unit;   


/* Insert keywords into symbol table */
int insertKeyWords(Env * env); 

int main (int argc, char * argv[]) {
	
        int read; 
	void * content = malloc(BUFFER); 
	Env * newTop = NULL; 
	FILE * yyFile, * in;
	
	/* Reading from stdin and writing to a file Input.txt which will be 
           as input to the parser */
	yyFile = fopen("Input.txt", "w");
	if (yyFile == 0) printf ("Error in opening file to save input stream\n"); 
	 if (feof(stdin)) printf ("Stdin in already in EOF state"); 


    	while ((read = fread(content, 1, BUFFER, stdin))) {
        	fwrite(content, read, 1, yyFile);
    	}
    	if (ferror(stdin)) printf("There was an error while reading from stdin\n");

	fseek(yyFile, 0, SEEK_SET); 
    	fclose(yyFile); 
 
	/* Evoking CPP as the preprocessor */
	if(!(in = popen("cpp Input.txt", "r"))){
        	exit(1);
    	}

    	printf("CPP output starts here ... \n\n"); 
	while(fgets(content, BUFFER, in)!= NULL){
        	printf("%s", content);
    	}

	printf("\n\nEnd of CPP output. ");   
	
        /* Prepping the file Input.txt which will be used as input to the parser/scanner */ 
	yyin = fopen("Input.txt", "r");
	if (yyin == 0) {
		printf("Error with opening input file for the lexer.\n"); 
	} 
	top = createEnv(newTop);  
	
	
	/*Begin inserting keywords into Symbol Table now ...*/           	if (!(insertKeywords(top))) exit(EXIT_FAILURE); 
       /*Completed inserting keywords into Symbol Table */ 	



	/*Scanning will begin now... */


	printf("\n\nScanner/Parser output starts here ...\n\n"); 
	printf("Token               Line Number\n\n"); 	
	yyparse(); 
	
	printTree(unit);
	deleteTree(unit); 
 
	fclose(yyFile); 
	destroyEnv(top); 
	return 0; 
} 



int insertKeywords(Env * env) {



insertType(env,"typedef", 0, TYPEDEF);
insertType(env,"sizeof", 0, SIZEOF);
insertType(env,"extern", 0, EXTERN);
insertType(env,"static", 0, STATIC);
insertType(env,"auto", 0, AUTO);
insertType(env,"register", 0, REGISTER);
insertType(env,"inline", 0, INLINE);
insertType(env,"const", 0, CONST);
insertType(env,"restrict", 0, RESTRICT);
insertType(env,"volatile", 0, VOLATILE);
insertType(env,"bool", 0, BOOL);
insertType(env,"char", 0, CHAR);
insertType(env,"short", 0, SHORT);
insertType(env,"int", 0, INT);
insertType(env,"long", 0, LONG);
insertType(env,"signed", 0, SIGNED);
insertType(env,"unsigned", 0, UNSIGNED);
insertType(env,"float", 0, FLOAT);
insertType(env,"double", 0, DOUBLE);
insertType(env,"void", 0, VOID);
insertType(env,"complex", 0, COMPLEX);
insertType(env,"imaginary", 0, IMAGINARY);
insertType(env,"struct", 0, STRUCT);
insertType(env,"union", 0, UNION);
insertType(env,"enum", 0, ENUM);
insertType(env,"case", 0, CASE);
insertType(env,"default", 0,DEFAULT);
insertType(env,"if", 0, IF);
insertType(env,"else", 0, ELSE);
insertType(env,"switch", 0, SWITCH);
insertType(env,"while", 0, WHILE);
insertType(env,"do", 0, DO);
insertType(env,"for", 0, FOR);
insertType(env,"goto", 0, GOTO);
insertType(env,"continue", 0,CONTINUE);
insertType(env,"break", 0, BREAK);
insertType(env,"return", 0, RETURN);
insertType(env,"alignas", 0, ALIGNAS);
insertType(env,"alignof", 0, ALIGNOF);
insertType(env,"atomic", 0, ATOMIC);
insertType(env,"generic", 0, GENERIC);
insertType(env,"noreturn", 0, NORETURN);
insertType(env,"static_assert", 0, STATIC_ASSERT);
insertType(env,"thread_local", 0, THREAD_LOCAL);
insertType(env,"attribute", 0, ATTRIBUTE);

 return 1;
}

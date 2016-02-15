/*
 * File: P1/csan.l
 * Desc: This is the file inputed to the Flex scanner for generating
 *	 the cscan.c file to be used by the compiler. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/13/2016
 */ 




O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\f]
comments (\/\/.*|#.*)


%{

#include <stdio.h>
#include "Env.h"
#include "y.tab.h"
#include "Node.h"

void pragmaHandler(void); 
void commentR(void); 
void yyerror(char *); 
int linenum = 1; 
char prag[]= "pragma";  
char byte[] = "byte_order"; 
char push[] = "push"; 
char pop[] = "pop"; 
char little[] = "little"; 
char big[] = "big"; 
int byteOrder = 0; 

#ifndef YYSTYPE
#define YYSTYPE int
#endif 

%}


%%

{comments}		{pragmaHandler();}                 
"/*"                    {commentR(); }


"auto"			{ printf("%-20s%10d\n",yytext,linenum);   yylval.str=strdup(yytext); return(AUTO); }
"break"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(BREAK); }
"case"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(CASE); }
"char"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(CHAR); }
"const"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(CONST); }
"continue"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(CONTINUE); }
"default"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(DEFAULT); }
"do"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(DO); }
"double"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(DOUBLE); }
"else"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ELSE); }
"enum"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ENUM); }
"extern"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(EXTERN); }
"float"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(FLOAT); }
"for"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(FOR); }
"goto"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(GOTO); }
"if"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(IF); }
"int"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(INT); }
"long"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(LONG); }
"register"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(REGISTER); }
"return"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(RETURN); }
"short"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(SHORT); }
"signed"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(SIGNED); }
"sizeof"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(SIZEOF); }
"static"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(STATIC); }
"struct"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(STRUCT); }
"switch"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(SWITCH); }
"typedef"		{ printf("%-20s%10d\n",yytext,linenum);  yylval.str=strdup(yytext);return(TYPEDEF); }
"union"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(UNION); }
"unsigned"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(UNSIGNED); }
"void"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(VOID); }
"volatile"		{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(VOLATILE); }
"while"			{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(WHILE); }
"inline"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(INLINE); }
 "restrict"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(RESTRICT); }
"complex"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(COMPLEX); }
"imaginary"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(IMAGINARY); }

"alignas"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ALIGNAS); }

"alignof"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ALIGNOF); }

"atomic"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ATOMIC); }

"generic"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(GENERIC); }
"noreturn"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(NORETURN); }

"static_assert"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(STATIC_ASSERT); }

"thread_local"                 { printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(THREAD_LOCAL); }

"__attribute__" 	{ printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(ATTRIBUTE); }





{L}{A}*         	{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return (getType(top, yytext));  
			}
{HP}{H}+{IS}?           {		
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(I_CONSTANT); 
			}
{NZ}{D}*{IS}?		{		
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(I_CONSTANT); 
			}
	
"0"{O}*{IS}?		{		
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(I_CONSTANT); 
			}

{CP}?"'"([^'\\\n]|{ES})+"'"	{		
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(I_CONSTANT); 
			}

{D}+{E}{FS}?		{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}

{D}*"."{D}+{E}?{FS}?	{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}

{D}+"."{E}?{FS}?	{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}

{HP}{H}+{P}{FS}? 	{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}

{HP}{H}*"."{H}+{P}{FS}? {	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}

{HP}{H}+"."{P}{FS}?	{	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(F_CONSTANT); 
			}	        
({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+ {	
				printf("%-20s%10d\n",yytext,linenum); yylval.str=strdup(yytext); return(STRING_LITERAL); 
			}

"..."			{ printf("%-20s%10d\n",yytext,linenum); return(ELLIPSIS); }
">>="			{ printf("%-20s%10d\n",yytext,linenum); return(RIGHT_ASSIGN); }
"<<="			{ printf("%-20s%10d\n",yytext,linenum); return(LEFT_ASSIGN); }
"+="			{ printf("%-20s%10d\n",yytext,linenum);return(ADD_ASSIGN); }
"-="			{ printf("%-20s%10d\n",yytext,linenum);  return(SUB_ASSIGN); }
"*="			{ printf("%-20s%10d\n",yytext,linenum);  return(MUL_ASSIGN); }
"/="			{ printf("%-20s%10d\n",yytext,linenum);  return(DIV_ASSIGN); }
"%="			{ printf("%-20s%10d\n",yytext,linenum);  return(MOD_ASSIGN); }
"&="			{ printf("%-20s%10d\n",yytext,linenum); return(AND_ASSIGN); }
"^="			{ printf("%-20s%10d\n",yytext,linenum); return(XOR_ASSIGN); }
"|="			{ printf("%-20s%10d\n",yytext,linenum);  return(OR_ASSIGN); }
">>"			{ printf("%-20s%10d\n",yytext,linenum);  return(RIGHT_OP); }
"<<"			{ printf("%-20s%10d\n",yytext,linenum);  return(LEFT_OP); }
"++"			{ printf("%-20s%10d\n",yytext,linenum);  return(INC_OP); }
"--"			{ printf("%-20s%10d\n",yytext,linenum); return(DEC_OP); }
"->"			{ printf("%-20s%10d\n",yytext,linenum);  return(PTR_OP); }
"&&"			{ printf("%-20s%10d\n",yytext,linenum);  return(AND_OP); }
"||"			{ printf("%-20s%10d\n",yytext,linenum);  return(OR_OP); }
"<="			{ printf("%-20s%10d\n",yytext,linenum); return(LE_OP); }
">="			{ printf("%-20s%10d\n",yytext,linenum);  return(GE_OP); }
"=="			{ printf("%-20s%10d\n",yytext,linenum);  return(EQ_OP); }
"!="			{ printf("%-20s%10d\n",yytext,linenum); return(NE_OP); }
";"			{ printf("%-20s%10d\n",yytext,linenum);  return(';'); }
("{"|"<%")		{ printf("%-20s%10d\n",yytext,linenum);  return('{'); }
("}"|"%>")		{ printf("%-20s%10d\n",yytext,linenum);  return('}'); }
","			{ printf("%-20s%10d\n",yytext,linenum);  return(','); }
":"			{ printf("%-20s%10d\n",yytext,linenum);  return(':'); }
"="			{ printf("%-20s%10d\n",yytext,linenum);  return('='); }
"("			{ printf("%-20s%10d\n",yytext,linenum);  return('('); }
")"			{ printf("%-20s%10d\n",yytext,linenum);  return(')'); }
("["|"<:")		{ printf("%-20s%10d\n",yytext,linenum);  return('['); }
("]"|":>")		{ printf("%-20s%10d\n",yytext,linenum);  return(']'); }
"."			{ printf("%-20s%10d\n",yytext,linenum);  return('.'); }
"&"			{ printf("%-20s%10d\n",yytext,linenum);  return('&'); }
"!"			{ printf("%-20s%10d\n",yytext,linenum);  return('!'); }
"~"			{ printf("%-20s%10d\n",yytext,linenum);  return('~'); }
"-"			{ printf("%-20s%10d\n",yytext,linenum);  return('-'); }
"+"			{ printf("%-20s%10d\n",yytext,linenum);  return('+'); }
"*"			{ printf("%-20s%10d\n",yytext,linenum);  return('*'); }
"/"			{ printf("%-20s%10d\n",yytext,linenum);  return('/'); }
"%"			{ printf("%-20s%10d\n",yytext,linenum);  return('%'); }
"<"			{ printf("%-20s%10d\n",yytext,linenum);  return('<'); }
">"			{ printf("%-20s%10d\n",yytext,linenum);  return('>'); }
"^"			{ printf("%-20s%10d\n",yytext,linenum);  return('^'); }
"|"			{ printf("%-20s%10d\n",yytext,linenum);  return('|'); }
"?"			{ printf("%-20s%10d\n",yytext,linenum);  return('?'); }
\n			{++linenum;}
.			/*do nothing */
{WS}+                   /* do nothing */ 

%%


int getType(Env * top, char * str){
	
	if (typeExists(top, str))return (typeExists(top, str));        	
	 else return IDENTIFIER; 

}

void commentR(void)
{
    int c;

    while ((c = input()) != 0) {
        if (c=='\n') ++linenum;
	if (c == '*')
        {
            while ((c = input()) == '*'); 

	   if (c =='\n') ++linenum;  

            if (c == '/')
                return;

            if (c == 0)
                break;
         }
	}
    yyerror("Unterminated comment");
}

/* 1 is Big and 0 is small */
void pragmaHandler(void) {


    if(strstr(yytext, prag) != NULL) {
     	
		if((strstr(yytext, byte) != NULL)) {
				
				if ((strstr(yytext,push)) !=NULL) {
					
					if ((strstr(yytext,little)) != NULL) {
				
						if (byteOrder == 1) {
							printf("Pushing Little Endian ...%10d\n", linenum);
							byteOrder = 0;
							return;   	
						}
					
						else {
							printf("Error: already using Little Endian ...%10d\n", linenum); 
							return; 
						}	
		        		}		 
			

					else if ((strstr(yytext,big)) !=NULL) {
					
						if (byteOrder == 0) {			
				 			printf ("Pushing Big Endian ....%10d\n", linenum); 	
							byteOrder = 1;
							return;  
						}
						
						else {
							printf("Error: already using Big Endian...%10d\n", linenum); 
							return; 
						}
					}
			}
			else if ((strstr(yytext, pop)) != NULL) {
				if (byteOrder == 0) {
			     	 printf("Popping Little Endian and pushing Big Endian ...%5d\n", linenum);  				
			      byteOrder = 1;
			      return; 
			}
			else if (byteOrder == 1) {
			    printf("Popping Big Endian and pushing Little Endian ...%5d\n", linenum); 
			    byteOrder = 0;
			    return; 	 			
			}	
		} 
	}
     }
  return;   
}


int yywrap() {
 return 1; 
}	

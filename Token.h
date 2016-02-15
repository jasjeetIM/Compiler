/*
 * File: P1/Token.h
 * Desc: This file defines the Token structure used by the SymbolEntry
 *       struct. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/10/2016
 *
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>

typedef struct Token {

	int id, line_num;  
        char * lexeme; 

}Token; 

#endif

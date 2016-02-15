/*
 * File: P1/SymbolEntry.h
 * Desc: This defines the SymbolEntry structure to be used by the SymbolTable
 *       class. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/10/2016
 *
 */

#ifndef SYMBOLENTRY_H
#define SYMBOLENTRY_H


#include <stdlib.h>
#include "Token.h"

typedef struct SymbolEntry { 
        Token * token; 
        struct SymbolEntry * next; 
}SymbolEntry; 

#endif

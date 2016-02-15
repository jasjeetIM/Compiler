/*
 * File: P1/SymbolTable.h
 * Desc: Defines functions to be implemented by the Symbol Table.
 * Author: Jasjeet Dhaliwal
 * Date: 1/10/2016
 *
 */

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdio.h>
#include <string.h>
#include "SymbolEntry.h"
#include "Token.h"

typedef struct SymbolTable {

	size_t size, max_size, curr_size;  
	float max_load;   
	SymbolEntry ** tbl_nodes; 
} SymbolTable; 

SymbolTable * createTable(size_t size);
int stDestroy (SymbolTable * table);  
int stInsert(SymbolTable * table, const char * str, int lm, int ID);
int stGet(SymbolTable * table, const char * str); 
int stGetLex(SymbolTable * table, const char * str); 
int stRemove (SymbolTable * table, const char * str); 
unsigned long st_hash (SymbolTable * table, const char * str); 
int stResize (SymbolTable * table); 


#endif

/* 
 * File: P1/Env.h
 * Desc: This is the environment of the current symbol table. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/23/2016
 *
 */

#ifndef ENV_H
#define ENV_H
#define TABLESIZE 1000

#include "SymbolTable.h"



typedef struct Env {
	SymbolTable * table;
	SymbolTable * typeTable; 
	struct Env * prev; 
} Env; 

Env * createEnv(Env * prev); 
int destroyEnv(Env * env); 
int idExists(Env* env, char * str); 
int typeExists(Env * env, char * str); 
int insertID (Env *env, char * str, int ln, int id); 
int insertType(Env * env, char * str, int ln, int id); 


extern Env * top; 

#endif

/*
 * File: P1/Env.c
 * Desc: Implements the Env class which will be used for managing scopes. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/23/2016
 *
 */

#include "Env.h"



/* Constructor for the environment object */

Env * createEnv (Env * prev)  {
	Env * env;  	
	if (!(env = malloc(sizeof(Env)))) return 0; 
	
	 
	if (!(env->table=createTable(TABLESIZE))) return 0; 

	
	if (!(env->typeTable=createTable(TABLESIZE))) return 0; 

	env->prev = prev;
        return env; 
}


/* Destructor for the environment object */ 
int destroyEnv(Env * env) {
	if (!(stDestroy(env->table))) return 0; 
	
	if (!(stDestroy(env->typeTable))) return 0; 

	free (env);
        return 1; 
}



/* Checks if a string has been added to the Symbol Table for Identifiers */ 
int idExists(Env * env, char * str) {
	int i  = 0;
	Env * temp = env;  
	while (temp) {
		if((stGet(temp->table, str))) return 1; 
		else {temp= temp->prev; i++; } 
	}
	return 0; 
}	



/* Checks if a string has been added to the Symbol Table for Typedefs and Enums */ 
int typeExists(Env * env, char * str) {
	int i = 0; 
	Env * temp = env; 
	while (temp) {
		if ((stGet(temp->typeTable, str))) return (stGet(temp->typeTable, str));	
		else {temp =temp->prev; i++; }
	}
	return 0; 
}

/* Inserts a token into the identifier symbol table */ 	
int insertID (Env * env, char * str, int lm, int id) {
	if (!(stInsert(env->table, str, lm, id))) return 0; 
	return 1; 

}

/* Inserts a token into the typedef/enum symbol table */ 
int insertType (Env * env, char * str, int ln, int id) {
	if (!(stInsert(env->typeTable, str, ln, id))) return 0; 
	return 1; 
}












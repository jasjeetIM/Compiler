/*
 * File: P1/SymbolTable.c
 * Desc: This is an implementation file for the SymbolTable class. 
 * Author: Jasjeet Dhaliwal
 * Date: 1/10/2016
 *
 */

#include "SymbolTable.h"



/* Constructor for the symbol table object */
SymbolTable * createTable(size_t size) {
	SymbolTable * table; 
    if (!(table = (SymbolTable *)malloc(sizeof(SymbolTable))))
	return NULL; 

  
    if (!(table->tbl_nodes = (SymbolEntry**)calloc(size, sizeof(SymbolEntry*))))
    {
	free(table); 
	return NULL; 
    }
    table->size = size; 
    table->max_load = 0.90f; 
    table->max_size = (size_t)(table->max_load * size); 
    table->curr_size = 0; 	
    return table; 
}


/* Desctructor for the symbol table object */
int stDestroy (SymbolTable * table) {
	size_t index;
	SymbolEntry * node, * oldnode; 
	for(index=0; index<table->size; ++index)
	{
		node = table->tbl_nodes[index]; 
         	while (node)
		{
			free(node->token->lexeme);
			free(node->token);  
			oldnode = node; 
			node = node->next; 
			free(oldnode);
                 }
	}
	  free(table->tbl_nodes);
	  free(table); 
	  return 1; 
}

/* Powerful hash function */ 
unsigned long stHash(SymbolTable * table, const char * str) {
	unsigned long hash = 5381; 
	int c; 
	
	while (c = *str++)
        	hash = (( hash << 5) + hash) + c; // hash * 33 + c

	return hash; 
}


/* Generic insert function to insert tokens into a symbol table */ 
int stInsert (SymbolTable * table, const char * str, int ln, int ID) {
	SymbolEntry * node;
	Token * token; 

	if (!(token=malloc(sizeof(Token)))) return 0; 
	token->line_num = ln; 
	token->lexeme = strdup(str); 
	token->id = ID; 

	if(table->curr_size >= table->max_size)
	{
		if(!stResize(table)) return 0; 
	}
	  
	int index = (int)( stHash(table, str)%(table->size));
	  
        node = table->tbl_nodes[index]; 
        while (node)
        { 
		if (!strcmp(node->token->lexeme, str))
		{			
			node->token = token; 
			return 1; 
		}
		node= node->next; 
	}

	if (!(node=malloc(sizeof(SymbolEntry)))) return 0; 
	node->token = token; 
        node->next = table->tbl_nodes[index]; 
	table->tbl_nodes[index] = node; 
	table->curr_size++; 
	return 1; 
}



/*Boolean function that searches for a string in the symbol table */
int stGet (SymbolTable * table, const char * str) {
	int index = (int)( ( stHash(table, str))%(table->size));

        SymbolEntry * node = table->tbl_nodes[index]; 
	
	while (node)
	{
		if (!strcmp(node->token->lexeme, str))
			return node->token->id; 
		node=node->next; 
	}

	return 0; 
}

/* Returns the numeric id of a token. Used by the scanner 
 * to resolve typedef/enum vs identifier ambiguity*/
int  stGetLex (SymbolTable * table, const char * str) {
	int index = (int)( ( stHash(table, str))%(table->size));

        SymbolEntry * node = table->tbl_nodes[index]; 
	
	while (node)
	{
		if (!strcmp(node->token->lexeme, str))
			return node->token->id; 
		node=node->next; 
	}

	return 0; 
}


/* Removes an entry from the symbol table */ 
int stRemove (SymbolTable * table, const char * str) {
	SymbolEntry * node, * prevnode=NULL; 
	int index = (int) ( (stHash(table, str))%(table->size)); 
        
	node = table->tbl_nodes[index]; 
	while (node)
	{
		if (!strcmp(node->token->lexeme, str))
                {
			/* Assuming lexeme will be allocated on the heap*/
		       //free(node->token->lexeme); 
			free(node->token); 
			if (prevnode) prevnode = node->next; 
			else table->tbl_nodes[index] =node->next; 
			free(node);
			return 0;  
		 }
		
		 prevnode = node; 
		 node = node->next; 
	}

 	return 0; 
} 


/* Resize incase the size is greater that 0.9 * max_size */ 
int stResize (SymbolTable * table) {
	SymbolTable newtbl; 
	SymbolEntry * node, *nextnode;
	
	size_t size = (size_t)((table->size)*2); 
	newtbl.size = size;

	if(!(newtbl.tbl_nodes=calloc(size,sizeof(SymbolEntry*)))) return 0; 
        
	size_t i; 
	for (i = 0; i< size; ++i)
        { 
		for (node = table->tbl_nodes[i]; node; node=nextnode)
		{
			nextnode = node->next; 
			stInsert(&newtbl, node->token->lexeme, node->token->line_num, node->token->id); 
			stRemove (table, node->token->lexeme); 
		}
	}

	free(table->tbl_nodes); 
	table->tbl_nodes = newtbl.tbl_nodes; 
	table->size = newtbl.size; 

	return 1; 
}
                

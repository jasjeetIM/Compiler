/* 
 * File: P1/Node.h
 * Desc: This file declares the node that will be used to form a binary tree. 
 * Author: Jasjeet Dhaliwal
 * Date: 2/11/2016
 *
 */

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NODE 0
#define LEAF 1

typedef struct Node {  
	char * val;   
	struct Node * left, * right;  
	int type;  
}Node;


Node * makeLeaf (char * val); 
Node * makeNode (char * name); 
int setRight(Node * node,  Node * right); 
int  setLeft(Node * node, Node * left);
Node * primaryExpression( char * one, Node * two, char * three); 
Node * generic_selection( char * one, char *two, Node * three, char * four, Node * five, char * six); 
Node * generic_assoc_list( Node * one, char * two, Node * three); 
Node * generic_association1( Node * one, char * two, Node * three); 
Node * generic_association2( char * one, char * two, Node * three); 
Node * postfix_expression1( Node * one, char * two, Node * three, char * four); 
Node * postfix_expression2( Node * one, char * two, char * three); 
Node * postfix_expression3( Node * one, char * two, Node * three, char * four); 
Node * postfix_expression4( Node * one, char * two, char * three); 
Node * postfix_expression5( Node * one, char * two); 
Node * postfix_expression6( char * one, Node * two, char * three, char * four, Node * five, char * six); 
Node * postfix_expression7( char * one, Node * two, char * three, char * four, Node * five, char * six, char * seven); 
Node * argument_expression_list( Node * one, char * two, Node * three); 
Node * unary_expression1( char * one, Node * two); 
Node * unary_expression2( Node * one, Node * two); 
Node * unary_expression3( char * one, char * two, Node * three, char * four); 
Node * cast_expression( char * one, Node * two, char * three, Node * four); 
Node * multiplicative_expression( Node * one, char * two, Node * three); 
Node * additive_expression( Node * one, char * two, Node * three); 
Node * shift_expression( Node * one, char * two, Node * three); 
Node * relational_expression( Node * one, char * two, Node * three); 
Node * equality_expression( Node * one, char * two, Node * three); 
Node * and_expression( Node * one, char * two, Node * three); 
Node * exclusive_or_expression( Node * one, char * two, Node * three); 
Node * inclusive_or_expression( Node * one, char * two, Node* three); 
Node * logical_and_expression( Node * one, char * two, Node * three); 
Node * logical_or_expression( Node * one, char * two, Node * three); 
Node * conditional_expression( Node * one, char * two, Node * three, char * four, Node * five); 
Node * assignment_expression( Node * one, Node * two, Node * three); 
Node * expression( Node * one, char * two, Node * three); 
Node * declaration1( Node * one, char * two); 
Node * declaration2( Node * one, Node * two, char * three); 
Node * declaration_specifiers( Node * one, Node * two); 
Node * attribute_specifier1( char * one, char * two, char * three, char * four, char * five); 
Node * attribute_specifier2( char * one, char * two, char * three, Node * four, char * five, char * six); 
Node * attribute_list( Node * one, char * two, Node * three); 
Node * attribute1( char * one, char * two, char * three); 
Node * attribute2( char * one, char * two, Node * three, char * four); 
Node * attribute_params_list( Node * one, char * two, Node * three); 
Node * init_declarator_list( Node * one, char * two, Node * three); 
Node * init_declarator( Node * one, char * two, Node * three); 
Node * struct_or_union_specifier1( Node * one, char * two, Node * three, char * four); 
Node * struct_or_union_specifier2( Node * one, char * two, char * three, Node * four, char * five); 
Node * struct_or_union_specifier3( Node * one, char * two); 
Node * struct_declaration_list( Node * one, Node * two); 
Node * struct_declaration1( Node * one, char * two); 
Node * struct_declaration2( Node * one, Node * two, char * three); 
Node * specifier_qualifier_list( Node * one, Node * two); 
Node * struct_declarator_list( Node * one, char * two, Node * three); 
Node * struct_declarator1( char * one, Node * two); 
Node * struct_declarator2( Node * one, char * two, Node * three); 
Node * enum_specifier1( char * one, char * two, Node * three, char * four); 
Node * enum_specifier2( char * one, char * two, Node * three, char * four, char * five); 
Node * enum_specifier3( char * one, char * two, char * three, Node * four, char * five); 
Node * enum_specifier4( char * one, char * two, char * three, Node * four, char * five, char * six); 
Node * enum_specifier5( char * one, char * two); 
Node * enumerator_list( Node * one, char * two, Node * three); 
Node * enumerator( Node * one, char * two, Node * three); 
Node * atomic_type_specifier( char * one, char * two, Node * three, char * four); 
Node * alignment_specifier( char * one, char * two, Node * three, char * four); 
Node * direct_declarator1( Node * one, Node * two); 
Node * direct_declarator2( char * one, Node * two, char * three); 
Node * direct_declarator3( Node * one, char * two, char * three); 
Node * direct_declarator4( Node * one, char * two, char * three, char * four); 
Node * direct_declarator5( Node * one, char * two, char * three, Node * four, Node * five, char * six); 
Node * direct_declarator6( Node * one, char * two, char * three, Node * four, char * five); 
Node * direct_declarator7( Node * one, char * two, Node * three, char * four, char * five); 
Node * direct_declarator8( Node * one, char * two, Node * three, char * four, Node * five, char * six); 
Node * direct_declarator9( Node * one, char * two, Node * three, Node * four, char * five); 
Node * direct_declarator10( Node * one, char * two, Node * three, char * four); 
Node * pointer1( char * one, Node * two, Node * three); 
Node * pointer2( char * one, Node * two); 
Node * type_qualifier_list( Node * one, Node * two); 
Node * parameter_type_list( Node * one, char * two, char * three); 
Node * parameter_list( Node * one, char * two, Node * three); 
Node * parameter_declaration( Node * one, Node * two); 
Node * identifier_list( Node * one, char * two, char * three); 
Node * type_name( Node * one, Node * two); 
Node * abstract_declarator( Node * one, Node * two); 
Node * direct_abstract_declarator1( char * one, Node * two, char * three); 
Node * direct_abstract_declarator2( char * one, char * two);Node * direct_abstract_declarator3( char * one, char * two, char * three); 
Node * direct_abstract_declarator4( char * one, char * two, Node * three, Node * four, char * five); 
Node * direct_abstract_declarator5( char * one, char * two, Node * three, char * four); 
Node * direct_abstract_declarator6( char * one, Node * two, char * three, Node * four, char * five); 
Node * direct_abstract_declarator7( char * one, Node * two, Node * three, char * four); 
Node * direct_abstract_declarator8( Node * one, char * two, char * three); 
Node * direct_abstract_declarator9( Node * one, char * two, char * three, char * four); 
Node * direct_abstract_declarator10( Node * one, char * two, char * three, Node * four, Node * five, char * six); 
Node * direct_abstract_declarator11( Node * one, char * two, char * three, Node * four, char * five); 
Node * direct_abstract_declarator12( Node * one, char * two, Node * three, Node * four, char * five); 
Node * direct_abstract_declarator13( Node * one, char * two, Node * three, char * four, Node * five, char * six); 
Node * direct_abstract_declarator14( Node * one, char * two, Node * three, char * four); 
Node * initializer1( char * one, Node * two, char * three); 
Node * initializer2( char * one, Node * two, char * three, char * four); 
Node * initializer_list1( Node * one, char * two, Node * three, Node * four); 
Node * initializer_list2( Node * one, char * two, Node * three); 
Node * designation( Node * one, char * two); 
Node * designator_list( Node * one, Node * two); 
Node * designator1( char * one, Node * two, char * three); 
Node * designator2( char * one, char * two); 
Node * static_assert_declaration( char * one, char * two, Node * three, char * four, char * five, char * six, char * seven); 
Node * labeled_statement1( char * one, char * two, Node * three); 
Node * labeled_statement2( char * one, Node * two, char * three, Node * four); 
Node * compound_statement1( char * one, char * two); 
Node * compound_statement2( char * one, Node * two, char * three); 
Node * block_item_list( Node * one, Node * two); 
Node * expression_statement( Node * one, char * two); 
Node * selection_statement1( char * one, char * two, Node * three, char * four, Node * five, char * six, Node * seven); 
Node * selection_statement2( char * one, char * two, Node * three, char * four, Node * five); 
Node * iteration_statement1( char * one, char * two, Node * three, char * four, Node * five); 
Node * iteration_statement2( char * one, Node * two, char * three, char * four, Node * five, char * six, char * seven); 
Node * iteration_statement3( char * one, char * two, Node * three, Node * four, char * five, Node * six); 
Node * iteration_statement4( char * one, char * two, Node * three, Node * four, Node * five, char * six, Node * seven); 
Node * jump_statement1( char * one, char * two, char * three); 
Node * jump_statement2( char * one, char * two); 
Node * jump_statement3( char * one, Node * two, char * three); 
Node * translation_unit( Node * one, Node * two); 
Node * function_definition1( Node * one, Node * two, Node * three, Node * four); 
Node * function_definition2( Node * one, Node * two, Node * three); 
Node * declaration_list( Node * one, Node * two); 

Node * declarator( Node * one, Node * two); 
Node * makeOne( Node * one);  
Node * declaration3(Node * one, Node * two, Node * three, char * four); 



void printTree(Node * root); 
void postOrder(Node * node, int level);  
void nError(char * str); 
void deleteTree(Node * node); 
extern Node * unit; 
 
#endif

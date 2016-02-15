/* 
 * File: P1/Node.c
 * Desc: This file implements the functions used by the Node struct to f	 form the binary ast. 
 * Author: Jasjeet Dhaliwal
 * Date: 2/12/2016
 *
 */

#include "Node.h"

Node * makeLeaf (char * val) {
	Node * node; 
	if (!(node = (Node *)malloc(sizeof(Node)))) nError("Error: could not allocate memory for a Leaf."); 
	
	node->type = LEAF; 
	if (!(node->val = (char *)malloc( strlen((char *)(val)) + 1 ))) nError("Error: could not allocate memory for node->val"); 	
	memset(node->val, '\0', strlen((char *)(val)) + 1); 
	strcpy(node->val, val); 
	node->left = NULL; 
	node->right = NULL;
	return node; 
 }

Node * makeNode (char * name) {
	Node * node; 
	if (!(node = (Node *)malloc(sizeof(Node)))) nError("Error: could not allocate memory for Node."); 
	node->type = NODE; 
	if(!(node->val = (char*)malloc( strlen((char*)(name)) +1  )))nError("Error: could not allocate memory for node->name"); 
	memset(node->val, '\0', strlen((char *)(name)) + 1); 
	strcpy(node->val, name); 
	node->left = NULL; 
	node->right = NULL; 

	return node; 
 }

int setRight(Node * node, Node * right) {
	if (!node) nError("Error: setRight(Node* node, Node* right) received a null node pointer."); 

	if (!right)nError("Error: setRight(Node* node, Node* right) received a null right pointer."); 
	node->right = right;  
	return 1; 
}; 


int setLeft(Node * node, Node * left) {
	if (!node) nError("Error: setLeft(Node* node, Node* left) received a null node pointer."); 
	if (!left) nError("Error: setLeft(Node* node, Node* left) received a null left pointer."); 
	node->left = left;  
	return 1; 
} 


void postOrder(Node * node, int level) {
	 	   
	if (node->left){ 
		if (node->left->type == LEAF) postOrder(node->left, level+1);
		else postOrder(node->left,level); 
	}
	
	FILE * file; 
	file = fopen("output.ast", "a"); 
	int i = 0; 
	
	if (node->type == LEAF) {
		for (; i < level; ++i) 
			fprintf(file, "|");
		if (level <= 0) fprintf(file, "|"); 
		fprintf(file, "%s\n", node->val); 
	}
	fclose(file); 
	
	if (node->right) postOrder(node->right,level); 

}


void printTree(Node * root) {
	FILE * file; 
	file = fopen("output.ast", "a"); 
	if(!root) nError("Error: printTree(Node * root) received a null root pointer."); 

	fprintf(file, "AST Print Initializing...\n\nProgram\n");
	fclose(file);  
	postOrder(root, 0);
	file = fopen("output.ast", "a"); 
	fprintf(file, "\nAST Print Completed.\n"); 
	fclose(file);  
	
}



void deleteTree(Node * node) {
	if (!node) return; 
	deleteTree(node->left); 
	deleteTree(node->right); 
	free(node); 
}

void nError(char * str) {
	printf("%s\n", str); 
	exit(EXIT_FAILURE); 
}



Node * primary_expression( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("primary_expression"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3); 
	return parent;
 } 
Node * generic_selection( char * one, char * two, Node * three, char * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4, * c6; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("generic_selection"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 
	c6 = makeLeaf(six); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three); 
	setRight(three, c4); 
	setRight(c4, five); 
	setRight(five, c6); 
	return parent;
 } 
Node * generic_assoc_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("generic_assoc_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three); 
	return parent;
 }
Node * generic_association1( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("generic_association1"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 }
Node * generic_association2( char * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("generic_association2");
	c1 = makeLeaf(one);  
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * postfix_expression1( Node * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression1"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4); 
	return parent;
 } 
Node * postfix_expression2( Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression2"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 
Node * postfix_expression3( Node * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression3"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * postfix_expression4( Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression4"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 
Node * postfix_expression5( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression5"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	return parent;
 } 
Node * postfix_expression6( char * one, Node * two, char * three, char * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3, * c4, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression6"); 
	c1= makeLeaf(one);
	c3 = makeLeaf(three); 
	c4 = makeLeaf(four); 
	c6 = makeLeaf(six);   

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, c3); 
	setRight(c3, c4); 
	setRight(c4, five); 
	setRight(five, c6); 
	return parent;
 } 
Node * postfix_expression7( char * one, Node * two, char * three, char * four, Node * five, char * six, char * seven) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3, * c4, * c6, * c7;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("postfix_expression7"); 
	c1= makeLeaf(one);
	c3 = makeLeaf(three); 
	c4 = makeLeaf(four); 
	c6 = makeLeaf(six);   
	c7 = makeLeaf(seven); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, c3); 
	setRight(c3, c4); 
	setRight(c4, five); 
	setRight(five, c6);
	setRight(c6, c7); 
	return parent;
 } 
Node * argument_expression_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("argument_expression_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
 	return parent;
 }
Node * unary_expression1( char * one, Node * two) {
	//Creating node pointers for leaf nodes
	Node * c1;    
	
	//Make parent and leaf nodes
	Node * parent = makeNode("unary_expression1"); 
	c1= makeLeaf(one); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	return parent;
 } 
Node * unary_expression2( Node * one, Node * two) {	
	//Make parent and leaf nodes
	Node * parent = makeNode("unary_expression2"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * unary_expression3( char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("unary_expression3"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4); 
	return parent;
 }

Node * cast_expression( char * one, Node * two, char * three, Node * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c3;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("cast_expression"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3);
	setRight(c3, four);
	return parent;
 }


 
Node * multiplicative_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("multiplicative_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * additive_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("additive_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 }
Node * shift_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("shift_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * relational_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("relational_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * equality_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("equality_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * and_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("and_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * exclusive_or_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("exclusive_or_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * inclusive_or_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("inclusive_or_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 }
Node * logical_and_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("logical_and_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * logical_or_expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("logical_or_expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * conditional_expression( Node * one, char * two, Node * three, char * four, Node * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("conditional_expression"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4); 
	setRight(c4, five); 
	return parent;
 } 
Node * assignment_expression( Node * one, Node * two, Node * three) {
	//Make parent and leaf nodes
	Node * parent = makeNode("assignment_expression"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two); 
	setRight(two, three); 
	return parent;
 }
Node * expression( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("expression"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * declaration1( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("declaration1"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	return parent;
 } 
Node * declaration2( Node * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("declaration2"); 
	c3 = makeLeaf(three);  
 
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	setRight(two, c3); 
	return parent;
 } 
Node * declaration_specifiers( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("declaration_specifiers"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * attribute_specifier1( char * one, char * two, char * three, char * four, char * five) {
	//Creating node pointers for leaf nodes
	Node *c1, * c2, * c3, * c4, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute_specifier1");
	c1 = makeLeaf(one);  
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c4 = makeLeaf(four); 
	c5 = makeLeaf(five);   

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	setRight(c3, c4); 
	setRight(c4, c5); 
	return parent;
 }

 Node * attribute_specifier2( char * one, char * two, char * three, Node * four, char * five, char * six) {
	//Creating node pointers for leaf nodes
	Node *c1, * c2, * c3, * c5, * c6; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute_specifier2");
	c1 = makeLeaf(one);  
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c5 = makeLeaf(five); 
	c6 = makeLeaf(six);   

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5);
	setRight(c5, c6);
	return parent;
 } 
Node * attribute_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * attribute1( char * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	return parent;
 } 
Node * attribute2(  char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * attribute_params_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("attribute_params_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * init_declarator_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("init_declarator_list"); 
	c2 = makeLeaf(two); 
printf("Init with val: %d\n", parent); 
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * init_declarator( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("init_declarator"); 
	c2 = makeLeaf(two); 
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one);
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * struct_or_union_specifier1( Node * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_or_union_specifier1"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * struct_or_union_specifier2( Node * one, char * two, char * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_or_union_specifier2"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c5 = makeLeaf(five); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5); 
	return parent;
 }

Node * struct_or_union_specifier3( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_or_union_specifier3"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	return parent;
 }

 
Node * struct_declaration_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declaration_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * struct_declaration1( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declaration1"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	return parent;
 } 
Node * struct_declaration2( Node * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declaration2"); 
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	setRight(two, c3);
	return parent;
 } 
Node * specifier_qualifier_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("specifier_qualifier_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * struct_declarator_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declarator_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * struct_declarator1( char * one, Node * two) {
	//Creating node pointers for leaf nodes
	Node * c1;    
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declarator1"); 
	c1= makeLeaf(one); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	return parent;
 } 
Node * struct_declarator2( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("struct_declarator2"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * enum_specifier1( char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enum_specifier1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * enum_specifier2( char * one, char * two, Node * three, char * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enum_specifier2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);
	c5 = makeLeaf(five);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, three);
	setRight(three, c4); 
	setRight(c4, c5);
	return parent;
 } 
Node * enum_specifier3( char * one, char * two, char * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c3, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enum_specifier3"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);
	c5 = makeLeaf(five);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5);
	return parent;
 } 
Node * enum_specifier4( char * one, char * two, char * three, Node * four, char * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c3, * c5, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enum_specifier4"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);
	c5 = makeLeaf(five);  
	c6 = makeLeaf(six); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5);
	setRight(c5, c6); 
	return parent;
 } 
Node * enum_specifier5( char * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enum_specifier5"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	return parent;
 } 
Node * enumerator_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enumerator_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * enumerator( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("enumerator"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * atomic_type_specifier( char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("atomic_type_specifier"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * alignment_specifier( char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("alignment_specifier"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * direct_declarator1( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator1"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * direct_declarator2( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator2"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3);
	return parent;
 } 

Node * direct_declarator3(Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator3"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  
	
	
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 

Node * direct_declarator4( Node * one, char * two, char * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator4"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3); 
	setRight(c3, c4); 
	return parent;
 } 
Node * direct_declarator5( Node * one, char * two, char * three, Node * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator5"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c6 = makeLeaf(six);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3); 
	setRight(c3, four);
	setRight(four, five); 
	setRight(five, c6); 
	return parent;
 } 
Node * direct_declarator6( Node * one, char * two, char * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator6"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c5 = makeLeaf(five); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5);
	return parent;
 }
Node * direct_declarator7( Node * one, char * two, Node * three, char * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4, * c5;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator7"); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four);
	c5 = makeLeaf(five);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three); 
	setRight(three, c4);
	setRight(c4, c5);
	return parent;
 } 
Node * direct_declarator8( Node * one, char * two, Node * three, char * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator8"); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four);
	c6 = makeLeaf(six);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three); 
	setRight(three, c4);
	setRight(c4, five);
	setRight(five, c6); 
	return parent;
 } 
Node * direct_declarator9( Node * one, char * two, Node * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c5;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator9"); 
	c2 = makeLeaf(two); 
	c5 = makeLeaf(five);   

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three); 
	setRight(three, four);
	setRight(four, c5);
	return parent;
 } 
Node * direct_declarator10( Node * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_declarator10"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * pointer1( char * one, Node * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c1;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("pointer1"); 
	c1 = makeLeaf(one);    

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, three);
	return parent;
 } 
Node * pointer2( char * one, Node * two) {
	//Creating node pointers for leaf nodes
	Node * c1;    
	
	//Make parent and leaf nodes
	Node * parent = makeNode("pointer2"); 
	c1= makeLeaf(one); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	return parent;
 } 
Node * type_qualifier_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("type_qualifier_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * parameter_type_list( Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("parameter_type_list"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 
Node * parameter_list( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("parameter_list"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * parameter_declaration( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("parameter_declaration"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * identifier_list( Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("identifier_list"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 
Node * type_name( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("type_name"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * abstract_declarator( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("abstract_declarator"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * direct_abstract_declarator1( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("direct_abstract_declarator1"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3);
	return parent;
 } 
Node * direct_abstract_declarator2( char * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	return parent;
 }
Node * direct_abstract_declarator3( char * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator3"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	return parent;
 } 
Node * direct_abstract_declarator4( char * one, char * two, Node * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c5;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator4"); 
	c1 = makeLeaf(one);
	c2 = makeLeaf(two); 
	c5 = makeLeaf(five);     

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, three);
	setRight(three, four); 
	setRight(four, c5); 
	return parent;
 } 
Node * direct_abstract_declarator5( char * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, *  c2, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator5"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * direct_abstract_declarator6( char * one, Node * two, char * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3, * c5;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator6"); 
	c1 = makeLeaf(one);
	c3 = makeLeaf(three); 
	c5 = makeLeaf(five);     

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, c3);
	setRight(c3, four); 
	setRight(four, c5);
	return parent;
 } 
Node * direct_abstract_declarator7( char * one, Node * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator7"); 
	c1 = makeLeaf(one);
	c4 = makeLeaf(four);      

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, three);
	setRight(three, c4); 
	return parent;
 } 
Node * direct_abstract_declarator8( Node * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("direct_abstract_declarator8"); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, c3);
	return parent;
 } 
Node * direct_abstract_declarator9( Node * one, char * two, char * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator9"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3); 
	setRight(c3, c4);
	return parent;
 }
Node * direct_abstract_declarator10( Node * one, char * two, char * three, Node * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator10"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c6 = makeLeaf(six);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3); 
	setRight(c3, four);
	setRight(four, five); 
	setRight(five, c6);
	return parent;
 }
Node * direct_abstract_declarator11( Node * one, char * two, char * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c3, * c5; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator11"); 
	c2 = makeLeaf(two); 
	c3 = makeLeaf(three);
	c5 = makeLeaf(five); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, c3);
	setRight(c3, four); 
	setRight(four, c5);
	return parent;
 } 
Node * direct_abstract_declarator12( Node * one, char * two, Node * three, Node * four, char * five) {
	//Creating node pointers for leaf nodes
	Node * c2, * c5;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator12"); 
	c2 = makeLeaf(two); 
	c5 = makeLeaf(five);   

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three); 
	setRight(three, four);
	setRight(four, c5);
	return parent;
 } 
Node * direct_abstract_declarator13( Node * one, char * two, Node * three, char * four, Node * five, char * six) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator13"); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four);
	c6 = makeLeaf(six);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three); 
	setRight(three, c4);
	setRight(c4, five);
	setRight(five, c6);
	return parent;
 }
Node * direct_abstract_declarator14( Node * one, char * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c2, * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode( "direct_abstract_declarator14"); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	setRight(three, c4);
	return parent;
 } 
Node * initializer1( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("initializer1"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3); 
	return parent;
 } 
Node * initializer2( char * one, Node * two, char * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3, * c4;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("initializer2"); 
	c1 = makeLeaf(one);
	c3 = makeLeaf(three); 
	c4 = makeLeaf(four);      

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, c3);
	setRight(c3, c4);
	return parent;
 } 
Node * initializer_list1( Node * one, char * two, Node * three, Node * four) {
	//Creating node pointers for leaf nodes
	Node * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("initializer_list1"); 
	c2 = makeLeaf(two);

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	setRight(c2, three);
	setRight(three, four);
	return parent;
 } 
Node * initializer_list2( Node * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("initializer_list2"); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2); 
	setRight(c2, three);
	return parent;
 } 
Node * designation( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("designation"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	return parent;
 } 
Node * designator_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("designator_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * designator1( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("designator1"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 
	
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3); 
	return parent;
 } 
Node * designator2( char * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("designator2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	return parent;
 } 
Node * static_assert_declaration( char * one, char * two, Node * three, char * four, char * five, char * six, char * seven) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4, * c5, * c6, * c7;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("static_assert_declaration"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 
	c4 = makeLeaf(four); 
	c5 = makeLeaf(five); 
	c6 = makeLeaf(six); 
	c7 = makeLeaf(seven); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2,three);
	setRight(three, c4);
	setRight(c4, c5); 
	setRight(c5, c6); 
	setRight(c6, c7); 
	return parent;
 }

Node * labeled_statement1( char * one, char * two, Node * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2;     
	
	//Make parent and leaf nodes
	Node * parent = makeNode("labeled_statement1"); 
	c1= makeLeaf(one);
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2); 
	setRight(c2, three); 
	return parent;
 } 
Node * labeled_statement2( char * one, Node * two, char * three, Node * four) { 
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("labeled_statement2"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two ,c3);
	setRight(c3, four); 
	return parent;
 }
Node * compound_statement1( char * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("compound_statement1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	return parent;
 } 
Node * compound_statement2( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 

	//Make parent and leaf nodes
	Node * parent = makeNode("compound_statement2"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three);
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two); 
	setRight(two, c3);
 
	return parent;
 } 
Node * block_item_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("block_item_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * expression_statement( Node * one, char * two) {
	//Creating node pointers for leaf nodes
	Node * c2; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("expression_statement"); 
	c2 = makeLeaf(two);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, c2);
	return parent;
 } 
Node * selection_statement1( char * one, char * two, Node * three, char * four, Node * five, char * six, Node * seven) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4, * c6;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("selection_statement1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four); 
	c6 = makeLeaf(six);  

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2 , three);
	setRight(three, c4);
	setRight(c4, five); 
	setRight(five, c6); 
	setRight(c6, seven); 
	return parent;
 } 
Node * selection_statement2( char * one, char * two, Node * three, char * four, Node * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("selection_statement2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2 , three);
	setRight(three, c4);
	setRight(c4, five);
	return parent;
 } 
Node * iteration_statement1( char * one, char * two, Node * three, char * four, Node * five) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c4;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("iteration_statement1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2 , three);
	setRight(three, c4);
	setRight(c4, five);
	return parent;
 } 
Node * iteration_statement2( char * one, Node * two, char * three, char * four, Node * five, char * six, char * seven) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3, * c4, * c6, * c7;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("iteration_statement2"); 
	c1= makeLeaf(one);
	c3 = makeLeaf(three); 
	c4 = makeLeaf(four); 
	c6 = makeLeaf(six);   
	c7 = makeLeaf(seven); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, two);
	setRight(two, c3); 
	setRight(c3, c4); 
	setRight(c4, five); 
	setRight(five, c6);
	setRight(c6, c7);
	return parent;
 } 
Node * iteration_statement3( char * one, char * two, Node * three, Node * four, char * five, Node * six) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c5;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("iteration_statement3"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c5 = makeLeaf(five); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2 , three);
	setRight(three, four);
	setRight(four, c5);
	setRight(c5, six); 
	return parent;
 } 

Node * iteration_statement4( char * one, char * two, Node * three, Node * four, Node * five, char * six, Node * seven) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c6;   
	
	//Make parent and leaf nodes
	Node * parent = makeNode("iteration_statement4"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c6 = makeLeaf(six); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2 , three);
	setRight(three, four);
	setRight(four, five);
	setRight(five, c6); 
	setRight(c6, seven); 
	return parent;
 } 
Node * jump_statement1( char * one, char * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c2, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("jump_statement1"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two);
	c3 = makeLeaf(three); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	setRight(c2, c3);
	return parent;
 } 
Node * jump_statement2( char * one, char * two){
	//Creating node pointers for leaf nodes
	Node * c1, * c2;  
	
	//Make parent and leaf nodes
	Node * parent = makeNode("jump_statement2"); 
	c1 = makeLeaf(one); 
	c2 = makeLeaf(two); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1, c2);
	return parent;
 }

Node * jump_statement3( char * one, Node * two, char * three) {
	//Creating node pointers for leaf nodes
	Node * c1, * c3; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("jump_statement3"); 
	c1 = makeLeaf(one); 
	c3 = makeLeaf(three); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, c1); 
	setRight(c1,two);
	setRight(two, c3);
	return parent;
 }
 
Node * translation_unit( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("translation_unit"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	return parent;
 } 
Node * function_definition1( Node * one, Node * two, Node * three, Node * four) {	
	//Make parent and leaf nodes
	Node * parent = makeNode("function_definition1"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two);
	setRight(two, three);
	setRight(three, four); 
	return parent;
 }
Node * function_definition2( Node * one, Node * two, Node * three) {
	//Make parent and leaf nodes
	Node * parent = makeNode("function_definition2"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two); 
	setRight(two, three);
	return parent;
 } 
Node * declaration_list( Node * one, Node * two) {
	//Make parent and leaf nodes
	Node * parent = makeNode("declaration_list"); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one, two); 
	return parent;
 }

Node * makeOne(Node * one) {
	
	//Make parent and leaf nodes
	Node * parent = makeNode("Attribute Node");  
         
	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	return parent;
 }


Node * declarator( Node * one, Node * two) {
	Node * parent = makeNode("declarator"); 
	setLeft(parent, one); 
	setRight(one, two); 


	return parent;
 }

Node * declaration3(Node * one, Node * two, Node * three, char * four) {
	//Creating node pointers for leaf nodes
	Node * c4; 
	
	//Make parent and leaf nodes
	Node * parent = makeNode("jump_statement3"); 
	c4 = makeLeaf(four); 

	//Set left pointer for parent and right pointers for leaf nodes
	setLeft(parent, one); 
	setRight(one,two);
	setRight(two, three);
	setRight(three, c4); 
	return parent;
}


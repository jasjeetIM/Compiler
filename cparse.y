%{
#include <stdio.h>
#include <stdlib.h>
#include "Env.h"
#include "Node.h"

int yydebug=1; 
char typed[6] = {'t','y','p','e','d','\0'}; 
char enm[5] = {'e','n','u','m','\0'}; 
int yylex(void); 
extern int linenum; 
int typeUpdate(Env * env, Node * type, Node * str);
int idUpdate(Env * env, char * str); 
Env * saved; 
Node * unit; 


%}

%union {
    int num; 
    char * str;
 struct Node * node;  
}

%type<node>  constant string expression generic_selection
%type<node>  enumeration_constant generic_assoc_list generic_association 
%type<node> postfix_expression primary_expression argument_expression_list
%type<node> type_name  assignment_expression 
%type<node> unary_expression unary_operator cast_expression multiplicative_expression
%type<node> additive_expression shift_expression relational_expression
%type<node> equality_expression and_expression exclusive_or_expression
%type<node> inclusive_or_expression logical_and_expression logical_or_expression
%type<node> conditional_expression assignment_operator constant_expression
%type<node> declaration_specifiers static_assert_declaration
%type<node> storage_class_specifier type_specifier type_qualifier function_specifier
%type<node>  alignment_specifier attribute_specifier
%type<node> init_declarator init_declarator_list declarator initializer
%type<node> struct_or_union_specifier struct_or_union struct_declaration_list
%type<node> atomic_type_specifier enum_specifier struct_declaration 
%type<node> specifier_qualifier_list struct_declarator_list 
%type<node> struct_declarator enumerator_list enumerator
%type<node> pointer direct_declarator type_qualifier_list parameter_type_list
%type<node> identifier_list parameter_list parameter_declaration abstract_declarator
%type<node> direct_abstract_declarator initializer_list designation 
%type<node> designator_list designator labeled_statement compound_statement
%type<node> expression_statement selection_statement iteration_statement 
%type<node> jump_statement statement block_item_list block_item declaration
%type<node> translation_unit external_declaration function_definition declaration_list
%type<node> attribute attribute_list attribute_params_list param

%type<str> '(' ')' '{' '}' '[' ']' ';' ',' '.' '=' ':'
%type<str> '^' '&' '*' '+' '-' '!' '~' '/' '%' '<' '>' '|' '?'

%token<str> I_CONSTANT F_CONSTANT
%token<str> IDENTIFIER STRING_LITERAL FUNC_NAME SIZEOF
%token<str> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token<str> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token<str> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token<str> XOR_ASSIGN OR_ASSIGN
%token<str> TYPEDEF_NAME ENUMERATION_CONSTANT
%token<str> TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token<str> CONST RESTRICT VOLATILE
%token<str> BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token<str> COMPLEX IMAGINARY 
%token<str> STRUCT UNION ENUM ELLIPSIS
%token<str> CASE DEFAULT IF ELSE SWITCH WHILE DO 
%token<str> FOR GOTO CONTINUE BREAK RETURN
%token<str> ALIGNAS ALIGNOF ATOMIC GENERIC 
%token<str> NORETURN STATIC_ASSERT THREAD_LOCAL ATTRIBUTE

%start translation_unit
%%

primary_expression
	: IDENTIFIER { idUpdate(top, $1); $$ = makeLeaf($1); }
	| constant { $$ =  $1; }
	| string {$$= $1;  }
	| '(' expression ')' {$$ = primary_expression("(", $2, ")");}
	| generic_selection {$$ = $1;  }
	;

constant
	: I_CONSTANT {$$ = makeLeaf($1); } /*includes character_constant */
	| F_CONSTANT {$$ = makeLeaf($1); }
	| ENUMERATION_CONSTANT {$$ = makeLeaf($1); }	/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER { idUpdate(top, $1); $$ = makeLeaf($1);  }
	;

string
	: STRING_LITERAL {$$ = makeLeaf($1); }
	| FUNC_NAME { $$ = makeLeaf($1); }
	;

generic_selection
	: GENERIC '('  assignment_expression  ','  generic_assoc_list ')' {$$ = generic_selection( $1, "(", $3, ",", $5, ")");} 
	;

generic_assoc_list
	: generic_association { $$ = $1;  }
	| generic_assoc_list ',' generic_association { $$ = generic_assoc_list ($1, ",", $3); }
	;

generic_association
	: type_name ':' assignment_expression {$$ = generic_association1( $1, ":", $3); }
	| DEFAULT ':' assignment_expression { $$ = generic_association2($1, ":", $3); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' {$$ = postfix_expression1( $1, "[", $3, "]"); }
	| postfix_expression '(' ')' { $$ = postfix_expression2( $1, "(", ")"); }
	| postfix_expression '(' argument_expression_list ')' { $$ = postfix_expression3($1, "(", $3, ")"); }
	| postfix_expression '.' IDENTIFIER { idUpdate(top, $3); $$ = postfix_expression4( $1, "." , $3); }
	| postfix_expression PTR_OP IDENTIFIER { idUpdate(top, $3); $$ = postfix_expression4( $1, $2, $3); }
	| postfix_expression INC_OP {$$ = postfix_expression5( $1, $2); }
	| postfix_expression DEC_OP {$$ = postfix_expression5( $1, $2); }
	| '(' type_name ')' '{' initializer_list '}' { $$ = postfix_expression6( "(" , $2, ")", "{", $5, "}"); }
	| '(' type_name ')' '{' initializer_list ',' 	'}' { $$ = postfix_expression7("(", $2,")", "{", $5,",", "}"); }
	;

argument_expression_list
	: assignment_expression {$$ = $1; }
	| argument_expression_list ',' assignment_expression { $$ = argument_expression_list( $1, ",", $3); }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = unary_expression1( $1, $2); }
	| DEC_OP unary_expression { $$ = unary_expression1($1, $2); }
	| unary_operator cast_expression { $$ =unary_expression2( $1, $2); }
	| SIZEOF unary_expression { $$ = unary_expression1($1, $2); }
	| SIZEOF '(' type_name ')' { $$ = unary_expression3( $1, "(", $3, ")"); }
	| ALIGNOF '(' type_name ')'{$$ = unary_expression3( $1, "(", $3, ")"); }
	;

unary_operator
	: '&' {$$ = makeLeaf("&"); }
	| '*' {$$ = makeLeaf("*"); }
	| '+' {$$ = makeLeaf("+"); }
	| '-' {$$ = makeLeaf("-"); }
	| '~' {$$ = makeLeaf("~"); }
	| '!' {$$ = makeLeaf("!"); }
	;

cast_expression
	: unary_expression {$$ = $1;  }
	| '(' type_name ')' cast_expression {$$ =  cast_expression( "(", $2, ")", $4); }
	;

multiplicative_expression
	: cast_expression {$$ = $1;  }
	| multiplicative_expression '*' cast_expression {$$ = multiplicative_expression( $1, "*", $3); }
	| multiplicative_expression '/' cast_expression {$$ = multiplicative_expression( $1, "/", $3); }
	| multiplicative_expression '%' cast_expression {$$ = multiplicative_expression( $1, "%", $3); }
	;

additive_expression
	: multiplicative_expression {$$ = $1;  }
	| additive_expression '+' multiplicative_expression {$$ = additive_expression($1, "+", $3); }
	| additive_expression '-' multiplicative_expression {$$ = additive_expression($1, "-", $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression {$$ = shift_expression($1, $2, $3); }
	| shift_expression RIGHT_OP additive_expression {$$ = shift_expression($1, $2, $3); }
	;

relational_expression
	: shift_expression {$$ = $1; }
	| relational_expression '<' shift_expression {$$ = relational_expression($1, "<", $3); }
	| relational_expression '>' shift_expression {$$ = relational_expression($1, ">", $3); }
	| relational_expression LE_OP shift_expression {$$ = relational_expression($1, $2, $3); }
	| relational_expression GE_OP shift_expression {$$ = relational_expression($1, $2, $3); }
	;

equality_expression
	: relational_expression {$$ = $1; }
	| equality_expression EQ_OP relational_expression {$$ = equality_expression($1, $2, $3);}
	| equality_expression NE_OP relational_expression {$$ = equality_expression($1, $2, $3); }
	;

and_expression
	: equality_expression {$$ = $1; }
	| and_expression '&' equality_expression {$$ = and_expression($1,"&", $3); } 
	;

exclusive_or_expression
	: and_expression {$$ = $1; }
	| exclusive_or_expression '^' and_expression {$$ = exclusive_or_expression($1, "^", $3); }
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression {$$ = inclusive_or_expression($1, "|", $3); }
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {$$ = logical_and_expression($1, $2, $3); }
	;

logical_or_expression
	: logical_and_expression {$$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {$$ = logical_or_expression($1, $2, $3); }
	;

conditional_expression
	: logical_or_expression {$$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression {$$ = conditional_expression($1, "?", $3,":", $5); }
	;

assignment_expression
	: conditional_expression {$$ = $1; }
	| unary_expression assignment_operator assignment_expression {$$ = assignment_expression($1, $2, $3); }
	;

assignment_operator
	: '=' {$$ = makeLeaf("=");}
	| MUL_ASSIGN{$$ = makeLeaf($1);} 
	| DIV_ASSIGN {$$ = makeLeaf($1);}
	| MOD_ASSIGN {$$ = makeLeaf($1);}
	| ADD_ASSIGN {$$ = makeLeaf($1);}
	| SUB_ASSIGN {$$ = makeLeaf($1);}
	| LEFT_ASSIGN {$$ = makeLeaf($1);}
	| RIGHT_ASSIGN {$$ = makeLeaf($1);}
	| AND_ASSIGN {$$ = makeLeaf($1);}
	| XOR_ASSIGN {$$ = makeLeaf($1);}
	| OR_ASSIGN {$$ = makeLeaf($1);}
	;

expression
	: assignment_expression {$$ = $1; }
	| expression ',' assignment_expression {$$ = expression($1, ",", $3); }
	;

constant_expression
	: conditional_expression {$$ = $1; }
	;

declaration
	: declaration_specifiers ';' { $$ = declaration1($1, ";"); }
	| declaration_specifiers init_declarator_list
	{typeUpdate(top,$1,$2);} ';' {$$ = declaration2($1, $2, ";"); }
	| static_assert_declaration { $$ = $1; }
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	| storage_class_specifier { $$ = $1; }
	| type_specifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	| type_specifier {$$ = $1; }
	| type_qualifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	| type_qualifier {$$ = $1; }
	| function_specifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	| function_specifier  {$$ = $1; }
	| alignment_specifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	| alignment_specifier {$$ = $1; }
	| attribute_specifier declaration_specifiers {$$ = declaration_specifiers($1, $2); }
	;


attribute_specifier
		  : ATTRIBUTE '(''('  ')' ')' {$$ = attribute_specifier1($1, "(", "(", ")", ")"); }
		  | ATTRIBUTE '(''(' attribute_list  ')'')' { $$ = attribute_specifier2($1, "(", "(", $4, ")", ")"); }
		  ; 

attribute_list: 
		attribute { $$ = $1; }
		| attribute_list ',' attribute {$$ = attribute_list($1, ",", $3); }
		;

attribute: 
	| IDENTIFIER { idUpdate(top, $1); $$ = makeLeaf($1);}
	| IDENTIFIER '(' ')' {idUpdate(top, $1); $$ = attribute1($1, "(", ")"); }
	| IDENTIFIER '(' attribute_params_list  ')' {idUpdate(top, $1);$$ =  attribute2($1, "(", $3, ")"); }
	; 

attribute_params_list:
	| param {$$ = $1; }
	| attribute_params_list ',' param {$$ = attribute_params_list($1, ",", $3); }
	; 

param:
     IDENTIFIER {idUpdate(top, $1); $$ = makeLeaf($1); }
     | I_CONSTANT { $$ = makeLeaf($1); }
     ; 
	 

init_declarator_list
	: init_declarator {$$ = $1; }
	| init_declarator_list ',' init_declarator { $$ = init_declarator_list($1, ",", $3); }
	;

init_declarator
	: declarator '=' initializer {$$ = init_declarator($1, "=", $3); }
	| declarator {$$ = $1; }
	;

storage_class_specifier
	: TYPEDEF {$$ = makeLeaf($1); }
	| EXTERN {$$ = makeLeaf($1); }
	| STATIC {$$ = makeLeaf($1); }
	| THREAD_LOCAL {$$= makeLeaf($1); }
	| AUTO {$$ = makeLeaf($1); }
	| REGISTER {$$ = makeLeaf($1); }
	;

type_specifier
	: VOID {$$ = makeLeaf($1); }
	| CHAR {$$ = makeLeaf($1); }
	| SHORT {$$ = makeLeaf($1); }
	| INT {$$ = makeLeaf($1); }
	| LONG {$$ = makeLeaf($1); }
	| FLOAT {$$ = makeLeaf($1); }
	| DOUBLE {$$ = makeLeaf($1); }
	| SIGNED {$$ = makeLeaf($1); }
	| UNSIGNED {$$ = makeLeaf($1); }
	| BOOL {$$ = makeLeaf($1); }
	| COMPLEX {$$ = makeLeaf($1); }
	| IMAGINARY 	{$$ = makeLeaf($1); }
	| atomic_type_specifier { $$ = $1; } 
	| struct_or_union_specifier {$$ = $1; }
	| enum_specifier {$$ = $1;  }
	| TYPEDEF_NAME 	{$$ = makeLeaf($1); }
	;

struct_or_union_specifier
	: struct_or_union '{' 
	{saved = top; top = createEnv(saved);}
	 struct_declaration_list 
	'}' 
	{$$ = struct_or_union_specifier1($1, "{", $4, "}"); destroyEnv(top); top = saved; saved = top->prev; }
	| struct_or_union IDENTIFIER '{'
	{saved = top; top = createEnv(saved); }
	 struct_declaration_list 
	'}'
	{$$ = struct_or_union_specifier2($1, $2, "{", $5, "}"); destroyEnv(top); top = saved; saved = top->prev;idUpdate(top,$2);}
	| struct_or_union IDENTIFIER {idUpdate(top, $2); $$ = struct_or_union_specifier3($1, $2); }
	;

struct_or_union
	: STRUCT {$$ = makeLeaf($1); }
	| UNION { $$ = makeLeaf($1); }
	;

struct_declaration_list
	: struct_declaration {$$ = $1; }
	| struct_declaration_list struct_declaration {$$ = struct_declaration_list($1, $2); }
	;

struct_declaration
	: specifier_qualifier_list ';'	{$$ = struct_declaration1($1, ";"); }
	| specifier_qualifier_list struct_declarator_list ';' {$$ = struct_declaration2($1, $2, ";"); }
	| static_assert_declaration {$$ = $1; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {$$ = specifier_qualifier_list($1, $2); }
	| type_specifier {$$ = $1; }
	| type_qualifier specifier_qualifier_list {$$ = specifier_qualifier_list($1, $2); }
	| type_qualifier {$$ = $1; }
	;

struct_declarator_list
	: struct_declarator {$$ = $1; }
	| struct_declarator_list ',' struct_declarator {$$ = struct_declarator_list($1, ",", $3); }
	;

struct_declarator
	: ':' constant_expression {$$ = struct_declarator1( ":", $2); }
	| declarator ':' constant_expression {$$ = struct_declarator2($1,":", $3); }
	| declarator {$$ = $1; }
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {$$ =  enum_specifier1($1, "{", $3, "}"); }
	| ENUM '{' enumerator_list ',' '}' {$$ = enum_specifier2( "{", $2, $3, ",", "}"); }
	| ENUM IDENTIFIER 
	'{' enumerator_list '}' {idUpdate(top, $2); $$ = enum_specifier3($1, $2, "{", $4, "}"); }
	| ENUM IDENTIFIER
	'{' enumerator_list ',' '}' {idUpdate(top, $2); $$ = enum_specifier4($1, $2, "{", $4, ",", "}"); }
	| ENUM IDENTIFIER {idUpdate(top, $2); $$ = enum_specifier5($1, $2); }
	;

enumerator_list
	: enumerator {$$ = $1; }
	| enumerator_list ',' enumerator {$$ = enumerator_list($1, ",", $3); }
	;

enumerator	
	: enumeration_constant '=' constant_expression {$$ = enumerator($1, "=", $3); }
	| enumeration_constant {$$ = $1; }
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')' { $$ = atomic_type_specifier($1, "(", $3, ")"); }
	;

type_qualifier
	: CONST {$$ = makeLeaf($1); }
	| RESTRICT {$$ = makeLeaf($1); }
	| VOLATILE {$$ = makeLeaf($1); }
	| ATOMIC {$$ = makeLeaf($1); }
	;

function_specifier
	: INLINE {$$ = makeLeaf($1); }
	| NORETURN {$$ = makeLeaf($1); }
	;

alignment_specifier
	: ALIGNAS '(' type_name ')' {$$ = alignment_specifier($1, "(", $3, ")"); }
	| ALIGNAS '(' constant_expression ')' {$$ = alignment_specifier($1, "(", $3, ")"); }
	;

declarator
	: pointer direct_declarator {$$ = declarator($1, $2); }
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER {idUpdate(top, $1); $$ = makeLeaf($1); }
	| direct_declarator attribute_specifier {$$ = direct_declarator1($1, $2); }
	| '(' declarator ')' {$$ = direct_declarator2( "(", $2,")");}
	| direct_declarator '[' ']' {$$ = direct_declarator3($1, "[", "]"); }
	| direct_declarator '[' '*' ']'{$$ = direct_declarator4($1, "[", "*", "]"); }
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' {$$ = direct_declarator5($1, "[", $3, $4, $5, "]"); }
	| direct_declarator '[' STATIC assignment_expression ']' {$$ = direct_declarator6($1, "[", $3, $4, "]"); }
	| direct_declarator '[' type_qualifier_list '*' ']' {$$ = direct_declarator7($1, "[", $3, "*", "]"); }
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'{$$ = direct_declarator8($1, "[", $3, $4, $5, "]"); }
	| direct_declarator '[' type_qualifier_list assignment_expression ']' {$$ = direct_declarator9($1, "[", $3, $4, "]"); }
	| direct_declarator '[' type_qualifier_list ']' {$$ = direct_declarator10($1, "[", $3, "]"); }
	| direct_declarator '[' assignment_expression ']'  {$$ = direct_declarator10($1, "[", $3, "]"); }
	| direct_declarator '(' parameter_type_list ')' {$$ = direct_declarator10($1, "(", $3, ")"); }
	| direct_declarator '(' ')'{$$ = direct_declarator3( $1,"(", ")");  }
	| direct_declarator '(' identifier_list ')' {$$ = direct_declarator10($1, "(", $3, ")"); }
	;

pointer
	: '*' type_qualifier_list pointer {$$ = pointer1( "*", $2, $3); }
	| '*' type_qualifier_list {$$ = pointer2( "*", $2); }
	| '*' pointer {$$ = pointer2( "*", $2); }
	| '*' {$$ = makeLeaf("*"); }
	;

type_qualifier_list
	: type_qualifier {$$ = $1; }
	| type_qualifier_list type_qualifier {$$ = type_qualifier_list($1, $2); }
	;


parameter_type_list
	: parameter_list ',' ELLIPSIS {$$ = parameter_type_list($1, ",", $3); }
	| parameter_list { $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration {$$ = parameter_list($1, ",", $3); }
	;

parameter_declaration
	: declaration_specifiers declarator {$$ = parameter_declaration($1, $2); }
	| declaration_specifiers abstract_declarator {$$ = parameter_declaration($1, $2); }
	| declaration_specifiers {$$ = $1; }
	;

identifier_list
	: IDENTIFIER {idUpdate(top, $1); $$ = makeLeaf($1); }
	| identifier_list ',' IDENTIFIER {idUpdate(top, $3);$$ = identifier_list($1, ",", $3); }
	;

type_name
	: specifier_qualifier_list abstract_declarator {$$ = type_name($1, $2); }
	| specifier_qualifier_list {$$ = $1;}
	;

abstract_declarator
	: pointer direct_abstract_declarator {$$= abstract_declarator($1, $2); }
	| pointer {$$ = $1; }
	| direct_abstract_declarator { $$ = $1; }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' {$$ = direct_abstract_declarator1( "(", $2, ")"); }
	| '[' ']' {$$ = direct_abstract_declarator2( "[", "]"); }
	| '[' '*' ']' {$$ = direct_abstract_declarator3( "[", "*", "]"); }
	| '[' STATIC type_qualifier_list assignment_expression ']'{$$ = direct_abstract_declarator4("[" , $2, $3, $4, "]"); }
	| '[' STATIC assignment_expression ']' {$$ = direct_abstract_declarator5( "[", $2, $3, "]"); }
	| '[' type_qualifier_list STATIC assignment_expression ']' {$$ = direct_abstract_declarator6( "[", $2, $3, $4, "]"); }
	| '[' type_qualifier_list assignment_expression ']'{$$ = direct_abstract_declarator7( "[", $2, $3, "]"); }
	| '[' type_qualifier_list ']' {$$ = direct_abstract_declarator1( "[", $2, "]"); }
	| '[' assignment_expression ']' {$$ = direct_abstract_declarator1( "[", $2, "]"); }
	| direct_abstract_declarator '[' ']'{$$ = direct_abstract_declarator8($1, "[","]"); }
	| direct_abstract_declarator '[' '*' ']'{$$ = direct_abstract_declarator9($1, "[", "*", "]");}
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'{$$ = direct_abstract_declarator10($1,"[",$3,$4,$5,"]");}
	| direct_abstract_declarator '[' STATIC assignment_expression ']' {$$ = direct_abstract_declarator11($1, "[", $3, $4, "]"); }
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']' {$$ = direct_abstract_declarator12($1, "[", $3, $4, "]"); }
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'{$$ = direct_abstract_declarator13($1,"[",$3,$4,$5,"]");}
	| direct_abstract_declarator '[' type_qualifier_list ']'{$$ = direct_abstract_declarator14($1, "[", $3, "]"); }
	| direct_abstract_declarator '[' assignment_expression ']'{$$ = direct_abstract_declarator14($1, "[",$3, "]"); }
	| '(' ')' { $$ = direct_abstract_declarator2( "(", ")"); }
	| '(' parameter_type_list ')' {$$ =  direct_abstract_declarator1( "(", $2, ")"); }
	| direct_abstract_declarator '(' ')' {$$ = direct_abstract_declarator8($1, "(", ")"); }
	| direct_abstract_declarator '(' parameter_type_list ')' {$$ = direct_abstract_declarator14($1, "(", $3, ")"); }
	;

initializer
	: '{'initializer_list 	'}' {$$ = initializer1( "{", $2, "}"); }
	| '{'initializer_list ',' '}'{$$ = initializer2( "{", $2, ",", "}"); }
	| assignment_expression {$$ = $1; }
	;

initializer_list
	: designation initializer {$$ = $1; }
	| initializer {$$ = $1; }
	| initializer_list ',' designation initializer {$$ = initializer_list1($1,",", $3, $4); }
	| initializer_list ',' initializer {$$ = initializer_list2($1, ",", $3); }
	;

designation
	: designator_list '=' {$$ = designation($1, "="); }
	;

designator_list
	: designator {$$ = $1; }
	| designator_list designator {$$ = designator_list($1, $2); }
	;

designator
	: '[' constant_expression ']' {$$ = designator1( "[", $2, "]"); }
	| '.' IDENTIFIER {idUpdate(top, $2); } {$$ = designator2( ".", $2); }
	;

static_assert_declaration
	: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';' {$$ = static_assert_declaration($1, "(", $3, ",", $5, ")", ";"); }
	;

statement
	: labeled_statement {$$ = $1; }
	| compound_statement {$$ = $1; }
	| expression_statement {$$ = $1; }
	| selection_statement {$$ = $1; }
	| iteration_statement {$$ = $1; }
	| jump_statement {$$ = $1; }
	;

labeled_statement
	: IDENTIFIER {idUpdate(top, $1); } 
	':' statement {$$ = labeled_statement1($1, ":", $4); }
	| CASE constant_expression ':' statement { $$ = labeled_statement2($1, $2, ":", $4); }
	| DEFAULT ':' statement {$$ = labeled_statement1($1, ":", $3); }
	;

compound_statement
	: '{'
	{saved = top; top = createEnv(saved); }
	 '}'
	{$$ = compound_statement1( "{", "}"); destroyEnv(top); top = saved; saved = top->prev; }
	| '{' {saved = top; top = createEnv(saved); } block_item_list '}'{$$ = compound_statement2( "{", $3, "}"); destroyEnv(top); top = saved; saved = top->prev;}
	;

block_item_list
	: block_item {$$ = $1; }
	| block_item_list block_item {$$ = block_item_list($1, $2); }
	;

block_item
	: declaration {$$ = $1; }
	| statement {$$ = $1; }
	;

expression_statement
	: ';'  {$$ = makeLeaf(";"); }
	| expression ';'{$$ = expression_statement($1, ";"); }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement {$$ = selection_statement1($1, "(", $3, ")", $5, $6, $7); }
	| IF '(' expression ')' statement {$$ = selection_statement2($1, "(", $3, ")", $5); }
	| SWITCH '(' expression ')' statement {$$ = selection_statement2($1, "(", $3, ")", $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = iteration_statement1($1, "(", $3, ")", $5); }
	| DO statement WHILE '(' expression ')' ';' {$$ = iteration_statement2($1, $2, $3, "(", $5,")", ";"); }
	| FOR '(' expression_statement expression_statement ')' statement {$$ = iteration_statement3($1, "(", $3, $4, ")", $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = iteration_statement4($1, "(", $3, $4, $5, ")", $7);}
	| FOR '(' declaration expression_statement ')' statement {$$ = iteration_statement3($1, "(", $3, $4, ")", $6); }
	| FOR '(' declaration expression_statement expression ')' statement {$$ = iteration_statement4($1, "(", $3, $4, $5, ")", $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';' {idUpdate(top, $2); $$ = jump_statement1($1, $2, ";"); }
	| CONTINUE ';'{$$ = jump_statement2($1, ";"); }
	| BREAK ';'{$$ = jump_statement2($1, ";"); }
	| RETURN ';'{$$ = jump_statement2($1, ";"); }
	| RETURN expression ';'{$$ = jump_statement3($1, $2, ";"); }
	;

translation_unit
	: external_declaration {$$ = $1; unit = $$;}
	| translation_unit external_declaration {$$ = translation_unit($1, $2);unit=$$; }
	;

external_declaration
	: function_definition {$$ = $1; }
	| declaration {$$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {$$ = function_definition1($1, $2, $3, $4); }
	| declaration_specifiers declarator compound_statement {$$ =  function_definition2($1, $2, $3); }
	;

declaration_list
	: declaration {$$ = $1; }
	| declaration_list declaration {$$ = declaration_list($1, $2); }
	;

%%


void yyerror(char *err) {
    fprintf(stderr, "%s in line : %d\n",
	    err,  linenum  );
	 
}


int idUpdate(Env* top, char* str) {
	if (idExists(top, str)) return 0; 
	else {
		if (!(insertID(top, str, linenum, IDENTIFIER)))
			return 0;  
	}
	return 1; 
}



int typeUpdate (Env* top, Node * type,  Node * str) {
	Node * temp; 
	char * typename, * string; 
		
	//Check typedef vs enumeration_constant
	temp = type;
	  
	while (temp->left) {	
		temp = temp->left; 
	}
	typename = temp->val; 
	
	// get identifier value
	temp = str;  
	while(temp->left) { 
		temp = temp->left; 	
	}
	string = temp->val; 
	
	// insert into symbol table
       	if (!strncmp(typename, typed, 4)) {
		if (!(typeExists(top, string))) {
			if (!(insertType(top, string, linenum, TYPEDEF_NAME)))
			return 0; 
		}
	}
	if (!strncmp(typename, enm, 4)) {
		if (!(typeExists(top, string))) {
			if (!(insertType(top, string, linenum, ENUMERATION_CONSTANT)))
			return 0; 
		}

	}
	
	return 1; 
}

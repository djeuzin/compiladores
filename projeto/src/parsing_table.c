/***************************/
/*  Cross: C- Compiler     */
/*  parsing_table.c        */
/*  Contém a definição da  */
/*  da tabela preditiva    */
/*  LL(1) do parser        */
/***************************/

#include "parsing_table.h"

int parsingTable[][44]= {
//       ID, NUM,  +,  -,  *,  /,  <,  >,  =,  !=,  ;,  ,,  (,  ),  [,  ],  {,  }, ERR,  <=,  >=,  ==, ELSE,  IF, INT, RETURN, VOID, WHILE,   $
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   1,      0,    1,     0,   0},  // PROG
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   2,      0,    2,     0,   0},  // DECL_LIST
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   3,      0,    3,     0,   4},  // DECL_LIST_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   5,      0,    5,     0,   0},  // DECLARATION
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  6,  0,  7,  0,  6,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // DECLARATION_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   8,      0,    8,     0,   0},  // VAR_DECL
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  9,  0,  0,  0, 10,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // VAR_DECL_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,  11,      0,   12,     0,   0},  // TYPE_SPEC
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,  13,      0,   14,     0,   0},  // PARAMS
	{15,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0, 16,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // VOID-PARAMS
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,  17,      0,   17,     0,   0},  // PARAM_LIST
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0, 18,  0, 19,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // PARAM_LIST_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,  20,      0,   20,     0,   0},  // PARAM
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0, 22,  0, 22, 21,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // PARAM_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0, 23,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // COMP_STMT
	{24,  24,  0,  0,  0,  0,  0,  0,  0,   0, 24,  0, 24,  0,  0,  0, 24, 24,   0,   0,   0,   0,    0,  24,  24,     24,   24,    24,   0},  // LOCAL_DECL
	{26,  26,  0,  0,  0,  0,  0,  0,  0,   0, 26,  0, 26,  0,  0,  0, 26, 26,   0,   0,   0,   0,    0,  26,  25,     26,   25,    26,   0},  // LOCAL_DECL_
	{27,  27,  0,  0,  0,  0,  0,  0,  0,   0, 27,  0, 27,  0,  0,  0, 27, 27,   0,   0,   0,   0,    0,  27,   0,     27,    0,    27,   0},  // STMT_LIST
	{28,  28,  0,  0,  0,  0,  0,  0,  0,   0, 28,  0, 28,  0,  0,  0, 28, 29,   0,   0,   0,   0,    0,  28,   0,     28,    0,    28,   0},  // STMT_LIST_
	{30,  30,  0,  0,  0,  0,  0,  0,  0,   0, 30,  0, 30,  0,  0,  0, 31,  0,   0,   0,   0,   0,    0,  32,   0,     34,    0,    33,   0},  // STATEMENT
	{35,  35,  0,  0,  0,  0,  0,  0,  0,   0, 36,  0, 35,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // EXP_STMT
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,  37,   0,      0,    0,     0,   0},  // SELECTION_STMT
	{39,  39,  0,  0,  0,  0,  0,  0,  0,   0, 39,  0, 39,  0,  0,  0, 39, 39,   0,   0,   0,   0,   38,  39,   0,     39,    0,    39,   0},  // SELECTION_STMT_
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,    40,   0},  // ITERATION_STMT
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,     41,    0,     0,   0},  // RETURN_STMT
	{43,  43,  0,  0,  0,  0,  0,  0,  0,   0, 42,  0, 43,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // RETURN_STMT_
	{44,  46,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 45,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // EXPRESSION
	{ 0,   0, 47, 47, 47, 47, 47, 47, 47,   0, 47, 47, 48, 47, 47, 47,  0,  0,   0,  47,  47,  47,    0,   0,   0,      0,    0,     0,   0},  // EXPRESSION_
	{ 0,   0, 50, 50, 50, 50, 50, 50, 49,  50, 50, 50,  0, 50,  0, 50,  0,  0,   0,  50,  50,  50,    0,   0,   0,      0,    0,     0,   0},  // EXPRESSION__
	{51,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // VAR
	{ 0,   0, 53, 53, 53, 53, 53, 53, 53,  53, 53, 53,  0, 53, 52, 53,  0,  0,   0,  53,  53,  53,    0,   0,   0,      0,    0,     0,   0},  // VAR_
	{ 0,   0,  0,  0,  0,  0, 54, 54,  0,  54, 55, 55,  0, 55,  0, 55,  0,  0,   0,  54,  54,  54,    0,   0,   0,      0,    0,     0,   0},  // SIMPLE_EXP
	{ 0,   0,  0,  0,  0,  0, 57, 58,  0,  61,  0,  0,  0,  0,  0,  0,  0,  0,   0,  56,  59,  60,    0,   0,   0,      0,    0,     0,   0},  // RELOP
	{62,  62,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 62,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // ADD_EXP
	{ 0,   0, 63, 63,  0,  0, 64, 64,  0,  64, 64, 64,  0, 64,  0, 64,  0,  0,   0,  64,  64,  64,    0,   0,   0,      0,    0,     0,   0},  // ADD_EXP_
	{ 0,   0, 65, 66,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // ADDOP
	{67,  67,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 67,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // TERM
	{ 0,   0, 69, 69, 68, 68, 69, 69,  0,  69, 69, 69,  0, 69,  0, 69,  0,  0,   0,  69,  69,  69,    0,   0,   0,      0,    0,     0,   0},  // TERM_
	{ 0,   0,  0,  0, 70, 71,  0,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // MULOP
	{73,  74,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 72,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // FACTOR
	{ 0,   0, 75, 75, 75, 75, 75, 75,  0,  75, 75, 75, 76, 75, 75, 75,  0,  0,   0,  75,  75,  75,    0,   0,   0,      0,    0,     0,   0},  // FACTOR_
	{77,  77,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 77, 78,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // ARGS
	{79,  79,  0,  0,  0,  0,  0,  0,  0,   0,  0,  0, 79,  0,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0},  // ARG_LIST
	{ 0,   0,  0,  0,  0,  0,  0,  0,  0,   0,  0, 80,  0, 81,  0,  0,  0,  0,   0,   0,   0,   0,    0,   0,   0,      0,    0,     0,   0}   // ARG_LIST_
};

/*

program 		-> declaration-list
declaration-list 	-> <ADD_SIBLING_STOPPER> declaration declaration-list_ <ADD_SIBLINGS>
declaration-list_ 	-> declaration declaration-list_
declaration-list_ 	-> 
declaration 		-> type-specifier ID declaration_
declaration_ 		-> var-declaration_ 
declaration_ 		-> ( <SET_FUN_DECL> <ADD_SIBLING_STOPPER> params ) <ADD_SIBLING> <ADD_PARAM_CHILD> compound-stmt <ADD_STMT_CHILD>
var-declaration 	-> type-specifier ID var-declaration_
var-declaration_ 	-> ; <SET_VAR_DECL>
var-declaration_ 	-> [ NUM <SET_ARRAY_DECL> ] ;
type-speficier 		-> INT 
type-speficier 		-> VOID
params			-> INT ID param_ param-list_ 
params 			-> VOID void-params
void-params		-> ID param_ param-list_ 
void-params		-> <SET_VOID_PARAM>
param-list 		-> param param-list_
param-list_		-> , param param-list_ 
param-list_ 		-> 
param 			-> type-specifier ID param_
param_ 			-> [] <SET_ARRAY_PARAM>
param_ 			-> <SET_VAR_PARAM>
compound-stmt 		-> { <ADD_SIBLING_STOPPER> local-declarations statement-list } <ADD_SIBLING>
local-declarations 	-> local-declarations_
local-declarations_	-> var-declaration local-declarations_ 
local-declarations_	-> 
statement-list 		-> statement-list_
statement-list_		-> statement statement-list_ 
statement-list_		-> 
statement 		-> expression-stmt 
statement 		-> compound-stmt 
statement 		-> selection-stms 
statement 		-> iteration-stmt 
statement 		-> return-stmt
expression-stmt 	-> expression; 
expression-stmt 	-> ;
selection-stmt 		-> IF ( expression ) <ADD_EXP_CHILD> statement <ADD_STMT_CHILD> selection-stmt_
selection-stmt_		-> ELSE statement <ADD_ELSE_CHILD>
selection-stmt_ 	-> 
iteration-stmt 		-> WHILE ( expression ) <ADD_EXP_CHILD> statement <ADD_STMT_CHILD>
return-stmt 		-> RETURN return-stmt_
return-stmt_		-> ; 
return-stmt_		-> expression ; <ADD_EXP_CHILD>
expression 		-> ID expression_
expression 		-> ( expression ) term_ add-expression_ simple-expression_ 
expression 		-> NUM term_ add-expression_ simple-expression_
expression_ 		-> var_ expression__ 
expression_ 		-> ( <SET_FUN_CALL> <ADD_SIBLING_STOPPER> args ) <ADD_SIBLING> <ADD_PARAM_CHILD> term_ add-expression_ simple-expression_
expression__		-> = expression <ADD_EXP_CHILD>
expression__ 		-> term_ add-expression_ simple-expression_
var 			-> ID var_
var_ 			-> [ <SET_ARRAY> expression ] <ADD_INDEX_CHILD>
var_ 			-> <SET_VAR>
simple-expression_	-> relop additive-expression <BUILD_EXP>
simple-expression_ 	-> 
relop 			-> <= 
relop 			-> < 
relop 			-> > 
relop 			-> >= 
relop 			-> == 
relop 			-> !=
additive-expression 	-> term add-expression_
add-expression_ 	-> addop term <BUILD_EXP> add-expression_
add-expression_		-> 
addop 			-> + 
addop 			-> -
term 			-> factor term_
term_			-> mulop factor <BUILD_EXP> term_ 
term_ 			-> 
mulop 			-> * 
mulop			-> /
factor 			-> ( expression ) 
factor 			-> ID factor_ 
factor 			-> NUM 
factor_ 		-> var_ 
factor_ 		-> ( <SET_FUN_CALL> <ADD_SIBLING_STOPPER> args ) <ADD_SIBLING> <ADD_PARAM_CHILD>
args 			-> arg-list 
args 			-> 
arg-list 		-> expression arg-list_
arg-list_		-> , expression arg-list_
arg-list_ 		-> 

----------------

program				-> declaration-list
declaration-list 	-> declaration declaration-list_
declaration-list_ 	-> declaration declaration-list_ | eps
declaration 		-> type-specifier ID declaration_
declaration_ 		-> var-declaration_ | ( params ) compound-stmt
var-declaration 	-> type-specifier ID var-declaration_
var-declaration_ 	-> ; | [ NUM ] ;
type-speficier 		-> INT | VOID
//fun-declaration 	-> type-specifier ID ( params ) compoun-stmt
params 				-> INT ID param_ param-list_ | VOID void-params
void-params			-> ID param_ param-list_ | eps
param-list 			-> param param-list_
param-list_			-> , param param-list_ | eps
param 				-> type-specifier ID param_
param_ 				-> [] | eps
compound-stmt 		-> { local-declarations statement-list }
local-declarations 	-> local-declarations_
local-declarations_ -> var-declaration local-declarations_ | eps
statement-list 		-> statement-list_
statement-list_		-> statement statement-list_ | eps
statement 			-> expression-stmt | compound-stmt | selection-stms | iteration-stmt | return-stmt
expression-stmt 	-> expression ; | ;
selection-stmt 		-> IF ( expression ) statement selection-stmt_
selection-stmt_		-> ELSE statement | eps
iteration-stmt 		-> WHILE ( expression ) statement
return-stmt 		-> RETURN return-stmt_
return-stmt_		-> ; | expression ;
expression 			-> ID expression_ | ( expression ) term_ add-expression_ simple-expression_ | NUM term_ add-expression_ simple-expression_
expression_ 		-> var_ expression__ | (args) term_ add-expression_ simple-expression_
expression__		-> = expression | term_ add-expression_ simple-expression_
var 				-> ID var_
var_ 				-> [ expression ] | eps
//simple-expression -> additive-expression simple-expression_
simple-expression_	-> relop additive-expression | eps
relop 				-> <= | < | > | >= | == | !=
additive-expression -> term add-expression_
add-expression_ 	-> addop term add-expression_
addop 				-> + | -
term 				-> factor term_
term_				-> mulop factor term_ | eps
mulop 				-> * | /
factor 				-> ( expression ) | ID factor_ | NUM
factor_ 			-> var_ | (args)
//call 				-> ID ( args )
args 				-> arg-list | eps
arg-list 			-> expression arg-list_
arg-list_			-> , expression | eps

--------First-------------

First(program) = {INT, VOID}
First(declaration-list) = {INT, VOID}
First(declaration-list_) = {INT, VOID, eps}
First(declaration) = {INT, VOID}
First(declaration_) = {'(', ;, '['}
First(var-declaration) = {INT, VOID}
First(var-declaration_) = {;, '['}
First(type-speficier) = {INT, VOID}
First(params) = {INT, VOID}
First(void-params) = {ID, eps}
First(param-list) = {INT, VOID}
First(param-list_) = {',', eps}
First(param) = {INT, VOID}
First(param_) = {'[', eps}
First(compound-stmt) = {'{'}
First(local-declarations) = {INT, VOID, eps}
First(local-declarations_) = {INT, VOID, eps}
First(statement-list) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, eps}
First(statement-list_) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, eps}
First(statement) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN}
First(expression-stmt) = {ID, NUM, '(', ;}
First(selection-stmt) = {IF}
First(selection-stmt_) = {ELSE, eps}
First(iteration-stmt) = {WHILE}
First(return-stmt) = {RETURN}
First(return-stmt_) = {ID, NUM, '(', ;}
First(expression) = {ID, NUM, '('}
First(expression_) = {'(', '[', '=', *, /, +, -}
First(expression__) = {'=', *, /, +, -, eps}
First(var) = {ID}
First(var_) = {'[', eps}
First(simple-expression_) = {<=, <, >, >=, ==, !=, eps}
First(relop) = {<=, <, >, >=, ==, !=}
First(additive-expression) = {ID, NUM, '('}
First(add-expression_) = {+, -, esp}
First(addop) = {+, -}
First(term) = {ID, NUM, '('}
First(term_) = {*, /, eps}
First(mulop) = {*, /}
First(factor) = {ID, NUM, '('}
First(factor_) = {'(', '[', eps}
First(args) = {ID, NUM, '(', eps}
First(arg-list) = {ID, NUM, '('}
First(arg-list_) = {',', eps}

--------Follow-------------

Follow(program) = {$}
Follow(declaration-list) = {$}
Follow(declaration-list_) = {$}
Follow(declaration) = {INT, VOID, $}
Follow(declaration_) = {INT, VOID, $}
Follow(var-declaration) = {INT, VOID, ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}'}
Follow(var-declaration_) = {INT, VOID, $, ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}'}
Follow(type-speficier) = {ID}
Follow(params) = {')'}
Follow(void-params) = {')'}
Follow(param-list) = {}
Follow(param-list_) = {')'}
Follow(param) = {',', ')'}
Follow(param_) = {',', ')'}
Follow(compound-stmt) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', INT, VOID, $, ELSE}
Follow(local-declarations) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}'}
Follow(local-declarations_) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}'}
Follow(statement-list) = {'}'}
Follow(statement-list_) = {'}'}
Follow(statement) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(expression-stmt) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(selection-stmt) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(selection-stmt_) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(iteration-stmt) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(return-stmt) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(return-stmt_) = {ID, NUM, '(', ;, '{', IF, WHILE, RETURN, '}', ELSE}
Follow(expression) = {;, ')', ',', ']'}
Follow(expression_) = {;, ')', ',', ']'}
Follow(expression__) = {;, ')', ',', ']'}
Follow(var) = {}
Follow(var_) = {'=', +, -, *, /, <=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(simple-expression_) = {;, ')', ',', ']'}
Follow(relop) = {ID, NUM, '('}
Follow(additive-expression) = {;, ')', ',', ']'}
Follow(add-expression_) = {<=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(addop) = {ID, NUM, '('}
Follow(term) = {+, -, *, /, <=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(term_) = {+, -, <=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(mulop) = {ID, NUM, '('}
Follow(factor) = {+, -, *, /, <=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(factor_) = {+, -, *, /, <=, <, >, >=, ==, !=, ;, ')', ',', ']'}
Follow(args) = {')'}
Follow(arg-list) = {')'}
Follow(arg-list_) = {')'}
*/
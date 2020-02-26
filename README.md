# -Expression-Evaluator
 an expression-evaluation module and integrate it with the interface module for the interpreter project so that the user has the option to evaluate expressions (without variables used in the expressions).
Given a table storing the values of a number of variables, the functions in this module are implemented to evaluate any infix arithmetic or logic expression with parentheses, arithmetic operators (+, −, *, /, %), relational operators (>, >=, <, <=, = =), logical operators (&&, ||, !), numerical constants, and the variables in the table.

 

Algorithms and data structures

Evaluating arithmetic expressions and logic expressions: Arithmetic expressions and logic expressions are infix expressions
(for example, in 3*4, the binary operator * appears between the two operands 3 and 4) involving various arithmetic, 
relational, and logocal operators ( e.g. +, −, *, /, %, >=, <, <=, = =, &&, ||, !) with different precedence levels. 
One major hurdle to evaluate these infix expressions is to apply the operators to evaluate portions of the expressions 
in the right order respecting the precedence levels of the operators. For example, in 2+3*4, we need to evaluate 3*4 first, 
instead of doing 2+4.
Infix-to-postfix conversion and Postfix evaluation: To deal with this, one possibility is to first convert a given infix 
expression into a corresponding postfix expression and then use a stack to help evaluate the postfix expression. The issue of 
operator precedence levels is resolved by conversion into the postfix expression since the postfix expression uniquely defines
the order for applying the operators during the evaluation. Very carefully read and understand the following descriptions regarding 
the details of the algorithms and data structures for infix-to-postfix conversion。 and Postfix evaluation。.
Using vectors to simulate the operations of stacks: We will use the vector class (as a sequential container) in the C++ Standard 
Template Library together with its methods such as push_back( ) and pop_back( ) operation to simulate the operator of a stack
needed in the conversion and evaluation algorithms.
Using associative maps to keep the names and values of variables: We will use the associative map class (as an associative container)
in the C++ Standard Template Library to handle the storage and update of the values of the variables used in the expression evaluation.
You should carefully study the examples on how to use the associative map in cpp。 and mapAsAssociativeArray.cpp。
. Another useful resource is the map container description in the SGI online tutorials on the C++ Standard Template Library

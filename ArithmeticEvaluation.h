/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                               */
/* Purpose: Definition of ArithmeticEvaluation class                 */
/* ArithmeticEvaluation class uses Stacks to evaluate a mathematical */
/* expression                                                        */
/*********************************************************************/

#ifndef STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H
#define STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H

# include <iostream>
#include <unordered_map>
# include "Stack.cpp"
using namespace std;

class ArithmeticEvaluation {
private:
    Stack<double> numStack;                         // Stack to store numbers
    Stack<char> opStack;                            // Stack to store operators

    double num;                                     // temp variable for storing number
    char op;                                        // temp variable for storing operator

    bool opFlag;                                    // flag shows the item read previously is an operator
    bool beginFlag;                                 // flag shows it's the beginning of reading

    /**
     * @Brief a hashmap of operators. Key is the operator, and value is
     * their corresponding precedence rank. higher number of precedence
     * rank means the operator has higher precedence
     */
    unordered_map<char, int> precedenceMap;

public:

    /**
     * @Brief the default constructor
     * @Detail the function will initialize all the member variables
     * and set "opFlag = false" and "beginFlag = True". It will also
     * set all the precedence for operators in precedenceMap.
     */
    ArithmeticEvaluation();

    /**
     * @Brief getPrecedence returns the precedence of an operator (eg. '+')
     * @Detail the function will check the user provided op against the
     * precedenceMap in the class to get the op's precedence
     * @Input 'op' is the operator the user wants to check precedence for.
     * @Output the precedence rank of an operator
     */
    int getPrecedence(char op1);

    /**
     * @Brief compare the precedence of two 'char' variables, to see if the var on the
     * LHS has less precedence than the one at RHS ---> LHS < RHS
     * @Input 1st char is the 'LHS', and the 2nd char is the 'RHS'.
     * @Output a boolean result. If RHS has less precedence than the RHS, the output is
     * TRUE. Otherwise, the output is FALSE
     */
    bool isLessPrecedence(char leftOp, char rightOp);

    /**
     * @Brief do calculation using the top operator in the stack, and the top two
     * values from the numStack.
     * @Detail the function will take operator "op" from the top of opStack. And
     * top two values "x" and "y" from numStack, where x is on top of y. The function
     * will do the calculation "y op x", and save the result back to numStack
     */
    void calculation();

    /**
     * @Brief function for evaluating an arithmetic expression
     * @Detail when the function start to run, it will ask the user to
     * provide an arithmetic expression. Then the function will print out the
     * arithmetic calculation of the expression user provided
     */
    double evaluation();

};


#endif //STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H

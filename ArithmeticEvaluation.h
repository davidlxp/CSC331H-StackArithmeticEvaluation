/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                               */
/* Purpose: Definition of ArithmeticEvaluation class                 */
/* ArithmeticEvaluation class uses Stacks to evaluate a mathematical */
/* expression                                                        */
/*********************************************************************/

#ifndef STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H
#define STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "Stack.cpp"
using namespace std;

class ArithmeticEvaluation {
public:
    /**
     * @Brief the default constructor
     * @Detail the function will set all the precedence for operators in precedenceMap.
     */
    ArithmeticEvaluation();

    /**
     * @Brief function for evaluating an mathematical expression and provide
     * calculated result
     * @Detail when the function start to run, it will calculate the mathExpression
     * user provided. After running, it will save the result to the input variable
     * user provided
     * @Input a string variable represent a mathematical expression,
     * and a double variable which record the calculated result
     */
    void evaluation(const string& mathExpression, double& resultNum);

private:
    Stack<double> numStack;                         // Stack to store numbers
    Stack<char> opStack;                            // Stack to store operators

    /**
     * @Brief a hashmap of operators. Key is the operator, and value is
     * their corresponding precedence rank. higher number of precedence
     * rank means the operator has higher precedence
     */
    map<char, int> precedenceMap;

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
    bool isLessOrEqualPrecedence(char leftOp, char rightOp);

    /**
     * @Brief do calculation using the top operator in the stack, and the top two
     * values from the numStack.
     * @Detail the function will take operator "op" from the top of opStack. And
     * top two values "x" and "y" from numStack, where x is on top of y. The function
     * will do the calculation "y op x", and save the result back to numStack
     */
    void calculation();

    /**
     * @Brief function to check if an input MATH operator is allow in this program
     * @Input the operator which we want to check if it's an MATH operator allowed
     * in this program
     * @Output a boolean indicates whether an operator which allow in this program
     */
    bool isMathOp(char op);

    /**
     * @Brief function handle the situation where peek a number (int or decimal)
     * @Detail add the number to numStack
     */
    void handleNumber(double& num, bool& opFlag, bool& beginFlag);

    /**
     * @Brief function handle the situation where peek a non-digital, which is operator
     */
    void handleOperator(char& op, char& preOp, bool& opFlag, bool& beginFlag, bool& forbiddenOp);

    /**
     * @Brief function handle the case where "-" and "+" do not stands
     * for subtraction or addition. On contrary, they stands for negativity
     * and positivity of a number
     * @Detail
     * --> if '-' or '+' appears at the beginning of the arithmetic expression,
     * they should stand for negativity or positivity of number. In this case,
     * we turn the form like '+-3 + 4' into '(+1) * (-1) * 3 + 4'
     * --> if '-' or '+' discovered in the middle of expression, but right after another operator,
     * which is not ')'. They also stand for negativity or positivity of number. In this case,
     * we turn the form like '3+ -  2' into '3+ (-1) * 2'.
     * --> in this step we put '1' or '-1' into numStack, and '*' into opStack
     * @Input
     * op: a reference to the current "op" variable
     * preOp: a reference to the operator in the last round
     * opFlag: a reference to a boolean flag which indicates whether last item is an operator
     * beginFlag: a reference to a boolean flag which indicates whether it's beginning of input
     * forbiddenOp: a reference to a boolean flag which is TRUE when meet unrecognized operator
     */
    void handleSpecialMinusPlusSign(const char& op);

    /**
     * @Brief function handles the case where seeing a "." symbol
     * @Detail if ever read '.', it must be a part of a decimal number like '.6' = '0.6'
     * we change the form like '.6' to '0.1 * 6'
     * @Input an operator read from string stream
     */
    void handleDecimalSymbol(const char& op);

    /**
     * @Brief function handles the case where seeing a "(" symbol
     * @Detail function will read the operator '(' immediately
     * and push it into the opStack
     * @Input an operator read from string stream
     */
    void handleOpenParen(const char& op);

    /**
     * @Brief function handles the case where seeing a ")" symbol
     * @Detail function will do calculation to remove operators from
     * opStack until see an "(". The "(" will be pop from the stack
     * which indicates all the calculation within "()" is done
     */
    void handleCloseParen();

    /**
     * @Brief function handles the case where seeing a `+`, `-`,
     * `*`, `/` operator
     * @Detail function will compare new operator's precedence to the
     * top operator in opStack. If new operator has less or equal
     * precedence to the top operator, we will use the top operator from
     * stack to do calculation, and pop it. The process will finish when
     * new operator no longer has less or equal precedence than the top
     * operator in the stack, or the top operator is '('. When all
     * calculation is finished, push the new operator into the opStack
     * @Input an operator read from string stream
     */
    void handleMathOperator(const char& op);

    /**
     * @Brief function used all the remaining operators in the opStack to
     * do calculation until empty the opStack
     * @Detail after reading all the user input, if there still are unused operators
     * in the opStack, which means there still are some calculations needed to be done
     */
    void calculateUntilEmpty();

    /**
     * @Brief the function pops all elements from numStack and opStack until they are empty.
     * @Detail if the calculation process is terminated due to detected unknown operator, we need
     * to clean up the opStack and numStack to be prepared for the next math expression evaluation.
     */
    void popUntilEmpty();

    /**
     * @Brief function returns calculation answer of user's input
     * @Detail after doing calculation until the opStack is empty. The only 1 number
     * remains in the numStack is the final calculation result of user input
     * @Output the calculated answer of the math expression user provided
     */
    double getAnswer();

};


#endif //STACKARITHMETICEVALUATION_ARITHMETICEVALUATION_H

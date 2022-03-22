/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                               */
/* Purpose: Implementation of ArithmeticEvaluation class             */
/*********************************************************************/

#include "ArithmeticEvaluation.h"

ArithmeticEvaluation::ArithmeticEvaluation()
{
    // insert the operator and their precedence ranking into hashmap
    precedenceMap.insert(pair<char,int>('+', 1));
    precedenceMap.insert(pair<char,int>('-', 2));
    precedenceMap.insert(pair<char,int>('*', 3));
    precedenceMap.insert(pair<char,int>('/', 4));
}

int ArithmeticEvaluation::getPrecedence(char op1)
{
    int res = -1;

    // if the key exists in map, get the value (precedence rank) from the map
    if (precedenceMap.find(op1) != precedenceMap.end())
        res = precedenceMap.at(op1);

    return res;
}

bool ArithmeticEvaluation::isLessOrEqualPrecedence(char leftOp, char rightOp)
{
    int leftPrecedence = getPrecedence(leftOp);
    int rightPrecedence = getPrecedence(rightOp);
    return leftPrecedence <= rightPrecedence;
}

void ArithmeticEvaluation::calculation()
{
    char op1;                  // create a char variable to store the operator
    opStack.Top(op1);       // get the value of top operator from opStack
    opStack.pop();             // remove the top operator from stack

    double rhs, lhs;           // for example, in "x + y", y is rhs, and x is lhs
    numStack.Top(rhs);      // get the value of rhs from numStack
    numStack.pop();            // remove the rhs from stack
    numStack.Top(lhs);      // get the value of lhs from numStack
    numStack.pop();            // remove the lhs from stack

    double calcResult;         // variable to store calculation result of lhs and rhs

    switch (op1)                // do calculation according to different operators
    {
        case '+':
            calcResult = lhs + rhs;
            break;
        case '-':
            calcResult = lhs - rhs;
            break;
        case '*':
            calcResult = lhs * rhs;
            break;
        case '/':
            calcResult = lhs / rhs;
            break;
        default:
            calcResult = -1;
            break;
    }

    numStack.push(calcResult); // push the calculated result back to the numStack
}

double ArithmeticEvaluation::evaluation()
{
    // Initialize useful variables
    double num = 0;                               // temp variable for storing number
    char op = '\0';                               // temp variable for storing operator

    bool opFlag = false;                          // flag shows the item read previously is an operator
    bool beginFlag = true;                        // flag shows it's the beginning of reading

    // Start to take input and evaluate an mathematical expression
    cout << "Please Provide Arithmetic Expression for Evaluation: ";

    while (cin.peek() != '\n')
    {
        // 1. skip the whitespace if any
        if (cin.peek() == ' ')
        {
            handleWhiteSpace();                  // handle the whitespace from user input
        }
        // 2. if meet a number (int or decimal)
        else if (isdigit(cin.peek()))
        {
            cin >> num;
            handleNumber(num);                   // handle the number from user input

            opFlag = false;                      // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                   // once read something, it's not beginning of expression anymore
        }
        // 3. when seeing '-' or '+' operator, and they don't stand for Arithmetic operators
        else if ((cin.peek() == '-' || cin.peek() == '+') && (beginFlag || (opFlag && op != ')')))
        {
            cin >> op;                          // read the operator '-' or '+'
            handleSpecialMinusPlusSign(op);     // handle the special '-' or '+' sign

            opFlag = true;                      // the last read is an operator '*', so opFlag turns to True
            beginFlag = false;                  // once read something, it's not beginning of expression anymore
        }
        // 4. when see ".", handle it as a part of decimal number
        else if (cin.peek() == '.')
        {
            cin >> op;                              // read the decimal so the input stream can move on
            handleDecimalSymbol(op);                // handle decimal symbol

            opFlag = true;                          // the last read is an operator '*', so opFlag turns to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
        // 5. if meet operators under the other situation which are not stated above
        else
        {
            cin >> op;                              // read the new operator

            char opTop = '\0';                      // '\0' means the char is empty
            opStack.Top(opTop);                  // try to get the top operator from stack

            if (op == '(' || opTop == '\0')         // if op is '(' or if the opStack is empty
                handleOpenParenOrOpStackEmpty(op);
            else                                    // if op is not '(' and there are item in the opStack
            {
                if (op == ')')                      // a. if we read a ')' operator
                    handleCloseParen();
                else                                 // b. if we read anyone from '+-*/' operators
                    handleMathOperator(op);
            }

            opFlag = true;                          // read an operator, turns opFlag to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
    }

    calculateUntilEmpty();                          // deplete all operators to complete all undone calculations
    return getAnswer();                             // return the calculation answer
}


void ArithmeticEvaluation::handleWhiteSpace()
{
    cin.ignore();
}

void ArithmeticEvaluation::handleNumber(const double& num)
{
    numStack.push(num);
}

void ArithmeticEvaluation::handleSpecialMinusPlusSign(const char& op)
{
    if (op == '-')                      // operator '-' means '-1 *'
        numStack.push(-1);         // add number '-1' to number stack
    else                                // operator '+' means '1 *'
        numStack.push(1);          // add number '1' to number stack

    opStack.push('*');             // add operator '*' to stack
}

void ArithmeticEvaluation::handleDecimalSymbol(const char& op)
{
    numStack.push(0.1);                // push 0.1 to the number stack
    opStack.push('*');                 // push '*' to the operator stack
}

void ArithmeticEvaluation::handleOpenParenOrOpStackEmpty(const char& op)
{
    opStack.push(op);                       // directly push the new op into opStack
}

void ArithmeticEvaluation::handleCloseParen()
{
    char opTop = '\0';                      // '\0' means the char is empty
    opStack.Top(opTop);                  // try to get the top operator from stack

    while (opTop != '(')                    // we keep pop operators and do calculation until meet '('
    {
        // do calculation and update new top operator
        calculation();
        opStack.Top(opTop);
    }
    opStack.pop();                          // calculation between '(' and ')' end, so remove '(' from stack
}

void ArithmeticEvaluation::handleMathOperator(const char& op)
{
    char opTop = '\0';                      // '\0' means the char is empty
    opStack.Top(opTop);                  // try to get the top operator from stack

    while (opTop != '\0' && opTop != '(' && isLessOrEqualPrecedence(op, opTop))
    {
        calculation();

        // set opTop back to NULL before get the next opTop.
        // It prevents the infinity loop when the opStack is
        // empty already but, opTop still shows the last
        // operator (opTop not get updated because nothing
        // can be returned from opStack)
        opTop = '\0';
        opStack.Top(opTop);
    }
    opStack.push(op);               // add the new operator to stack
}

void ArithmeticEvaluation::calculateUntilEmpty()
{
    while (!opStack.isEmpty())
        calculation();
}

double ArithmeticEvaluation::getAnswer()
{
    double answer;
    numStack.Top(answer);
    numStack.pop();
    return answer;
}


/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 28, 2022                                               */
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

int ArithmeticEvaluation::getPrecedence(char op1) const
{
    int res = -1;

    // if the key exists in map, get the value (precedence rank) from the map
    if (precedenceMap.find(op1) != precedenceMap.end())
        res = precedenceMap.at(op1);

    return res;
}

bool ArithmeticEvaluation::isLessOrEqualPrecedence(char leftOp, char rightOp) const
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

bool ArithmeticEvaluation::isMathOp(char op) const
{
    bool judge = false;
    if (precedenceMap.find(op) != precedenceMap.end())
        judge = true;
    return judge;
}

void ArithmeticEvaluation::evaluation(const string& mathExpression, double& resultNum)
{
    // Initialize useful variables
    double num = 0;                            // temp variable for storing number
    char op = '\0';                            // temp variable for storing operator

    char preOp;                                // variable for recording op from last round

    bool opFlag = false;                       // flag shows the item read previously is an operator
    bool beginFlag = true;                     // flag shows it's the beginning of reading
    bool forbiddenOp = false;                  // check if detected operators not allowed

    stringstream ss;                           // "string stream" class turn string into input stream, like "cin"
    ss.str(mathExpression);                    // convert a math expression to input stream

    // Start to take input and evaluate a mathematical expression
    while (ss.peek() != EOF && !forbiddenOp)
    {
        if (ss.peek() == ' ')                  // 1. if meet white space
            ss.ignore();
        else if (isdigit(ss.peek()))           // 2. if meet a number (int or decimal)
        {
            ss >> num;
            handleNumber(num, opFlag, beginFlag);
        }
        else                                   // 3. if meet an operator
        {
            preOp = op;                        // record op which from last round
            ss >> op;                          // read current op
            handleOperator(op, preOp, opFlag, beginFlag, forbiddenOp);
        }
    }

    // Validate the reason of getting out of the loop
    if (forbiddenOp)                            // if process stop due to found forbidden operator
    {
        cout << "Please provide correct math expression!" << endl;        // callout error operator!
        popUntilEmpty();                                                  // empty two stacks for next evaluation
    }
    else                                        // if process stop due to successfully reading all the contents
    {
        calculateUntilEmpty();                  // deplete all operators to complete all undone calculations
        resultNum = getAnswer();                // return the calculation answer
    }
}

void ArithmeticEvaluation::handleNumber(double& num, bool& opFlag, bool& beginFlag)
{
    numStack.push(num);

    opFlag = false;                    // read a number, it's not operator, so opFlag turns to False
    beginFlag = false;                 // once read something, it's not beginning of expression anymore
}

void ArithmeticEvaluation::handleOperator(char& op, char& preOp, bool& opFlag, bool& beginFlag, bool& forbiddenOp)
{
    // 1. when seeing special '-' or '+' operator where they don't stand for Arithmetic operators
    if ((op == '-' || op == '+') && (beginFlag || (opFlag && preOp != ')')))
        handleSpecialMinusPlusSign(op);
    // 2. handle normal math operators allowed in this program
    else if (isMathOp(op))
        handleMathOperator(op);
    // 3. when see ".", handle it as a part of decimal number
    else if (op == '.')
        handleDecimalSymbol(op);
    // 4. handle close parenthesis
    else if (op == ')')
        handleCloseParen();
    // 5. handle open parenthesis
    else if (op == '(')
        handleOpenParen(op);
    // 6. seeing an unknown operator
    else
    {
        cout << "Invalid Operator detected: " << op << endl;
        forbiddenOp = true;
    }

    opFlag = true;                     // read an operator, so opFlag turns to True
    beginFlag = false;                 // once read something, it's not beginning of expression anymore
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

void ArithmeticEvaluation::handleOpenParen(const char& op)
{
    opStack.push(op);                       // push the new op into opStack
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

void ArithmeticEvaluation::popUntilEmpty()
{
    while (!opStack.isEmpty())
        opStack.pop();

    while (!numStack.isEmpty())
        numStack.pop();
}

double ArithmeticEvaluation::getAnswer()
{
    double answer;
    numStack.Top(answer);
    numStack.pop();
    return answer;
}


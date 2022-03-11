
# include <iostream>
#include <unordered_map>
# include "Stack.cpp"

using namespace std;

/**
 * @Brief function for evaluating an arithmetic expression
 * @Detail when the function start to run, it will ask the user to
 * provide an arithmetic expression. Then the function will print out the
 * arithmetic calculation of the expression user provided
 */
void arithmeticEvaluation();

/**
 * @Brief getPrecedence returns the precedence of an operator (eg. '+')
 * @Input 'op' is the operator the user wants to check precedence for.
 * 'precedenceMap' a hashmap of operators with their corresponding precedence.
 * The larger number of precedence means the operator has higher precedence
 * @Output the precedence rank of an operator
 */
int getPrecedence(char op, unordered_map<char, int>& precedenceMap);

/**
 * @Brief compare the precedence of two 'char' variables, to see if the var on the
 * LHS has less precedence than the one at RHS ---> LHS < RHS
 * @Input 1st char is the 'LHS', and the 2nd char is the 'RHS'. The unordered_map
 * is a hashmap which records the relationship between char and their corresponding
 * precedence rank, for example, '*' has precedence rank 3
 * @Output a boolean result. If RHS has less precedence than the RHS, the output is
 * TRUE. Otherwise, the output is FALSE
 */
bool isLessPrecedence(char leftOp, char rightOp, unordered_map<char, int>& precedenceMap);

/**
 * @Brief do calculation using the top operator in the stack, and the top two
 * values from the numStack.
 * @Detail the function will take operator "op" from the top of opStack. And
 * top two values "x" and "y" from numStack, where x is on top of y. The function
 * will do the calculation "y op x", and save the result back to numStack
 * @Input 1st char stack is opStack which saves the operators. 2nd double stack is
 * the numStack which saves the double numbers
 */
void calculation(Stack<char>& opStack, Stack<double>& numStack);

/**
* @Brief printStack pop all items from a Stack and print all of them
*/
template <class T>
void printStack(Stack<T>& stack);


int main() {

    arithmeticEvaluation();
    return 0;
}

void arithmeticEvaluation()
{
    Stack<double> numStack;                         // Stack to store numbers
    Stack<char> opStack;                            // Stack to store operators

    double num;                                     // temp variable for storing number
    char op;                                        // temp variable for storing operator

    bool opFlag = false;                            // flag shows the item read previously is an operator
    bool beginFlag = true;                          // flag shows it's the beginning of reading

    // a hashmap of operators. Key is the operator, and value is their corresponding precedence rank
    // higher number of precedence rank means the operator has higher precedence
    unordered_map<char, int> precedenceMap
            ({
                     {'+', 1},
                     {'-', 2},
                     {'*', 3},
                     {'/', 4},
             });

    cout << "Please Provide Arithmetic Evaluation: ";
    while (cin.peek() != '\n')
    {
        // 1. skip the whitespace if any
        if (cin.peek() == ' ')
        {
            cin.ignore();
        }
            // 2. if meet a number
        else if (isdigit(cin.peek()))
        {
            cin >> num;
            numStack.push(num);

            opFlag = false;                      // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                   // once read something, it's not beginning of expression anymore
        }
            // 3. when seeing '-' or '+' operator when they don't stand for Arithmetic operators
            // --> if '-' or '+' appears at the beginning of the arithmetic expression,
            //     they should stand for negativity or positivity of number. In this case,
            //     we turn the form like '+-3 + 4' into '(+1) * (-1) * 3 + 4'
            // --> if '-' or '+' discovered in the middle of expression, but right after another operator,
            //     which is not ')'. They also stand for negativity or positivity of number. In this case,
            //     we turn the form like '3+ -  2' into '3+ (-1) * 2'.
            // --> in this step we put '1' or '-1' into numStack, and '*' into opStack
        else if ((cin.peek() == '-' || cin.peek() == '+') && (beginFlag || (opFlag && op != ')')))
        {
            cin >> op;                          // read the operator '-' or '+'

            if (op == '-')                      // operator '-' means '-1 *'
                numStack.push(-1);         // add number '-1' to number stack
            else                                // operator '+' means '1 *'
                numStack.push(1);          // add number '1' to number stack

            opStack.push('*');             // add operator '*' to stack

            opFlag = true;                      // the last read is an operator '*', so opFlag turns to True
            beginFlag = false;                  // once read something, it's not beginning of expression anymore

        }
            // 4. if ever read '.', it must be a part of a decimal number like '.6' = '0.6'
            //    we change the form like '.6' to '0.1 * 6'
        else if (cin.peek() == '.')
        {
            cin >> op;                              // read the decimal so the input stream can move on

            numStack.push(0.1);                // push 0.1 to the number stack
            opStack.push('*');                 // push '*' to the operator stack

            opFlag = true;                          // the last read is an operator '*', so opFlag turns to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
            // 5. if meet operators under the other situation which are not stated above
            //    read them as normal arithmetic operators
        else
        {
            cin >> op;                              // read the new operator

            char opTop = '\0';                      // '\0' means the char is empty
            opStack.Top(opTop);                  // try to get the top operator from stack

            if (op == '(' || opTop == '\0')         // if op is '(' or if the opStack is empty
                opStack.push(op);                   // directly push the new op into opStack
            else                                    // if op is not '(' and there are item in the opStack
            {
                if (op == ')')                      // a. if we read a ')' operator
                {
                    while (opTop != '(')            // we keep pop operators and do calculation until meet '('
                    {
                        // do calculation and update new top operator
                        calculation(opStack, numStack);
                        opStack.Top(opTop);
                    }
                    opStack.pop();                  // calculation between '(' and ')' end, so remove '(' from stack
                }
                else                                // b. if we read anyone from '+-*/' operators
                {
                    // if new operator has less precedence than the top operator in opStack,
                    // we will use the top operator from stack to do calculation, and pop it.
                    // The process will finish when new operator no longer has less precedence
                    // than the top operator in the stack, or the top operator is '('. When
                    // all calculation is finished, push the new operator into the opStack
                    while (opTop != '\0' && opTop != '(' && isLessPrecedence(op, opTop, precedenceMap))
                    {
                        calculation(opStack, numStack);

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
            }

            opFlag = true;                          // read an operator, turns opFlag to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
    }

    // after reading all the user input, if there still are unused operators in the opStack,
    // use them all to do calculation, until the opStack is empty. By the time, there should
    // only remain 1 number in the numStack, which is the calculation result of the user input
    while (!opStack.isEmpty())
        calculation(opStack, numStack);

    double answer;
    numStack.Top(answer);
    numStack.pop();
    cout << "Answer: " + to_string(answer) << endl;


    // print the final stack
    cout << endl << endl;
    cout << "Number Stack" << endl;
    printStack(numStack);

    cout << "Operator Stack" << endl;
    printStack(opStack);
}


int getPrecedence(char op, unordered_map<char, int>& precedenceMap)
{
    int res = -1;

    // if the key exists in map, get the value (precedence rank) from the map
    if(precedenceMap.find(op) != precedenceMap.end())
        res = precedenceMap.at(op);

    return res;
}

bool isLessPrecedence(char leftOp, char rightOp, unordered_map<char, int>& precedenceMap)
{
    int leftPrecedence = getPrecedence(leftOp, precedenceMap);
    int rightPrecedence = getPrecedence(rightOp, precedenceMap);
    return leftPrecedence < rightPrecedence;
}

void calculation(Stack<char>& opStack, Stack<double>& numStack)
{
    char op;                   // create a char variable to store the operator
    opStack.Top(op);        // get the value of top operator from opStack
    opStack.pop();             // remove the top operator from stack

    double rhs, lhs;           // for example, in "x + y", y is rhs, and x is lhs
    numStack.Top(rhs);      // get the value of rhs from numStack
    numStack.pop();            // remove the rhs from stack
    numStack.Top(lhs);      // get the value of lhs from numStack
    numStack.pop();            // remove the lhs from stack

    double calcResult;         // variable to store calculation result of lhs and rhs

    switch (op)                // do calculation according to different operators
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
    }

    numStack.push(calcResult); // push the calculated result back to the numStack
}

template <class T>
void printStack(Stack<T>& stack)
{
    while (!stack.isEmpty())
    {
        T temp;
        stack.Top(temp);
        stack.pop();
        cout << temp << endl;
    }
    cout << endl;
}


# include <iostream>
# include <vector>
# include "Stack.cpp"

/**
* @Brief printStack pop all items from a Stack and print all of them
*/
template <class T>
void printStack(Stack<T>&);

/**
 * @Brief getPrecedence returns the precedence of an operator (eg. '+')
 * @Input 'op' is the operator the user wants to check precedence for.
 * 'opPrecedence' a vector of operators with user defined precedence.
 * operator which listed on the rearer part of the vector has higher precedence.
 * @Output the precedence of an operator
 */
int getPrecedence(char&, vector<char>&);


int main() {

    Stack<double> numStack;                         // Stack to store numbers
    Stack<char> opStack;                            // Stack to store operators

    double num;                                     // temp variable for storing number
    char op;                                        // temp variable for storing operator

    bool opFlag = false;                            // flag shows the item read previously is an operator
    bool beginFlag = true;                          // flag shows it's the beginning of reading

    // a vector of operators, ordered by their precedence. The operator with the highest precedence is at the rear.
    vector<char> precedence { '+', '-', '*', '/' };

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

            opFlag = false;                         // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
        // 3. when seeing '-' or '+' operator when they don't stand for Arithmetic operators
        // --> if '-' or '+' appears at the beginning of the arithmetic expression,
        //     they should stand for negativity or positivity of number. In this case,
        //     we turn the form like '+-3 + 4' into '(+1) * (-1) * 3 + 4'
        // --> if '-' or '+' discovered in the middle of expression, but right after another operator,
        //     which is not ')'. They also stand for negativity or positivity of number. In this case,
        //     we turn the form like '3+ -  2' into '3+ (-1) * 2'.
        else if ((cin.peek() == '-' || cin.peek() == '+') && (beginFlag || (opFlag && op != ')')))
        {
            cin >> op;                          // read the operator '-' or '+'

            if (op == '-')                      // operator '-' means '-1 *'
                numStack.push(-1);         // add number '-1' to number stack
            else                                // operator '+' means '1 *'
                numStack.push(1);         // add number '1' to number stack

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
            cin >> op;
            opStack.push(op);
            opFlag = true;                          // read an operator, turns opFlag to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
    }

    cout << "Number Stack" << endl;
    printStack(numStack);

    cout << "Operator Stack" << endl;
    printStack(opStack);

    return 0;
}

template <class T>
int getPrecedence(char& op, vector<char>& opPrecedence)
{
    int res = -1;
    for (int i=0; i<opPrecedence.size(); ++i)
    {
        if (op == opPrecedence[i])
        {
            res = i;
            break;
        }
    }
    return res;
}

template <class T>
bool isLessPrecedence(char& leftOp, char& rightOp, vector<char>& opPrecedence)
{
    int leftPrecedence = getPrecedence(leftOp, opPrecedence);
    int rightPrecedence = getPrecedence(rightOp, opPrecedence);
    return leftOp < rightOp;
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

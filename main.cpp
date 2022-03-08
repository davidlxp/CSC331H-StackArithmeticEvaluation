
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
            beginFlag = false;                      // once read a number, it's not beginning of expression anymore

        }
        // 3. if it's the beginning, and start with '-' or '+'
        else if (beginFlag && (cin.peek() == '-' || cin.peek() == '+'))
        {
            numStack.push(0);                  // push a 0 (eg. turn "-3+4" into form of "0-3+4")
            cin >> op;                              // read and push the operator '+' or '-'
            opStack.push(op);

            opFlag = true;                          // the last read is an operator so opFlag turns to True
            beginFlag = false;                      // once read something, it's not beginning of expression anymore
        }
        // 4. if peek an operator, and in front of it there's another operator which is not ')', and current operator
        //    is '-' or '+', then this operator will be read along with the number behind it like '+8' or '-8'
        else if (!beginFlag && opFlag && op!=')' && (cin.peek() == '-' || cin.peek() == '+'))
        {
            char tempOp;                            // save '-' or '+' to a temp operator
            cin >> tempOp;                          // read and get the tempOp

            while (cin.peek() == ' ')               // skip the whitespace (if any) between operator and the number
                cin.ignore();

            cin >> num;                             // read the pure number (without sign)

            if (tempOp == '-')                      // assign negativity to the number based on saved operator
                num = 0 - num;

            numStack.push(num);                     // push the number to stack

            opFlag = false;                         // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                      // once read a number, it's not beginning of expression anymore
        }
        // 5. if ever read '.', it must be a part of a decimal number like '.6' = '0.6'
        else if (cin.peek() == '.')
        {
            cin >> num;                             // read '.' together with the number behind it
            numStack.push(num);                     // push the number to stack

            opFlag = false;                         // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                      // once read a number, it's not beginning of expression anymore
        }
        // 6. if meet operators under the other situation which are not stated above
        else
        {
            cin >> op;

            opStack.push(op);

            opFlag = true;                          // read an operator, turns opFlag to True
            beginFlag = false;                      // once read an operator, it's not beginning of expression anymore
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

//template <class T>
//bool isLessPrecedence(char& leftOp, char& rightOp, vector<char>& opPrecedence)
//{
//    bool res = false;
//
//
//}

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

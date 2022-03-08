
# include <iostream>
# include "Stack.cpp"

// printStack pop all items from a Stack and print all of them
template <class T>
void printStack(Stack<T>& stack);


int main() {

    Stack<double> numStack;                         // Stack to store numbers
    Stack<char> opStack;                            // Stack to store operators

    double num;                                     // temp variable for storing number
    char op;                                        // temp variable for storing operator

    bool opFlag = false;                            // flag shows the item read previously is an operator
    bool beginFlag = true;                          // flag shows it's the beginning of reading


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

            cout << "done" << endl;
        }
        // 4. if peek an operator, and in front of it there's another operator which is not ')', and this operator
        //    is not '(', then this operator will be read along with the number behind it like '+8' or '-8'
        else if (!beginFlag && opFlag && op!=')' && cin.peek() != '(')
        {
            cin >> num;                             // read the operator with the number behind it
            numStack.push(num);                     // save the number

            opFlag = false;                         // read a number, it's not operator, so opFlag turns to False
            beginFlag = false;                      // once read a number, it's not beginning of expression anymore
        }
        // 5. if meet operators under the other situation which not stated above
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

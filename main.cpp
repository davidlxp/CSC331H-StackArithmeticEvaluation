/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                              */
/* Purpose: Section for testing the ArithmeticEvaluation program     */
/*********************************************************************/

# include <iostream>
# include <string>
# include "ArithmeticEvaluation.h"
using namespace std;

/**
 * @Brief read the math expression user provided
 * @Output output is the string of expression user provided
 */
string readMathExpression();

/**
 * @Brief evaluate a mathematical expression and print the
 * calculated answer for the provided math expression
 * @Input a string of mathematical expression
 */
void evaluateMathExpression(string mathExpression);

/**
 * @Brief print the menu of the program and ask the user
 * to make a selection based on the information in the menu
 * @Output an integer stands for the index of the choice user made
 */
int printMenu();

/**
 * @Brief run the console UI integrated program. Provide basic
 * instruction of using the program, and evaluate the mathematical
 * expression user provided
 */
void runProgram();


int main()
{
    // run the program with user interface
    runProgram();

    return 0;
}

string readMathExpression()
{
    cout << "Please Provide Arithmetic Expression for Evaluation: ";
    string inputExpression;
    getline(cin, inputExpression);
    return inputExpression;
}

void evaluateMathExpression(string mathExpression)
{
    ArithmeticEvaluation evaluator;          // instantiate ArithmeticEvaluation class
    double num = INT_MAX;                    // instantiate a default "num" variable

    // evaluate the expression user provided
    evaluator.evaluation(mathExpression, num);
    cout << "Answer: " << num << endl;
}

int printMenu()
{
    int choice;

    cout << "\nMain Menu:" << endl;
    cout << "1. Evaluate a Mathematical Expression" << endl;
    cout << "2. Exit The Program" << endl;
    cout << "Please make a selection by index: ";

    string choiceStr;
    getline(cin, choiceStr);
    choice = stoi(choiceStr);

    return choice;
}

void runProgram()
{

    cout << "\nWelcome to the Arithmetic Evaluator!";
    cout << "\nIf you provide me a mathematical expression, I could solve it for you." << endl;
    cout << "\nPlease follows the rules below when providing an mathematical expression:";
    cout << "\n=> Both integers and decimal numbers are allowed";
    cout << "\n=> Only +, -, *, / operators are allowed" << endl;

    int choice = printMenu();
    while (choice != 2)
    {
        if (choice == 1)
        {
            // ask user to provide a math expression
            string mathExpression;
            mathExpression = readMathExpression();

            // evaluate
            evaluateMathExpression(mathExpression);
        }
        else
        {
            cout<<"\nNumber is not correct. Please look at "
                <<"choices and reenter\n\n";
        }

        choice = printMenu();
    }
}
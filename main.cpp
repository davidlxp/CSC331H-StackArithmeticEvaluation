/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                              */
/* Purpose: Section for testing the ArithmeticEvaluation program     */
/*********************************************************************/

# include <iostream>
# include "ArithmeticEvaluation.h"
using namespace std;

/**
 * @Brief read the math expression user provided
 * @Output output is the string of expression user provided
 */
string readMathExpression();

int main()
{
    ArithmeticEvaluation evaluator;          // instantiate ArithmeticEvaluation class
    double num = INT_MAX;

    int choice = 1;
    while (choice != -1)
    {
        // ask user to provide a math expression
        string mathExpression;
        mathExpression = readMathExpression();

        // evaluate the expression user provided
        evaluator.evaluation(mathExpression, num);
        cout << "Answer: " << num << endl;

        // read user's choice as string and turn it into integer
        cout << "Please provide a new instruction" << endl;
        string choiceStr;
        getline(cin, choiceStr);
        choice = stoi(choiceStr);
    }

    return 0;
}

string readMathExpression()
{
    cout << "Please Provide Arithmetic Expression for Evaluation: ";
    string inputExpression;
    getline(cin, inputExpression);
    return inputExpression;
}
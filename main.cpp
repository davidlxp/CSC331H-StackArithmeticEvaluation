/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 17, 2022                                              */
/* Purpose: Section for testing the ArithmeticEvaluation program     */
/*********************************************************************/

# include <iostream>
# include "ArithmeticEvaluation.h"

using namespace std;

int main()
{
    ArithmeticEvaluation evaluator;          // instantiate ArithmeticEvaluation class
    double num = INT_MAX;
    evaluator.evaluation(num);            // start to evaluate an expression and save to variable num
    cout << "Answer: " << num << endl;       // print the calculated result

//    int choice = 1;
//    while (choice != -1)
//    {
//        evaluator.evaluation(num);
//        cout << "Answer: " << num << endl;
//        cout << "Please provide a new instruction" << endl;
//        cin >> choice;
//    }

    return 0;
}



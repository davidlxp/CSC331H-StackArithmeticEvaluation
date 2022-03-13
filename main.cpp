/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 13, 2022                                              */
/* Purpose: Section for testing the ArithmeticEvaluation program     */
/*********************************************************************/

# include <iostream>
# include "ArithmeticEvaluation.h"

using namespace std;

int main()
{
    ArithmeticEvaluation evaluator;          // instantiate ArithmeticEvaluation class
    double num = evaluator.evaluation();     // start to evaluate an expression and save to variable num

    cout << "Answer: " << num << endl;       // print the calculated result

    return 0;
}



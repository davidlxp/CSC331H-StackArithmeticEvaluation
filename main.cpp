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
    ArithmeticEvaluation evaluator;
    double num = evaluator.evaluation();

    cout << "Answer: " << num << endl;

    return 0;
}



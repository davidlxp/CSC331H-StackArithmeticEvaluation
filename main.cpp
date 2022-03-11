
# include <iostream>
# include "ArithmeticEvaluation.h"

using namespace std;

int main()
{
    ArithmeticEvaluation evaluator;
    double num = evaluator.arithmeticEvaluation();
    cout << "Answer: " + to_string(num) << endl;

    return 0;
}


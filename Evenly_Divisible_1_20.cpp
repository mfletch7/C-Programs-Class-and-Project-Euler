//Problem 5 from Project Euler, evenly divisible number by all of the numbers 1 to 20
//Created by Michael Fletcher, April 22, 2016
//2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder
//What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

#include <iostream>
using namespace std;

int main()
{
    int num = 0;
    bool test = false;
    int testCount = 0;
    int answerNum = 0;

    while(test == false)
    {
        testCount = 0;
        num += 1;
        for(int counter = 1; counter <= 20; counter += 1)
        {
            if(num % counter == 0)
                testCount += 1;
            //end if
        }// end for loop
        if(testCount >= 20)
        {
            answerNum = num;
            test = true;
        }// end if
    }// end while loop
    for(int i = 20.0; i >= 1.0; i -= 1.0)
    {
        cout << answerNum << "/" << i << " = " << answerNum/i << endl;
        cout << answerNum << " mod " << i << " is " << answerNum % i << endl;
    }
    cout << endl << "The number is: " << answerNum << endl;
    return 0;
}// end main function

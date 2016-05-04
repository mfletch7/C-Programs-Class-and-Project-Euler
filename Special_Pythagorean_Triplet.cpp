//Problem 9 from project Euler, A pythagorean triplet is where for 3 numbers a < b < c, a squared + b squared = c squared
//Created by Michael Fletcher, April 22, 2016
//Find the Pythagorean triplet where a+b+c = 1000.

#include <iostream>
#include <cmath>        //use of sqrt function and pow function
#include <iomanip>      //use of the setprecision function
using namespace std;

int main()
{
    int answer = 1000;
    int a, b = 0;
    double c;

    for (a = 1; a <= 1000; a++)
    {
        for (b = a; b <= 1000; b++)
        {
            c = sqrt((pow(a,2)) + (pow(b,2)));
            int temp = c * 100000;
            if (temp % 100000 == 0)                 //c is a whole number
            {
                if(a + b + c == answer)
                {
                    cout << "a is " << a << " b is " << b << " and c is " << c << endl;
                    cout << "The sum a + b + c is " << a+b+c << endl;
                    cout << fixed << setprecision(0) << "The product is: " << a*b*c << endl;
                    break;
                }//end answer if
            }// end mod if
        }// end b for loop
    }// end a for loop
    return 0;
}

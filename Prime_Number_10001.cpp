//Problem 7 from project Euler, What is the 10001st prime number
//Created by Michael Fletcher, April 26, 2016

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int num1 = 0;
    int num2 = 2;
    int primeNum = 0;
    bool prime = false;

    while(num1 <= 10000)
    {
        prime = true;
        int temp = sqrt(num2);
        for(int i = 2; i <= temp; i += 1)
        {
            if(num2 % i == 0)
            {
                prime = false;
                i = temp;
            }// end if
        }// end for loop
            if(prime == true)
            {
                num1 += 1;
                primeNum = num2;
                if(num1 % 1000 == 0)
                    cout << "The " << num1 << "th prime number is " << primeNum << endl;
            }// end if
        num2 += 1;
    }// end while loop
    cout << endl << "The " << num1 << "th prime number is " << primeNum << endl;
}

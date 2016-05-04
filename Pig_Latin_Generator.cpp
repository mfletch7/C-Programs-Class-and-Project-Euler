//Advanced 13-33, input a word and then output the pig-latin form of it
//Created by Michael Fletcher, April 20, 2016

#include <iostream> //cin, cout
#include <string>   //string class
using namespace std;

int main()
{
    //Variable declaration
    const string lc_vowelArray[5] = {"A", "E", "I", "O", "U"};
    const string uc_vowelArray[5] = {"a", "e", "i", "o", "u"};
    string userWord = "";
    int firstVowel = 100;

    cout << "Enter a word, please (-1 to quit): ";  //Obtain word, initial word
    cin >> userWord;

    while (userWord != "-1") {
    for (int counter = 0; counter < 5; counter += 1){
        if(userWord.find(lc_vowelArray[counter]) != -1 && userWord.find(lc_vowelArray[counter]) < firstVowel)
            firstVowel = userWord.find(lc_vowelArray[counter]);
        if(userWord.find(uc_vowelArray[counter]) != -1 && userWord.find(uc_vowelArray[counter]) < firstVowel)
            firstVowel = userWord.find(uc_vowelArray[counter]);
    }   //end for loop for finding first vowel
    //Output
    switch (firstVowel){
    case 0:
    case 100:
        cout << userWord.insert(userWord.length(), "-way") << endl;
    }   // end switch
    if (firstVowel > 0 && firstVowel < userWord.length())
        cout << userWord.substr(firstVowel) + "-" + userWord.substr(0,firstVowel) + "ay" << endl;
    // end if
    cout << "Enter a word, please (-1 to quit): ";  //Obtain word, initial word
    cin >> userWord;
    firstVowel = 100;
    }   //end while loop
}// end main function

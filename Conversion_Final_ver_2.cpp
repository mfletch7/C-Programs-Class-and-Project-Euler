 //This is my final project program for C++ class at SWATC
//This program reads in a number with units from a user and converts it to a different set of units desired by the user
//Created June 2, 2016

#include <iostream>         //Use of cin and cout
#include <iomanip>          //Use of setprecision
#include <fstream>
#include <stdlib.h>         //Use of atof
#include <algorithm>        //Use of transform
#include <string>           //Use of + for concatenation
#include <ostream>
#include <sstream>
using namespace std;

//The arrays are set as global variables because after information from text file is read into the arrays, they will be used for information only,
//the arrays will not be modified. This will be simpler and easier to understand than passing the arrays to various functions that will need them.
const int arraySize = 20;
string fileLines[arraySize] = {""};
string types[arraySize] = {""};
string units[arraySize][arraySize] = {""};
double factors[arraySize][arraySize] = {0};

//Function prototypes
void readInfo();
void printInfoToScreen();
void userInput(double &uFactor, string &);
string convertFrom(string selection, int &x, int &y);
string upper(string select);
string lower(string select);
int convertTo(int xCoord);
double newConvertTo(string &newU, int x, int &conv);
void modifyFile(int xCoord, int yCoord);
double temperatureConvert(double uNumber, string selection, string &newU);

int main()
{
    //Variable declarations
    ifstream inUnitFile;
    string userSelection = "";
    double userNumber = 0.0;
    int xCoordinate = 0;
    int yCoordinate = 0;
    string userType = "";
    double selectionFactor = 0.0;
    int unitConvertTo = 0;
    double newFactor = 0.0;
    double newNumber = 0.0;
    string newUnit = "";
    bool writeToFile = false;

    inUnitFile.open("UnitsFactors.txt");
    if(inUnitFile.is_open() == false)
    {
        cout << "file not found";
        return 0;
    }//end if
    inUnitFile.close();

    readInfo();
    //printInfoToScreen();
    do
    {
    userInput(userNumber, userSelection);                                      //userSelection is the units input by the user and userNumber is the number
    if(upper(userSelection) == "QUIT")
    {
        return 0;
    }
    userType = convertFrom(userSelection, xCoordinate, yCoordinate);            //The xCoordinate and yCoordinate are passed by reference to grab the array location of the unit and factor
    if(userType == "Other")
    {
        return 0;
    }

    //Temperature is a different method of conversion so it is treated as a unique case
    if(userType == "Temperature")
    {
        newNumber = temperatureConvert(userNumber, userSelection, newUnit);
        cout << "The answer is: " << newNumber << " " << newUnit << endl;
        userNumber = 0.0;
        userSelection = "";
    }
    else
    {
        selectionFactor = factors[xCoordinate][yCoordinate];
        unitConvertTo = convertTo(xCoordinate);                                                                 //unitConvertTo contains the y coordinate of the factor to change to
        if(unitConvertTo != 100){
            newFactor = factors[xCoordinate][unitConvertTo];
        }
        else{
            newFactor = newConvertTo(newUnit, xCoordinate, unitConvertTo);
        }
        cout << "The answer is " << newFactor/selectionFactor*userNumber << " " << units[xCoordinate][unitConvertTo] << endl;
    }
    }while(userSelection != "Quit");

    system("Pause");
    return 0;
}

void readInfo()
{
    ifstream inUnitFile;
    int outLoopCount = 0;
    string unitString = "";
    int firstSpace = 0;
    int secondSpace = 0;
    int thirdSpace = 0;
    string temp1 = "";
    string tempFactor = "";

    inUnitFile.open("UnitsFactors.txt");
    getline(inUnitFile, unitString, '\n');
    //unitString.erase(0,3);
    while(inUnitFile.eof() == false)
    {
        fileLines[outLoopCount] = unitString;
        getline(inUnitFile, unitString, '\n');
        outLoopCount++;
    }
    fileLines[outLoopCount] = unitString;
    inUnitFile.close();

    for(int i=0; i<=outLoopCount; i++)
    {
        temp1 = fileLines[i];
        firstSpace = 0;
        secondSpace = temp1.find(" ", firstSpace);
        types[i] = temp1.substr(firstSpace, secondSpace);
        firstSpace = secondSpace;
        for(int j=0; j<20; j++)
        {
            secondSpace = temp1.find(" ", firstSpace+1);
            thirdSpace = temp1.find(" ", secondSpace+1);
            if(secondSpace < firstSpace)
            {
                j = 20;
                continue;
            }
            units[i][j] = temp1.substr(firstSpace+1, ((secondSpace-1) - firstSpace));

            tempFactor = temp1.substr(secondSpace+1, (thirdSpace - secondSpace));
            factors[i][j] = atof(tempFactor.c_str());

            firstSpace = thirdSpace;
        }
    }
    inUnitFile.close();
}

//This function was used for development and is left here for additional development if needed. It is turned off simply by commenting out the call to it in main function
void printInfoToScreen()
{
    for(int i=0; i < arraySize; i++)
    {
        if(types[i] != "")
        {
            cout << types[i] << " ";
            for (int j=0; j < arraySize; j++)
            {
                if(units[i][j] != "")
                    cout << units[i][j] << " " << factors[i][j] << " ";
            }
            cout << endl;
        }
    }
}

void userInput(double &uFactor, string &unitInput)
{
    double tempFactor = 0.0;
    string tempString = "Not_Correct";
    do
    {
        cout << "What would you like to have converted (number and units (0 Quit to quit) )" << endl;
        cout << "(types: " << types[0];
        for(int i=1; i<arraySize; i++)
        {
            if(types[i] != "")
                cout << ", " << types[i];
        }
        cout << ")" << endl;
        cout << "(F, R, K, C for temperature)" << endl;
        cin >> tempFactor;
        cin >> tempString;
        cin.clear();
        cin.ignore(100, '\n');
        /*cout << "tempFactor is " << tempFactor << endl;
        cout << "tempString is " << tempString << endl;*/
        if(tempString == "Not_Correct")
        {
            cin.clear();
            cout << "Please include a space between the number and units" << endl;
            cout << "Please use 0 Quit to quit" << endl;
            tempFactor = 0.0;
        }
    }while(tempString == "Not_Correct");
    uFactor = tempFactor;
    unitInput = tempString;
}

//This uses information from the user to find the units and factor position in the arrays. It returns the units in the array found equivalent to input from the user
string convertFrom(string selection, int &x, int &y)
{
    int typeChoice = 0;
    int unitChoice = 0;
    int counter = 0;
    string tempUnit = "";
    char modifyAns = ' ';

    if(selection.length() <= 1)
        selection = upper(selection);
    if(selection == "F" || selection == "R" || selection == "K" || selection == "C")
    {
        return "Temperature";
    }

    for(int i=0; i<arraySize; i++)
    {
        for(int j=0; j<arraySize; j++)
        {
            if(units[i][j] != "")
            {
                tempUnit = units[i][j];
                if(tempUnit == selection || tempUnit == upper(selection) || tempUnit == lower(selection))
                {
                    x = i;
                    y = j;
                    tempUnit = types[i];
                    return tempUnit;
                }
            }
        }
    }
    cout << "What type of unit are you looking to convert?" << endl;
    for(int i=0; i<arraySize; i++)
    {
        if(types[i] != "")
        {
            cout << i << ": " << types[i] << endl;
            counter++;
        }
    }
    cout << counter << ": Other" << endl;
    do{
        cin >> typeChoice;
        if(typeChoice < 0 || typeChoice > counter + 1)
            cout << "Please enter a selection between 0 and " << counter << endl;
        }while(typeChoice < 0 || typeChoice > counter);

    if(typeChoice == counter)
    {
        cout << "Coming Soon" << endl;
        cout << "Thank you for your participation, check back later" << endl;
        return "Other";
    }
    else
    {
        x = typeChoice;
        counter = 0;

        cout << "Is the units the equivalent of one of the following:" << endl;
        for(int j=0; j<arraySize; j++)
        {
            if(units[x][j] != "")
            {
                cout << j << ": " << units[x][j] << endl;
                counter++;
            }
        }
        cout << counter << ": Other" << endl;
        do{
        cin >> unitChoice;
        if(unitChoice < 0 || unitChoice > counter)
            cout << "Please enter a selection between 0 and " << counter << endl;
        }while(unitChoice < 0 || unitChoice > counter);

        y = unitChoice;

        if(unitChoice < counter)
        {
            return units[x][y];
        }
        else
        {
            cout << "What is the factor from " << units[x][0] << " to " << selection << endl;
            cin >> factors[x][counter];
            units[x][counter] = selection;
            cout << "Do you want to add this to the file for future use (Y/N) ";
            cin >> modifyAns;
            if(modifyAns == 'Y' || modifyAns == 'y')
                modifyFile(x, counter);
            return selection;
        }
    }
}

double temperatureConvert(double uNumber, string selection, string &newU)
{
    string convertTemp[4] ={"C", "K", "F", "R"};
    int tempChoice = 0;
    char selectChoice = ' ';
    char stringChoice = ' ';

    selection = upper(selection);
    cout << "Which temperature would you like to convert to?" << endl;
    for(int i=0; i<4; i++)
    {
        if(selection != convertTemp[i])
        {
            cout << i << ": " << convertTemp[i] << endl;
        }
    }
    do{
        cin >> tempChoice;
        if(tempChoice < 0 || tempChoice >= 4)
            cout << "Please enter a number between 0 and 3" << endl;
    }while(tempChoice < 0 || tempChoice >= 4);

    selectChoice = selection.at(0);
    stringChoice = convertTemp[tempChoice].at(0);
    newU = convertTemp[tempChoice];

    switch (selectChoice)
    {
    case 'C':
        switch (stringChoice)
        {
        case 'K':
            return uNumber + 273;
        case 'F':
            return (uNumber*1.8) + 32;
        case 'R':
            return (uNumber+273) * 1.8;
        }
    case 'K':
        switch (stringChoice)
        {
        case 'C':
            return uNumber - 273;
        case 'F':
            return (uNumber * 1.8) - 459.67;
        case 'R':
            return uNumber * 1.8;
        }
    case 'F':
        switch (stringChoice)
        {
        case 'C':
            return (uNumber - 32) * 5/9;
        case 'K':
            return (uNumber + 459.67) * 5/9;
        case 'R':
            return uNumber + 459.67;
        }
    case 'R':
        switch (stringChoice)
        {
        case 'C':
            return (uNumber - 491.67) * 5/9;
        case 'K':
            return uNumber * 5/9;
        case 'F':
            return uNumber - 459.67;
        }
    }
}

int convertTo(int xCoord)
{
    string tempUnit = "";
    int userChoice = 0;
    int tempSelect = 0;

    cout << "What unit do you want to convert to?" << endl;

    for(int j=0; j<arraySize; j++)
    {
    if(units[xCoord][j] != "")
        {
            cout << j << ": " << units[xCoord][j] << endl;
            tempSelect++;
        }
    }
    cout << tempSelect << ": Other" << endl;
    do
    {
        cin >> userChoice;
        if(userChoice < 0 || userChoice > tempSelect+1)
            cout << "Please enter a number between 0 and " << tempSelect << endl;
    }while(userChoice < 0 || userChoice > tempSelect+1);
    if(userChoice < tempSelect)
        return userChoice;
    else
        return 100;
}

double newConvertTo(string &newU, int x, int &conv)
{
    string tempInput = "";
    int inputSelect = 0;
    int counterSelect = 0;
    double userFactor = 0.0;
    char modifyAns = ' ';

    cout << "What unit would you like to convert to?" << endl;
    cin >> tempInput;

    cout << "Is the unit " << tempInput << " equivalent to one of the following?" << endl;
    for(int j=0; j<arraySize; j++)
    {
        if(units[x][j] != "")
        {
            cout << j << ": " << units[x][j] << endl;
            counterSelect++;
        }
    }
        cout << counterSelect << ": Other" << endl;
    do{
        cin >> inputSelect;
        if(inputSelect < 0 || inputSelect > counterSelect)
            cout << "Please select a number between 0 and " << counterSelect << endl;
    }while(inputSelect < 0 || inputSelect > counterSelect);

    if(inputSelect < counterSelect)
    {
        return factors[x][inputSelect];
    }
    else
    {
        cout << "What is the conversion factor from " << units[x][0] << " to " << tempInput << "?" << endl;
        cin >> userFactor;
        factors[x][counterSelect] = userFactor;
        units[x][counterSelect] = tempInput;
        conv = counterSelect;
        cout << "Do you want to add this to the file for future use (Y/N) ";
        cin >> modifyAns;
        if(modifyAns == 'Y' || modifyAns == 'y')
            modifyFile(x, counterSelect);
        return userFactor;
    }
}

string upper(string select)
{
    string upperSelect = "";
    string temp = "";

    for(int i=0; i<select.length(); i++)
    {
        temp = toupper(select.at(i));
        upperSelect = upperSelect + temp;
    }
    return upperSelect;
}

string lower(string select)
{
    string lowerSelect = "";
    string temp = "";

    for(int i=0; i<select.length(); i++)
    {
        temp = tolower(select.at(i));
        lowerSelect = lowerSelect + temp;
    }
    return lowerSelect;
}

void modifyFile(int xCoord, int yCoord)
{
    ofstream outUnitFile;
    ostringstream streamFactor;
    double temp = 0.0;
    int loc = 0;
    int pos = 0;
    int pass = 0;
    string tempWord = "";

    cout << "Please enter the password to modify the file: ";
    cin >> pass;

    if(pass == 7777)
    {
        temp = factors[xCoord][yCoord];
        streamFactor << temp;
        tempWord = streamFactor.str();
        fileLines[xCoord] = fileLines[xCoord] + units[xCoord][yCoord] + " " + tempWord + " ";

        outUnitFile.open("UnitsFactors.txt", ios::out);
        loc = outUnitFile.tellp();
        cout << "the position is " << loc << endl;
        for(int i=0; i<arraySize; i++)
        {
            if(fileLines[i] != "")
            {
                outUnitFile << fileLines[i];
                if(fileLines[i+1] != "")
                    outUnitFile << endl;
            }
        }
        outUnitFile.close();
    }
}

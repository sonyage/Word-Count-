//
// quadratic_SGE.cpp
//
// Sonya Gomez Enriquez
// 08/28/2019
// Assignment 1
// This assignment solves for the roots of a quadratic function
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

bool ReadOneSet(double &a, double &b, double &c, istream& file, bool &aLine,
                bool &dataEndsNoError);
int CalcRoots(double a, double b, double c, double &root1, double &root2);
void PrintFunct(double a, double b, double c, double root1, double root2,
                 int ansType, ostream &out, bool noError);
int main()
{
    double a = 0, b = 0, c = 0; // coefficients
    int ansType = 1;            // decides what print message based on root ans
    double root1 = 0, root2 = 0;// holds roots, if any
    string in = "", out = "";   // holds file names
    bool dataRead = true;       // holds if error is encountered
    bool dataEndsNoError = false; // holds whether data ended w/o error
    bool aLine = true; // holds whether a == 0 or not for when printing

    cout << "What is the name of your input file? " << flush;
    cin  >> in;
    cout << "What is the name of your output file? " << flush;
    cin  >> out;

    ifstream inFile(in);
    ofstream outFile(out);

    if(!inFile)
    {
        cout << "Error opening " << in << "!" << endl;
    }
    else if(!outFile)
    {
        cout << "Error opening " << out << "!" << endl;
    }
    else // if no errors, runs rest of program
    {
        outFile << "Input file: " << in << endl
                << "Output file: " << out << endl;

        //dataRead = ReadOneSet(a, b, c, inFile);
        while(dataRead) //check that no errors yet encountered
        {
            dataRead = ReadOneSet(a, b, c, inFile, aLine, dataEndsNoError);

            if(dataRead && aLine)
            {
                ansType = CalcRoots(a, b, c, root1, root2);
            }
            else
            {
                ansType = -1; // "this isnt a quadratic" message
            }

            if(!dataEndsNoError) // if data has no errors, nothing to print
            {
                PrintFunct(a, b, c, root1, root2, ansType, outFile, dataRead);
            }
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}

bool ReadOneSet(double &a, double &b, double &c, istream &file, bool &aLine,
                 bool &dataEndsNoError)
{ // returns false = failed read , returns true if data read correctly
    bool read = true;
    aLine = true; // resets line value before read

    if(!file.eof())
    {
        file >> a;
        if(a == 0)
        {
            aLine = false;
        }
    }
    else
    {
        dataEndsNoError = true; // marks if data ends without an error
    }                           // will use this when deciding if error print
                                // needed
    if(!file.eof())
    {
        file >> b;
    }
    else
    {
        read = false;
    }

    if(!file.eof())
    {
        file >> c;
    }
    else
    {
        read = false;
    }

    file.ignore(); // ignore '/n' new line for next read
    return read;
}

int CalcRoots(double a, double b, double c, double &root1, double &root2)
{
    int ansType = 0;

    if(a == 0)
    {
        ansType = -1;
    }
    else if(((b*b) - (4*a*c)) < 0)
    {
        ansType = -2;
    }
    else
    {
        root1 = (-b + sqrt((b*b - 4*a*c)))/ (2*a);
        root2 = (-b -  sqrt((b*b - 4*a*c)))/ (2*a);
        ansType = 0;
    }
    return ansType;
}

void PrintFunct(double a, double b, double c, double root1, double root2,
                 int ansType, ostream &out, bool noError)
{
    static bool title = false;
    static int numSet = 0; // to number table

    if(!title) // checks if title already printed
    {
        out << "Table of Quadratic Coefficients and Roots:" << endl;
        out << left << setw(12) << "   A" << setw(9) << "B" << setw(9)
                << " C" << setw(12) << "Root 1" << setw(12) << "Root 2" << endl;
        title = true;
    }

    if(!noError) // was there an error reading the data?
    {
        out << left << ++numSet << ") " << setw(9)
            << "Error on data input." << endl;
    }
    else
    {
        out << left << ++numSet << ") " << setw(9)
            << a << setw(9) << b << setw(9)<< c;

        if(ansType == 0)
        {
            out << setw(12) << root1 << setw(9) << root2 << endl;
        }

        else if(ansType == -1) // missing "a" value print message
        {
            out << "This is not a quadratic." << endl;
        }
        if(ansType == -2) // imaginary/complex solution print message
        {
            out << "There is a complex solution." << endl;
        }
    }

    return;
}

/*
 *  ev176P2.cpp
 *
 *  COSC 051 Fall 2015
 *  Project #2
 *  Author: Erik Van de Water
 *
 *  Due on: OCT 26, 2015
 *
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance
 * on this project with the exceptions of the lecture notes and those
 * items noted below.
 *
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 *
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

int main(int argc, const char * argv[] )
{
    // -- global constants --

    const string MESSAGE_ERROR_FATAL = "Program will exit now";
    const string MESSAGE_ERROR_FILE_OPEN = "The input file failed to open.";
    const string MESSAGE_WELCOME = "Welcome to the Widget Processing System. ";
    const string MESSAGE_GOODBYE = "Thank you for using the Widget Processing System. ";
    const string PROMPT_INPUT_FILE = "Please enter complete path and name of input data file: ";

    const int SPACER = 10;

    // -- local variables --

    // strings

    string oneRow =          "";
    string fileNameAndPath = "";
    string headers =         "";

    string state =           "";
    string region =          "";
    string orderDate =       "";
    string color =           "";
    string customerNumber =  "";
    string firstName =       "";
    string lastName =        "";
    string address =         "";
    string line = "----------------------------------------------------------------------------------------";
    string newLineAfterDate = "";

    // numbers

    // ints

    int currentRow =      0;
    int numErrors =       0;
    int coneNumber =      0;
    int cylinderNumber =  0;
    int sphereNumber =    0;

    int fileYear =        0;
    int fileMonth =       0;
    int fileDay =         0;

    int orderYear =       0;
    int orderMonth =      0;
    int orderDay =        0;


    // doubles

    double radius =          0.0;
    double height =          0.0;
    double slantHeight =     0.0;
    double surfaceArea =     0.0;
    double volume =          0.0;
    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;
    double price =           0.0;
    double profit =          0.0;

    double coneCost =        0.0;
    double conePrice =       0.0;
    double coneProfit =      0.0;

    double cylinderCost =    0.0;
    double cylinderPrice =   0.0;
    double cylinderProfit =  0.0;


    double sphereCost =      0.0;
    double spherePrice =     0.0;
    double sphereProfit =    0.0;

    double totalNumber =     0.0;
    double totalCost =       0.0;
    double totalPrice =      0.0;
    double totalProfit =     0.0;
    double averageNumber =   0.0;
    double averageCost =     0.0;
    double averagePrice =    0.0;
    double averageProfit =   0.0;

    // others

    char dateDelimiter =    '/';
    char shapeCode =       'a';
    char materialCode =    'a';
    ifstream  inFileStream; //no initial value

    // -- user input --

    cout << MESSAGE_WELCOME << endl;
    cout << PROMPT_INPUT_FILE << endl;

    getline(cin, fileNameAndPath);

    inFileStream.open(fileNameAndPath.c_str());

    if (!inFileStream) {
        cout << MESSAGE_ERROR_FILE_OPEN << endl;
        cout << "check to ensure the file:" << fileNameAndPath << " is valid.\n";
        cout << MESSAGE_ERROR_FATAL << endl;
        return -1;
    }
    else {
        cout << fileNameAndPath << "\nsuccessfully opened for reading.\n";

        // -- file date checking for line 1--

        inFileStream >> fileYear >> dateDelimiter >> fileMonth >> dateDelimiter >> fileDay;
        cout << fileDay << endl;
        if (fileYear < 1000 || fileYear > 9999 || fileMonth > 12
           || fileMonth < 1 || fileDay > 31 || fileDay < 1) {
            cout << "ERROR BELOW: Typo in file date";
        }
        getline(inFileStream, newLineAfterDate); // handle newline character

        // -- handling headers --

        getline(inFileStream, headers); // used to store the value of the unused headers of the file

        // -- outputting headers --

        cout << "Region" << setw(6) << "Date" << setw(11) << "Codes" << setw(15) << "Dimensions"
        << setw(8) << "Color" << setw(12) << "S. Area" << setw(8) << "Cost" << setw(12)
        << "Price" <<  setw(10) << "Profit" << endl;
        cout << line << endl;

        // -- input values --

        currentRow = 1;

        while (inFileStream >> state >> region >> orderYear >> dateDelimiter >>
               orderMonth >> dateDelimiter >> orderDay >> shapeCode
               >> materialCode >> radius >> height >> color >> customerNumber >>
               firstName >> lastName && getline(inFileStream, address)) {

            // -- validations --

            // orderDate

            if (orderYear < 1000 || orderYear > 9999 || orderMonth > 12
               || orderMonth < 1 || orderDay > 31 || orderDay < 1) {
                cout << "ERROR BELOW: Typo in order date" << endl;
                numErrors++;
            }
            if (orderYear > fileYear) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth > fileMonth) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth == fileMonth && orderDay > fileDay) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }

            // shapeCode

            if ((shapeCode != 'o') && (shapeCode != 'y') && (shapeCode != 'p')
                && (shapeCode != 'O') && (shapeCode != 'Y') && (shapeCode != 'P')) {
                cout << "ERROR BELOW: Not a legitimate shape." << endl;
                numErrors++;
            }

            // materialCode

            if ((materialCode != 'k') && (materialCode != 'a') && (materialCode != 'u')
              && (materialCode != 'K') && (materialCode != 'A') && (materialCode != 'U')) {
                cout << "ERROR BELOW: Not a legitimate material." << endl;
                numErrors++;
            }

            // radius

            if ((radius < 3) || (radius > 36)) {
                cout << "ERROR BELOW: The radius entered is outside of limits" << endl;
                numErrors++;
            }

            // height

            if ((shapeCode == 'o') || (shapeCode == 'y') || shapeCode == 'O' || shapeCode == 'Y'){
                if ((height < radius)  || (height > radius * 1.5)){
                  cout << "ERROR BELOW: The height entered is outside of limits" << endl;
                  numErrors++;
                }
            }

            // color

            if (!(color == "Red" || color == "Orange" || color == "Yellow" ||
                        color == "Green" || color == "Blue" ||
                        color == "Indigo" || color == "Violet")) {
                cout << "ERROR BELOW: invalid color." << endl;
                numErrors++;
            }

            // -- output non-calculated values --

            cout << setprecision(2) << fixed << setw(6) << region << setw(5)
            << orderYear << dateDelimiter << setw(2)
            << orderMonth << dateDelimiter << setw(2) << orderDay <<
            setw(3) << shapeCode << setw(3) << materialCode << setw(7) << radius;
            if (height == -1) {
                cout << setw(7) << "n/a" << setw(SPACER) << color;
            }
            else {
                cout << setprecision(2) << fixed << setw(7) << height << setw(SPACER) << color;
            }

            // -- decision to calculate --

            if (numErrors < 1) { // calculate and display calculated outputs
                if (shapeCode == 'o' || shapeCode == 'O') {
                    slantHeight = sqrt(pow(radius,2)+pow(height,2));
                    surfaceArea = 3.14*pow(radius,2) + 3.14*radius*slantHeight;
                    volume  = (3.14*pow(radius,2) * height)/3;
                }
                else if (shapeCode == 'y' || shapeCode == 'Y'){
                    surfaceArea = 2*3.14*radius*(height + radius);
                    volume = 3.14*pow(radius,2)*height;
                }
                else {
                    surfaceArea = 4*3.14*pow(radius,2);
                    volume = (4*3.14*pow(radius,3))/3;
                }

                //cost calculations

                if (materialCode == 'k' || materialCode == 'K') {
                    materialCost = 1.26 * surfaceArea;
                    laborCost = 256.27 + (0.4 * materialCost);
                }
                else if (materialCode == 'a' || materialCode == 'A') {
                    materialCost = 0.49 * surfaceArea;
                    laborCost = 32.10 + (0.1 * materialCost);
                }
                else {
                    materialCost = 6.32 * surfaceArea;
                    laborCost = 785.16 + (0.8 * materialCost);
                }

                // -- individual costs --

                // row output calculation variables

                cost = materialCost + laborCost;
                price = cost * 1.25;
                profit = price - cost;

                // cylinder

                if (shapeCode == 'y' || shapeCode == 'Y') {
                    cylinderNumber++;
                    cylinderCost = cylinderCost + cost;
                    cylinderPrice = cylinderPrice + price;
                    cylinderProfit = cylinderProfit + profit;
                }

                // cone

                else if (shapeCode == 'o' || shapeCode == 'O') {
                    coneNumber++;
                    coneCost = coneCost + cost;
                    conePrice = conePrice + price;
                    coneProfit = coneProfit + profit;
                }

                // sphere

                else if (shapeCode == 'p' || shapeCode == 'P') {
                    sphereNumber++;
                    sphereCost = sphereCost + cost;
                    spherePrice = spherePrice + price;
                    sphereProfit = sphereProfit + profit;
                }

                // -- totals incrementing --

                totalNumber++;
                totalCost = totalCost + cost;
                totalPrice = totalPrice + price;
                totalProfit = totalProfit + profit;

                // -- calculated row outputs --

                cout << setprecision(2) << fixed << setw(11) << surfaceArea << setw(11)
                << cost << setw(11) << price << setw(11) << profit << endl;

            }
            else {
                cout << endl;
            }
            currentRow++;
            numErrors = 0;
       }
    } // end while

    // -- calculate averages --

    averageNumber = totalNumber / 3;
    averageCost = totalCost / 3;
    averagePrice = totalPrice / 3;
    averageProfit = totalProfit / 3;

    // -- summary outputs --

    cout << setw(50) << "Total" << endl;
    cout << setw(8) << "Shape" << setw(10) << "Number" << setw(15) << "Cost" <<
    setw(20) << "Price" << setw(20) << "Profit" << endl;

    cout << line << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cone" << setw(7) << coneNumber <<
    setw(20) << coneCost << setw(20) << conePrice << setw(20) << coneProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cylinder" << setw(7) <<
    cylinderNumber << setw(20) << cylinderCost << setw(20) << cylinderPrice <<
    setw(20) << cylinderProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Sphere" << setw(7) <<
    sphereNumber << setw(20) << sphereCost << setw(20) << spherePrice << setw(20) <<
    sphereProfit << endl;
    cout << line << endl;
    cout << setw(8) << "Average" << setw(7) << setprecision(0) << averageNumber <<
    setw(20) << setprecision(2) << averageCost << setw(20) << setprecision(2) <<
    averagePrice << setw(20) << setprecision(2) << averageProfit << endl;

    // -- last steps --

    cout << "Finished reading " << currentRow - 1 << " lines from the file." << endl;
    cout << MESSAGE_GOODBYE << endl;
    inFileStream.close();
    return 0;
}

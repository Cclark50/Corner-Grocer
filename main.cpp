#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include "GrocerySales.h"
using namespace std;

/*@author Christian Clark
 *@date 8/3/24
 *
 *This program create a saleslist that records the frequency of all items in an input file
 *creates a frequency.dat file to save the frequency of all items in a smaller list
 *can print the count of a single item, all itmes, or a histogram of all items
 */

//prints the menu that the user will see to make a choice
void printChoices()
{
    cout << endl << "---------------------------------------------" << endl;
    cout << "1 - Get Frequency of One Item" << endl;
    cout << "2 - Get Frequency of All Items" << endl;
    cout << "3 - Print Histogram of All Items" << endl;
    cout << "q - Quit Program" << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;
}

//prints the frequency of a single item
void printFreqOne(const unique_ptr<GrocerySales>& t_salesList)
{
    string input;
    cout << "Enter Item to Check Frequency of: " << endl;
    getline(cin, input);
    try
    {
        cout << t_salesList->getItemString(input) << endl;
    }//if item does not exist, getItemString will throw an exception
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
}

// prints the fequency of all items in the saleslist
void printFreqAll(const unique_ptr<GrocerySales>& t_salesList)
{
    cout << "Frequency List of All Items" << endl;
    cout << "---------------------------" << endl;
    t_salesList->printFrequencyAllItems();
    cout <<  "---------------------------" << endl;
}

//prints a histogram of all items in the saleslist
void printHistogramAll(const unique_ptr<GrocerySales>& t_salesList)
{
    cout << "Histogram of All Items" << endl;
    cout << "----------------------" << endl;
    t_salesList->printHistogram();
    cout <<  "----------------------" << endl;
}

//handles user input
void menu(const unique_ptr<GrocerySales>& t_salesList)
{
    string userInput;
    do
    {
        printChoices();
        getline(cin, userInput);
        switch (userInput[0])
        {
        case '1':
            printFreqOne(t_salesList);
            break;
        case '2':
            printFreqAll(t_salesList);
            break;
        case '3':
            printHistogramAll(t_salesList);
            break;
        case 'q':
            cout << "Quitting program" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }while (userInput[0] != 'q' || userInput[0] == 'Q');
}

int main()
{
    //the sales list object
    auto salesList = std::make_unique<GrocerySales>();
    //either reads the frequency.dat file first
    if(std::filesystem::exists("frequency.dat"))
    {
        salesList->readDatFile("frequency.dat");
    } //or reads the input file
    else if(!salesList->populateList("CS210_Project_Three_Input_File.txt"))
    {
        //if populate list fails then close program due to no valid input
        cout << "Invalid File. Closing Program." << endl;
        system("pause");
        return 1;
    }
    //writes the dat file to save the list
    salesList->writeDatFile("frequency.dat");

    cout << "Corner Grocer Records List" << endl;
    cout << "==========================";
    //beginning of user input portion of the program
    menu(salesList);
    return 0;
}

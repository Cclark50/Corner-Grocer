//
// Created by metat on 8/2/2024.
//

#include "GrocerySales.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

/*@author Christian Clark
 *@date 8/3/24
 *
 *this class basically acts as an abstracted map
 *with the ability to read and write a certain kind of file
 *and output a formatted single item
 *a frequency list, or a histogram of all items
 */

//adds an item to the map
void GrocerySales::add(const std::string& t_input)
{
    if(contains(t_input))
    {
        m_sales[t_input]++;
        return;
    }
    m_sales[t_input] = 1;
}

void GrocerySales::add(const std::string& t_name, int t_count)
{
    if(contains(t_name))
    {
        m_sales[t_name] += t_count;
        return;
    }
    m_sales[t_name] = t_count;
}

//gets the count of an item in the map
int GrocerySales::operator[](const std::string& t_str)
{
    if(m_sales.count(t_str) <= 0)
    {
        throw std::invalid_argument("Item does not exist");
    }
    return m_sales[t_str];
}

//default constructor that does not do anything because it does not need to
GrocerySales::GrocerySales()
{
}

//gets the count of an item in the map, is used because i cannot figure out how to make [] overloading work
//with make_unique
int GrocerySales::at(const std::string& t_str)
{
    //throws an exception if the passed in item does not exist
    if(m_sales.count(t_str) <= 0)
    {
        throw std::invalid_argument("Item does not exist");
    }
    return m_sales[t_str];
}

//give a bool value if the passed item exists
bool GrocerySales::contains(const std::string& t_str)
{
    return m_sales.count(t_str) > 0;
}

//reads an input file and collects the count of all items in that list
bool GrocerySales::populateList(const string& t_file)
{
    string temp;
    ifstream file(t_file);
    if(!file.is_open())
    {
        file.close();
        cout << "could not open file" << endl;
        return false;
    }
    while(!file.fail())
    {
        if(file.eof())
        {
            break;
        }
        file >> temp;
        add(temp);
    }
    file.close();
    return true;
}

//prints the histogram of all items
void GrocerySales::printHistogram()
{
    auto iter = m_sales.begin();
    while(iter != m_sales.end())
    {
        cout << iter->first << ": ";
        for(int i = 0; i < iter->second; i++)
        {
            cout << '*';
        }
        cout << endl;
        ++iter;
    }
}

//when given an iterator, will get the string version of that item in that iteration
std::string GrocerySales::getItemString(std::map<std::string, int>::iterator t_iter)
{
    std::stringstream output;
    output << t_iter->first << ": " << t_iter->second;
    return output.str();
}

//gets the string representation of an item passed in as a string
std::string GrocerySales::getItemString(const std::string& t_item)
{
    //throws an exception if the item given does not exist
    if(m_sales.count(t_item) <= 0)
    {
        throw std::invalid_argument("Item does not exist");
    }
    std::stringstream output;
    output << t_item << ": " << m_sales[t_item];
    return output.str();
}

//private method that allows other functions to specify an ostream to use this iterator loop to write to
void GrocerySales::writeToOutStream(std::ostream& stream)
{
    auto iter = m_sales.begin();
    while(iter != m_sales.end())
    {
        stream << getItemString(iter) << endl;
        ++iter;
    }
}

//prints the frequency of all items
void GrocerySales::printFrequencyAllItems()
{
    writeToOutStream(cout);
}

//writes a dat file given a file name
void GrocerySales::writeDatFile(const std::string& t_filename)
{

    ofstream outfile(t_filename);
    if(!outfile.is_open())
    {
        cout << "Could not create output file" << endl;
        return;
    }
    writeToOutStream(outfile);
    outfile.close();
}

//if the frequency.dat file already exists, read it to the map
bool GrocerySales::readDatFile(const std::string& t_filename)
{
    string name;
    int count;
    ifstream infile(t_filename);
    if(!infile.is_open())
    {
        infile.close();
        cout << "Could not open frequency.dat" << endl;
        return false;
    }
    while(!infile.fail())
    {
        if(infile.eof())
        {
            break;
        }
        getline(infile, name, ':');
        //when we reach the end of the file it still reads in a blank string so this prevents that last blank
        //from being written to the map
        //this is a bit of a hack but it works so is it really a hack?
        if(name.empty())
        {
            continue;
        }
        infile >> count;
        add(name, count);
        infile.ignore();
    }
    infile.close();
    return true;
}

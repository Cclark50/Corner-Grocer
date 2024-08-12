//
// Created by metat on 8/2/2024.
//

#ifndef GROCERYSALES_H
#define GROCERYSALES_H

#include <map>
#include <ostream>
#include <string>

class GrocerySales {
private:
   std::map<std::string, int> m_sales;
   void writeToOutStream(std::ostream& stream);
public:
   //this overload did not work with make_unique and I cant find out why
   int operator[](const std::string& str);
   GrocerySales();
   bool contains(const std::string& t_str);
   bool populateList(const std::string&);
   std::map<std::string, int>::iterator begin(){return m_sales.begin();}
   std::map<std::string, int>::iterator end(){return m_sales.end();}
   int at(const std::string& t_str);
   void add(const std::string& t_input);
   void add(const std::string& t_name, int count);
   void printHistogram();
   void printFrequencyAllItems();
   static std::string getItemString(std::map<std::string, int>::iterator t_iter);
   std::string getItemString(const std::string& t_item);
   void writeDatFile(const std::string& t_filename);
   bool readDatFile(const std::string& t_filename);
};



#endif //GROCERYSALES_H

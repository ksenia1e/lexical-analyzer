#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <algorithm>
#include <fstream>
using namespace std;

class staticTable 
{
public:
   vector <string> simbols;

   string getByKey(int key);

   void getTable();

   void createTable();

   void printTable();
};

template <class Type>
class dynamicTable 
{
public:
   vector <Type> data;

   Type getByKey(int key);

   void add(Type value);

   void removeByValue(Type value);

   bool checkValue(Type value);

   void getTable();

   void printTable();
};

struct err
{
    string word;
    int number_er;
    int number_str;
    string comment;
};

staticTable st;
dynamicTable <string> stringTable;
dynamicTable <int> constTable;

vector<string> strings;
vector<err> errors;
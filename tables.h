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

   string getByKey(int key)
   {
      if (key >= 0 && key < simbols.size())
         return simbols[key];

      return "err";
   }

   void getTable()
   {
      for (int i = 0; i < simbols.size(); i++)
      {
         cout << simbols[i] << endl;
      }
   }

   void createTable()
   {
      simbols.resize(18);

      // type
      simbols[0] = ("int");

      // operations
      simbols[1] = ("+");
      simbols[2] = ("-");
      simbols[3] = ("*");

      // operations comparasion
      simbols[4] = ("<");    
      simbols[5] = ("!=");   
      simbols[6] = ("==");

      // =
      simbols[7] = ("=");

      // signs
      simbols[8] = ("(");
      simbols[9] = (")");
      simbols[10] = ("{");
      simbols[11] = ("}");

      // operators
      simbols[12] = ("if");
      simbols[13] = ("else");
      simbols[14] = ("main");

      simbols[15] = ("/");
      simbols[16] = (";");
      simbols[17] = ("return");
   }

   void printTable()
   {
      ofstream out;
      out.open("staticTable.txt");

      if (out.is_open())
      {
         for (int i = 0; i < simbols.size(); i++)
         {
            out << i << ": " << simbols[i] << endl;
         }
      }
      else {
         cout << "Ошибка открытия файла" << endl;
      }
      out.close();
   }
};

template <class Type>
class dynamicTable
{
public:
   vector <Type> data;

   Type getByKey(int key)
   {
      if (key >= 0 && key < data.size())
         return data[key];

      return "err";
   }

   void add(Type value)
   {
      data.push_back(value);
   }

   void removeByValue(Type value)
   {
      for (size_t i = 0; i < data.size(); ++i)
      {
         if (data[i] == value)
         {
            data.erase(data.begin() + i);
            break;
         }
      }
   }

   bool checkValue(Type value)
   {
      auto p = find(data.begin(), data.end(), value);
      return p == end(data) ? false : true;
   }

   void getTable()
   {
      for (int i = 0; i < data.size(); i++)
      {
         cout << data[i] << endl;
      }
   }

   void printTable(string &s)
   {
      ofstream out;
      out.open(s);

      if (out.is_open())
      {
         for (int i = 0; i < data.size(); i++)
         {
            out << i << ": " << data[i] << endl;
         }
      }
      else {
         cout << "Ошибка открытия файла" << endl;
      }
      out.close();
   }
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

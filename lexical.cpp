#include "tables.h"

int GetType(char &symbol)
{
    if ('0' <= symbol && symbol <= '9')
        return 0;
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '=' || symbol == '!' || symbol == '<')
        return 1;
    if ('a' <= symbol && symbol <= 'z' || 'A' <= symbol && symbol <= 'Z' || symbol == '_')
        return 2;
    if (symbol == '/')
        return 3;
    if (symbol == ';')
       return 4;
    if (symbol == '{' || symbol == '}' || symbol == '(' || symbol == ')')
       return 5;
    return -1;
}

void ReadWords()
{
    string s;
    ifstream in("program.txt");
    if(in.is_open()){
        while(getline(in, s))
        {
            strings.push_back(s);
        }
    }
    in.close();
}

void PrintTokens(vector<pair<int, int>> &tokens)
{
    ofstream out("tokens.txt");
    for (int i = 0; i < tokens.size(); i++)
        out << "(" << tokens[i].first << ", " << tokens[i].second << ")" << endl;
    out.close();
}

void PrintErrors(vector <err> errors)
{
    ofstream out("errors.txt");
    for (int i = 0; i < errors.size(); i++)
    {
        out << "Код ошибки: " << errors[i].number_er << endl;
        out << "Номер строки: " << errors[i].number_str << endl;
        out << errors[i].comment << errors[i].word << endl;
        out << "--------------------" << endl;
    }
}

void CreateTokens(vector<pair<int, int>> &tokens)
{
    ReadWords();
    
    vector<char> word;
    st.createTable();
    int zs{0};
    // 0 - таблица констант, 1 - таблица переменных, 2 - таблица зарезервированных символов
    for (int i = 0; i < strings.size(); i++)
    {
       int x{ 0 }, q{ 0 };
       bool flag1{ 0 };
        for (int c = 0; c < strings[i].size(); c++)
        {
           if (flag1 == 1)
              break;
           bool flag{ 0 };
           char a = strings[i][c];
           if (a != ' ' && a != '\t')
              word.push_back(a);
           if (strings[i][c+1] == ' ' || c == strings[i].size() - 1)
           {
              c++;
              int type = GetType(word[0]);
              int size, size1, size2, size3, j, p1=0, p2=0;
              switch (type)
              {
              case(0):
                 for (j = 1; j < word.size(); j++)
                 {
                    int t_next = GetType(word[j]);
                    if (t_next != 0)
                    {
                       err e;
                       e.number_er = 0, e.number_str = i + 1,
                          e.word = word[j], e.comment = "Недопустимый cимвол ";
                       errors.push_back(e);
                       word.clear();
                       break;
                    }
                 }

                 for (j = 0, q = word.size() - 1; j < word.size(); j++, q--)
                    x += (word[q] - '0') * pow(10, j);
                 constTable.add(x);
                 tokens.push_back(make_pair(0, constTable.data.size() - 1));
                 word.clear();
                 break;

              case(1):
                 size = word.size();
                 switch (size)
                 {
                 case(1):
                    for (j = 1; j < 5; j++)
                    {
                       if (st.simbols[j][0] == word[0])
                       {
                          zs = j;
                          tokens.push_back(make_pair(2, zs));
                          break;
                       }
                    }
                    if (st.simbols[7][0] == word[0])
                    {
                       zs = 7;
                       tokens.push_back(make_pair(2, zs));
                    }
                    break;

                 case(2):
                    if (st.simbols[5][0] == word[0])
                    {
                       if (st.simbols[5][1] == word[1])
                       {
                          zs = 5;
                          tokens.push_back(make_pair(2, zs));
                       }
                       else
                          flag = 1;
                    }
                    if (st.simbols[6][0] == word[0])
                    {
                       if (st.simbols[6][1] == word[1])
                       {
                          zs = 6;
                          tokens.push_back(make_pair(2, zs));
                       }
                       else
                          flag = 1;
                    }
                    if (flag == 1)
                    {
                       err e;
                       e.number_er = 1, e.number_str = i + 1,
                          e.word = word[1], e.comment = "Недопустимый cимвол ";
                       errors.push_back(e);
                       word.clear();
                       break;
                    }
                    break;

                 default:
                    err e;
                    e.number_er = 1, e.number_str = i + 1,
                       e.word = word[2], e.comment = "Недопустимый cимвол ";
                    errors.push_back(e);
                    word.clear();
                    break;
                 }
                 word.clear();
                 break;
              
              case(2):
                 size2 = word.size();
                 switch (size2)
                 {
                 case(2):
                    if (st.simbols[12][1] == word[1])
                    {
                       zs = 12;
                       tokens.push_back(make_pair(2, zs));
                       break;
                    }
                    else if (GetType(word[1]) == 2)
                    {
                       tokens.push_back(make_pair(1, stringTable.data.size() - 1));
                       string s (word.begin(), word.end());
                       stringTable.add(s);
                       break;
                    }
                    for (j = 1; j < word.size(); j++)
                    {
                       int t_next = GetType(word[j]);
                       if (t_next != 2)
                       {
                          err e;
                          e.number_er = 2, e.number_str = i + 1,
                             e.word = word[j], e.comment = "Недопустимый cимвол ";
                          errors.push_back(e);
                          word.clear();
                          break;
                       }
                    }

                 case(3):
                    for (j = 0; j < 3; j++)
                    {
                       if (st.simbols[0][j] != word[j])
                          flag = 1;
                    }
                    if (flag == 1)
                    {
                       for (j = 1; j < word.size(); j++)
                       {
                          int t_next = GetType(word[j]);
                          if (t_next != 2)
                          {
                             err e;
                             e.number_er = 2, e.number_str = i + 1,
                                e.word = word[j], e.comment = "Недопустимый cимвол ";
                             errors.push_back(e);
                             word.clear();
                             flag = 0;
                             break;
                          }
                       }
                       if (flag != 0)
                       {
                          string s(word.begin(), word.end());
                          stringTable.add(s);
                          tokens.push_back(make_pair(1, stringTable.data.size() - 1));
                          break;
                       }
                    }
                    tokens.push_back(make_pair(2, 0));
                    break;

                 case(4):
                    
                    for (j = 0, p1 = 13, p2 = 14; j < 4; j++)
                    {
                       if (st.simbols[13][j] != word[j])
                       {
                          p1 = 0;
                          break;
                       }
                       if (st.simbols[14][j] != word[j])
                       {
                          p2 = 0;
                          break;
                       }
                    }
                    if (p1 == 0 && p2 == 0)
                    {
                       for (j = 1; j < word.size(); j++)
                       {
                          int t_next = GetType(word[j]);
                          if (t_next != 2)
                          {
                             err e;
                             e.number_er = 2, e.number_str = i + 1,
                                e.word = word[j], e.comment = "Недопустимый cимвол ";
                             errors.push_back(e);
                             word.clear();
                             flag = 0;
                             break;
                          }
                       }
                       if (flag != 0)
                       {
                          string s(word.begin(), word.end());
                          stringTable.add(s);
                          tokens.push_back(make_pair(1, stringTable.data.size() - 1));
                          break;
                       }
                    }
                    if (p1 != 0)
                    {
                       tokens.push_back(make_pair(2, p1));
                       break;
                    }
                    if (p2 != 0)
                    {
                       tokens.push_back(make_pair(2, p2));
                       break;
                    }
                    break;

                 case(6):
                    for (j = 0; j < 6; j++)
                    {
                       if (st.simbols[17][j] != word[j])
                          flag = 1;
                    }
                    if (flag == 1)
                    {
                       for (j = 1; j < word.size(); j++)
                       {
                          int t_next = GetType(word[j]);
                          if (t_next != 2)
                          {
                             err e;
                             e.number_er = 2, e.number_str = i + 1,
                                e.word = word[j], e.comment = "Недопустимый cимвол ";
                             errors.push_back(e);
                             word.clear();
                             flag = 0;
                             break;
                          }
                       }
                       if (flag != 0)
                       {
                          string s(word.begin(), word.end());
                          stringTable.add(s);
                          tokens.push_back(make_pair(1, stringTable.data.size() - 1));
                          break;
                       }
                    }
                    tokens.push_back(make_pair(2, 17));
                    break;

                 default:
                    for (j = 1; j < word.size(); j++)
                    {
                       int t_next = GetType(word[j]);
                       if (t_next != 2)
                       {
                          err e;
                          e.number_er = 2, e.number_str = i + 1,
                             e.word = word[j], e.comment = "Недопустимый cимвол ";
                          errors.push_back(e);
                          word.clear();
                          break;
                       }
                    }
                    string s(word.begin(), word.end());
                    stringTable.add(s);
                    tokens.push_back(make_pair(1, stringTable.data.size() - 1));
                    break;
                 }
                 word.clear();
                 break;

              case(3):
                 size3 = word.size();
                 switch (size3)
                 {
                 case(2):
                    if (st.simbols[15][0]==word[1])
                    {
                       flag1 = 1;
                       //tokens.push_back(make_pair(2, 15));
                       break;
                    }
                    else
                    {
                       err e;
                       e.number_er = 3, e.number_str = i + 1,
                          e.word = word[1], e.comment = "Недопустимый cимвол, ожидался '/' вместо ";
                       errors.push_back(e);
                       word.clear();
                       break;
                    }

                 default:
                    err e;
                    e.number_er = 3, e.number_str = i + 1,
                       e.word = word[0], e.comment = "Недопустимый cимвол, ожидалось '//' вместо ";
                    errors.push_back(e);
                    word.clear();
                    break;
                 }
                 word.clear();
                 break;

              case(4):
                 if (word.size() > 1)
                 {
                    err e;
                    e.number_er = 4, e.number_str = i + 1,
                       e.word = word[1], e.comment = "Недопустимый cимвол ";
                    errors.push_back(e);
                    word.clear();
                    break;
                 }
                 tokens.push_back(make_pair(2, 16));
                 word.clear();
                 break;

              case(5):
                 if (word.size() > 1)
                 {
                    err e;
                    e.number_er = 5, e.number_str = i + 1,
                       e.word = word[1], e.comment = "Недопустимый cимвол ";
                    errors.push_back(e);
                    word.clear();
                    break;
                 }
                 for (j = 8; j < 12; j++)
                 {
                    if (st.simbols[j][0] == word[0])
                    {
                       zs = j;
                       break;
                    }
                 }
                 tokens.push_back(make_pair(2, zs));
                 word.clear();
                 break;

              default:
                 err e;
                 e.number_er = -1, e.number_str = i + 1,
                    e.word = word[0], e.comment = "Неизвестный cимвол ";
                 errors.push_back(e);
                 word.clear();
              }
           }
        }
    }

    st.printTable();
    string s1 = { "constTable.txt" };
    constTable.printTable(s1);
    string s2 = { "dynamicTable.txt" };
    stringTable.printTable(s2);
    PrintTokens(tokens);
    PrintErrors(errors);
}

int main()
{
    vector<pair<int, int>> token;
    CreateTokens(token);
}
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
        out << tokens[i].first << tokens[i].second << endl;
    out.close();
}

void PrintErrors(vector <err> errors)
{
    ofstream out("errors.txt");
    for (int i = 0; i < errors.size(); i++)
    {
        out << "Код ошибки: " << errors[i].number_er << endl;
        out << "Номер строки: " << errors[i].number_str << endl;
        out << errors[i].comment << endl;
        out << "--------------------" << endl;
    }
}

void CreateTokens(vector<pair<int, int>> &tokens)
{
    ReadWords();
    
    vector<string> words;
    st.createTable();

    bool findendComment = false;

    for (int i = 0; i < strings.size(); i++)
    {
        words.clear();
        char* token = strtok(strings[i].data(), " ");
        
        while(token != nullptr)
        {
            words.push_back(token);
            token = strtok(nullptr, " ");
        }

        bool newstr = false;
        // Идем по словам в строке
        for (auto word: words)
        {
            
            if (newstr)
            {
                break;
            }
            
            char x = word[0];
            
            // Если конец двустрочного комментария еще не найден
            if (findendComment)
            {
                x = 3;
            }

            switch (GetType(x))
            {
                // const
                case (0):
                {
                    bool flag = 0;
                    for (char symb: word)
                    {
                        if (symb < '0' || symb > '9')
                        {
                            err e;
                            e.number_er = 0, e.number_str = i + 1, 
                            e.word = word, e.comment = "Недопустимый cимвол " + symb;
                            errors.push_back(e);
                            flag = 1;
                            break;
                        }
                    }

                    // Если ошибок не было, создаем токен
                    if (!flag)
                    {
                        constTable.add(stoi(word));
                        auto p = make_pair(2, constTable.data.size());
                        tokens.push_back(p);
                    }

                    break;
                }
                    

                // specific symbols
                case (1):
                {
                    int k = 1;
                    bool flag = false;

                    for (; k < 5; k++)
                    {
                        if (word[0] == st.simbols[k][0])
                        {
                            if (word.size() > 1)
                            {
                                flag = true;
                                err e;
                                e.number_er = 1, e.number_str = i, 
                                e.word = word, e.comment = "Недопустимый символ " + word[1];
                                errors.push_back(e);
                                break;
                            }
                            break;
                        }
                    }

                    if (word[0] = st.simbols[5][0])
                    {
                        k = 5;
                        if (word.size() > 1)
                        {
                            if (word[1] != st.simbols[5][1])
                            {
                                flag = true;
                                err e;
                                e.number_er = 1, e.number_str = i, 
                                e.word = word, e.comment = "Недопустимый символ " + word[1];
                                errors.push_back(e);
                                break;
                            }
                            
                            if (word.size() > 2)
                            {
                                flag = true;
                                err e;
                                e.number_er = 1, e.number_str = i, 
                                e.word = word, e.comment = "Лишний символ " + word[2];
                                errors.push_back(e);
                                break;
                            }
                        }
                        else 
                        {
                            flag = true;
                            err e;
                            e.number_er = 1, e.number_str = i, 
                            e.word = word, e.comment = "Отсутсвует символ =";
                            errors.push_back(e);
                            break;
                        }
                    }

                    if (word[0] == st.simbols[6][0])
                    {
                        k = 7;
                        if (word.size() > 1)
                        {
                            k = 6;
                            if (word[1] != st.simbols[6][1])
                            {
                                flag = true;
                                err e;
                                e.number_er = 1, e.number_str = i, 
                                e.word = word, e.comment = "Недопустимый символ " + word[1];
                                errors.push_back(e);
                                break;
                            }
                            
                            if (word.size() > 2)
                            {
                                flag = true;
                                err e;
                                e.number_er = 1, e.number_str = i, 
                                e.word = word, e.comment = "Лишний символ " + word[2];
                                errors.push_back(e);
                                break;
                            }
                        }
                    }

                    // Если ошибок не было, создаем токен
                    if (!flag)
                    {
                        auto p = make_pair(0, k);
                        tokens.push_back(p);
                    }
                    break;
                }
                
                // identifier
                case (2):
                {
                    bool flag = 0;
                    
                    for (auto symb: word)
                    {
                        if (!(symb == '_' || (symb >= '0' && symb <= '9') || 
                        (symb >= 'a' && symb <= 'z') || (symb >= 'A' && symb <= 'Z')))
                        {
                            flag = 1;
                            err e;
                            e.number_er = 2, e.number_str = i, 
                            e.word = word, e.comment = "Недопустимый символ " + symb;
                            errors.push_back(e);
                            break;
                        }
                    }
                    
                    if (!flag)
                    {
                        bool is_static = 0;
                        for(int k = 0; k < st.simbols.size(); k++)
                        {
                            if (word == st.simbols[i])
                                is_static = 1;
                        }

                        // Если слово зарезервированно
                        if (is_static)
                        {
                            auto p = make_pair(0, i);
                            tokens.push_back(p);
                        }
                        else
                        {
                            stringTable.add(word);
                            auto p = make_pair(1, stringTable.data.size());
                            tokens.push_back(p);
                        }
                        
                    }

                    break;
                }
                    
                
                // comment
                case (3):
                {
                    if (!findendComment)
                    {
                        for(auto elem : word)
                        {
                            if (elem == '*')
                            {
                                findendComment = false;
                                
                                break;
                            }
                        }
                    }

                    // Если мы не в двустрочном комментарии
                    if (!findendComment)
                    {
                        if (word.size() > 1)
                        {   
                            if (word[1] == '/')
                            {
                                newstr = true;
                                break;
                            }
                            else if (word[1] == '*')
                            {
                                findendComment = true;
                            }
                            else 
                            {
                                err e;
                                e.number_er = 3, e.number_str = i, 
                                e.word = word, e.comment = "Недопустимый символ " + word[1];
                                errors.push_back(e);
                                break;
                            }
                        }
                        else
                        {
                            err e;
                            e.number_er = 3, e.number_str = i, 
                            e.word = word, e.comment = "Отсутсвует символ / или *";
                            errors.push_back(e);
                            break;
                        }
                    }
                    
                    // Если конец двустрочного комментария еще не найден
                    if (findendComment)
                    {
                        // Если "*/" не найдено
                        if(strings[i].find("*/") == string::npos)
                        {
                            newstr = true;
                            break;
                        }

                        findendComment = false;
                        break;
                    }
                }
                
                // error
                case (-1):
                {
                    err e;
                    e.number_er = -1, e.number_str = i, 
                    e.word = word, e.comment = "Недопустимый символ " + x;
                    errors.push_back(e);
                    break;
                }
            }
        }
    }

    st.printTable();
    constTable.printTable();
    stringTable.printTable();
    PrintTokens(tokens);
    PrintErrors(errors);
}

int main()
{
    vector<pair<int, int>> token;
    CreateTokens(token);
}
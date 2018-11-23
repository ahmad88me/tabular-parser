#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <list>

using namespace std;

class Parser{
    public:
        Parser(string);
        std::list<std::list<string>*> *parse();
        void set_delimiter(char);
        void set_escape_chars(string);
    private:
        string m_escape_chars;
        char m_delimiter;
        string m_file_dir;
        std::list<string> * parse_line(string);

};

#endif


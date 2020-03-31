#include <iostream>
#include <fstream>
#include <ctype.h>
#include "parser.h"

Parser::Parser(string file_dir) {
    //    m_escape_chars = "\"\'";
    m_escape_chars = "\"";
    m_delimiter = ',';
    m_file_dir = file_dir;
}

void Parser::set_delimiter(char d) {
    m_delimiter = d;
}

void Parser::set_escape_chars(string s) {
    m_escape_chars = s;
}

std::list<std::list<string>*>* Parser::parse() {
    ifstream in_file(m_file_dir);
    string line;
    std::list<std::list<string>*>* cols = new std::list<std::list<string>*>;
    std::list<string>* row;
    unsigned long num_of_cols;
    if(in_file.is_open()) {
        if(getline(in_file, line)) {
            row = this->parse_line(line);
            for(int i=0; i<row->size(); i++) {
                cols->push_back(new std::list<string>);
            }
            num_of_cols = row->size();
            auto it_row=row->cbegin();
            for(auto it_col=cols->cbegin(); it_col != cols->cend(); it_col++, it_row++) {
                (*it_col)->push_back(*it_row);
            }
        }
        while(getline(in_file, line)) {
            row = this->parse_line(line);
            if(row->size()==num_of_cols) {
                auto it_row=row->cbegin();
                for(auto it_col=cols->cbegin(); it_col != cols->cend(); it_col++, it_row++) {
                    (*it_col)->push_back(*it_row);
                }
            }
            //cols->push_back(row);
        }
        //            for(auto it=cols->cbegin(); it != cols->cend(); it++){
        //                for(auto jt=(*it)->cbegin(); jt != (*it)->cend(); jt++){
        //                    cout << *jt << "\t";
        //                }
        //                cout<<endl;
        //            }
    }
    else {
        cout << "Error opening the file\n";
    }
    return cols;
}


std::list<std::list<string>*>* Parser::parse_vertical() {
    ifstream in_file(m_file_dir);
    string line;
    std::list<std::list<string>*>* rows = new std::list<std::list<string>*>;
    std::list<string>* row;
    unsigned long num_of_cols;
    if(in_file.is_open()) {
        if(getline(in_file, line)) {
            row = this->parse_line(line);
            rows->push_back(row);
            num_of_cols = row->size();
        }
        while(getline(in_file, line)) {
            row = this->parse_line(line);
            if(row->size()==num_of_cols) {
                rows->push_back(row);
            }
        }
    }
    else {
        cout << "Error opening the file\n";
    }
    return rows;
}


std::list<string>* Parser::parse_line(string line) {
    std::list<string>* elements = new std::list<string>;
    unsigned long long i, start_idx=0, j;
    string t;
    bool open_escape=false;
    char null_escape_char='\a'; // this will act as a null, it can by any other character not used
    char escape_char;
    escape_char = null_escape_char; // just to check if a escape char
    //cout << "the line: <<"<<line<<">>"<<endl;
    for(i=0; i<line.size(); i++) {
        if(escape_char==null_escape_char) {
            //
            for(j=0; j<m_escape_chars.length(); j++) {
                if(line[i]==m_escape_chars[j]) { // escape character start
                    escape_char=m_escape_chars[j];
                    open_escape = true;
                }
            }
            if(escape_char!=null_escape_char) {
                continue;
            }
        }
        if(line[i]==m_delimiter && !open_escape) {
            //cout << "start_idx: "<< start_idx<< "  of size: "<<(i-start_idx)<<endl;
            t = line.substr(start_idx, i-start_idx);
            //cout << "printing t: <"<<t<<"> \n";
            //            elements->push_back(t);
            elements->push_back(get_printable(t));
            start_idx = i+1;
        }
        else if(open_escape && line[i]==escape_char) {
            open_escape = false;
            escape_char = null_escape_char;
        }
    }
    //cout<< "\n\nlist size:" <<line.size()<<endl;
    //cout << "start_idx: "<< start_idx<<endl;
    t = line.substr(start_idx, line.size()-start_idx);
    //cout << "printing last t: <"<<t<<">" << endl;
    //elements->push_back(t);
    elements->push_back(get_printable(t));
    return elements;
}

string Parser::get_printable(string s) {
    string t="";
    for(long i=0; i<s.size(); i++) {
        if(iscntrl(s[i])==0) {
            t += s[i];
        }
    }
    return t;
}






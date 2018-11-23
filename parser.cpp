#include <iostream>
#include <fstream>
#include "parser.h"

Parser::Parser(string file_dir){
    m_escape_chars = "\"\'";
    m_delimiter = ',';
    m_file_dir = file_dir;
}

void Parser::set_delimiter(char d){
    m_delimiter = d;
}

void Parser::set_escape_chars(string s){
    m_escape_chars = s;
}

std::list<std::list<string>*>* Parser::parse(){
    ifstream in_file(m_file_dir);
    string line;
    std::list<std::list<string>*> * cols = new std::list<std::list<string>*>;
    std::list<string>* row;
    unsigned long num_of_cols;
    if(in_file.is_open()){
        if(getline(in_file, line)){
            row = this->parse_line(line);
            for(int i=0;i<row->size();i++){
                cols->push_back(new std::list<string>);
            }
            num_of_cols = row->size();
            auto it_row=row->cbegin();
            for(auto it_col=cols->cbegin(); it_col != cols->cend(); it_col++, it_row++){
                (*it_col)->push_back(*it_row);
            }
        }
            while(getline(in_file, line)){
                row = this->parse_line(line);
                if(row->size()==num_of_cols){
                    auto it_row=row->cbegin();
                    for(auto it_col=cols->cbegin(); it_col != cols->cend(); it_col++, it_row++){
                        (*it_col)->push_back(*it_row);
                    }
                }
                //cols->push_back(row);
            }
            for(auto it=cols->cbegin(); it != cols->cend(); it++){
                for(auto jt=(*it)->cbegin(); jt != (*it)->cend(); jt++){
                    cout << *jt << "\t";
                }
                cout<<endl;
            }
    }
    else{
        cout << "Error opening the file\n";
    }
}

std::list<string> * Parser::parse_line(string line){
    std::list<string> *elements = new std::list<string>;
    int i, start_idx=0;
    string t;
    for(i=0;i<line.size();i++){
        if(line[i]==m_delimiter){
            t = line.substr(start_idx, i-start_idx);
            elements->push_back(t);
            start_idx = i+1;
        }
    }
    t = line.substr(start_idx, line.size()-start_idx);
    elements->push_back(t);
    return elements;
}





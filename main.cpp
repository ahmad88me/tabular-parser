#include <iostream>
#include "parser.h"
using namespace std;

int main(int argc, char** argv) {
    std::list<std::list<string>*>* data;
    string fdir = "test-q.csv";
    if(argc==2) {
        fdir = argv[1];
    }
    cout << "Parsing: "<<fdir;
    Parser p(fdir);
    cout << "\nHorizonal mode: \n"<<endl;
    data = p.parse();
    for(auto it=data->cbegin(); it!=data->cend(); it++) {
        for(auto jt=(*it)->cbegin(); jt!=(*it)->cend(); jt++) {
            cout << (*jt) << " ";
        }
        cout << endl<<"----------"<<endl;
    }
    cout << "\nVertical mode: \n"<<endl;
    data = p.parse_vertical();
    for(auto it=data->cbegin(); it!=data->cend(); it++) {
        for(auto jt=(*it)->cbegin(); jt!=(*it)->cend(); jt++) {
            cout << (*jt) << " ";
        }
        cout << endl<<"----------"<<endl;
    }
    return 0;
}

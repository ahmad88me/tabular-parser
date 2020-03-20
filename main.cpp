#include <iostream>
#include "parser.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Parser parser("test.csv");
    std::list<std::list<string>*>* data;
    Parser p("test.csv");
    cout << "\nHorizonal mode: \n"<<endl;
    data = p.parse();
    for(auto it=data->cbegin();it!=data->cend();it++){
        for(auto jt=(*it)->cbegin();jt!=(*it)->cend();jt++){
            cout << (*jt) << " ";
        }
        cout << endl<<"----------"<<endl;
    }

    cout << "\nVertical mode: \n"<<endl;
    data = p.parse_vertical();
    for(auto it=data->cbegin();it!=data->cend();it++){
        for(auto jt=(*it)->cbegin();jt!=(*it)->cend();jt++){
            cout << (*jt) << " ";
        }
        cout << endl<<"----------"<<endl;
    }    return 0;

}

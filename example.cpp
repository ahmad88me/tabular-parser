#include <tabular_parser/parser.h>

#include <iostream>
#include <list>

using namespace std;

int main(){

    std::list<std::list<string>*>* data;
    Parser p("test.csv");
    data = p.parse();
    for(auto it=data->cbegin();it!=data->cend();it++){
        for(auto jt=(*it)->cbegin();jt!=(*it)->cend();jt++){
            cout << (*jt) << " ";
        }
        cout << endl<<"----------"<<endl;
    }
    return 0;
}

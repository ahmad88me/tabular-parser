#include <iostream>
#include "parser.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Parser parser("test.csv");
    parser.parse();
    return 0;

}

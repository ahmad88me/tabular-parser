#include <gtest/gtest.h>
#include <list>
#include <iostream>
#include <string>
#include "parser.h"

using namespace std;

namespace {


    TEST(ParserTest, TestSetup) {
        EXPECT_EQ(1, 1);
    }

    TEST(ParserTest, TestParsingCSV) {
        std::list<std::list<string>*>* data;
        Parser parser("test.csv");
        data = parser.parse();
        cout<< "\n\n data size: ";
        cout << data->size() << endl;
        EXPECT_EQ(3, data->size());
        EXPECT_EQ(4, (*(data->cbegin()))->size());
    }

    TEST(ParserTest, Vertical) {
        std::list<std::list<string>*>* data;
        Parser parser("test.csv");
        data = parser.parse_vertical();
        cout<< "\n\n data size: ";
        cout << data->size() << endl;
        EXPECT_EQ(4, data->size());
        EXPECT_EQ(3, (*(data->cbegin()))->size());
    }

    TEST(ParserTest, VerticalWithQ) {
        std::list<std::list<string>*>* data;
        Parser parser("test-q.csv");
        data = parser.parse_vertical();
        cout<< "\n\n data size: ";
        cout << data->size() << endl;
        EXPECT_EQ(4, data->size());
        EXPECT_EQ(3, (*(data->cbegin()))->size());
    }

}// namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



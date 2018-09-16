#ifndef __CAFFE_PARSE_TREE_BUILDER_HPP__
#define __CAFFE_PARSE_TREE_BUILDER_HPP__
#include <iostream>
#include <string>


class CaffeParseTreeBuilder
{
    public:
        CaffeParseTreeBuilder() {};
        ~CaffeParseTreeBuilder() {};

    public:
        void PrintStr(const std::string& str);
        void PrintInt(const int& i);
        void PrintDouble(const double& d);

};

#endif

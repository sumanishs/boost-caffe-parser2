#include <boost/spirit/include/qi.hpp>
#include "caffe_parse_tree_builder.hpp"

#include <iostream>

namespace qi = boost::spirit::qi;

struct PrintStr {
    void operator()(const std::string& str, qi::unused_type, qi::unused_type ) const{
        //std::cout << str;
        ptb.PrintStr(str);
    }
    PrintStr(CaffeParseTreeBuilder& aPtb):ptb(aPtb){ }
    CaffeParseTreeBuilder& ptb;
};

struct PrintInt {
    void operator()(const int& i, qi::unused_type, qi::unused_type ) const{
        //std::cout << i;
        ptb.PrintInt(i);
    }
    PrintInt(CaffeParseTreeBuilder& aPtb):ptb(aPtb){ }
    CaffeParseTreeBuilder& ptb;
};

struct PrintDouble {
    void operator()(const double& d, qi::unused_type, qi::unused_type ) const{
        //std::cout << d;
        ptb.PrintDouble(d);
    }
    PrintDouble(CaffeParseTreeBuilder& aPtb):ptb(aPtb){ }
    CaffeParseTreeBuilder& ptb;
};

#include <boost/spirit/include/qi.hpp>

#include <iostream>

namespace qi = boost::spirit::qi;

struct PrintStr {
    void operator()(const std::string& str, qi::unused_type, qi::unused_type ) const{
        std::cout << str;
    }
    PrintStr(){ }
};

struct PrintInt {
    void operator()(const int& i, qi::unused_type, qi::unused_type ) const{
        std::cout << i;
    }
    PrintInt(){ }
};

struct PrintDouble {
    void operator()(const double& d, qi::unused_type, qi::unused_type ) const{
        std::cout << d;
    }
    PrintDouble(){ }
};

/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include "caffereader.hpp"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "caffe_parse_tree_builder.hpp"

using namespace boost::spirit;

bool 
CaffeReader::Read(std::string& filename){

    typedef std::string::iterator base_iterator_type;
    typedef lex::lexertl::token< base_iterator_type, boost::mpl::vector<unsigned int, std::string> > token_type;
    typedef lex::lexertl::lexer<token_type> lexer_type;
    typedef caffe_tokens<lexer_type> caffe_tokens;
    typedef caffe_tokens::iterator_type iterator_type;
    typedef caffe_grammar<iterator_type, caffe_tokens::lexer_def> caffe_grammar;

    CaffeParseTreeBuilder* ptb = new CaffeParseTreeBuilder();

    caffe_tokens tokens;                         // Our lexer
    caffe_grammar grammar(tokens, ptb);                  // Our parser

    std::ifstream inFile;
    inFile.open(filename.c_str());
    if(inFile.fail()){
        std::cout << "Cannot open file to read...." << std::endl;
        return false;
    }

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str(strStream.str());
    str.pop_back();
    std::cout << "File content:" << str << "!" << std::endl;
    inFile.close();

    std::string::iterator it = str.begin();
    iterator_type iter = tokens.begin(it, str.end());
    iterator_type end = tokens.end();

    std::string ws("WS");
    bool r = qi::phrase_parse(iter, end, grammar, qi::in_state(ws)[tokens.self]);

    if (r && iter == end)
    {
        std::cout << "\n-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        return true;
    }
    else
    {
        std::cout << "\n-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
        return false;
    }

    std::cout << "Bye... :-) \n\n";
    return true;
}

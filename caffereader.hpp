/**********************************************************************/
/* Author: Sumanish <sumanish.cse.jgec@gmail.com>                     */
/* Modified By: Sumanish <sumanish.cse.jgec@gmail.com>                */
/*                                                                    */  
/* This source code can be downloaded, use, modify, distribute        */
/* freely with this headed intact. Please don't delete this header.   */
/**********************************************************************/ 

#include <iostream>
#include <string>

#include "caffe_grammar.hpp"


class CaffeReader {

    public:
        CaffeReader() {}
        ~CaffeReader() {}

        bool Read(std::string& filename);
};


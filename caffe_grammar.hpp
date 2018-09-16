#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/bind.hpp>

#include "caffe_tokens.hpp"
#include "caffe_functors.hpp"

using namespace boost::spirit;
using namespace boost::phoenix;

template <typename Iterator, typename Lexer>
struct caffe_grammar 
  : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{
    template <typename TokenDef>
    caffe_grammar(TokenDef const& tok)
      : caffe_grammar::base_type(start)
    {
        using boost::spirit::_val;
		using boost::spirit::_1;
		using boost::spirit::_2;
		using boost::spirit::_3;
		using boost::spirit::_4;

        start       = +statements;   
        statements  = name_
                    | phase_
                    | type_
					| include_
                    | mean_file_
                    | input_
                    | input_dim_
                    | dim_
                    | alpha_
                    | beta_
                    | top_        
                    | bottom_     
                    | lr_mult_    
                    | decay_mult_ 
                    | num_output_ 
                    | kernel_size_
                    | stride_     
                    | local_size_ 
                    | pool_       
                    | pad_        
                    | group_      
                    | dropout_ratio_
                    | input_shape_
                    | param_
                    | convolution_param_
                    | lrn_param_
                    | pooling_param_
                    | inner_product_param_
                    | dropout_param_
                    | layer_
                    ;

        phase_          = tok.phase_    [PrintStr()] >> ':' >> str_identifier [PrintStr()];
        name_           = tok.name_     [PrintStr()] >> ':' >> str_identifier [PrintStr()];
        type_           = tok.type_     [PrintStr()] >> ':' >> str_identifier [PrintStr()];

		str_identifier  = tok.identifier [_val = _1]
						| string_	[_val = _1]
						;

		string_         = '"' >> tok.identifier >> '"';

		include_        = tok.include_          [PrintStr()] >> ':' >> '{' >> phase_ >> '}';
        mean_file_      = tok.mean_file_        [PrintStr()] >> ':' >> str_identifier       [PrintStr()];
        input_          = tok.input_            [PrintStr()] >> ':' >> str_identifier       [PrintStr()];
        input_dim_      = tok.input_dim_        [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        dim_            = tok.dim_              [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        alpha_          = tok.alpha_            [PrintStr()] >> ':' >> tok.double_constant  [PrintDouble()]; 
        beta_           = tok.beta_             [PrintStr()] >> ':' >> tok.double_constant  [PrintDouble()]; 
        top_            = tok.top_              [PrintStr()] >> ':' >> str_identifier       [PrintStr()];
        bottom_         = tok.bottom_           [PrintStr()] >> ':' >> str_identifier       [PrintStr()];
        lr_mult_        = tok.lr_mult_          [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        decay_mult_     = tok.decay_mult_       [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        num_output_     = tok.num_output_       [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        kernel_size_    = tok.kernel_size_      [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        stride_         = tok.stride_           [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        local_size_     = tok.local_size_       [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        pool_           = tok.pool_             [PrintStr()] >> ':' >> str_identifier       [PrintStr()];
        pad_            = tok.pad_              [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        group_          = tok.group_            [PrintStr()] >> ':' >> tok.int_constant     [PrintInt()];
        dropout_ratio_  = tok.dropout_ratio_    [PrintStr()] >> ':' >> tok.double_constant  [PrintDouble()];
        input_shape_    = tok.input_shape_      [PrintStr()] >> '{' >> +input_shape_statements_ >> '}';
        input_shape_statements_ = dim_;

        param_          = tok.param_            [PrintStr()] >> '{' >> +param_statements_ >> '}';
        param_statements_ = lr_mult_
                           | decay_mult_
                           ;

        weight_filler_  = tok.weight_filler_ [PrintStr()] >> '{' >> +weight_filler_statements_ >> '}';
        weight_filler_statements_   = type_
                                     | stride_
                                     | pad_
                                     ;   
        
        bias_filler_  = tok.bias_filler_ [PrintStr()] >> '{' >> +bias_filler_statements_ >> '}';
        bias_filler_statements_   = type_
                                     | stride_
                                     | pad_
                                     ;   

        convolution_param_ = tok.convolution_param_ [PrintStr()] >> '{' >> +convolution_param_statements_ >> '}';
        convolution_param_statements_ = num_output_
                                       | kernel_size_
                                       | stride_
                                       | pad_
                                       | group_
                                       | weight_filler_
                                       | bias_filler_
                                       ;           

        lrn_param_  = tok.lrn_param_ [PrintStr()] >> '{' >> +lrn_param_statements_ >> '}';
        lrn_param_statements_ = local_size_
                               | alpha_
                               | beta_
                               | weight_filler_
                               | bias_filler_
                               ; 

        pooling_param_  = tok.pooling_param_ [PrintStr()] >> '{' >> +pooling_param_statements_ >> '}';
        pooling_param_statements_   = pool_
                                     | kernel_size_
                                     | stride_
                                     | weight_filler_
                                     | bias_filler_
                                     ; 

        inner_product_param_    = tok.inner_product_param_ [PrintStr()] >> '{' >> +inner_product_param_statements_ >> '}';
        inner_product_param_statements_ = num_output_
                                         | pad_
                                         | group_
                                         | weight_filler_
                                         | bias_filler_
                                         ;

        dropout_param_  = tok.dropout_param_ [PrintStr()] >> '{' >> +dropout_param_statements_ >> '}';
        dropout_param_statements_ = dropout_ratio_
                                   | num_output_
                                   | pad_
                                   | group_
                                   | weight_filler_
                                   | bias_filler_
                                   ;     

        layer_  = tok.layer_ [PrintStr()] >> '{' >> +layer_statements_ >> '}';
        layer_statements_ = name_
                           | type_
                           | bottom_
                           | top_
                           | param_
                           | convolution_param_
                           | pooling_param_
                           | lrn_param_
                           | inner_product_param_
                           | dropout_param_
                           ;      
    
		qi::on_error<qi::fail>
		  (
		   start
		   , std::cout
		   << val("Error! Expecting ")
		   << _4                               // what failed?
		   << val(" here: \"")
		   << construct<std::string>(_3, _2)   // iterators to error-pos, end
		   << val("\"")
		   << std::endl
		  );
    }

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > start, statements;
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > phase_, name_, type_, include_, mean_file_, input_, input_dim_, dim_, alpha_,
                                                     beta_, top_, bottom_, lr_mult_, decay_mult_, num_output_, kernel_size_, stride_, 
                                                     local_size_, pool_, pad_, group_, dropout_ratio_, input_shape_, input_shape_statements_,
                                                     param_, param_statements_, convolution_param_, convolution_param_statements_,
                                                     lrn_param_, lrn_param_statements_, pooling_param_, pooling_param_statements_,
                                                     inner_product_param_, inner_product_param_statements_, dropout_param_,
                                                     dropout_param_statements_, layer_, layer_statements_, weight_filler_, weight_filler_statements_,
                                                     bias_filler_, bias_filler_statements_
                                                     ;

    qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > string_;

	qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > str_identifier;
};

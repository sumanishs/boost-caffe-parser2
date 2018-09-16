#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/bind.hpp>
#include "caffe_parse_tree_builder.hpp"

#include "caffe_tokens.hpp"
#include "caffe_functors.hpp"

using namespace boost::spirit;
using namespace boost::phoenix;

template <typename Iterator, typename Lexer>
struct caffe_grammar 
  : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{
    template <typename TokenDef>
    caffe_grammar(TokenDef const& tok, CaffeParseTreeBuilder* aPtb)
      : caffe_grammar::base_type(start), ptb(aPtb)
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
                    | source_ 
                    | backend_ 
                    | batch_size_ 
                    | crop_size_ 
                    | mirror_ 
                    | channels_ 
                    | height_
                    | width_ 
                    | mean_ 
                    | std_ 
                    | value_
                    | data_param_
                    | transform_param_
                    | memory_data_param_
                    ;

        phase_          = tok.phase_    [PrintStr(*ptb)] >> ':' >> str_identifier [PrintStr(*ptb)];
        name_           = tok.name_     [PrintStr(*ptb)] >> ':' >> str_identifier [PrintStr(*ptb)];
        type_           = tok.type_     [PrintStr(*ptb)] >> ':' >> str_identifier [PrintStr(*ptb)];

		str_identifier  = tok.identifier [_val = _1]
						| string_	[_val = _1]
						;

		string_         = '"' >> tok.identifier >> '"';

		include_        = tok.include_          [PrintStr(*ptb)] >> ':' >> '{' >> phase_ >> '}';
        mean_file_      = tok.mean_file_        [PrintStr(*ptb)] >> ':' >> str_identifier       [PrintStr(*ptb)];
        input_          = tok.input_            [PrintStr(*ptb)] >> ':' >> str_identifier       [PrintStr(*ptb)];
        input_dim_      = tok.input_dim_        [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        dim_            = tok.dim_              [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        alpha_          = tok.alpha_            [PrintStr(*ptb)] >> ':' >> (tok.double_constant  [PrintDouble(*ptb)] | tok.double_exp_constant [PrintStr(*ptb)]); 
        beta_           = tok.beta_             [PrintStr(*ptb)] >> ':' >> (tok.double_constant  [PrintDouble(*ptb)] | tok.double_exp_constant [PrintStr(*ptb)]); 
        top_            = tok.top_              [PrintStr(*ptb)] >> ':' >> str_identifier       [PrintStr(*ptb)];
        bottom_         = tok.bottom_           [PrintStr(*ptb)] >> ':' >> str_identifier       [PrintStr(*ptb)];
        lr_mult_        = tok.lr_mult_          [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        decay_mult_     = tok.decay_mult_       [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        num_output_     = tok.num_output_       [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        kernel_size_    = tok.kernel_size_      [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        stride_         = tok.stride_           [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        local_size_     = tok.local_size_       [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        pool_           = tok.pool_             [PrintStr(*ptb)] >> ':' >> str_identifier       [PrintStr(*ptb)];
        pad_            = tok.pad_              [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        group_          = tok.group_            [PrintStr(*ptb)] >> ':' >> tok.int_constant     [PrintInt(*ptb)];
        dropout_ratio_  = tok.dropout_ratio_    [PrintStr(*ptb)] >> ':' >> (tok.double_constant  [PrintDouble(*ptb)] | tok.double_exp_constant [PrintStr(*ptb)]);
        input_shape_    = tok.input_shape_      [PrintStr(*ptb)] >> '{' >> +input_shape_statements_ >> '}';
        input_shape_statements_ = dim_;
        source_         = tok.source_           [PrintStr(*ptb)] >> ':' >> str_identifier   [PrintStr(*ptb)];
        backend_        = tok.backend_          [PrintStr(*ptb)] >> ':' >> str_identifier   [PrintStr(*ptb)];
        batch_size_     = tok.batch_size_       [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        crop_size_      = tok.crop_size_        [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        mirror_         = tok.mirror_           [PrintStr(*ptb)] >> ':' >> str_identifier   [PrintStr(*ptb)];
        channels_       = tok.channels_         [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        height_         = tok.height_           [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        width_          = tok.width_            [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        mean_           = tok.mean_             [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        std_            =  tok.std_             [PrintStr(*ptb)] >> ':' >> (tok.double_constant [PrintDouble(*ptb)] | tok.double_exp_constant [PrintStr(*ptb)]);
        value_          = tok.value_            [PrintStr(*ptb)] >> ':' >> value_type_;
        value_type_     = tok.int_constant      [PrintInt(*ptb)]
                         | tok.double_constant  [PrintDouble(*ptb)]
                         | tok.double_exp_constant [PrintStr(*ptb)] 
                         ;
        lrn_k_          = tok.lrn_k_        [PrintStr(*ptb)] >> ':' >> tok.int_constant [PrintInt(*ptb)];
        norm_region_    = tok.norm_region_  [PrintStr(*ptb)] >> ':' >> str_identifier   [PrintStr(*ptb)];

        param_            = tok.param_      [PrintStr(*ptb)] >> '{' >> +param_statements_ >> '}';
        param_statements_ = lr_mult_
                           | decay_mult_
                           ;

        weight_filler_  = tok.weight_filler_ [PrintStr(*ptb)] >> '{' >> +weight_filler_statements_ >> '}';
        weight_filler_statements_   = type_
                                     | stride_
                                     | pad_
                                     | mean_    
                                     | std_
                                     | value_
                                     ;   
        
        bias_filler_  = tok.bias_filler_ [PrintStr(*ptb)] >> '{' >> +bias_filler_statements_ >> '}';
        bias_filler_statements_   = type_
                                     | stride_
                                     | pad_
                                     | mean_    
                                     | std_
                                     | value_
                                     ;   

        convolution_param_ = tok.convolution_param_ [PrintStr(*ptb)] >> '{' >> +convolution_param_statements_ >> '}';
        convolution_param_statements_ = num_output_
                                       | kernel_size_
                                       | stride_
                                       | pad_
                                       | group_
                                       | weight_filler_
                                       | bias_filler_
                                       ;           

        lrn_param_  = tok.lrn_param_ [PrintStr(*ptb)] >> '{' >> +lrn_param_statements_ >> '}';
        lrn_param_statements_ = local_size_
                               | alpha_
                               | beta_
                               | weight_filler_
                               | bias_filler_
                               | lrn_k_
                               | norm_region_
                               ; 

        pooling_param_  = tok.pooling_param_ [PrintStr(*ptb)] >> '{' >> +pooling_param_statements_ >> '}';
        pooling_param_statements_   = pool_
                                     | kernel_size_
                                     | stride_
                                     | weight_filler_
                                     | bias_filler_
                                     ; 

        inner_product_param_    = tok.inner_product_param_ [PrintStr(*ptb)] >> '{' >> +inner_product_param_statements_ >> '}';
        inner_product_param_statements_ = num_output_
                                         | pad_
                                         | group_
                                         | weight_filler_
                                         | bias_filler_
                                         ;

        dropout_param_  = tok.dropout_param_ [PrintStr(*ptb)] >> '{' >> +dropout_param_statements_ >> '}';
        dropout_param_statements_ = dropout_ratio_
                                   | num_output_
                                   | pad_
                                   | group_
                                   | weight_filler_
                                   | bias_filler_
                                   ;     

        data_param_ = tok.data_param_ [PrintStr(*ptb)] >> '{' >> +data_param_statements_ >> '}';
        data_param_statements_ = source_
                                | backend_
                                | batch_size_
                                ;

        transform_param_ = tok.transform_param_ [PrintStr(*ptb)] >> '{' >> +transform_param_statements_ >> '}';
        transform_param_statements_ = crop_size_
                                     | mirror_
                                     | mean_file_
                                     ;   

        memory_data_param_  = tok.memory_data_param_ [PrintStr(*ptb)] >> '{' >> +memory_data_param_statements_ >> '}';
        memory_data_param_statements_ = batch_size_
                                       | channels_
                                       | height_
                                       | width_
                                       ;

        layer_  = tok.layer_ [PrintStr(*ptb)] >> '{' >> +layer_statements_ >> '}';
        layer_statements_ = name_
                           | type_
                           | bottom_
                           | top_
                           | include_
                           | param_
                           | convolution_param_
                           | pooling_param_
                           | lrn_param_
                           | inner_product_param_
                           | dropout_param_
                           | data_param_
                           | transform_param_
                           | memory_data_param_
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
                                                     bias_filler_, bias_filler_statements_, source_, backend_, batch_size_, crop_size_, mirror_,
                                                     channels_, height_, width_, mean_, std_, value_, value_type_, data_param_, data_param_statements_,
                                                     transform_param_, transform_param_statements_, memory_data_param_, memory_data_param_statements_,
                                                     lrn_k_, norm_region_   
                                                     ;

    qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > string_;

	qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > str_identifier;

    CaffeParseTreeBuilder*  ptb;
};

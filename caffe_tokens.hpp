#define BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <fstream>
#include <string>

using namespace boost::spirit;
using boost::phoenix::val;

enum token_ids
{
    ID_INT_CONSTANT = 1000,
    ID_DOUBLE_CONSTANT,
    ID_NAME,
    ID_PHASE,
    ID_TYPE,
	ID_INCLUDE,
    ID_MEAN_FILE,
    ID_INPUT,
    ID_INPUT_DIM,
    ID_DIM,
    ID_ALPHA,
    ID_BETA,
    ID_TOP,
    ID_BOTTOM,
    ID_LR_MULT,
    ID_DECAY_MULT,
    ID_NUM_OUTPUT,
    ID_KERNEL_SIZE,
    ID_STRIDE,
    ID_LOCAL_SIZE,
    ID_POOL,
    ID_PAD,
    ID_GROUP,
    ID_DROPOUT_RATIO,
    ID_INPUT_SHAPE,
    ID_PARAM,
    ID_CONVOLUTION_PARAM,
    ID_LRN_PARAM,
    ID_POOLING_PARAM,
    ID_INNER_PRODUCT_PARAM,
    ID_DROPOUT_PARAM,
    ID_WEIGHT_FILLER,
    ID_BIAS_FILLER,
    ID_SOURCE,
    ID_BACKEND,
    ID_BATCH_SIZE,
    ID_CROP_SIZE,
    ID_MIRROR,
    ID_CHANNELS,
    ID_HEIGHT,
    ID_WIDTH,
    ID_MEAN,
    ID_STD,
    ID_VALUE,
    ID_DATA_PARAM,
    ID_TRANSFORM_PARAM,
    ID_MEMORY_DATA_PARAM,
    ID_LAYER,
    ID_IDENTIFIER,
};

template <typename Lexer>
struct caffe_tokens : lex::lexer<Lexer>
{
    caffe_tokens()
    {
        identifier      = "[a-zA-Z_][a-zA-Z0-9_.\\\-\\\/]*";
        int_constant    = "[0-9]+";
        double_constant = "[0-9]+.[0-9]+";
        name_           = "name";
        phase_          = "phase";
        type_           = "type";
        include_        = "include";
        mean_file_      = "mean_file";
        input_          = "input";
        input_dim_      = "input_dim";
        dim_            = "dim";
        alpha_          = "alpha";
        beta_           = "beta";
        top_            = "top";
        bottom_         = "bottom";
        lr_mult_        = "lr_mult";
        decay_mult_     = "decay_mult";
        num_output_     = "num_output";
        kernel_size_    = "kernel_size";
        stride_         = "stride";
        local_size_     = "local_size";
        pool_           = "pool";
        pad_            = "pad";
        group_          = "group";
        dropout_ratio_  = "dropout_ratio"; 
        input_shape_    = "input_shape";
        param_          = "param";
        convolution_param_ = "convolution_param";
        lrn_param_      = "lrn_param";
        pooling_param_  = "pooling_param";
        inner_product_param_    = "inner_product_param";
        dropout_param_  = "dropout_param";
        weight_filler_  = "weight_filler";
        bias_filler_    = "bias_filler";
        layer_          = "layer";
        source_         = "source";
        backend_        = "backend";
        batch_size_     = "batch_size";
        crop_size_      = "crop_size";
        mirror_         = "mirror";
        channels_       = "channels";
        height_         = "height";
        width_          = "width";
        mean_           = "mean";
        std_            = "std";
        value_          = "value";
        data_param_     = "data_param";
        transform_param_ = "transform_param";
        memory_data_param_ = "memory_data_param";

        this->self = lex::token_def<>('(') | ')' | '{' | '}' | '=' | ';' | ':' | '"' | '"';

        this->self.add
            (int_constant, ID_INT_CONSTANT)
            (double_constant, ID_DOUBLE_CONSTANT)
            (name_, ID_NAME)
            (phase_, ID_PHASE)
            (type_, ID_TYPE)
			(include_, ID_INCLUDE)
            (mean_file_, ID_MEAN_FILE)
            (input_, ID_INPUT)
            (input_dim_, ID_INPUT_DIM)
            (dim_, ID_DIM)
            (alpha_, ID_ALPHA) 
            (beta_, ID_BETA)
            (top_, ID_TOP)
            (bottom_, ID_BOTTOM)
            (lr_mult_, ID_LR_MULT)
            (decay_mult_, ID_DECAY_MULT)
            (num_output_, ID_NUM_OUTPUT)
            (kernel_size_, ID_KERNEL_SIZE)
            (stride_, ID_STRIDE)
            (local_size_, ID_LOCAL_SIZE)
            (pool_, ID_POOL)
            (pad_, ID_PAD)
            (group_, ID_GROUP)
            (dropout_ratio_, ID_DROPOUT_RATIO) 
            (input_shape_, ID_INPUT_SHAPE)
            (param_, ID_PARAM)
            (convolution_param_, ID_CONVOLUTION_PARAM)
            (lrn_param_, ID_LRN_PARAM)
            (pooling_param_, ID_POOLING_PARAM)
            (inner_product_param_, ID_INNER_PRODUCT_PARAM)
            (dropout_param_, ID_DROPOUT_PARAM)
            (layer_, ID_LAYER)
            (weight_filler_, ID_WEIGHT_FILLER)
            (bias_filler_, ID_BIAS_FILLER)
            (source_, ID_SOURCE)
            (backend_, ID_BACKEND)
            (batch_size_, ID_BATCH_SIZE)
            (crop_size_, ID_CROP_SIZE)
            (mirror_, ID_MIRROR)
            (channels_, ID_CHANNELS)
            (height_, ID_HEIGHT)
            (width_, ID_WIDTH)
            (mean_, ID_MEAN)
            (std_, ID_STD)
            (value_, ID_VALUE)
            (data_param_, ID_DATA_PARAM)
            (transform_param_, ID_TRANSFORM_PARAM)
            (memory_data_param_, ID_MEMORY_DATA_PARAM)
            (identifier, ID_IDENTIFIER)
        ;

        this->self("WS") 
            =   lex::token_def<>("[ \\t\\n]+") 
            |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"
            ;
    }

    lex::token_def<std::string> identifier, name_, phase_, type_, include_, mean_file_, input_, input_dim_, dim_,
                                alpha_, beta_, top_, bottom_, lr_mult_, decay_mult_, num_output_, kernel_size_,
                                stride_, local_size_, pool_, pad_, group_, dropout_ratio_, input_shape_, param_, 
                                convolution_param_, lrn_param_, pooling_param_, inner_product_param_, dropout_param_,
                                layer_, weight_filler_, bias_filler_, source_, backend_, batch_size_, crop_size_, mirror_,
                                channels_, height_, width_, mean_, std_, value_, data_param_, transform_param_,
                                memory_data_param_
                                ;
    lex::token_def<unsigned int> int_constant;
    lex::token_def<double> double_constant;
};

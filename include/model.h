// include guard
#ifndef __MODEL_H_INCLUDED__
#define __MODEL_H_INCLUDED__

#include <dlib/dnn.h>
#include <opencv2/opencv.hpp>


template <
    int N, // Number of convolutions
    typename SUBNET // Subnetwork
    > 
using layer = dlib::max_pool<2,2,2,2, dlib::relu<dlib::con<N,2,2,1,1,SUBNET>>>;

template<
    int nbClasses
    >
using my_conv_net = dlib::loss_multiclass_log<
                        dlib::softmax<dlib::fc<nbClasses, // Output layer with "softmax" activation function 
                        // dlib::dropout< // Dropout with probability(drop rate) = 0.5
                        dlib::relu<
                        dlib::fc<1024, // Fully connected neural network of 1024 neurons with "relu" activation function
                        layer<512,
                        layer<256,
                        layer<128,
                        layer<64,
                        dlib::input<std::vector<cv::Mat>>
                        >>>>>>>>>;

#endif //__MODEL_H_INCLUDED__
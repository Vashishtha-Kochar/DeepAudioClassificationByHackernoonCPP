// // -*- coding: utf-8 -*-

// // from __future__ import absolute_import
// // from __future__ import division
// // from __future__ import print_function

// // import os
// // from PIL import Image
// // from random import shuffle
// // import numpy as np
// // import pickle

// // from imageFilesTools import getImageData
// // from config import datasetPath
// // from config import slicesPath
# include<string>
# include<map>
#include <dlib/dnn.h>
#include "config.h"
        
//Creates and save dataset from slices
void createDatasetFromSlices(int nbPerGenre, std::vector<std::string> genres){

    // Iterate through all genres and seprate files for training, validation and testing into appropriate paths
    for(std::vector<std::string>::iterator genre = genres.begin(); genre < genres.end(); genre++)
    {
        // Create target directory if it doesn't exist
        int i = 0;
        fs::path temp( trainDatasetPath + (*genre) );
        if( fs::is_directory( temp) )
        {
            std::cout<<"\nDirectory already exists : " + trainDatasetPath + (*genre) + " Contents may be overwritten.";
        }
        else
        {   
            // Make the directory
            fs::create_directory(trainDatasetPath + (*genre));
            fs::create_directory(validationDatasetPath + (*genre));
            fs::create_directory(testDatasetPath + (*genre));
            std::cout<<"\nDirectories created : " + trainDatasetPath + (*genre) + "\t" + validationDatasetPath + (*genre) + "\t" + testDatasetPath + (*genre) + "\nContents may be overwritten.";
        }
        for ( fs::recursive_directory_iterator iter(slicesPath + (*genre) ); iter!=fs::recursive_directory_iterator(); ++iter)
        {
            std::string toPath = "";
            if ( i < nbPerGenre*(1-validationRatio - testRatio) ) 
                toPath = trainDatasetPath + (*genre) + '/' + (iter->path().filename()).string();
            else if ( i < nbPerGenre*(1-testRatio) )
                toPath = validationDatasetPath + (*genre) + '/' + (iter->path().filename()).string();
            else if (i < nbPerGenre)
                toPath = testDatasetPath + (*genre) + '/' + (iter->path().filename()).string();
            else
                break;
            fs::copy_file(iter->path(), toPath);
            std::cout<<"\nCopied " + (iter->path()).string() + " -> " + toPath;
            i++;
        }
    }
}
// //Loads dataset
// //Mode = "train" or "test"
std::map<std::string, std::vector<cv::Mat> > getDataset(int nbPerGenre, std::string mode, std::vector<std::string> genres)
{
    std::map<std::string, std::vector<cv::Mat> > dataset;
    std::string myDatasetPath = "";
    
    // TODO: find a way to save the dataset for reloading later so you only have to load dataset once
    if(mode == "train")
    {
        myDatasetPath = trainDatasetPath;
    }
    else if (mode == "validation")
    {
        myDatasetPath = validationDatasetPath;
    }
    else if (mode == "test")
    {
        myDatasetPath = testDatasetPath;
    }

    // Check if train directory is empty
    fs::directory_iterator temp(myDatasetPath), end;
    if( temp == end )
    {
        // There are no files in the directory
        std::cout<<"\nCreating the datasets.";
        createDatasetFromSlices(nbPerGenre, genres);
    }
    else
    {   
        std::cout<<"\nDirectory already contains files : " + trainDatasetPath;
    }
    std::cout<<"\n[+] Loading " +mode +" dataset... ";

    for(std::vector<std::string>::iterator genre = genres.begin(); genre < genres.end(); genre++)
    {
        std::vector<cv::Mat> images_of_genre;
        std::cout<<"\nAddding genre "<<(*genre);

        // Iterate and load the images from the appropriate dataset path
        for ( fs::recursive_directory_iterator iter(myDatasetPath+ (*genre) ); iter!=fs::recursive_directory_iterator(); ++iter)
        {
            std::string filename = (iter->path().filename()).string();
            cv::Mat img = cv::imread( (iter->path()).string() );
            images_of_genre.push_back(img);
        }
        dataset.insert({*genre, images_of_genre});
    }
    std::cout<<"\n"+ mode + " dataset loaded! ✅";
    return dataset;
}


// Import Pillow:
// from PIL import Image
// import os.path
# include <string>
# include <boost/filesystem.hpp>
# include <iostream>
# include <boost/gil/gil_all.hpp>
# include <dlib/image_io.h>
# include <opencv2/opencv.hpp>


namespace fs = boost::filesystem;
// from config import spectrogramsPath, slicesPath


// Creates slices from spectrogram
// TODO Improvement - Make sure we don't miss the end of the song
void sliceSpectrogram(std::string filename, int desiredSize)
{
	std::string spectrogramsPath = "../Data/Spectrograms/";
	std::string slicesPath = "../Data/Slices/";
	std::string slicePath;
	
	std::string genre = filename.substr( 0, filename.find('_') ); 	// Ex. Dubstep_19.png

	// Load the full spectrogram
	cv::Mat img = cv::imread( spectrogramsPath + filename );

	// Compute approximate number of 128x128 samples
	int height = img.size().height;
	int width = img.size().width;
	std::cout<<"\nSize of image : "<<height<<" X "<<width;
	// width, height = img.size
	int nbSamples = int(width/desiredSize);

	// Create path for the genre if not existing
	slicePath = slicesPath +genre + "/";
	fs::path temp(slicePath);
    if( fs::exists( temp) )
    {
        std::cout<<"\nDirectory already exists : " + slicePath + " Contents may be overwritten.";
    }
    else
    {   
        // Make the directory
        fs::create_directory(slicePath);
    }

	// For each sample crop the image and save the slice
	for(int i = 0; i < nbSamples; i++)
	{
		// dlib::array2d<dlib::rgb_pixel> slicedImg;
		int sliceNumber = i+1;
		std::cout<<"\nCreating slice: " + std::to_string(sliceNumber) +"/" + std::to_string(nbSamples) +" for " + filename;
		// Extract and save 128x128 sample
		int startPixel = i*desiredSize;
		cv::Rect croppedRectangle = cv::Rect(startPixel , 0, desiredSize, desiredSize);
		cv::Mat croppedImage = img(croppedRectangle);
		cv::imwrite( slicePath + filename.substr(0, filename.length()-4) + "_" + std::to_string(i) + ".png", croppedImage );
	}
}

// Slices all spectrograms
void createSlicesFromSpectrograms(std::string spectrogramsPath, int desiredSize)
{
	for (fs::recursive_directory_iterator iter(spectrogramsPath); iter!=fs::recursive_directory_iterator(); ++iter)
    {
        // First identify all the files
        std::string filename = (iter->path().filename()).string();
        std::string toMatch = ".png";
        if(filename.compare(filename.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        {
            sliceSpectrogram(filename,desiredSize);
        }
        else
        {
            std::cout<<"\nFile is not png. : "<<filename;
            continue;
        }
    }		
}

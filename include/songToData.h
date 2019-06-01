// include guard
#ifndef __SONGTODATA_H_INCLUDED__
#define __SONGTODATA_H_INCLUDED__

# include "audioFilesTools.h"
# include "sliceSpectrogram.h"
# include <iostream>
# include <map>
# include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// Create spectrogram from mp3 files, returns status
void createSpectrogram(std::string filename, std::string newFilename)
{
    // TODO : the following must be syncronised with main by taking parameters or shared resources
    std::string rawDataPath = "../Data/Raw/";
    std::string tempDataPath = "../Data/Tmp/";
    std::string spectrogramsPath = "../Data/Spectrograms/";
    std::string pixelPerSecond = "50";

    std::string command;
    // std::cout<<"\nChecking file : "<<rawDataPath+filename;
	// Create temporary mono track if needed
	if(isMono(rawDataPath+filename))
    {
		// Copy the file as is
		command = "cp "+ rawDataPath+filename + " "+ tempDataPath+newFilename;
    }
    else
	{
        // Creates a mono(single channel) output file which is a mix-down of input channels 1 and 2
		command = "sox " + rawDataPath+filename + " "+ tempDataPath+newFilename +" remix 1,2";
    }
    // std::cout << "\nExecuting command : " <<command;
	int status = system(command.c_str());
    if (status < 0)
    {
        std::cerr << "\nError: Couldn't execute command : " <<command;
        // return -1;
    }
    else
    {
        if (WIFEXITED(status))
        {
            // std::cout << "\nCommand returned normally " + command + "   Exit code " << WEXITSTATUS(status);
        }
        else
        {
           std::cout << "\nCommand exited abnormaly : " + command;
        //    return -1;
        }
    }

	filename = newFilename;
    newFilename = newFilename.substr(0, newFilename.find(".mp3")) + ".png";
	// Create monochrome(-m) raw spectrogram(-r) with resolution of (pixelPerSecond by 200) pixels in size (-X, -Y)
	//  Raw spectrogram : suppress the display of axes and legends
	command = "sox " + tempDataPath + filename + " -n spectrogram -Y 200 -X " + pixelPerSecond + " -m -r -o " + spectrogramsPath+newFilename;
	
    status = system(command.c_str());
    if (status < 0)
    {
        std::cerr << "\nError: Couldn't execute command : " <<command;
        // return -1;
    }
    else
    {
        if (WIFEXITED(status))
        {
            //std::cout << "\nCommand returned normally " + command + "   Exit code " << WEXITSTATUS(status);
        }
        else
        {
           std::cout << "\nCommand exited abnormaly : " + command;
        //    return -1;
        }
    }

    // return 0;
}

// Creates .png whole spectrograms from mp3 files
void createSpectrogramsFromAudio(std::string rawDataPath ,std::string spectrogramPath){
	std::map<std::string, int> genresID;
    // struct stat info;
    // int index = 0;

    // Create directory if it does not exist
    fs::path temp(spectrogramPath);
    if( fs::exists( temp) )
    {
        std::cout<<"\nDirectory already exists : " + spectrogramPath + " Contents may be overwritten.";
    }
    else
    {   
        // Make the directory
        fs::create_directory(spectrogramPath);
    }

    for (fs::recursive_directory_iterator iter(rawDataPath); iter!=fs::recursive_directory_iterator(); ++iter)
    {
        // First identify all the files
        std::string filename = (iter->path().filename()).string();
        std::string toMatch = ".mp3";
        if(filename.compare(filename.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        {
            // std::cout<<"\nCreating spectrogram for file "<< index+1<<"/"<<nbFile<<"...";
            std::cout<<"\nCreating spectrogram for file : "<< filename;
            std::string fileGenre = getGenre(rawDataPath+filename);
            if ( genresID.find(fileGenre) == genresID.end() )
            {
                // not found
                genresID[fileGenre] = 1;
            } 
            else 
            {
                // found
                genresID[fileGenre] = genresID[fileGenre] + 1;
            }
            int fileID = genresID[fileGenre];
            std::string newFilename = fileGenre+"_"+std::to_string(fileID)+".mp3";
            createSpectrogram(filename,newFilename);
        }
        else
        {
            std::cout<<"\nFile is not mp3. : "<<filename;
            continue;
        }
    }
}

// Whole pipeline .mp3 -> .png slices
void createSlicesFromAudio(std::string rawDataPath ,std::string spectrogramPath, std::string slicesPath)
{
    int desiredSize = 128;
	std::cout<<"\nCreating spectrograms...";
	createSpectrogramsFromAudio(rawDataPath, spectrogramPath);
	std::cout<<"\nSpectrograms created!";

	std::cout<<"\nCreating slices...";
	createSlicesFromSpectrograms(spectrogramPath, desiredSize);
	std::cout<<"\nSlices created!";
}

#endif // __SONGTODATA_H_INCLUDED__

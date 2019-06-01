// include guard
#ifndef __CLASSIFY_H_INCLUDED__
#define __CLASSIFY_H_INCLUDED__

# include <taglib/fileref.h>
# include <boost/filesystem.hpp>

// Function to add genre data to file
void classifyGenres(std::string path)
{
    namespace fs  = boost::filesystem;
    int i = 1;
    for (fs::recursive_directory_iterator entry(path); entry!=fs::recursive_directory_iterator(); ++entry)
    {
        // First identify all the files
        std::string file = entry->path().string();
        std::string toMatch = ".mp3";
        if(file.compare(file.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        {
            TagLib::FileRef f( file.c_str());
            std::string genre = (f.tag() -> genre()).toCString();
            if(genre.empty())
            {
                genre = file.substr(0, file.find("."));
                f.tag() -> setGenre(genre);
                std::cout<<"\nAssigning " + genre + " genre to "<<file;
            }
            else
            {
                std::cout<<"\n["<<i<<"] "<<file<<" has " + genre + " genre";
                i++;
            }

            if(!f.save())
            {
                std::cout<<"Error in saving tag for the file : "<<file;
            }
        }
        else
        {
            std::cout<<"\nFile is not mp3. : "<<file;
            continue;
        }
    }
}

#endif // __CLASSIFY_H_INCLUDED__
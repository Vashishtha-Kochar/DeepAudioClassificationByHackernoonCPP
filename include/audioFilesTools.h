// include guard
#ifndef __AUDIOFILESTOOLS_H_INCLUDED__
#define __AUDIOFILESTOOLS_H_INCLUDED__

# include <string>
# include <taglib/fileref.h>
# include <taglib/audioproperties.h>
# include <taglib/tag.h>

bool isMono(std::string filename)
{
    TagLib::FileRef file(filename.c_str());
    int noOfChannels = file.audioProperties() -> channels();
    return (noOfChannels == 1);
}

std::string getGenre(std::string filename)
{
    TagLib::FileRef file(filename.c_str());
    std::string genre = (file.tag() -> genre()).toCString();
    return genre;
}

#endif // __AUDIOFILESTOOLS_H_INCLUDED__
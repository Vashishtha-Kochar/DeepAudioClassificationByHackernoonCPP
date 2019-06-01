# How to use
1. Create the folders **bin**, **build** and **Data**. Also create the subdirectories as specified in the directory structure

2. Store the mp3 files to **Raw** subdirectory in the **Data** folder

# The directory structure:
1. **src** : has all the source(cpp) files

2. **include** : has all the header files

3. **bin** : has the output

4. **build** : has the cmake build files

5. **Data** : stores all the data
    
    a. **Dataset** : Stores the seprated datasets for training, validation and testing.

    b. **Raw** : Stores the raw mp3 files

    c. **Slices** : Stores sliced spectrogram images corresponding to every genre in dataset

    d. **Spectrograms** : Stores the spectrogram images for all the files
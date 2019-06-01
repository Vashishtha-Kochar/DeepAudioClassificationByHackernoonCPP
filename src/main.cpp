# include <string>
# include <vector>
# include <iostream>
# include <fstream>
# include <algorithm>
# include <map>
# include <audioFilesTools.h>
# include "classify.h"
# include "songToData.h"
# include "model.h"
# include "datasetTools.h"

using namespace std;
namespace fs = boost::filesystem;

// This function takes the filename (Relative path) of the config file
std::map<string, string> parseConfigFile(string filename)
{
    ifstream config_file (filename , ios::in);
    map<string, string> configs;
    string line;
    while( getline(config_file, line) )
    {
        string key, value;
        key = line.substr(0, line.find("="));
        value =  line.substr(line.find("=")+1);
        configs.insert({key,value});
    }
    return configs;
}

int main(int argc, char** argv)
{
    vector<string> arguements;
    map<string, string> parameters;

    // Convert command line arguements to vector of string omitting the first element
    for(int i = 1; i < argc; i++ ){
        arguements.push_back( string(argv[i]) );
    }

    // Parse the config file
    parameters = parseConfigFile("config.txt"); 

    // Displayig stats of the model
    cout<<"\n--------------------------";
    cout<<"\n| ** Config ** ";
    cout<<"\n| Validation ratio: "<<parameters["validationRatio"];
    cout<<"\n| Test ratio: "<<parameters["testRatio"];
    cout<<"\n| Slices per genre: "<<parameters["filesPerGenre"];
    cout<<"\n| Slice size: "<<parameters["sliceSize"];
    cout<<"\n--------------------------";


    /* Possible arguements that can be passed : 
        "--classify" : classify
        "--slice" : slice
        "--train" : train
        "--test" : test
    */
    
   // Check if train is passed
    if( find(arguements.begin(), arguements.end(), "--classify") != arguements.end() )
    {
        std::cout<<"\nClassifying genres";
        classifyGenres(parameters["rawDataPath"]);
	    return 0;
    }
    if(find(arguements.begin(), arguements.end(), "--slice") != arguements.end())
    {
        createSlicesFromAudio ( parameters["rawDataPath"] , parameters["spectrogramsPath"], parameters["slicesPath"] );
        return 0;
    }


    // List genres
    std::vector<std::string> genres;
    int nbGenres = 0;
    for (fs::recursive_directory_iterator iter(parameters["slicesPath"]); iter!=fs::recursive_directory_iterator(); ++iter)
    {
        if (fs::is_directory(iter->path()))
        {
            std::string genre = (iter->path().filename()).string();
            genres.push_back(genre);
            nbGenres++;
        }
    }
    
    if(nbGenres != 10){
        // Some error
        std::cout<<"\nThere must be only 10 genres";
        return 0;
    }

    // Create model 
    // my_conv_net<10> net;
    // dlib::dnn_trainer<my_conv_net<10>> trainer(net);
    // trainer.set_learning_rate(std::stod(parameters["learningRate"]));
    // trainer.set_min_learning_rate(std::stod(parameters["learningRate"])/1000);
    // trainer.set_mini_batch_size(std::stoi(parameters["batchSize"]));
    // trainer.set_max_num_epochs(std::stoi(parameters["nbEpoch"]));
    // trainer.be_verbose();

    // // // ask the trainer to save its state to a file named "mnist_sync" every 20 seconds.
    // trainer.set_synchronization_file("deepAudioClassify", std::chrono::seconds(20));
    
    if(find(arguements.begin(), arguements.end(), "--train") != arguements.end())
    {
        //get the dataset
        // std::vector<cv::Mat> training_images;
        // std::vector<std::string> training_labels;
        // std::map<std::string, std::vector<cv::Mat> > training_data = getDataset(1000, "train", genres);

        // // Convert the map into seprate vectors for training the data
        // for(std::map<std::string, std::vector<cv::Mat> >::iterator it_training_data = training_data.begin(); it_training_data != training_data.end(); it_training_data++)
        // {
        //     training_images.insert(training_images.end(),(it_training_data->second).begin(),(it_training_data->second).end());
        //     training_labels.insert(training_labels.end(), (it_training_data->second).size() ,  (it_training_data->first) );
        // }
        // // This line begins training.  By default, it runs SGD with our specified
        // // learning rate until the loss stops decreasing.  Then it reduces the learning rate by
        // // a factor of 10 and continues running until the loss stops decreasing again.  It will
        // // keep doing this until the learning rate has dropped below the min learning rate
        // // defined above or the maximum number of epochs as been executed
        // trainer.train(training_images, training_labels);

        // // Save the net. But, net will have a bunch of state in it related to the last batch of images it processed. So, we clean it
        // net.clean();
        // dlib::serialize("mnist_network.dat") << net;
        // // if we later wanted to recall the network from disk we can simply say: deserialize("mnist_network.dat") >> net;

        // // Find accuracy on train data
        // std::vector<unsigned long> predicted_labels = net(training_images);
        // int num_right = 0;
        // int num_wrong = 0;
        // // And then let's see if it classified them correctly.
        // for (size_t i = 0; i < training_images.size(); ++i)
        // {
        //     if (predicted_labels[i] == training_labels[i])
        //         ++num_right;
        //     else
        //         ++num_wrong;
            
        // }
        // cout << "training num_right: " << num_right << endl;
        // cout << "training num_wrong: " << num_wrong << endl;
        // cout << "training accuracy:  " << num_right/(double)(num_right+num_wrong) << endl;
    }
    if(find(arguements.begin(), arguements.end(), "--test") != arguements.end())
    {
        // Find accuracy on test data
        // std::vector<unsigned long> predicted_labels = net(testing_images);
        // int num_right = 0;
        // int num_wrong = 0;
        // for (size_t i = 0; i < testing_images.size(); ++i)
        // {
        //     if (predicted_labels[i] == testing_labels[i])
        //         ++num_right;
        //     else
        //         ++num_wrong;
            
        // }
        // cout << "testing num_right: " << num_right << endl;
        // cout << "testing num_wrong: " << num_wrong << endl;
        // cout << "testing accuracy:  " << num_right/(double)(num_right+num_wrong) << endl;

    }
    //Error handling
    if(argc == 1)
    {
        cerr<<"\nError : Too less arguements. Choose among \"--clasify\", \"--slice\", \"--train\", \"--test\"";
    }
    // TODO : If passed some other arguement
    // else
    // {
    //     cerr<<"Error : Wrong arguements passed. Choose among \"--clasify\", \"--slice\", \"--train\", \"--test\"";
    // }
    
    cout<<"\n";
    
    return 0;
}
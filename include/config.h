// include guard
#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__
#include<string>

const std::string spectrogramsPath="../Data/Spectrograms/";
const std::string slicesPath="../Data/Slices/";
const std::string datasetPath="../Data/Dataset/";
const std::string trainDatasetPath="../Data/Dataset/Training/";
const std::string validationDatasetPath="../Data/Dataset/Validation/";
const std::string testDatasetPath="../Data/Dataset/Testing/";
const std::string rawDataPath="../Data/Raw/";
const std::string tempDataPath="../Data/Tmp/";
const int pixelPerSecond=50;
const int sliceSize=128;
const int filesPerGenre=10;
const float validationRatio=0.3;
const float testRatio=0.1;
const int batchSize=128;
const float learningRate=0.001;
const int nbEpoch=5;

#endif
#!/bin/bash
set -e
# Any subsequent(*) commands which fail will cause the shell script to exit immediately
cd build
cmake ..
cmake --build . --config Release
cd ../bin
./DeepAudioClassificationByHackernoonCPP --slice
cd ..
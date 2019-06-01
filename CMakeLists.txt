cmake_minimum_required(VERSION 3.12.0 FATAL_ERROR)
# Every project needs a name
set (PROJECT_NAME "DeepAudioClassificationByHackernoonCPP")
project(${PROJECT_NAME})


# Declaring the directory structure
SET (BUILD_PNG ON) 
set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
set (MAIN_FILE ${PROJECT_SOURCE_DEFINITION_DIRECTORY}/main.cpp)

# Set options used by "CMake".
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Tell cmake we will need dlib.  This command will pull in dlib and taglib, and compile it
# into your project.
add_subdirectory(../libraries/dlib-19.17 dlib_build)
add_subdirectory(../libraries/taglib-1.11.1 taglib_build)

if(WIN32)
  set(OpenCV_DIR "d:/libs/opencv-2.4.8/build")
else()
  set(OpenCV_DIR "/usr/lib/opencv")
endif()

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})
# INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(Boost COMPONENTS filesystem REQUIRED)
if (Boost_FOUND)
  # From the offical documentation:
  # Add include directories to the build. [...] If the SYSTEM option is given,
  # the compiler will be told the directories are meant as system include
  # directories on some platforms (signalling this setting might achieve effects
  # such as the compiler skipping warnings [...])."
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})

  # From the offical documentation:
  # "Specify directories in which the linker will look for libraries. [...] Note
  # that this command is rarely necessary. Library locations returned by
  # find_package() and find_library() are absolute paths. Pass these absolute
  # library file paths directly to the target_link_libraries() command. CMake
  # will ensure the linker finds them."
  #link_directories (${Boost_LIBRARY_DIRS})
endif ()
# The next thing we need to do is tell CMake about the code you want to
# compile.

include_directories (${PROJECT_SOURCE_DECLARATION_DIRECTORY})

# "Add an executable to the project using the specified source files."
add_executable (${PROJECT_NAME} ${MAIN_FILE})
# "Link a target to given libraries."
# target_link_libraries(main Boost::filesystem )
target_link_libraries (${PROJECT_NAME} Boost::filesystem)
target_link_libraries(${PROJECT_NAME} dlib)
target_link_libraries(${PROJECT_NAME} -lpthread -lX11 -ltag)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} png)
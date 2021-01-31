# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# init_qt: Let's do the CMake job for us
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(USE_OPENCV_V4L2 ON)

# Define project name
project(irstereo)

OPTION(USE_CPU_ONLY
	"Build the project using cpu only"
OFF)

IF(USE_CPU_ONLY)
	add_definitions("-DUSE_CPU_ONLY")
endif(USE_CPU_ONLY)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(Qt5 REQUIRED Widgets)
find_package(OpenCV REQUIRED)
find_package(PCL 1.8 REQUIRED)

if(NOT USE_CPU_ONLY)
find_package(CUDA REQUIRED)
endif(NOT USE_CPU_ONLY)

include_directories(${PCL_INCLUDE_DIRS} "/usr/local/include")

if(NOT USE_CPU_ONLY)
INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
endif(NOT USE_CPU_ONLY)

add_definitions(${PCL_DEFINITIONS})

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} "main.cpp" "maindialog.cpp" "capturethread.cpp"
	"calibdialog.cpp" "canvas.cpp" "jpegdecode.cpp" "v4l2capture.cpp" "utils.cpp")

# Link your application with OpenCV libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets ${OpenCV_LIBS} ${PCL_LIBRARIES} -lturbojpeg)


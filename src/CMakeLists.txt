cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

#wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

#AudioFile
find_path(AUDIO_LIBRARY AudioFile.h)
include_directories(${AUDIO_LIBRARY})

#Armadillo
find_package(BLAS REQUIRED NAMES OpenBLAS)

find_path(ARMADILLO_LIBRARY armadillo)
include_directories(${ARMADILLO_LIBRARY})

add_executable(pozakres main.cpp melody.cpp
        ../include/melody.hpp ../include/noise.hpp ../include/markov.hpp ../include/oscillator.hpp ../include/random.hpp ../include/wave.hpp)
target_link_libraries(pozakres ${OpenBLAS_LIBRARIES})
target_link_libraries(pozakres ${wxWidgets_LIBRARIES})

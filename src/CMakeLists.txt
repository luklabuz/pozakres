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

set(SRC_FILES
        main.cpp melody.cpp
        player.cpp instrument.cpp piece.cpp filter.cpp random.cpp detail.cpp application.cpp)

if(WIN32)
    list(APPEND SRC_FILES resource.rc)
endif()

add_executable(pozakres ${SRC_FILES})
target_link_libraries(pozakres ${OpenBLAS_LIBRARIES})
target_link_libraries(pozakres ${wxWidgets_LIBRARIES})

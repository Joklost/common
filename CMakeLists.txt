cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_CXX_STANDARD 14)
project(common VERSION 1.0)

add_library(common src/strings.cpp src/helpers.cpp)
set_property(TARGET common PROPERTY POSITION_INDEPENDENT_CODE ON)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(common PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src test)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS common EXPORT CommonLibraryConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from install directory.
install(EXPORT CommonLibraryConfig DESTINATION cmake)

# This makes the project importable from the build directory
export(TARGETS common FILE CommonLibraryConfig.cmake)


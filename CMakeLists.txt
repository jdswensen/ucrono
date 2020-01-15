cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Package hunter
include("cmake-modules/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(ucrono)

# Import cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

# Get git tags and set lib version
include(SetSharedLibVersion)

# Use GNUInstallDirs to install libraries into correct
# locations on multiple platforms
include(GNUInstallDirs)

# Debug build
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug build")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS} -g -O0 -DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
    if (COVERAGE MATCHES ON)
        message(STATUS "Coverage enabled")
        find_package(PythonInterp)
        set(CMAKE_COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage --coverage")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_COVERAGE_FLAGS}")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_COVERAGE_FLAGS}")
    endif()
else()
    message(STATUS "Release build")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

# Define source files for library
set(UCRONO_SRC src/ucrono.c)
set(UCRONO_INC src)

set(LIBRARY_SRC
${UCRONO_SRC}
)

add_library(ucrono STATIC ${LIBRARY_SRC})

# Define header files for library
target_include_directories(ucrono PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${UCRONO_INC} libs/uthash/include
)

# Link libraries
target_link_libraries(ucrono ${LIBRARY_LINKS})
set_target_properties(ucrono
    PROPERTIES
    VERSION ${GENERIC_LIB_VERSION}
    SOVERSION ${GENERIC_LIB_SOVERSION}
)

# Install library to GNU locations
install(TARGETS ucrono EXPORT ucrono-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Add examples
set(callback_src 
examples/callback.c
)

add_executable(callback ${callback_src})
target_link_libraries(callback ucrono)
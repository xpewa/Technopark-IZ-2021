add_library(lib_static STATIC src/lib_static.c)
target_include_directories(lib_static PUBLIC include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
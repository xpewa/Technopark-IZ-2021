add_library(lib_shared SHARED src/lib_shared.c)
target_include_directories(lib_shared PUBLIC ../include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
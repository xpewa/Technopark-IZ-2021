if(BUILD_TESTS)
    add_library(test_stress_static src/test_stress_static.c)
    target_link_libraries(test_stress_static PRIVATE lib_static)
    target_include_directories(test_stress_static PUBLIC include)

    add_library(test_stress_shared src/test_stress_shared.c)
    target_link_libraries(test_stress_shared PRIVATE lib_shared)
    target_include_directories(test_stress_shared PUBLIC include)
endif()
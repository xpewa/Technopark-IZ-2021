add_executable(static_test test_lib_static.cpp)
target_link_libraries(static_test GTest::Main lib_static)

add_test(NAME static_test COMMAND static_test)
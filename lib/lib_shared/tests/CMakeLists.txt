add_executable(shared_test test_lib_shared.cpp)
target_link_libraries(shared_test GTest::Main lib_shared)

add_test(NAME shared_test COMMAND shared_test)
add_executable(tests test_main.cpp)
target_link_libraries(tests PRIVATE engine)
add_test(NAME smoke COMMAND tests)

add_executable(sst main.cpp)
target_include_directories(sst PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sst PRIVATE engine)

add_executable(vector_test main.c)
target_link_libraries(vector_test PRIVATE vector)
add_test(NAME LibraryUnitTests COMMAND vector_test)

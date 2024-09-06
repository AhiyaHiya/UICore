
enable_testing()

add_executable(tests
    main_test.cpp
)

target_link_libraries(tests UICore)

add_test(NAME UICoreTests COMMAND tests)
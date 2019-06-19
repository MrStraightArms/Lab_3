cmake_minimum_required(VERSION 2.8.8)

set(CPP
	test_main.cpp
	)

add_executable(main ${CPP})

target_link_libraries(main PUBLIC Calculator_class)
target_link_libraries(main PUBLIC gtest)
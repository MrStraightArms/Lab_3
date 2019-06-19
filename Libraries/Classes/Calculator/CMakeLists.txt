cmake_minimum_required(VERSION 2.8.8)

set(CPP
	Calculator.cpp
	)

set(HPP
	Calculator.hpp
	)

add_library(Calculator_class STATIC ${CPP} ${HPP})
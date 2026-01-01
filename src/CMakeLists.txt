cmake_minimum_required(VERSION 3.23)
project(KASMCompiler)
add_executable(KASMCompiler)
target_sources(KASMCompiler
	PRIVATE	
		main.c
)
target_link_libraries(KASMCompiler m)


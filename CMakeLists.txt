cmake_minimum_required(VERSION 3.16)
project(fox_ctf C)

set(CMAKE_C_STANDARD 11)

include_directories(c_programs)

add_executable(b32
		c_programs/b32_encoder.c)
add_executable(b64
		c_programs/b64_encoder.c)

add_executable(givemethepin
		c_programs/givemethepin-edited.c)

add_executable(givemethestring
	c_programs/givemethestring-edited.c)

add_executable(select_flag
		c_programs/select_the_flag_array.c)

add_executable(flag_exchanger
		c_programs/flag_exchanger.c)
cmake_minimum_required(VERSION 2.6)
project(ass1-52)

#Something about gplink

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

set(PIC_FLAGS "-mpic14 -p12f675")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PIC_FLAGS}")

set(ASS1_HEADERS
)

set(ASS1_SRCS
	${GAME2_HEADERS}
	src/ass1-52.c
)

add_executable(ass1-52 ${ASS1_SRCS})
cmake_minimum_required(VERSION 3.5)

project(DokuWiki LANGUAGES CXX)

find_package(XMLRPC REQUIRED c++2 client)

set(dokuwiki_headers
	include/dokuwiki.h
	source/dokuwiki.impl.h
)

set(dokuwiki_sources
	source/dokuwiki.impl.cpp
	source/dokuwiki.cpp
)

add_library(${PROJECT_NAME}
	${dokuwiki_headers}
	${dokuwiki_sources}
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		include
	PRIVATE
		${XMLRPC_INCLUDE_DIRS}
)

target_compile_features(${PROJECT_NAME} 
	PUBLIC 
		cxx_std_17
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		${XMLRPC_LIBRARIES}
)


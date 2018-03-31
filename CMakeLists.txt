cmake_minimum_required(VERSION 3.6)

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

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		include
	PRIVATE
		${XMLRPC_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		${XMLRPC_LIBRARIES}
)


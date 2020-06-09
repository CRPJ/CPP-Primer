cmake_minimum_required(VERSION 3.16)
project(query)

set(CMAKE_CXX_STANDARD 11)

add_executable(query main.cpp Query_base.h TextQuery.cpp TextQuery.h QueryResult.cpp QueryResult.h make_plural.h WordQuery.h NotQuery.cpp NotQuery.h BinaryQuery.h AndQuery.cpp AndQuery.h OrQuery.cpp OrQuery.h Query.cpp Query.h)
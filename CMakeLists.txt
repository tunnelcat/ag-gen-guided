cmake_minimum_required(VERSION 3.0)

# Uncomment for gcc
# set(CMAKE_C_COMPILER "gcc-8")
# set(CMAKE_CXX_COMPILER "g++-8")

project(ag_gen)

set_source_files_properties(
    mem.c
    PROPERTIES
        COMPILE_DEFINITIONS UNIT_TEST=1
)

# Common compiler options among built types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

# Specific compiler options for Debug or Release builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -ggdb -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g -Wall -pedantic -O1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1")

set(PostgreSQL_TYPE_INCLUDE_DIR "9.5")
set(PostgreSQL_ADDITIONAL_VERSIONS "10.1" "10" "9.5")

find_program(LSB_RELEASE lsb_release)
execute_process(COMMAND ${LSB_RELEASE} -is
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories("/usr/include/postgresql")

# Apple has a different openssl directory when using brew
if(APPLE)
    set(BISON_EXECUTABLE "/usr/local/opt/bison/bin/bison")
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

set(ENV{PKG_CONFIG_PATH} "/usr/local/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
find_package(PostgreSQL REQUIRED)

find_package(BISON 2.4 REQUIRED)
find_package(FLEX REQUIRED)
find_package(Boost REQUIRED)

find_package(OpenSSL)
find_package(Doxygen)

include_directories(${Boost_INCLUDE_DIRS})

pkg_check_modules(CMOCKA cmocka)
pkg_check_modules(CPPREDIS cpp_redis)

if(OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

# Enable thread-level parallelization if OpenMP is found.
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif(DOXYGEN_FOUND)

include_directories("${CMAKE_SOURCE_DIR}/src/")

file(GLOB ag_gen_src "${CMAKE_SOURCE_DIR}/src/ag_gen/*.cpp")
file(GLOB utils_src "${CMAKE_SOURCE_DIR}/src/util/*.c" "${CMAKE_SOURCE_DIR}/src/util/*.cpp")

########################
### Network Model Parser
########################

BISON_TARGET(nm_parser "${CMAKE_SOURCE_DIR}/src/parser/nm-parser/nm_parser.yy"
    "${CMAKE_CURRENT_BINARY_DIR}/nm_parser.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/nm_parser.tab.h")
FLEX_TARGET(nm_scanner "${CMAKE_SOURCE_DIR}/src/parser/nm-parser/nm_scanner.l"
    "${CMAKE_CURRENT_BINARY_DIR}/nm_scanner.c"
    COMPILE_FLAGS "-Pnm")
ADD_FLEX_BISON_DEPENDENCY(nm_scanner nm_parser)

#add_executable(nm_test ${FLEX_nm_scanner_OUTPUTS} ${BISON_nm_parser_OUTPUTS} ${utils_src})
#target_include_directories(nm_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_SOURCE_DIR}/src/compiler/nm-parser")

##########################
### Exploit Pattern Parser
##########################

BISON_TARGET(xp_parser "${CMAKE_SOURCE_DIR}/src/parser/xp-parser/xp_parser.yy"
    "${CMAKE_CURRENT_BINARY_DIR}/xp_parser.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/xp_parser.tab.h")
FLEX_TARGET(xp_scanner "${CMAKE_SOURCE_DIR}/src/parser/xp-parser/xp_scanner.l"
    "${CMAKE_CURRENT_BINARY_DIR}/xp_scanner.c"
    COMPILE_FLAGS "-Pxp")
ADD_FLEX_BISON_DEPENDENCY(xp_scanner xp_parser)

#add_executable(xp_test ${FLEX_xp_scanner_OUTPUTS} ${BISON_xp_parser_OUTPUTS} ${utils_src})
#target_include_directories(xp_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_SOURCE_DIR}/src/compiler/xp-parser")

####################
### Main application
####################

add_executable(ag_gen "${CMAKE_SOURCE_DIR}/src/main.cpp"
    ${FLEX_nm_scanner_OUTPUTS} ${BISON_nm_parser_OUTPUTS}
    ${FLEX_xp_scanner_OUTPUTS} ${BISON_xp_parser_OUTPUTS}
    ${ag_gen_src} ${utils_src})
target_link_libraries(ag_gen ${PostgreSQL_LIBRARIES})

add_executable(decode "${CMAKE_SOURCE_DIR}/src/tools/decode.cpp"
    ${ag_gen_src} ${utils_src})
target_link_libraries(decode ${PostgreSQL_LIBRARIES})

if(CPPREDIS_FOUND)
    #include_directories("${CPPREDIS_INCLUDE_DIRS}")
    link_directories("${CPPREDIS_LIBRARY_DIRS}")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DREDIS")

    target_link_libraries(ag_gen cpp_redis tacopie)
    target_link_libraries(decode cpp_redis tacopie)
endif()

################
### Unit Testing
################

if(CMOCKA_FOUND)
    add_executable(dynstr_test ${CMAKE_SOURCE_DIR}/src/util/mem.c ${CMAKE_SOURCE_DIR}/src/tests/mem_test.c)
    target_link_libraries(dynstr_test ${CMOCKA_LIBRARIES})
endif()

# Files to be added to build directory
configure_file("config.ini" "config.ini" COPYONLY)

if(CPPREDIS_FOUND)
add_custom_command(TARGET ag_gen PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/redis_scripts $<TARGET_FILE_DIR:ag_gen>/redis_scripts)
endif()

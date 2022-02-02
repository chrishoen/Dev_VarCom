cmake_minimum_required(VERSION 3.10)
set (project "SerialTest3")
project(${project} CXX)
my_find_src_files (src_files ${project})
add_executable (${project} ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

my_inc_import_RisLib(${project})
my_inc_import_CommonLib(${project})

my_lib_import_CommonLib(${project})
my_lib_import_RisLib(${project})

if (MSVC)
   install(TARGETS ${Project} DESTINATION "C:/aaa_prime/VarCom")
elseif (MYMODE STREQUAL ubuntu OR MYMODE STREQUAL wsl) 
   install(TARGETS ${Project} DESTINATION "/opt/prime/bin")
elseif (MYMODE STREQUAL beagle)
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND c:/windows/system32/openssh/scp ${CMAKE_CURRENT_BINARY_DIR}/${Project} pi@rpx:/opt/prime/bin)")
endif()

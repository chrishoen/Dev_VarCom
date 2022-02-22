cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)
include(MyPrecompiledHeader.cmake)
include(MySpecial.cmake)

project ("Dev_VarCom")
my_special1() 

add_subdirectory ("CommonLib")
add_subdirectory ("varcom")
return()

add_subdirectory ("CommonLib")
add_subdirectory ("SerialTest3")
return()

add_subdirectory ("Test")
return()

add_subdirectory ("CommonLib")
add_subdirectory ("Test")
return()





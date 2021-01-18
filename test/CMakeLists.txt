set(GTEST_ROOT ${PROJECT_SOURCE_DIR}/extern/gtest/googletest)
set(GMOCK_ROOT ${PROJECT_SOURCE_DIR}/extern/gtest/googlemock)

include_directories(${GTEST_ROOT})
include_directories(${GTEST_ROOT}/include)
include_directories(${GMOCK_ROOT})
include_directories(${GMOCK_ROOT}/include)

set(GTEST_SRC
  ${GTEST_ROOT}/src/gtest-all.cc
  ${GMOCK_ROOT}/src/gmock-all.cc
  ${GTEST_ROOT}/src/gtest_main.cc)


add_library(GTest ${GTEST_SRC})
set_target_properties(GTest PROPERTIES FOLDER Test)

function(CopyLib target)
  foreach(lib ${ARGN})
    add_custom_command(TARGET ${target} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       $<TARGET_FILE:${lib}>
                       $<TARGET_FILE_DIR:${target}>)
  endforeach()
endfunction()

#test
SET(TEST_PATH ${PROJECT_SOURCE_DIR}/test)
file(GLOB TEST_SRC ${TEST_PATH}/*.cc)
add_executable(TestDataStructure ${TEST_SRC})
target_link_libraries(TestDataStructure DataStructure GTest)
set_target_properties(TestDataStructure PROPERTIES LINKER_LANGUAGE CXX FOLDER Test)
CopyLib(TestDataStructure DataStructure)

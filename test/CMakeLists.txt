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
set_target_properties (GTest PROPERTIES FOLDER Test)
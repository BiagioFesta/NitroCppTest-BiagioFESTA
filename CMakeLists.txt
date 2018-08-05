cmake_minimum_required(VERSION 3.1)
project(NitroCpp)

set(SRC
  src/NitroCpp.cpp
  src/Rect.cpp
  src/Solver.cpp)
set(SRC_MAIN src/main.cpp)
set(INCLUDE_DIR_RAPIDJSON "thirdparty/rapidjson-1.1.0/include")
set(SRC_TEST
  test/main.cpp
  test/testNitroCpp.cpp
  test/testRect.cpp
  test/testSolver.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${SRC_MAIN})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR_RAPIDJSON})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

option(BUILD_TEST "Build Tests. Requires Gtest" NO)
if (${BUILD_TEST})
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)

  add_executable(${PROJECT_NAME}_test ${SRC} ${SRC_TEST})
  target_include_directories(${PROJECT_NAME}_test
    PRIVATE ${INCLUDE_DIR_RAPIDJSON}
    PRIVATE src)
  target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_14)
  target_link_libraries(${PROJECT_NAME}_test
    ${GTEST_BOTH_LIBRARIES}
    Threads::Threads)

  include(CTest)
  add_test(NAME TestAll COMMAND ${PROJECT_NAME}_test)
endif()

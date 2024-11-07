cmake_minimum_required(VERSION 3.14)
project(ircserv)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}-googletest
  #MessageParsingSuccessFile
  test/MessageTest.cpp
  #MessageParsingFile
  src/command.cpp
  src/message_parser.cpp
  src/utils.cpp
  src/error_status.cpp
  src/response_status.cpp
  src/user.cpp
  src/event.cpp
  src/optional_message.cpp
  src/channel.cpp
  src/channel_event.cpp
  src/mode.cpp
)
target_link_libraries(${PROJECT_NAME}-googletest
  GTest::gtest_main
)

target_include_directories(${PROJECT_NAME}-googletest PRIVATE
  includes
  includes/command.h
  includes/message_parser.h
  includes/utils.h
  includes/error_status.h
  includes/response_status.h
  includes/user.h
  includes/event.h
  includes/optional_message.h
  includes/channel.h
  includes/channel_event.h
  includes/mode.h
)

add_test(NAME test-pass-parsing COMMAND ${PROJECT_NAME}-googletest)

enable_testing()
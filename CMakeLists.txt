cmake_minimum_required(VERSION 3.16)
project(digital-pet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- sources ----
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
)

# --- ncurses ---
find_package(Curses REQUIRED)   # provides CURSES_LIBRARIES + CURSES_INCLUDE_DIR
target_include_directories(digital-pet PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(digital-pet PRIVATE ${CURSES_LIBRARIES})

# warnings (optional)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()


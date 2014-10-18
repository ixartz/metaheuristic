function(add_dir directory return)
  file(GLOB source
     "${directory}/*.h"
     "${directory}/*.cpp"
  )

  if (${directory} STREQUAL ".")
    set(group "root")
  else()
    set(group ${directory})
  endif()

  source_group(${group} FILES ${source})

  set(${return} ${source} PARENT_SCOPE)
endfunction(add_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -std=c++11")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

link_directories(${GLFW_LIBRARY_DIRS})

add_executable(metaheuristic main.cpp)

target_link_libraries(metaheuristic ${GLFW_LIBRARIES})

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

add_dir("io" source_io)
add_dir("model" source_model)
add_dir("positioning" source_positioning)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLM REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

link_directories(${GLFW_LIBRARY_DIRS})

add_executable(metaheuristic main.cpp ${source_io}
               ${source_model} ${source_positioning})

target_link_libraries(metaheuristic ${OPENGL_LIBRARIES}
                      ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES})

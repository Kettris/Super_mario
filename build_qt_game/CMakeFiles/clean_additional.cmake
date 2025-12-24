# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\super_mario_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\super_mario_autogen.dir\\ParseCache.txt"
  "super_mario_autogen"
  )
endif()

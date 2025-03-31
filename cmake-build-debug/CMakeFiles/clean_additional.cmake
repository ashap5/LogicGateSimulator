# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/LogicGateSimulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/LogicGateSimulator_autogen.dir/ParseCache.txt"
  "LogicGateSimulator_autogen"
  )
endif()

message(STATUS "Setup Python3")

include(ExternalProject)

find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
message(STATUS "  Python Executable is: " ${Python_EXECUTABLE})

#
# Packages
#

macro(python_cpm_package name)
  message(STATUS "Add Python package ${name}")
  CPMAddPackage(NAME ${ARGV})
  list(APPEND python_paths "${${name}_SOURCE_DIR}") 
endmacro()

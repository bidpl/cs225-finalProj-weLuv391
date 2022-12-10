# These Cmake Files were taken from our various MP assignment from the cs225 release-f22 and altered to suit our project
# Path definitions.
set(lib_dir ${CMAKE_CURRENT_SOURCE_DIR})

# Add overall libs library.
add_library(libs INTERFACE)
target_include_directories(libs INTERFACE ${lib_dir})

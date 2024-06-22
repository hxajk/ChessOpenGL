
# Set glad include directory

include_directories("C:/Deps/glad/include")

# Add glad library
add_library(glad STATIC IMPORTED)

# Create imported static library target for glad
set_property(TARGET glad PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/GLAD/src/glad.c)
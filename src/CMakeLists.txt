add_library(fsi_lib INTERFACE)
# TODO: Fix me
target_include_directories(fsi_lib INTERFACE "${PROJECT_SOURCE_DIR}/include")

add_executable(fsi main.cpp)
fsi_compile_options(fsi)
target_link_libraries(fsi
    PRIVATE
        fsi_lib
)

set_target_properties(fsi
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

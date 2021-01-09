# Include dirs
set(SECOND_IMPLEMENTATION_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Header files
set(SECOND_IMPLEMENTATION_HEADERS
    "pch.h"
    "core/logger.h"
    "helpers.hpp"
    "semaphore.hpp"
)

# Source files
set(SECOND_IMPLEMENTATION_SOURCES
    "main.cpp"
    "core/logger.cpp"
)

# Generate an config.h file based on config.in file
configure_file(${CMAKE_SOURCE_DIR}/second_implementation/config.in ${CMAKE_SOURCE_DIR}/second_implementation/config.h @ONLY NEWLINE_STYLE LF)

# First implementation executable
add_executable(second_implementation ${SECOND_IMPLEMENTATION_SOURCES})

# Definitions
target_compile_definitions(second_implementation
PUBLIC
    $<$<CONFIG:Debug>:ENABLE_LOG_MACROS>
)

# Setting the pre compiled header
target_precompile_headers(second_implementation PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

# First implementation properties
set_target_properties(second_implementation
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED 17
)

# First implementation include dirs
target_include_directories(second_implementation
PUBLIC
    ${SECOND_IMPLEMENTATION_INCLUDE_DIRS}
)

# First implementation libraries
target_link_libraries(second_implementation
PUBLIC
    spdlog
)

# Setting custom commandos to copy all needed files to the right location
add_custom_target(copy_resources_second_implementation ALL
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/second_implementation/assets ${CMAKE_BINARY_DIR}/bin/assets
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/second_implementation/assets ${CMAKE_SOURCE_DIR}/bin/assets
    DEPENDS second_implementation)

# Setting the install command to the app
install(TARGETS second_implementation RUNTIME DESTINATION bin)
install(TARGETS second_implementation LIBRARY DESTINATION lib)

# Include dirs
set(THIRD_IMPLEMENTATION_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VENDOR}/cli11
)

# Header files
set(THIRD_IMPLEMENTATION_HEADERS
    "pch.h"
    "core/logger.h"
    "base.hpp"
    "producer.hpp"
    "consumer.hpp"
)

# Source files
set(THIRD_IMPLEMENTATION_SOURCES
    "main.cpp"
    "core/logger.cpp"
)

# Generate an config.h file based on config.in file
configure_file(${CMAKE_SOURCE_DIR}/third_implementation/config.in ${CMAKE_SOURCE_DIR}/third_implementation/config.h @ONLY NEWLINE_STYLE LF)

# First implementation executable
add_executable(third_implementation ${THIRD_IMPLEMENTATION_SOURCES})

# Definitions
target_compile_definitions(third_implementation
PUBLIC
    $<$<CONFIG:Debug>:ENABLE_LOG_MACROS>
)

# Setting the pre compiled header
target_precompile_headers(third_implementation PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

# First implementation properties
set_target_properties(third_implementation
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED 17
)

# First implementation include dirs
target_include_directories(third_implementation
PUBLIC
    ${THIRD_IMPLEMENTATION_INCLUDE_DIRS}
)

# First implementation libraries
target_link_libraries(third_implementation
PUBLIC
    spdlog
)

# Setting custom commandos to copy all needed files to the right location
add_custom_target(copy_resources_third_implementation ALL
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/third_implementation/assets ${CMAKE_BINARY_DIR}/bin/assets
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/third_implementation/assets ${CMAKE_SOURCE_DIR}/bin/assets
    DEPENDS third_implementation)

# Setting the install command to the app
install(TARGETS third_implementation RUNTIME DESTINATION bin)
install(TARGETS third_implementation LIBRARY DESTINATION lib)

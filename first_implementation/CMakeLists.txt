# Include dirs
set(FIRST_IMPLEMENTATION_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Header files
set(FIRST_IMPLEMENTATION_HEADERS
    "pch.h"
    "core/logger.h"
    "base.hpp"
    "producer.hpp"
    "consumer.hpp"
)

# Source files
set(FIRST_IMPLEMENTATION_SOURCES
    "main.cpp"
    "core/logger.cpp"
)

# First implementation executable
add_executable(first_implementation ${FIRST_IMPLEMENTATION_SOURCES})

# Definitions
target_compile_definitions(first_implementation
PUBLIC
    $<$<CONFIG:Debug>:ENABLE_LOG_MACROS>
)

# Setting the pre compiled header
target_precompile_headers(first_implementation PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

# First implementation properties
set_target_properties(first_implementation
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED 17
)

# First implementation include dirs
target_include_directories(first_implementation
PUBLIC
    ${FIRST_IMPLEMENTATION_INCLUDE_DIRS}
)

# First implementation libraries
target_link_libraries(first_implementation
PUBLIC
    spdlog
)

# Setting custom commandos to copy all needed files to the right location
add_custom_target(copy_resources_first_implementation ALL
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/first_implementation/assets ${CMAKE_BINARY_DIR}/bin/assets
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/first_implementation/assets ${CMAKE_SOURCE_DIR}/bin/assets
    DEPENDS first_implementation)

# Setting the install command to the app
install(TARGETS first_implementation RUNTIME DESTINATION bin)
install(TARGETS first_implementation LIBRARY DESTINATION lib)

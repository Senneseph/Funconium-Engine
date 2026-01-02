cmake_minimum_required(VERSION 3.15)
project(FunconiumEngineWinVulkanDemo)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Platform-specific definitions
if(WIN32)
    add_definitions(-D_WIN32 -D_WINDOWS -DWIN32_LEAN_AND_MEAN)
endif()

# Source files
set(CORE_SOURCES
    src/demo/core/demo_core.c
)

set(WIN_SOURCES
    src/demo/win/demo.c
    src/demo/win/asset_loader.c
    src/demo/win/timing.c
    src/demo/win/logger.c
    src/demo/win/vulkan_wrapper.c
    src/demo/win/main.c
)

# Include directories
include_directories(
    src/demo/core
    src/demo/win
)

# Add executable
add_executable(funconium_demo_win_vulkan ${CORE_SOURCES} ${WIN_SOURCES})

# Find Vulkan
find_package(Vulkan REQUIRED)

# Link libraries for Windows
target_link_libraries(funconium_demo_win_vulkan
    user32
    gdi32
    ${Vulkan_LIBRARIES}
)

# Include Vulkan headers
target_include_directories(funconium_demo_win_vulkan PRIVATE ${Vulkan_INCLUDE_DIRS})

# Set output directory
set_target_properties(funconium_demo_win_vulkan PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy resources
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    add_custom_command(TARGET funconium_demo_win_vulkan POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:funconium_demo_win_vulkan>/resources"
        COMMENT "Copying resources to output directory"
    )
endif()

# Build instructions
message(STATUS "Funconium Engine Windows Vulkan Demo Configuration")
message(STATUS "================================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C standard: C17")
message(STATUS "Target: funconium_demo_win_vulkan.exe")
message(STATUS "Output directory: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "")
message(STATUS "To build:")
message(STATUS "  cmake --build . --config Release")
message(STATUS "")
message(STATUS "To run:")
message(STATUS "  ./bin/funconium_demo_win_vulkan.exe")
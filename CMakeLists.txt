cmake_minimum_required(VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("PVZOnline" VERSION 0.0.0 LANGUAGES CXX)

# Source files and headers
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Create the shared library
add_library(PVZOnline SHARED ${SRC_FILES} ${HEADERS} )
set_property(TARGET PVZOnline PROPERTY CXX_STANDARD 20)

# Include directories for PVZOnline
target_include_directories(PVZOnline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add subdirectory for MinHook
add_subdirectory(libs/minhook)

# Link MinHook library to PVZOnline
target_link_libraries(PVZOnline PRIVATE minhook)

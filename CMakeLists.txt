cmake_minimum_required(VERSION 3.14)
project(System_WatchDog)

# Set C++ standard and enable Qt automoc, autorcc, and autouic
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts Test)

# Platform-specific sources and definitions
if(WIN32)
    message(STATUS "Building for Windows")
    set(PLATFORM_SOURCES
        src/Platform/Windows/ProcessManagerWindows.cpp
        src/Platform/Windows/RAMMonitorWindows.cpp
        src/Platform/Windows/IOMonitorWindows.cpp
        src/Platform/Windows/NetworkMonitorWindows.cpp
        src/Platform/Windows/ThreadsMonitorWindows.cpp
        src/Platform/Windows/RegistryMonitorWindows.cpp
    )
    add_definitions(-DWINDOWS_PLATFORM)

    # Npcap SDK
    set(NPCAP_DIR "${CMAKE_SOURCE_DIR}/thirdparty/npcap")
    include_directories(${NPCAP_DIR}/Include)
    link_directories(${NPCAP_DIR}/Lib/x64) # or Lib/x86 for 32-bit
    set(NPCAP_LIBRARIES Packet wpcap)

elseif(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux")
    set(PLATFORM_SOURCES
        src/Platform/Linux/ProcessManagerLinux.cpp
        src/Platform/Linux/RAMMonitorLinux.cpp
        src/Platform/Linux/IOMonitorLinux.cpp
        src/Platform/Linux/NetworkMonitorLinux.cpp
        src/Platform/Linux/ThreadsMonitorLinux.cpp
    )
    add_definitions(-DLINUX_PLATFORM)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Add executable
add_executable(System_WatchDog
    src/main.cpp

    # Core logic (platform-agnostic)
    src/Core/ProcessManager/ProcessManager.cpp
    src/Core/RAMMonitor/RAMMonitor.cpp
    src/Core/IOMonitor/IOMonitor.cpp
    src/Core/NetworkMonitor/NetworkMonitor.cpp
    src/Core/ThreadsMonitor/ThreadsMonitor.cpp
    src/Core/RegistryMonitor/RegistryMonitor.cpp
    src/Core/Models/ProcessInfo.cpp
    src/Core/Models/SystemUsage.cpp
    src/Core/Utils/SystemUtils.cpp

    # GUI code (platform-agnostic)
    src/GUI/MainWindow/MainWindow.cpp
    src/GUI/MainWindow/MainWindow.h
    src/GUI/Graphs/CpuUsageGraph.cpp
    src/GUI/Graphs/MemoryUsageGraph.cpp
    src/GUI/DataViews/ProcessTableView.cpp

    # Platform-specific implementations
    ${PLATFORM_SOURCES}
)

# Include directories
target_include_directories(System_WatchDog PRIVATE
    src/Core
    src/GUI
    src/Platform
    ${NPCAP_DIR}/Include
)

# Link Qt libraries
target_link_libraries(System_WatchDog PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    ${NPCAP_LIBRARIES}
)

# # Add unit tests
# add_executable(System_WatchDog_Tests
#     src/Tests/TestProcessManager.cpp
#     src/Tests/TestRAMMonitor.cpp
#     src/Tests/TestIOMonitor.cpp
#     src/Tests/TestNetworkMonitor.cpp
#     src/Tests/TestThreadsMonitor.cpp
#     src/Tests/TestRegistryMonitor.cpp
# )
# target_link_libraries(System_WatchDog_Tests PRIVATE
#     Qt6::Core
#     Qt6::Test
# )

# add_test(NAME System_WatchDog_Tests COMMAND System_WatchDog_Tests)


# Optional: Explicitly list headers for IDE support
# target_sources(System_WatchDog PRIVATE
#     src/Core/ProcessManager/ProcessManager.h
#     src/Core/IOMonitor/IOMonitor.h
#     src/Core/NetworkMonitor/NetworkMonitor.h
#     src/Core/Models/ProcessInfo.h
#     src/Core/Utils/SystemUtils.h
#     src/GUI/MainWindow/MainWindow.h
#     src/GUI/Graphs/CpuUsageGraph.h
#     src/GUI/Graphs/MemoryUsageGraph.h
#     src/GUI/DataViews/ProcessTableView.h
# )

# Install target (optional)
install(TARGETS System_WatchDog DESTINATION bin)

#maybe add deployment scripts later...

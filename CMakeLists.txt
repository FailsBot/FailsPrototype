cmake_minimum_required(VERSION 3.10)

project("failsbot"
	VERSION 0.1.0)

# Bot Options
option(FAILSBOT_NO_PLUGINS "No plugins" OFF)

if(NOT BOT_KEY)
	message(FATAL_ERROR "You must set bot token key via CMake command line key -DBOT_KEY=<your_key_from_BotFather>")
endif()

if(NOT BOT_NAME)
	message(FATAL_ERROR "You must set bot @username via CMake command line key -DBOT_NAME=<username_without_at_sign>")
endif()

# Dependency management
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)

    # alias to non-global imported interface library
    add_library(FailsBot::network::libcurl INTERFACE IMPORTED)
    target_link_libraries(FailsBot::network::libcurl INTERFACE CONAN_PKG::libcurl)

endif()

# Config interface library for all dependent targets.
message("Generating Bot API header with your bot key and name...")
configure_file(src/cfg/botkey.h.in include/cfg/botkey.h @ONLY)
add_library(cfg INTERFACE)
add_library(FailsBot::cfg ALIAS cfg)
add_library(tgbotlib::cfg ALIAS cfg)
target_include_directories(cfg INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include include)

# Bot Sources

# check plugins
if(NOT FAILSBOT_NO_PLUGINS)
    add_subdirectory(src/plugins)
endif()

# main bot code
add_executable(failsbot
    src/main.cpp
)

# Add configured file path (with tokens) to include dir
target_include_directories(failsbot PRIVATE ${CONAN_INCLUDE_DIRS})
target_include_directories(failsbot PRIVATE ${cfg_INCLUDE_DIRS})

# bot transport library
add_subdirectory(src/tgbotlib)

# make an executable
target_link_libraries(failsbot
    PRIVATE
    tgbotlib
    cfg
#    CONAN_PKG::libcurl
#    ${CONAN_LIBS}
)

# set transport lib sources
add_library(tgbotlib
    writefn_data.c
    network.cpp
)
cmake_policy(SET CMP0076 NEW)
target_sources(tgbotlib INTERFACE writefn_data.h bot_network.h)
# target_include_directories(tgbotlib PRIVATE $<TARGET_PROPERTY:tgbotlib::cfg,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(tgbotlib cfg FailsBot::network::libcurl)
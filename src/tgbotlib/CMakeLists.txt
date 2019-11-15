# set transport lib sources
add_library(tgbotlib
    writefn_data.c
    network.cpp
)

target_sources(tgbotlib INTERFACE writefn_data.h bot_network.h)
target_include_directories(tgbotlib PRIVATE $<TARGET_PROPERTY:tgbotlib::cfg,INTERFACE_INCLUDE_DIRECTORIES>)
# wont work :(
# add_dependencies(tgbotlib INTERFACE tgbotlib::cfg)
# target_link_libraries(tgbotlib tgbotlib::cfg)

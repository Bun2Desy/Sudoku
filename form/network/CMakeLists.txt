add_library(network network.cpp)

target_include_directories(network INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(network Qt6::Widgets Qt6::Core Qt6::Gui)
target_link_libraries(network wsock32 ws2_32)
target_link_libraries(network C:/boost_1_84_0/bin.v2/libs/system/build/msvc-14.3/release/link-static/threading-multi/libboost_system-vc143-mt-x64-1_84.lib)
target_link_libraries(network C:/boost_1_84_0/bin.v2/libs/thread/build/gcc-13/release/link-static/threadapi-win32/threading-multi/visibility-hidden/libboost_thread-mgw13-mt-x64-1_84.a)
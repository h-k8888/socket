project(tcp)
message("tcp")
#find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system filesystem)
message(${Boost_LIBRARIES})

add_executable(tcp_client client_boost.cpp)
target_link_libraries(tcp_client
        ${Boost_LIBRARIES})

add_executable(tcp_server server_boost.cpp)
target_link_libraries(tcp_server
        ${Boost_LIBRARIES})
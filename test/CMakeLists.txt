cmake_minimum_required(VERSION 3.1...3.14)

# Back compatibility for VERSION range
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()


ADD_EXECUTABLE(testAbstractions  testLib.cpp cosmos/stage_1.cpp)
target_link_libraries(testAbstractions wallet-abstractions ${CRYPTOPP_LIBRARIES} ${Boost_LIBRARIES} gmock_main)

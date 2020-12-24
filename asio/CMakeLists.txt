CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# example ASIO async tcp chat stuff from 
# https://www.boost.org/doc/libs/1_71_0/doc/html/boost_asio/example/cpp11/chat/chat_client.cpp

PROJECT(asio)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(CMAKE_BUILD_TYPE "Release") # can also be Debug

FIND_PACKAGE(Boost COMPONENTS system REQUIRED)

ADD_EXECUTABLE(server chat_server.cpp)
TARGET_LINK_LIBRARIES(server pthread ${Boost_LIBRARIES})

ADD_EXECUTABLE(client chat_client.cpp)
TARGET_LINK_LIBRARIES(client pthread ${Boost_LIBRARIES})

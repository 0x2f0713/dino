# set(SOURCES lobby.cpp)
file(GLOB SOURCES "*.cpp")
ADD_LIBRARY(screen SHARED ${SOURCES})

target_link_libraries(screen ui)
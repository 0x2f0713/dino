# set(SOURCES lobby.cpp)
file(GLOB SOURCES "*.cpp")
ADD_LIBRARY(screen STATIC ${SOURCES})

target_link_libraries(screen PRIVATE ui)
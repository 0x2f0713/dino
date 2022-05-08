set(SOURCES lobby.cpp)
ADD_LIBRARY(screen lobby.cpp)
target_link_libraries(screen ${SDL2_IMAGE_LIBRARIES})
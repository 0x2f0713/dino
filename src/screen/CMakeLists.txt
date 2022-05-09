set(SOURCES *.cpp)
ADD_LIBRARY(screen *.cpp)
target_link_libraries(screen ${SDL2_IMAGE_LIBRARIES})
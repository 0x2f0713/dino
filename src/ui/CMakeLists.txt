set(SOURCES ui.cpp)
ADD_LIBRARY(ui SHARED ui.cpp)
target_link_libraries(ui SDL2::Image SDL2::TTF)
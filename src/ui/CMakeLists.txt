set(SOURCES ui.cpp)
ADD_LIBRARY(UIModule ui.cpp)
target_link_libraries(UIModule SDL2::Image SDL2::TTF)
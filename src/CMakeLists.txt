add_executable(MineSweeperlike main.cpp Board.h Board.cpp Game.h Game.cpp InputHandler.cpp InputHandler.h Renderer.h Renderer.cpp)
target_link_libraries(MineSweeperlike ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
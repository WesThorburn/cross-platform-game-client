project (client)
cmake_minimum_required(VERSION 3.5.1)
option(JS_ONLY "Compiles to native JS (No WASM)" OFF)

add_definitions(-std=c++11 -O3)
include_directories(include)

file(GLOB SOURCES src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")
add_executable(a ${SOURCES})

if(JS_ONLY)
	message(STATUS "Setting compilation target to native JavaScript")
	set(CMAKE_EXECUTABLE_SUFFIX ".js")
	set_target_properties(a PROPERTIES LINK_FLAGS "--pre-js ../setup/setup.js -s EXPORTED_FUNCTIONS='[_main, _onkeydown, _onkeyup, _onmousemove, _onmousedown, _onmouseup, _onwheel, _onblur, _onfocus, _touchstart, _touchend, _touchmove, _orientationchange, _onresize]'")
else(JS_ONLY)
	message(STATUS "Setting compilation target to WASM")
	set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
	set_target_properties(a PROPERTIES LINK_FLAGS "--pre-js ../setup/setup.js -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main, _onkeydown, _onkeyup, _onmousemove, _onmousedown, _onmouseup, _onwheel, _onblur, _onfocus, _touchstart, _touchend, _touchmove, _orientationchange, _onresize]'")
endif(JS_ONLY)
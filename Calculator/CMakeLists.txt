# CMakeList.txt: проект CMake для Calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Calculator")
# Добавьте источник в исполняемый файл этого проекта.
add_executable (Calculator "Calculator.cpp" "Calculator.h" "Loader.h" "Loader.cpp" "Operations.h" "Operations.cpp" "CalculatorApp.cpp")

add_custom_target(AddPlugins ALL)

add_custom_command(
TARGET NewPlugins
COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/plugins
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins

)
 
add_dependencies("Calculator" AddPlugins)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
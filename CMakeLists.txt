cmake_minimum_required(VERSION 3.10)
project(TextEditor)

set(CMAKE_CXX_STANDARD 17)

# Все исходники
set(SOURCES
    src/main.cpp
    src/Editor.cpp
    src/Tab.cpp
    src/SyntaxHighlighter.cpp
    src/PythonStrategy.cpp
    src/CppStrategy.cpp
    src/CSharpStrategy.cpp
    src/Command.cpp
    src/UndoManager.cpp
)

add_executable(TextEditor ${SOURCES})

# Если используешь заголовки
target_include_directories(TextEditor PRIVATE include)
cmake_minimum_required (VERSION 3.20)
project (game CXX)

add_executable (${PROJECT_NAME}
    source/main.cpp

    source/server/server.cpp

    source/client/client.cpp
    source/client/bomb.cpp
    source/client/fire.cpp
    source/client/object.cpp

    source/game/game.cpp

    source/image/image.cpp
)

target_include_directories (${PROJECT_NAME}
    PRIVATE
        include
)

target_link_libraries (${PROJECT_NAME}
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
)

target_compile_features (${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_compile_options (${PROJECT_NAME}
    PRIVATE
        -fdiagnostics-color=always

        -Wall
        -Wextra
        -fstack-protector-strong
        -fcheck-new
        -fstrict-overflow

        -march=native
        $<$<CONFIG:Debug>:
            -Og
            -g3
            -DDEBUG
            -ggdb
            -fsanitize=address,leak,undefined
        >

        $<$<CONFIG:Release>:
            -O2
            -flto
            -DNDEBUG
        >
)

target_link_options (${PROJECT_NAME}
    PRIVATE
        -march=native
        -Wl,-q
        $<$<CONFIG:Debug>:
            -Og
            -g3
            -DDEBUG
            -ggdb
            -fsanitize=address,leak,undefined
        >

        $<$<CONFIG:Release>:
            -O2
            -flto
        >
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

# cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++
# cmake --build build

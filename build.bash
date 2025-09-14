g++ -g -O0 -o a.out src/main.cpp \
    src/Game.cpp src/Entity.cpp src/Bullet.cpp src/Spawner.cpp src/Enemy.cpp src/Boss.cpp src/Fireball.cpp \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# .BASH SCRIPT

#!/bin/bash
# em++ -o a.html src/main.cpp src/Game.cpp src/Entity.cpp \
#     -I /home/mdzafir98/raylib/src \
#     -L /home/mdzafir98/raylib/src \
#     -lraylib \
#     -s USE_GLFW=3 \
#     -s ASYNCIFY \
#     -s ALLOW_MEMORY_GROWTH=1 \
#     -s ASSERTIONS=2 \
#     -O0 -gsource-map \
#     --shell-file /home/mdzafir98/raylib/src/minshell.html \
#     -DPLATFORM_WEB

# SIMPLE TEST EMSCRIPTEN
# em++ -o a.html src/main.cpp

# Steps to run emsdk
# 1) navigate to emsdk directory
# 2) run ./emsdk activate latest
# 3) run source ./emsdk_env.sh

# STEPS to run WEB GAME
# 1) bash build.bash
# 2) run python3 -m http.server
# 3) goto browser
# 4) goto http://127.0.0.0:8000/a.html

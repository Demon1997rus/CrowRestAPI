#!/bin/bash

# Создаем директорию 'build' и переходим в неё
mkdir -p build && cd build

# Выполняем cmake
cmake ..

# Проверяем, передан ли аргумент для make
if [ $# -eq 0 ]; then
    # Если аргументов нет, просто выполняем make
    make
else
    # Если аргумент есть, передаем его в make
    make -j"$1"
fi

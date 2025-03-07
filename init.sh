#!/bin/bash

# Путь к папке, в которой будет располагаться репозиторий cmake-helper
REPO_DIR="cmake-helper"

# Путь к папке, в которой будет располагаться репозиторий Crow
CROW_DIR="Crow"
CROW_REPO="https://github.com/CrowCpp/Crow.git"

# Путь к папке, в которой будет располагаться репозиторий Asio
ASIO_DIR="asio"
ASIO_REPO="https://github.com/chriskohlhoff/asio.git"

# Работа с cmake-helper репозиторием
if [ -d "$REPO_DIR" ]; then
    cd "$REPO_DIR" || exit
    git pull origin main
    cd ..
else
    git clone git@github.com:Demon1997rus/cmake-helper.git
fi

# Работа с Crow репозиторием
if [ -d "$CROW_DIR" ]; then
    cd "$CROW_DIR" || exit
    git pull origin master
    cd ..
else
    git clone "$CROW_REPO"
fi

# Работа с Asio репозиторием
if [ -d "$ASIO_DIR" ]; then
    cd "$ASIO_DIR" || exit
    git pull origin master
    cd ..
else
    git clone "$ASIO_REPO"
fi

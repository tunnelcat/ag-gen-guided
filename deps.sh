#!/bin/bash

OS=$(uname | tr 'A-Z' 'a-z')

if [[ $OS = 'darwin' ]]; then
    if hash brew 2>/dev/null; then
        xcode-select --install > /dev/null
        brew cask install postgres
        brew install postgresql cmake boost cmocka cppcheck doxygen graphviz tbb libconfig bison pkg-config
    else
        echo "Please install homebrew first."
    fi
elif [[ $OS = 'linux' ]]; then
    if hash pacman 2>/dev/null; then
        sudo pacman -S cmake postgresql boost cppcheck clang doxygen graphviz libconfig
    elif hash apt-get 2>/dev/null; then
        sudo apt-get -y install libboost-graph-dev postgresql postgresql-contrib \
            libpq-dev cppcheck clang valgrind doxygen graphviz cmake \
            build-essential bison flex libssl-dev libconfig++-dev libyaml-cpp-dev
    elif hash yum 2>/dev/null; then
        sudo yum install cmake epel-release postgresql-devel boost-devel \
            openssl-devel graphviz-devel bison-devel flex-devel cppcheck valgrind \
            tbb libconfig-devel
    else
        echo "Your distro is currently not supported."
    fi
else
    echo "Your operating system is not currently supported."
fi

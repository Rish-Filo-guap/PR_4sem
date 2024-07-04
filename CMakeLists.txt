cmake_minimum_required(VERSION 3.27.8)
project(PR_4sem)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR_4sem main.cpp
        forAll/forAll.h
        forAll/forAll.cpp
        RWbmp/RWbmp.h
        RWbmp/RWbmp.cpp
        RWbin/RWbin.cpp
        RWbin/RWbin.h
        RWrle/RWrle.h
        RWrle/RWrle.cpp
        RWhaf/RWhaf.h
        RWhaf/RWhaf.cpp
        RWari/RWari.h
        RWari/RWari.cpp
)

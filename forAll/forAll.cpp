//
// Created by Anton on 25.06.2024.
//
#include "forAll.h"

string GetModeStr(int mode){

    switch(mode){
        case 0:
            return "rgb_";
        case 1:
            return "wb_";
    };
}
/*
*  Created by chi on 2016/10/17.
*  Copyright © 2016年 chi. All rights reserved.
*/
#include "Tetrist.h"
#include <iostream>

using namespace std;

int
main(int argc, char **argv) {
    Tetrist game;  
    game.welcome_view();  
    system("cls");
    game.draw_screen();  
    game.play();  
    return 0;
}  
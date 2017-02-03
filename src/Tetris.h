/*
*  Created by chi on 2016/10/17.
*  Copyright © 2016年 chi. All rights reserved.
*/
#ifndef TETRIST_H
#define TETRIST_H

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

using namespace std;

class Tetrist { 
  #define I1 0 //棒形, A1: 縦, A2: 横
  #define I2 1 

  #define O 2 //正方形

  #define L11 3 //L型
  #define L12 4
  #define L13 5
  #define L14 6

  #define L21 7 
  #define L22 8
  #define L23 9
  #define L24 10


  #define S11 11 //S型
  #define S12 12

  #define S21 13
  #define S22 14

  #define GRAY 0x08  
  #define RED 0x0C  
  #define VIOLET 0x0D  
  #define YELLOW 0x0E  
  #define GREEN 0x0A 

  const int shape[15][8]=
  {
  {0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
  {0,0,1,0,0,1,1,1},
  {0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
  {1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
  {0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
  {0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
  };//Rectangular coordinates of each shape, x coordinate first

  const int high[15]={4,1,2,2,3,2,3,2,3,2,3,2,3,2,3};//the height of each shape

  private:  
    int screen[23][12];//main screen array 
    int refpos[2];//reference point, all shapes are drawed from it  
    int top;//the current top position  
    int point;//score  
    int level;//level  
    int ID;//the ID of current shape  
    int colorID;//the ID of color  

  public:
    Tetrist();
    void welcome_view();//welcom screen 
    void set_pos(int i,int j); //set cursor position
    void set_color(int color);//set color of each point 
    void draw_screen();//draw game screen  
    int  is_frame(int x,int y);//true: if the shape touch the frame  
    void create_shape(int x,int y,int num);//draw shape  
    void redraw_screen(int x,int y,int num);//redraw screen  
    void play();//run the game  
    void turn();//turn the shape  
    void update_screen();//update the game screen  
    void pause();//pause 
    void clear_notice_screen(); //clear notice screen before update it 
};  
#endif
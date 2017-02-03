/*
*  Created by chi on 2016/10/17.
*  Copyright © 2016年 chi. All rights reserved.
*/
#include "Tetrist.h"
using namespace std;

Tetrist::Tetrist() {  
  int i,j;  
  for(i=0;i<23;i++)  
     for(j=0;j<12;j++)  
        screen[i][j]=0;  
  refpos[0]=0;  //pos_y
  refpos[1]=5;  //pos_x
  point=0;  
  level=1;  
  top=99;  
  ID=0;  
} 

void 
Tetrist::set_pos(int pos_y,int pos_x) {
  //set cursor position
  //move the cursor to the specified position
  COORD pos={pos_y, pos_x};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void 
Tetrist::set_color(int colorID) {  
  int n_color;  
  switch(colorID) {  
    case 0: n_color = GRAY;break;  
    case 1: n_color = RED;break;  
    case 2: n_color = VIOLET;break;  
    case 3: n_color = YELLOW;break;  
    case 4: n_color = GREEN;break;  
  }  
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n_color);  
}  

void 
Tetrist::draw_screen() {
  //draw game screen  
  int i;  

  set_color(0);//background color  

  for(i=0;i<(14*2-1);i++) { //set top　frame  
      set_pos(i,0);  
      cout<<"-";  
  }

  for(i=1;i<=24;i++) {  
      set_pos(0,i); //set left frame  
      cout<<"|";  
      set_pos(13*2,i); //set right frame 
      cout<<"|";  
  }  

  for(i=0;i<(14*2-1);i++) {  
      set_pos(i,24);  
      cout<<"-";  
  }  
    
  //set notice frame
  i=15;  
  for(i=30;i<=50;i++) { //top frame  
      set_pos(i,0);  
      cout<<"-";  
  }  
  for(i=1;i<=8;i++) { //left, right frame
      set_pos(15*2,i);  
      cout<<"|";  
      set_pos(25*2,i);  
      cout<<"|";  
  }  
  for(i=30;i<=50;i++) {  
      set_pos(i,9);  
      cout<<"-";  
  }  

  set_pos(16*2,14);  
  cout<<"Tetrist by chi";  
  set_pos(16*2,17);  
  cout<<"Score: "<<point;  
  set_pos(16*2,18);  
  cout<<"Level: "<<level;  
}  

void 
Tetrist::clear_notice_screen() {
  int i, j;
  for(i=31;i<50;i++) { //top frame  
    for(j=2; j<=7; j++) {
      set_pos(i,j);  
      cout<<" ";  
    }
  }  
}
  
void 
Tetrist::create_shape(int x,int y,int num) {
  //draw shape  
  int i;  
  int nx,ny;  
  if (num<2) set_color(1);//0-1: 棒 
  else if(num<3) set_color(2);//2: 四角形  
  else if(num<11) set_color(3);//3-10: L型  
  else set_color(4);  //11-14: S型
  for(i=0;i<4;i++) {   
    nx=x+shape[num][i*2]; //真ん中に作るため、i*2
    ny=y+shape[num][i*2+1];  
    set_pos((ny+1)*2,nx+1);//  
    set_color(i+1);  
    cout<<"=";  
  }  
}  
  
void 
Tetrist::redraw_screen(int x,int y,int num)  {
//redraw game screen  
  int i;  
  int nx,ny;  
  for(i=0;i<4;i++) {   
    nx=x+shape[num][i*2];  
    ny=y+shape[num][i*2+1];  
    set_pos((ny+1)*2,nx+1);  
    cout<<" ";  
  }  
}  
  
void 
Tetrist::turn() {
//the same result as changing shape ID  
  switch(ID)  
  {  
    case I1: ID=I2; break;  
    case I2: ID=I1; break;  

    case O: ID=O; break;  

    case L11: ID=L12; break;  
    case L12: ID=L13; break;  
    case L13: ID=L14; break;  
    case L14: ID=L11; break;  

    case L21: ID=L22; break;  
    case L22: ID=L23; break;  
    case L23: ID=L24; break;  
    case L24: ID=L21; break;  
      
    case S11: ID=S12; break;  
    case S12: ID=S11; break;  

    case S21: ID=S22; break;  
    case S22: ID=S21; break;  
  }  
}  
  
void 
Tetrist::welcome_view() {  
    char x;  
    while(1)  
    {  
      system("cls");  
      cerr<<"================================"<<endl;  
      cerr<<"=      Tetrist on console      ="<<endl;
      cout<<"=                              ="<<endl;  
      cerr<<"=                       by chi ="<<endl;
      cout<<"=                              ="<<endl;     
      cerr<<"================================"<<endl;  
      cout<<"=    A: left D: right S: down  ="<<endl;  
      cout<<"=    W: change  P: pause       ="<<endl;  
      cout<<"=            Q: Quit           ="<<endl;  
      cerr<<"================================"<<endl;  
      cout<<"=                              ="<<endl;  
      cout<<"=    Select level: 1-9         ="<<endl;  
      cout<<"=                              ="<<endl;  
      cout<<"================================"<<endl;  
      cout<<"================================"<<endl;  
      set_pos(20,12);  
      x=_getch();  
      if(x<='9'&&x>='1') {
      //set level  
          level=x-'0';  
          break;  
      }  
    }  
}  
  
void 
Tetrist::update_screen() {
//update game screen  
  int clear;  //the number of lines need to be cleared
  int i,j,k;  
  int nx,ny;  
  int flag; //1: no line to be cleared 
  for(i=0;i<4;i++) {
  //update screen array data   
    nx=refpos[0]+shape[ID][i*2];  
    ny=refpos[1]+shape[ID][i*2+1];  
    screen[nx][ny]=1;  
  }  
  if(refpos[0]<top)  
     top=refpos[0];  
  clear=0; //the number of lines need to be cleared  
  for(i=refpos[0];i<refpos[0]+high[ID];i++) {  
    flag=0;  
    for(j=0;j<12;j++) { 
        if(screen[i][j]==0) {
         //can not clear line  
          flag=1; 
          break;  
        }  
    }  
    if(flag==0) {
     //need to clear some lines  
      for(k=i;k>=top;k--) {  
        if(k==0)  
          for(j=0;j<12;j++) {  
            screen[k][j]=0;  
            set_pos((j+1)*2,k+1);  
            cout<<" ";  
          }  
        else {  
          for(j=0;j<12;j++) {  
             screen[k][j]=screen[k-1][j];  
             set_pos((j+1)*2,k+1);  
             if(screen[k][j]==0)  
              cout<<" ";  
             else  
              cout<<"=";  
          }  
        }  
      }  
      top++;  
      clear++;  
      point+=clear*10*level;  
    }  
  }  
  set_color(0);  
  set_pos(16*2,17);  
  cout<<"Score: "<<point;  
}  
  
void Tetrist::play() {
  //run the game  
  int i=0;  
  char x;  
  int count;  
  int nextID;  
  int temp;  
  srand((int)time(0));  
  ID=rand()%15;//get shape ID randomly  
  nextID=rand()%15;
  create_shape(refpos[0],refpos[1],ID);//draw shape  
  create_shape(3,18,nextID); //draw notice shape  
  count=1000-level*100;  
  while(1) {  
    if(i>=count) {  
        i=0;
        if(is_frame(refpos[0]+1,refpos[1])) {  
             update_screen();//update game screen 
             ID=nextID;  
             refpos[0]=0;  
             refpos[1]=5;  
             redraw_screen(3,17,nextID);  
             nextID=rand()%15;  
             create_shape(refpos[0],refpos[1],ID);
             clear_notice_screen();  
             create_shape(3,17,nextID);  
             if(is_frame(refpos[0],refpos[1])) {  
                 //getch();  
                system("cls");  
                draw_screen();  
                set_pos(5,13);  
                cout<<"Game Over!!!" <<endl;
                set_pos(4,14);  
                cout<<"Final Score: " << point <<endl; 
                system("pause");  
                // welcome_view();
                exit(0); 
             }  
        } else {  
            redraw_screen(refpos[0],refpos[1],ID);  
            refpos[0]++;  
            create_shape(refpos[0],refpos[1],ID);  
        }  
    }  
    if(kbhit()) {
    //get keyboard input  
        x=getch();  
        if(x=='a'||x=='A') {
        //move to left  
          if(is_frame(refpos[0],refpos[1]-1)==0) {  
             redraw_screen(refpos[0],refpos[1],ID);  
             refpos[1]-=1;  
             create_shape(refpos[0],refpos[1],ID);  
          }  
        }  
        if(x=='d'||x=='D') {
        //move to right  
          if(is_frame(refpos[0],refpos[1]+1)==0) {  
             redraw_screen(refpos[0],refpos[1],ID);  
             refpos[1]+=1;  
             create_shape(refpos[0],refpos[1],ID);  
          }  
        }  
        if(x=='s'||x=='S') {
          if(is_frame(refpos[0]+2,refpos[1])==0) {  
             redraw_screen(refpos[0],refpos[1],ID);  
             refpos[0]+=1;  
             create_shape(refpos[0],refpos[1],ID);  
          }  
        }  
        if(x=='w'||x=='W') {
        //change direction  
          temp=ID;  
          turn();  
          if(!is_frame(refpos[0],refpos[1])) {  
               redraw_screen(refpos[0],refpos[1],temp);  
               create_shape(refpos[0],refpos[1],ID);  
           }  
          else  
              ID=temp;  
        }  
        if(x=='p'||x=='P') {  
            //getch();  
            //system("cls");  
            pause();  
        }  
        if(x=='q'||x=='Q') {  
            system("cls");
            draw_screen();  
            set_pos(5,13);  
            cout<<"Game Over!!!" <<endl;
            set_pos(4,14);  
            cout<<"Final Score: " << point <<endl;  
            system("pause");
            // welcome_view();
            exit(0);  
        }  
        while(kbhit())  
            getch();  
    }  
    Sleep(1);   
    i++;  
  }  
}  
  
int 
Tetrist::is_frame(int x,int y) {
//true: if the shape touch the frame  
  int i;  
  int nx,ny;  
  for(i=0;i<4;i++) {   
      nx=x+shape[ID][i*2];  
      ny=y+shape[ID][i*2+1];  
      if(nx<0||nx>=23||ny<0||ny>=12||screen[nx][ny]==1)  
        return 1;  
  }  
  return 0;  
} 

void 
Tetrist::pause() {  
  system("cls");  
  while(1) {     
    draw_screen();
    set_pos(8,13);  
    cout<<"Pause!!" <<endl;
    set_pos(4,14);  
    cout<<"Current Score: " << point <<endl;  
    if(getch()=='p'||getch()=='P') {
    set_pos(8,13);  
    cout<<"       " <<endl;
    set_pos(4,14);  
    cout<<"                    " <<endl;        
      break;
    }  
  } 
  set_pos(30,13);  
  cout<<"                "<<endl;  
  draw_screen();  
  int i ,j;  
  for(i=0;i<23;i++)  
    for(j=0;j<12;j++)  
        if(screen[i][j]==1) {     
            set_pos((j+1)*2,i+1);  
            cout<<"=";  
        }  
}  
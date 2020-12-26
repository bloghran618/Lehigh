#include <iostream>
#include <stdlib.h>

using namespace std;

void Print_Instructions() {
    cout<<"\n\nC++ does not offer a graphics library"<<endl;
    cout<<"So this game does not use graphics, sorry\n\n"<<endl;
    cout<<"Your avatar is indicated by the number 1"<<endl;
    cout<<"An empty space is indicated by the number 0"<<endl;
    cout<<"To move your avatar, use keys 2, 4, 6, and 8"<<endl;
    cout<<"8 will move you up, 2 will move you down,"<<endl;
    cout<<"4 will move you left and 6 will move you right\n\n"<<endl;
    cout<<"Your goal is to get the treasure, indicated by the number 8"<<endl;
    cout<<"If you succeed in getting the treasure, you win\n\n"<<endl;
    cout<<"BUT BEWARE! Enemies will try to stop you"<<endl;
    cout<<"These enemies are indicated by the number 2"<<endl;
    cout<<"Enemies will move one space each turn, chosen at random"<<endl;
    cout<<"If an enemy lands on the same square as you, you lose\n"<<endl;
}

void InitializeBoardStandard(int board[100][100])
{
    int boardx, boardy;
    for (boardy=0; boardy<10; boardy++) {
        for (boardx=0; boardx<10; boardx++) {
        board[boardx][boardy]=0;
        }
    }

    board[0][0]=1;
    board[5][5]=2;
    board[2][4]=2;
    board[4][2]=2;
    board[6][8]=2;
    board[8][6]=2;
    board[2][2]=2;
    board[2][8]=2;
    board[8][2]=2;
    board[9][9]=8;
}

void PrintBoardStandard(int board[100][100]) {
    int boardx, boardy;
    for (boardy=0; boardy<10; boardy++) {
            cout<<"\n";
        for (boardx=0; boardx<10; boardx++) {
            cout<<board[boardx][boardy]<<" ";
        }
    }
    cout<<"\n\n\n\n\n";
}

void ClearBoardStandard(int board[100][100]) {
    int boardx, boardy;
    for (boardy=0; boardy<10; boardy++) {
        for (boardx=0; boardx<10; boardx++) {
        board[boardx][boardy]=0;
        }
    }
}

void RunGameStandard(int board[100][100], int avatarx, int avatary, int enemy[99][2]) {
    avatarx=0;
    avatary=0;
int onoff;
    for (onoff=0; onoff<8; onoff++) {
        enemy[onoff][0]=1;
    }
    for (onoff=8; onoff<100; onoff++) {
        enemy[onoff][0]=0;
    }
    enemy[0][1]=5;
    enemy[0][2]=5;
    enemy[1][1]=2;
    enemy[1][2]=4;
    enemy[2][1]=4;
    enemy[2][2]=2;
    enemy[3][1]=6;
    enemy[3][2]=8;
    enemy[4][1]=8;
    enemy[4][2]=6;
    enemy[5][1]=2;
    enemy[5][2]=2;
    enemy[6][1]=2;
    enemy[6][2]=8;
    enemy[7][1]=8;
    enemy[7][2]=2;
    while (avatarx!=9 || avatary!=9) {
    ClearBoardStandard(board);
    cout<<"Move:  ";
    int avatarMove;
    cin>>avatarMove;
    switch(avatarMove) {
    case 2:
        avatary=avatary+1;
        board[avatarx][avatary]=1;
        break;
    case 4:
        avatarx=avatarx-1;
        board[avatarx][avatary]=1;
        break;
    case 6:
        avatarx=avatarx+1;
        board[avatarx][avatary]=1;
        break;
    case 8:
        avatary=avatary-1;
        board[avatarx][avatary]=1;
        break;
    default:
        cout<<"Incorrect Input"<<endl;
        cout<<"Enter one of the following values:"<<endl;
        cout<<"2 to move up"<<endl;
        cout<<"4 to move left"<<endl;
        cout<<"6 to move right"<<endl;
        cout<<"8 to move up"<<endl;
        cout<<"Thanks for your consideration"<<endl;
    }

    if (avatarMove==2 || avatarMove==4 || avatarMove==6 || avatarMove==8) {

    int Enemy_Move;
    int nenemy;

    for (nenemy=0; nenemy<8; nenemy++) {
    Enemy_Move= rand() % 4 + 1;
    int switchenemymove;
    switchenemymove=Enemy_Move+Enemy_Move;
    if (enemy[nenemy][2]==0 && switchenemymove==8) {
        switchenemymove=2;
    }
    if (enemy[nenemy][2]==9 && switchenemymove==2) {
        switchenemymove=8;
    }
    if (enemy[nenemy][1]==0 && switchenemymove==4) {
        switchenemymove=6;
    }
    if (enemy[nenemy][1]==9 && switchenemymove==6) {
        switchenemymove=4;
    }
     switch(switchenemymove) {
     case 2:
        enemy[nenemy][2]=enemy[nenemy][2]+1;
        board[enemy[nenemy][1]][enemy[nenemy][2]]=2;
        break;
     case 4:
        enemy[nenemy][1]=enemy[nenemy][1]-1;
        board[enemy[nenemy][1]][enemy[nenemy][2]]=2;
        break;
     case 6:
        enemy[nenemy][1]=enemy[nenemy][1]+1;
        board[enemy[nenemy][1]][enemy[nenemy][2]]=2;
        break;
     case 8:
        enemy[nenemy][2]=enemy[nenemy][2]-1;
        board[enemy[nenemy][1]][enemy[nenemy][2]]=2;
        break;
     }
    }



     for (nenemy=0; nenemy<8; nenemy++) {
     if ( avatarx==enemy[nenemy][1] && avatary==enemy[nenemy][2] ) {
        cout<<"You Lose!\n\n"<<endl;
        return;
     }
    board[9][9]=8;
    board[avatarx][avatary]=1;
    }
    PrintBoardStandard(board);
if (avatarx==9 && avatary==9) {
    cout<<"Congratulations, You Have Won!\n\n\n"<<endl;
}
    }
}
}

void RunGameCustom() {
    cout<<"\n\nWrite some code bro\n\n"<<endl;
}

int main() {
    int board[100][100];
    int enemy[99][2];
    int avatarx, avatary;
    avatarx=0;
    avatary=0;
    int selection;
    while (selection!=4) {
    cout<<"1. Start New Game (Standard)"<<endl;
    cout<<"2. Start New Game (Custom)"<<endl;
    cout<<"3. Instructions"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter Your Selection:   ";
    cin>>selection;
    switch (selection) {
case 1:
    InitializeBoardStandard(board);//This is for a 10x10 board
    PrintBoardStandard(board);
    RunGameStandard(board, avatarx, avatary, enemy);
    break;
case 2:
    RunGameCustom(); //This allows for board customization
    break;
case 3:
    Print_Instructions();
    break;
case 4:
    exit(0);
    break;
default:
    cout<<"\nEnter correct choice\n\n";
    }
    }
}

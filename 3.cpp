#include <iostream>
#include<windows.h>
#include<cstdio>
#include<ctime>
#include<fstream>
#include<conio.h>
#include<cstdlib>
using namespace std;

int board[4][4]={0};
int a[4][4];
char map[50][50];
int replayGame=0;
int gameScore;

void XoaManHinh()
{
	system("cls");
}
void gotoXY(int colum, int line)
{
    COORD coord;
    coord.X=colum;
    coord.Y=line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor(int num)
{
    HANDLE color;
    color=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color,num);
}
void fileScore(int sc)
{
    fstream fileScore;
    fileScore.open("Score.txt", ios::out);//mở file để ghi
    fileScore << sc;
    fileScore.close();
}
int bestScore()
{
    int sc;
    fstream fileScore;
    fileScore.open("Score.txt", ios::in);//mở file để đọc
    fileScore >> sc;
    fileScore.close();
    return sc;
}
void SetMap()
{
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(j%6==0) map[i][j]=' ';
			if(i%4==0) map[i][j]=' ';
		}
	}
}
void DrawMap()
{
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(i%4==0 || j%6==0) TextColor(10);
			else TextColor(36);
			cout<<map[i][j];
		}
		cout<<endl;
	}
	gotoXY(30, 3);
	TextColor(11);
	cout<<"Best Score:"<<bestScore();
	TextColor(11);
	gotoXY(30,4);
	cout<<"Introduction:";
	TextColor(8);
	gotoXY(30,5);
	cout<<"_A: Turn Left";
	TextColor(9);
	gotoXY(30,6);
	cout<<"_D: Turn Right";
	TextColor(10);
	gotoXY(30,7);
	cout<<"_W: Go Up";
	gotoXY(30,8);
	TextColor(11);
	cout<<"_S: Go Down";
	gotoXY(27,10);
	TextColor(15);
	cout<<" Choose 'e' to exit, 'r' to replay.";
	TextColor(10);
}
void taoHaiViTriDau()
{
    XoaManHinh();
    SetMap();
    DrawMap();
    gameScore=0;
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
    }
    srand(time(NULL));
    int xFirst, yFirst, xSecond, ySecond;
    xFirst=rand()%4;
    yFirst=rand()%4;
    do{
        xSecond=rand()%4;
        ySecond=rand()%4;
    }while(xFirst==xSecond || yFirst==ySecond);

    board[xFirst][yFirst]=2;
    board[xSecond][ySecond]=2;
}
void goUp()
{
	for (int j = 0; j < 4; j++){
		int t = 0;
		for (int i = 0; i < 4; i++){
			if (board[i][j] != 0){
				board[t][j] = board[i][j];t++;
			}
		}
		for (int i = t; i < 4; i++) board[i][j] =0;
	}
	for (int j = 0; j < 4; j++){
		int t = 0;
		for (int i = 0; i < 4; i++){
			if (board[i][j] != 0) {
				if (board[i][j] == board[i + 1][j]) {
					board[t][j] = 2 * board[i][j];
					gameScore += board[t][j];t++;i++;
				}
				else {
					board[t][j] = board[i][j];
					t++;
				}
			}
		}
		for (int i = t; i < 4; i++) board[i][j] = 0;
	}
}
void goDown()
{
	for (int j = 0; j < 4; j++){
		int t = 3;
		for (int i = 3; i >= 0; i--){
			if (board[i][j] != 0) {
				board[t][j] = board[i][j];t--;
			}
		}
		for (int i = t; i >= 0; i--) board[i][j] = 0;
	}
	for (int j = 0; j < 4; j++){
		int t = 3;
		for (int i = 3; i >= 0; i--){
			if (board[i][j] != 0) {
				if (board[i][j] == board[i - 1][j]){
					board[t][j] = 2 * board[i][j];
					gameScore += board[t][j];t--;i--;
				}
				else{
					board[t][j] = board[i][j];
					t--;
				}
			}
		}
		for (int i = t; i >= 0; i--) board[i][j] = 0;
	}
}
void turnLeft()
{
	for (int i = 0; i < 4; i++){
		int t = 0;
		for (int j = 0; j < 4; j++){
			if (board[i][j] != 0){
				board[i][t] = board[i][j];t++;
			}
		}
		for (int j = t; j < 4; j++) board[i][j] = 0;
	}
	for (int i = 0; i < 4; i++){
		int t = 0;
		for (int j = 0; j < 4; j++){
			if (board[i][j] != 0){
				if (board[i][j] == board[i][j + 1]){
					board[i][t] = 2 * board[i][j];
					gameScore += board[i][t];j++;t++;
				}
				else{
					board[i][t] = board[i][j];t++;
				}
			}
		}
		for (int j = t; j < 4; j++) board[i][j] = 0;
	}
}
void turnRight()
{
    for (int i = 0; i < 4; i++){
		int t = 3;
		for (int j = 3; j >= 0; j--){
			if (board[i][j] != 0){
				board[i][t] = board[i][j];t--;
			}
		}
		for (int j = t; j >= 0; j--) board[i][j] = 0;
	}
	for (int i = 0; i < 4; i++){
		int t = 3;
		for (int j = 3; j >= 0; j--){
			if (board[i][j] != 0){
				if (board[i][j] == board[i][j - 1]){
					board[i][t] = 2 * board[i][j];
					gameScore += board[i][t];j--;t--;
				}
				else{
					board[i][t] = board[i][j];t--;
				}
			}
		}
		for (int j=t; j>=0; j--) board[i][j] = 0;
	}
}
void SetColor(int num)
{
	if(num==2) TextColor(48);
	else if(num==4) TextColor(49);
	else if(num==8) TextColor(15);
	else if(num==16) TextColor(52);
	else if(num==32) TextColor(53);
	else if(num==64) TextColor(54);
	else if(num=128) TextColor(55);
	else if(num=256) TextColor(56);
	else if(num=512) TextColor(57);
	else if(num=1024) TextColor(58);
	else if(num=2048) TextColor(59);
	else if(num=4096) TextColor(60);
	else if(num==8192) TextColor(61);
	else if(num==16384) TextColor(62);
}
void DrawBoard(int board[][4])
{
    for (int i = 3; i <= 21; i += 6) {
		for (int j = 3; j <= 15; j += 4) {
            int x=(i-3)/6, y=(j-3)/4;
			TextColor(2);gotoXY(i,j);
            cout<<char(219)<<char(219)<<char(219);
			SetColor(board[y][x]);
			if (board[y][x] == 0){
				TextColor(2);gotoXY(i, j);
				cout<<char(219)<<char(219)<<char(219);
			}
			else if (board[y][y] < 100){
				gotoXY(i, j);
				cout<<board[y][x];
			}
			else {
				gotoXY(i, j);
				cout<<board[y][x];
			}
		}
    }
    gotoXY(30, 2);
	TextColor(11);
	cout<<"Score: ";
	TextColor(12);
	cout<<gameScore;
}

int kiemTraViTriTrong()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==0) return 1;
        }
    }
    return 0;
}
void addNum()
{
    int x,y;
    srand(time(NULL));
    if(kiemTraViTriTrong()==0) return;
    else{
        do{
            x=rand()%4;
            y=rand()%4;
        }while(board[x][y]!=0);

        if(rand()%100>89) board[x][y]=4;
        else board[x][y]=2;
    }
}
int testGameOver()
{
    if(kiemTraViTriTrong()==1) return 0;
    else if(kiemTraViTriTrong()==0){
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j]==board[i][j+1] || board[i][j]==board[i+1][j]) return 0;
            }
        }
    }
    return 1;
}
void Intro()
{
	gotoXY(1,5);
	TextColor(11);
	cout<<"        =======\n";
	Sleep(10);
	cout<<"     ===      ====\n";
	Sleep(10);
	cout<<"    ==       ====\n";
	Sleep(10);
	cout<<"           ====\n";
	Sleep(10);
	cout<<"         ====\n";
	Sleep(10);
	cout<<"       ====\n";
	Sleep(10);
	cout<<"     ====\n";
	Sleep(10);
	cout<<"   =====\n";
	Sleep(10);
	cout<<"  =============\n";
	Sleep(10);
	cout<<"  =============\n";
	gotoXY(20,5);
	Sleep(100);
	TextColor(12);
	cout<<"      =====\n";
	Sleep(10);
	gotoXY(20,6);
	cout<<"   ===     ===\n";
	Sleep(10);
	gotoXY(20,7);
	cout<<"  ===       ===\n";
	Sleep(10);
	gotoXY(20,8);
	cout<<" ===         ===\n";
	Sleep(10);
	gotoXY(20,9);
	cout<<" ===         ===\n";
	Sleep(10);
	gotoXY(20,10);
	cout<<" ===         ===\n";
	Sleep(10);
	gotoXY(20,11);
	cout<<" ===         ===\n";
	Sleep(10);
	gotoXY(20,12);
	cout<<"  ===       ===\n";
	Sleep(10);
	gotoXY(20,13);
	cout<<"   ===     ===\n";
	Sleep(10);
	gotoXY(20,14);
	cout<<"      =====\n";
	Sleep(10);
	gotoXY(36,5);
	Sleep(100);
	TextColor(14);
	cout<<"          ===\n";
	Sleep(10);
	gotoXY(36,6);
	cout<<"        ===\n";
	Sleep(10);
	gotoXY(36,7);
	cout<<"      ===     \n";
	Sleep(10);
	gotoXY(36,8);
	cout<<"    ===        ===\n";
	Sleep(10);
	gotoXY(36,9);
	cout<<"    ==============\n";
	Sleep(10);
	gotoXY(36,10);
	cout<<"    ==============\n";
	Sleep(10);
	gotoXY(36,11);
	cout<<"              ===\n";
	Sleep(10);
	gotoXY(36,12);
	cout<<"              ===\n";
	Sleep(10);
	gotoXY(36,13);
	cout<<"              ===\n";
	Sleep(10);
	gotoXY(36,14);
	cout<<"              ===\n";
	Sleep(10);
	gotoXY(54,5);
	Sleep(100);
	TextColor(10);
	cout<<"        ====\n";
	Sleep(10);
	gotoXY(55,6);
	cout<<"    ===    ===\n";
	Sleep(10);
	gotoXY(55,7);
	cout<<"   ===      ===\n";
	Sleep(10);
	gotoXY(55,8);
	cout<<"    ===    ===\n";
	Sleep(10);
	gotoXY(55,9);
	cout<<"       ====\n";
	Sleep(10);
	gotoXY(55,10);
	cout<<"    ===    ===\n";
	Sleep(10);
	gotoXY(55,11);
	cout<<"   ===      ===\n";
	Sleep(10);
	gotoXY(55,12);
	cout<<"   ===      ===\n";
	Sleep(10);
	gotoXY(55,13);
	cout<<"    ===    ===\n";
	Sleep(10);
	gotoXY(55,14);
	cout<<"       ====\n";
	Sleep(10);
	TextColor(13);
	cout<<endl;
	cout<<"Nhan phim bat ky de bat dau choi...";
	_getch();
}
void getKey(char c)
{
	if (c == 'w' || c == 'W') goUp();
    else if (c == 's' || c == 'S') goDown();
    else if (c == 'a' || c == 'A') turnLeft();
    else if (c == 'd' || c == 'D') turnRight();
    else if(c=='e') exit(1);
    else if(c=='r') replayGame=1;
}
int main()
{
    Intro();
    taoHaiViTriDau();
    while(1)
    {
        if(replayGame==1)
        {
            taoHaiViTriDau();
            replayGame=0;
        }
        DrawBoard(board);
        if(testGameOver()==1)
        {
            gotoXY(35,20);
            TextColor(60);
            cout<<"Game Over!";
            cout<<"Điểm của bạn:"<<gameScore;
            if(gameScore > bestScore()) {
                fileScore(gameScore);
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                    a[i][j]=board[i][j];
            }
        }
        char c=_getch();
        getKey(c);
        int k=0;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(a[i][j]!=board[i][j]) {
                    k=1; break;
                }
            }
        }
        if(k==0) continue;
        addNum();
    }
    _getch();

	return 0;
}

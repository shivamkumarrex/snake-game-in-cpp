#include <iostream>
#include <conio.h>
#include <windows.h>  //for sleep function and pixel function 
using namespace std;

bool gameOver;
const int height = 20;
const int width = 40;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int ntail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//Setup function for initialiase the value or set the value
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

//Draw function for draw all the stuff like board, snake, food, score 
void Draw()
{
    system("cls");
    for(int i = 0; i < width +2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int  j = 0; j < width; j++)
        {
            if(j == 0)
                cout << "#";
            if(i == y && j == x)
                cout << ">"; //head of the snake
            else if(i == fruity && j == fruitx)
                cout << "O"; //food
            else
            {
                bool print = false;
                for(int k =0; k < ntail; k++)
                {
                    if(tailx[k] == j && taily[k] == i)
                    {
                        cout << "*"; //body of the snake 
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";

            }
            if(j == width-1)
                cout << "#";
        }
        cout << endl;
    }
    
    for(int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;

}

//Input function for move the snake by getting input key
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 'x':
                gameOver = true;
                break;    
        }
    }
    
}

// Logic function that contain all the logic used in this game 
void Logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y; 
    for(int i = 1; i < ntail; i++)
    {
        prev2y = taily[i];
        prev2x = tailx[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default :
            break;
    }
    //if play inside the wall
    if(x < 0 || x > width || y < 0 || y > height)
        gameOver = true;

    //if go through the wall
    //if(x >= width) x = 0; else if(x < 0) x = width - 1;
    //if(y >= height) y = 0; else if(y < 0) y = height - 1;

    for(int i = 0; i < ntail; i++)
        if(tailx[i] == x && taily[i] == y)
            gameOver = true;
    if(x == fruitx && y == fruity)
        {
            score += 10;
            fruitx = rand() % width;
            fruity = rand() % height;
            ntail++;
        }
}
//Main driver function
int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(20);
    }
    return 0;

}

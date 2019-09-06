#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int hight = 20;
int x,y, fruitX, fruitY, score; // x and y are snake position
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void SetUp() {
    gameOver = false;
    dir = STOP;
    x = width /2;
    y = hight/2;
    fruitX = rand() % width;
    fruitY = rand() % hight;
    score = 0;
}

void Draw() {
    
    //****************************  Printing map  *****************************************
    system("cls");
    
    for(int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
        
        
    for(int i = 0; i < hight; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0)
                cout << "#";
            
            //Drawing snake and fruit
            if(i == y && j == x) {
                cout << "O";
            }
            else if(i == fruitY && j == fruitX) {
                
                cout << "F";
                
            }
            else 
            {
                bool printed = false;
                for(int k = 0; k < nTail; k++) 
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        printed = true;
                        cout << "o";
                    }
                    
                    
                }
                
                if(!printed)
                cout << " ";
                
            }
                
            if(j == width -1)
                cout << "#";
        }
        cout << endl;
    }    
    

    for(int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    
    // *******************************************
    
    //Printing score
    cout << "Score: " << score;
    
}

void Input() 
{
    if(_kbhit()) //if keyboard was pressed
    {
        switch (_getch()) //get the aski code ...  in other words move in one direction until user inputs a key to move to another direction
        {
            case 'a':
                dir = LEFT;
                break;
            case'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
    
    
}

void Logic() 
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    
    for(int i = 0; i < nTail; i++) 
    {
        //there are 2 previous variables, bc we need a momentary holder, nothign else
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        tailX[0] = x;
        tailY[0] = y;
    }
    
    switch(dir) 
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
            
        default:
            break;
    }
    
    /*//Terminate game if head goes out of the map
    if(x > width-1 || x < 0 || y > hight-1 || y < 0)
        gameOver = true;
    */    
    //To go thru walls
    if(x >= width) x = 0; else if(x < 0) x = width -1;
    if(y >= hight) y = 0; else if(y < 0) y = hight -1;
        
    //terminate if we hit ourself
    for(int i = 0; i < nTail; i++)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;

    //if we eat the fruit
    if(x == fruitX && y == fruitY) 
    {
        score += 10; //increase score and...
        
        //Spawn another fruit in a random location
        fruitX = rand() % width; 
        fruitY = rand() % hight;
        
        //and increase tail
        nTail++;
    }

}



int main() {
    
    //This is just to test how i would increase the speed
    int speed = 30;
    
    
    SetUp();
        
    while(!gameOver) {
        
        
        Draw();
        Input();
        Logic();
        Sleep(speed);
        
    }
    
    
    return 0;
    }
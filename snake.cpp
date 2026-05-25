#include <iostream>
#include <vector>
#include <conio.h>

const int row = 30;
const int column = 90;
bool gameIsEnd = 1;


struct Snake {
    int head;
    char direction;
    int X;
    int Y;
};


bool field(int X, int Y);


int keyStick(int X, int Y) {
    char key;
    Snake snake;
    snake.X = X;
    snake.Y = Y;
    while (gameIsEnd) {
        key = _getch();
        if (key == 0 || key ==char(0XE0)) 
        {
            key = _getch();
            switch (key) 
            {
                case 72: snake.direction = 'U';
                    snake.X -= 1;
                    break;
                           
                case 80: snake.direction = 'D';
                    snake.X += 1;
                    break;
                    
                case 75: snake.direction = 'L';
                    snake.Y -= 1;
                    break;

                case 77: snake.direction = 'R';
                    snake.Y += 1;
                    break;
            };
            
            if (field(snake.X, snake.Y) == 0) {
                return gameIsEnd = false;
            }
        }
    return 0;
    }
}

bool field(int X, int Y)
{
    Snake snake; 
    char grid[row][column];
    if (X >= row || Y >= column || X < 0 || Y < 0)
    {
        return 0;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (i == 0 || i == row-1 || j == 0 || j == column-1)
            {   
                std::cout << "*";
            } else 
            {   
                if (i == X && j == Y)
                {
                std::cout << "?";
                }
                else   
                {
                std::cout << " ";
                }
            }
            
        }

        std::cout << std::endl;
    }
    while (gameIsEnd != 0)
    {
        keyStick(X, Y);
    }
}

int main() 
{
    Snake snake;
    snake.X = 14;
    snake.Y = 44;
    int choose;

    std::cout << "--MENU--\n";
    std::cout << "1. Запуститься?\n";
    std::cout << "2. Exit \n";
    std::cout << "Выберите \n";
    std::cin >> choose;
    
    if (choose == 1)
    {
        keyStick(snake.X, snake.Y);
        return 0;
    }
    else if (choose == 2)
    {
        std::cout << "Пока урот";
        return 0;
    }
    
}

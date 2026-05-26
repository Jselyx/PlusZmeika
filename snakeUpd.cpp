#include <iostream>
#include <conio.h>
#include <utility>
#include <windows.h>
#include <random>

const int row = 30;
const int column = 90;


struct snake {
    int X = 14;
    int Y = 44;
    int lenght = 1;
    char direction;
};


std::tuple<int, int, bool> fruitGenerator(int fruitX, int fruitY, bool isFruit) {
    if (isFruit) {
        return std::make_tuple(fruitX, fruitY, isFruit);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, row -2);
    fruitX = distr(gen);

    std::uniform_int_distribution<> distr2(1, column -2);
    fruitY = distr2(gen);
    isFruit = true;

    return std::make_tuple(fruitX, fruitY, isFruit);
}


int gameMenu() {
    std::cout << "--MENU-- \n 1. Start \n 2. Exit \n";
    int choose;
    std::cin >> choose;
    return choose;
}


char lastKey(int X, int Y, char direction) {
    if (GetAsyncKeyState(VK_UP)) {
        direction = 'U';
        return direction;
    }
    else if (GetAsyncKeyState(VK_DOWN)) {
        direction = 'D';
        return direction;
    }
    else if (GetAsyncKeyState(VK_LEFT)) {
        direction = 'L';
        return direction;
    }
    else if (GetAsyncKeyState(VK_RIGHT)) {
        direction = 'R';
        return direction;
    }
    return direction;

}


void field(int X, int Y, int fruitX, int fruitY, bool isFruit) {
    system("cls");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
        if (i == 0 || i == row - 1 || j == 0 || j == column - 1)
        {
            std::cout<< "#";
        } else
        {
            if (i == X && j == Y) {
                std::cout << "$";
            }
            if (i == fruitX && j == fruitY && isFruit == true) {
                std::cout << "*";
            } else
            {
                std::cout << " "; 
            }
        }
        std::cout<<"\n";
    }
}


std::pair<int, int> iterationCalculator(char direction, int lastX, int lastY) {
    switch(direction) {
        case 'U': lastX -= 1; break;
        case 'D': lastX += 1; break;
        case 'L': lastY -= 1; break;
        case 'R': lastY += 1; break;
    }
    return {lastX, lastY};
}


bool allowMove(int X, int Y) {
    if (X == row - 1 || Y == column - 1 || X == 0 || Y == 0) {
        return false;
    }
    return true;
}

void gameLoop() {
    snake snake;
    char direction = 'U';
    char lastDirection;
    int lastX = snake.X, lastY = snake.Y;
    bool isallowed;
    bool isEnd = false;
    bool isFruit = false;
    bool haveFruit = false;
    int fruitX, fruitY;
    while (isEnd == false) {
        Sleep(250);
        lastDirection = lastKey(lastX, lastY, lastDirection);
        auto [newX, newY] = iterationCalculator(lastDirection, lastX, lastY);
        std::tie(fruitX, fruitY, haveFruit) = fruitGenerator(fruitX, fruitY, isFruit);
        isFruit = haveFruit;

        lastX = newX;
        lastY = newY;
        isallowed = allowMove(lastX, lastY);
        if (isallowed) {
            field(lastX, lastY, fruitX, fruitY, isFruit);
        }
        else {
            std::cout << "Вы проиграли, уродина\n";
            isEnd = true;
        }
    }
    return;
}

bool userChoose(int choose) {
    if (choose == 1) {
        gameLoop();
    }
    else {
        return 0;
    }
}

void menuStarter() {
    int choose;
    choose = gameMenu();
    if (!userChoose(choose)) {
        std::cout << "Игра завершена.";
    }
}

int main() {
    menuStarter();
    return 0;
}
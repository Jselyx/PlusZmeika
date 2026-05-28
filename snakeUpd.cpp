#include <iostream>
#include <utility>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <thread>
    #include <ncurses.h>
    #include <chrono>
#endif
#include <random>

const int row = 30;
const int column = 90;


struct snake {
    int X = 14;
    int Y = 44;
    int lenght = 1;
    char direction;
};

struct fruit {
    int fruitX;
    int fruitY;
    bool isFruit = false;
};


bool isEated(int X, int Y, int fruitX, int fruitY) {
    return X == fruitX && Y == fruitY;
}

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
    #ifdef _WIN32
    if (GetAsyncKeyState(VK_UP)) { direction = 'U'; }
    else if (GetAsyncKeyState(VK_DOWN)) { direction = 'D'; }
    else if (GetAsyncKeyState(VK_LEFT)) { direction = 'L'; }
    else if (GetAsyncKeyState(VK_RIGHT)) { direction = 'R'; }
    return direction;
    #else
    int key = getch();
    if (key == KEY_UP) { direction = 'U'; }
    else if (key == KEY_DOWN) { direction = 'D'; }
    else if (key == KEY_LEFT) { direction = 'L'; }
    else if (key == KEY_RIGHT) { direction = 'R'; }
    return direction;
    #endif
}


void field(int X, int Y, int fruitX, int fruitY, bool isFruit) {
    system("cls");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
        if (i == 0 || i == row - 1 || j == 0 || j == column - 1)
        {
            std::cout<< "#";
        } 
        else
        {
            if (i == X && j == Y) {
                std::cout << "$";
            }
            else if (i == fruitX && j == fruitY && isFruit == true) {
                std::cout << "*";
            } 
            else
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


std::tuple<char, char, bool, bool, bool> __init__() {
    char direction = 'U';
    char lastDirection;
    bool isallowed;
    bool isEnd = false;
    bool haveFruit = false;

    return std::make_tuple(direction, lastDirection, isallowed, isEnd, haveFruit);
}


void gameLoop() {
    snake snake;
    fruit fruit;
    auto [direction, lastDirection, isallowed, isEnd, haveFruit] = __init__();
    int lastX = snake.X, lastY = snake.Y;
    while (isEnd == false) {
        sleep(250);
        lastDirection = lastKey(lastX, lastY, lastDirection);
        auto [newX, newY] = iterationCalculator(lastDirection, lastX, lastY);
        std::tie(fruit.fruitX, fruit.fruitY, haveFruit) = fruitGenerator(fruit.fruitX, fruit.fruitY, fruit.isFruit);
        fruit.isFruit = haveFruit;

        lastX = newX;
        lastY = newY;
        isallowed = allowMove(lastX, lastY);
        if (isallowed) {
            fruit.isFruit = isEated(lastX, lastY, fruit.fruitX, fruit.fruitY);
            field(lastX, lastY, fruit.fruitX, fruit.fruitY, fruit.isFruit);
        }
        else {
            std::cout << "Вы проиграли, уродина\n";
            isEnd = true;
            return;
        }
    }
}

bool userChoose(int choose) {
    if (choose == 1) {
        gameLoop();
        return true;
    }
    else {
        return false;
    }
}

void menuStarter() {
    int choose;
    choose = gameMenu();
    if (!userChoose(choose)) {
        std::cout << "Игра завершена.";
    }
}

void ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void sleep(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    #endif
}

int main() {
    menuStarter();
    return 0;
}

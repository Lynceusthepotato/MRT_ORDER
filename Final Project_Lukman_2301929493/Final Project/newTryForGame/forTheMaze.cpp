//
//  forTheMaze.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 12/06/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include "forTheMaze.hpp"
#include <iostream>
#include <queue>


Game g;

bool forTheMaze::getYouDidMinMove(){
    return youDidMinMove;
}

void forTheMaze::setRandomizeMaze(int sRM){
    this -> randomizeMaze = sRM;
}

void forTheMaze::reachingEndOfTheMaze(){
    if(endingMaze == 1){
        std::cout << "*Narrator voice* You have reach the end point " << std::endl;
        std::cout << "*Narrator voice* I will now bring you to the outisde world " << std::endl;
        std::cout << "What?! this is lazy pro-" << std::endl;
    } else if (endingMaze == 2){
        std::cout << "*Narrator voice* I see you are trying to get the epic loot" << std::endl;
        std::cout << "*Narrator voice* Good luck to you then" << std::endl;
        std::cout << "Wait wh-" << std::endl;
    } else if (endingMaze == 3){
        std::cout << "*Narrator voice* I see you are tryin-" << std::endl;
        std::cout << "yeah yeah..." << std::endl;
    } else {
        std::cout << "YEET" << std::endl;
    }
    endingMaze++;
    if(moveCount <= minDistForReward){
        youDidMinMove = true;
    }
    insideMaze = false;
    g.dialogContinue();
    moveCount = 1;
}

void forTheMaze::shortestDistanceText(char map[N][M]){
    std::cout << "The shortest distance is : " << minDistance(map) << std::endl;
    std::cout << "Hey if you did this in the shortest distance Ill give you a some reward" << std::endl;
    minDistForReward = minDistance(map);
}
 

 
int forTheMaze::minDistance(char map[N][M]){
    qL source(0,0,0);
    bool visited[N][M];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(map[i][j] == '1'){
                visited[i][j] = true;
            } else {
                visited[i][j] = false;
            }
            if(map[i][j] == '4'){
                source.row = i;
                source.col = j;
            }
        }
    }
    std::queue<qL> q;
    q.push(source);
    visited[source.row][source.col] = true;
    while (!q.empty()){
        qL p = q.front();
        q.pop();
        
        if (map[p.row][p.col] == '9'){
            return p.dist;
        }
        if (p.row - 1 >= 0 && visited[p.row - 1][p.col] == false){
            q.push(qL(p.row - 1, p.col, p.dist + 1));
            visited[p.row - 1][p.col] = true;
        }
        if (p.row + 1 < N && visited[p.row + 1][p.col] == false){
            q.push(qL(p.row + 1, p.col, p.dist + 1));
            visited[p.row + 1][p.col] = true;
        }
        if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false){
            q.push(qL(p.row , p.col - 1, p.dist + 1));
            visited[p.row][p.col - 1] = true;
        }
        if (p.col + 1 < M && visited[p.row][p.col + 1] == false){
            q.push(qL(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col + 1] = true;
        }
    }
    return -1;
}

void forTheMaze::mazeMapOne(){
    char map[N][M] = {
    "1111111111111",
    "1410101000001",
    "1010001011101",
    "1000111000001",
    "1010000011101",
    "1010111010001",
    "1010100011101",
    "1010111010101",
    "1000000000191",
    "1111111111111"};
    shortestDistanceText(map);
    g.dialogContinue();
    x = 1;
    y = 1;
    while(insideMaze == true)
    {
        for (int display=0;display<10;display++)
        {
            std::cout << map[display] << std::endl;
        }
        std::cin >> movement;
        system("clear");
        switch(movement){
            case 's':
            {
                int y2 = y + 1;
                if(map[y2][x] == '0')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                } else if(map[y2][x] == '9')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'w':
            {
                int y1 = y - 1;
                if (map[y1][x] == '0')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                } else if (map[y1][x] == '9')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'a':
            {
                int x2 = x - 1;
                if(map[y][x2]== '0')
                {
                    map[y][x]= '0';
                    x--;
                    map[y][x]= '4';
                } else if (map[y][x2] == '9')
                {
                    map[y][x] = '0';
                    x--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'd':
            {
                int x1 = x + 1;
                if (map[y][x1] == '0'){
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                } else if (map[y][x1] == '9')
                {
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            default:{
                continue;
            }
                break;
        }
        moveCount += 1;
    }
}

void forTheMaze::mazeMapTwo(){
    char map[N][M] = {
    "1111111111111",
    "1010101000001",
    "1010001011101",
    "1000111000001",
    "1010000011101",
    "1010111010001",
    "1010100011101",
    "1010111010101",
    "1000000004191",
    "1111111111111"};
    shortestDistanceText(map);
    g.dialogContinue();
    x = 9;
    y = 8;
    while(insideMaze == true)
    {
        for (int display=0;display<10;display++)
        {
                std::cout << map[display] << std::endl;
        }
        std::cin >> movement;
        system("clear");
        switch(movement){
            case 's':
            {
                int y2 = y + 1;
                if(map[y2][x] == '0')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                } else if(map[y2][x] == '9')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'w':
            {
                int y1 = y - 1;
                if (map[y1][x] == '0')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                } else if (map[y1][x] == '9')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'a':
            {
                int x2 = x - 1;
                if(map[y][x2]== '0')
                {
                    map[y][x]= '0';
                    x--;
                    map[y][x]= '4';
                } else if (map[y][x2] == '9')
                {
                    map[y][x] = '0';
                    x--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'd':
            {
                int x1 = x + 1;
                if (map[y][x1] == '0'){
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                } else if (map[y][x1] == '9')
                {
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            default:
            {
                continue;
            }
                break;
        }
        moveCount += 1;
    }
}

void forTheMaze::mazeMapThree(){
    char map[N][M] = {
    "1111111111111",
    "1010101010091",
    "1010001011101",
    "1000111000001",
    "1110000011101",
    "1010111000001",
    "1010000111101",
    "1010111010101",
    "1000000004101",
    "1111111111111"};
    shortestDistanceText(map);
    g.dialogContinue();
    x = 9;
    y = 8;
    while(insideMaze == true)
    {
        for (int display=0;display<10;display++)
        {
                std::cout << map[display] << std::endl;
        }
        std::cin >> movement;
        system("clear");
        switch(movement){
            case 's':
            {
                int y2 = y + 1;
                if(map[y2][x] == '0')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                } else if(map[y2][x] == '9')
                {
                    map[y][x] = '0';
                    y++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'w':
            {
                int y1 = y - 1;
                if (map[y1][x] == '0')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                } else if (map[y1][x] == '9')
                {
                    map[y][x] = '0';
                    y--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'a':
            {
                int x2 = x - 1;
                if(map[y][x2]== '0')
                {
                    map[y][x]= '0';
                    x--;
                    map[y][x]= '4';
                } else if (map[y][x2] == '9')
                {
                    map[y][x] = '0';
                    x--;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            case 'd':
            {
                int x1 = x + 1;
                if (map[y][x1] == '0'){
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                } else if (map[y][x1] == '9')
                {
                    map[y][x] = '0';
                    x++;
                    map[y][x] = '4';
                    reachingEndOfTheMaze();
                }
                break;
            }
            default:
            {
                continue;
            }
                break;
        }
        moveCount += 1;
    }
}
    
void forTheMaze::setInsideMaze(bool iM){
    this -> insideMaze = iM;
}

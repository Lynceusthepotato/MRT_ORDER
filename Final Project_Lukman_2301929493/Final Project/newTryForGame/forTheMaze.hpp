//
//  forTheMaze.hpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 12/06/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#define N 10
#define M 20

#ifndef forTheMaze_hpp
#define forTheMaze_hpp

#include <stdio.h>
#include "Game.hpp"

class forTheMaze {
    
public:

    void mazeMapOne();
    void mazeMapTwo();
    void mazeMapThree();
    void shortestDistanceText(char map[N][M]);
    // void goToBattle(); can't ;-;
    int minDistance(char map[N][M]);
    void reachingEndOfTheMaze();
    void setInsideMaze(bool iM);
    void setRandomizeMaze(int sRM);
    bool getYouDidMinMove();
    
    
private:
    int reward;
    int endingMaze = 1;
    bool insideMaze = true;
    bool youDidMinMove = false;
    int minDistForReward;
    int moveCount = 1;
    char movement;
    char map[N][M];
    int x,x1,x2,y,y1,y2;
    int randomizeMaze;
};

class qL : public forTheMaze {
public:
    int row,col,dist;
    qL(int a, int b, int c) : row(a), col(b), dist(c){}

};
#endif /* forTheMaze_hpp */

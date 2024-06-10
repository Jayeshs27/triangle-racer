#if !defined(__SCORE_H__)
#define __SCORE_H__

#include "libraries.h"

class CurrentScoreBoard{
    public:
    CurrentScoreBoard();
    void incrementScore();
    void draw();
    private:
    unsigned long long int score;
};

class FinalScoreBoard{
    public:
    FinalScoreBoard();
    void draw();
    private:
    unsigned long long int finalScore;
};


#endif // __SCORE_H__

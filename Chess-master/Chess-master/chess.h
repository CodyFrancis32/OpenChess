#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <iostream>
#include <QPainter>
#include <QColor>   //if I recall correctly, defined as 3 values, green blue red.  255 255 255 is white....etc lookup
#include <QMouseEvent>
#include <QDebug>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

void paintEvent(QPaintEvent*); //prototype THIS PROBABLY ISNT NEEDED SINCE PROTOTYPE IS IN  CHESS. Doesnt hurt to leave it in.
void draw(int x, int y, QPainter* paint); //protoype   THIS PROBABLY ISNT NEEDED SINCE PROTOTYPE IS IN  CHESS
//Debugging
    //virtual bool canMove(int startx, int starty, int endx, int endy);//=0;
    //bool canMove(int startx, int starty, int endx, int endy);

class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = 0);
    ~Chess();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    int startx;
    int starty;
    int endx;
    int endy;
};

class Piece //: Chess
{
public:
    int id; 
    Piece(bool);   //calling constructor
    bool color;
    QImage image;//(Piece);
    void draw(int x, int y, QPainter* paint); //prototype
    virtual bool canMove(int startx, int starty, int endx, int endy)=0;
};

class Rook : public Piece
{
public:
    //int id;
    Rook (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy);// = false;
};

class Bishop : public Piece
{
public:
    Bishop (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy); //= false;
};

class Queen : public Piece
{
public:
    Queen (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy);

};

//King and Pawn are easiest, starting here and working my way though other classes.
class King : public Piece
{
public:
    King (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy);
    //Debugging/Testing
        /*bool canMove(int startx, int starty, int endx, int endy)
        {
            if(abs(startx-endx)==1 && abs(starty-endy)==1)
                if(board[endx][endy] !=NULL && board[endx][endy]->color!=color)
                        return true;
            else
                return false;
        }*/
};

class Knight : public Piece
{
public:
    Knight (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy);
};

class Pawn : public Piece
{
public:
    Pawn (bool c); //calling constructor
    bool canMove(int startx, int starty, int endx, int endy);
};

#endif // CHESS_H

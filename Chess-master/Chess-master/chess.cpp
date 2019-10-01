#include "chess.h"

Piece*  board[8][8];   //make space for board array


Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Chess by Cody Francis");
    resize(44*8, 44*8);         //make size of screen
    for (int y=0;y<8;y++)
    {
        for (int x=0;x<8;x++)
        {
            board[x][y]=NULL;  // set all spots to NULL
        }
    }
    //CORDINATES FOR EACH
    //board[x][y]  (X IS FIRST THAN Y)
    board[0][0] = new Rook(false); //setting rooks to black at location
    board[7][7] = new Rook(true);
    board[7][0] = new Rook(false);
    board[0][7] = new Rook(true);
    board[1][0] = new Knight(false);
    board[1][7] = new Knight(true);
    board[2][0] = new Bishop(false);
    board[2][7] = new Bishop(true);
    board[3][0] = new Queen(false);
    board[3][7] = new Queen(true);
    board[4][0] = new King(false);
    board[4][7] = new King(true);
    board[5][0] = new Bishop(false);
    board[5][7] = new Bishop(true);
    board[6][0] = new Knight(false);
    board[6][7] = new Knight(true);
    //pawns
    for (int y=0;y<8;y++)
    {
        for (int x=0;x<8;x++)
        {
            if (y==6)
                board[x][y]=new Pawn(true);
            if (y==1)
                board[x][y]=new Pawn(false);
        }
    }


}

Chess::~Chess()
{

}

void Chess::paintEvent(QPaintEvent*)
{
    QPainter paint(this);

    //int checker_board[8][8];
    int count = 0;

    for (int y=0; y<8; y++)
    {
        for (int x=0; x<8; x++)
        {
            if ((count++ % 2) == 0)
                paint.fillRect(x*44,y*44,44,44,QColor(177,113,24));
            else
                paint.fillRect(x*44,y*44,44,44,QColor(233,174,95));
        }
        count++;
    }

    for (int y=0;y<8;y++)
    {
        for (int x=0;x<8;x++)
        {
            if(board[x][y]!=NULL)
                board[x][y]->draw(x,y,&paint);
        }
    }


}

Piece::Piece(bool c) //constructor
{
    //bool color = c; //white = true
    color = c;
}

Rook::Rook(bool c):Piece(c) //constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wrook.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/brook.gif").toImage();
}

bool Rook:: canMove(int startx, int starty, int endx, int endy)
{
    int i;
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
   // Collision detection
    if (startx == endx)
    {
        // Horizontal move
        if (starty < endy)
        {
            // Move down
            for (i = starty + 1; i < endy; ++i)
                if (board[startx][i] != NULL)// && board[startx][i]->color==color)
                    return false;

        }
        else
        {
            // Move up
            for (i = starty - 1; i > endy; --i)
                if (board[startx][i] != NULL)// && board[startx][i]->color==color) //cant allow passing of non color piece
                    return false;
        }
    }
    else if (starty == endy)
    {
        // Vertical move
        if (startx < endx)
        {
            // Move right
            for (i = startx + 1; i < endx; ++i)
                if (board[i][starty] != NULL)// && board[i][starty]->color==color)
                    return false;
        }
        else
        {
            // Move left
            for (i = startx - 1; i > endx; --i)
                if (board[i][starty] != NULL)// && board[i][starty]->color==color)
                    return false;
        }
    }
    else
    {
        // Not a valid rook move (neither horizontal nor vertical)
        return false;
    }

    return true;
}

Bishop::Bishop(bool c):Piece(c) //constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wbishop.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/bbishop.gif").toImage();
    //canMove = false;
}

bool Bishop:: canMove(int startx, int starty, int endx, int endy)
{
    int i;
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
    if(starty>endy && startx < endx) //moving up and to the right  
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count = 1;
            for (i = startx + 1; i < endx; ++i)
            {
               if (board[startx+count][starty-count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty>endy && startx > endx) //moving up and to the left
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count =  1;
            for (i = startx - 1; i > endx; --i)
            {
               if (board[startx-count][starty-count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty<endy && startx < endx) //moving down and to the right
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count = 1;
            for (i = starty + 1; i < endy; ++i)
            {
               if (board[startx+count][starty+count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty<endy && startx > endx) //moving down and to the left
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count =  1;
            for (i = starty + 1; i < endy; ++i)
            {
               if (board[startx-count][starty+count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }


    else
    {
        // Not a valid move
        return false;
    }

    return true;
}

Queen::Queen(bool c):Piece(c) //constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wqueen.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/bqueen.gif").toImage();
    //canMove = false;
}

bool Queen:: canMove(int startx, int starty, int endx, int endy)
{
    int i;
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
   // Collision detection
    if (startx == endx)
    {
        // Horizontal move
        if (starty < endy)
        {
            // Move down
            for (i = starty + 1; i < endy; ++i)
                if (board[startx][i] != NULL)// && board[startx][i]->color==color)
                    return false;

        }
        else
        {
            // Move up
            for (i = starty - 1; i > endy; --i)
                if (board[startx][i] != NULL)// && board[startx][i]->color==color) //cant allow passing of non color piece
                    return false;
        }
    }
    else if (starty == endy)
    {
        // Vertical move
        if (startx < endx)
        {
            // Move right
            for (i = startx + 1; i < endx; ++i)
                if (board[i][starty] != NULL)// && board[i][starty]->color==color)
                    return false;
        }
        else
        {
            // Move left
            for (i = startx - 1; i > endx; --i)
                if (board[i][starty] != NULL)// && board[i][starty]->color==color)
                    return false;
        }
    }
    else if(starty>endy && startx < endx) //moving up and to the right  
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count = 1;
            for (i = startx + 1; i < endx; ++i)
            {
               if (board[startx+count][starty-count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty>endy && startx > endx) //moving up and to the left
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count =  1;
            for (i = startx - 1; i > endx; --i)
            {
               if (board[startx-count][starty-count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty<endy && startx < endx) //moving down and to the right
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count = 1;
            for (i = starty + 1; i < endy; ++i)
            {
               if (board[startx+count][starty+count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }

    else if(starty<endy && startx > endx) //moving down and to the left
    {
        if (abs(startx-endx)==abs(starty-endy))
        {
            int count =  1;
            for (i = starty + 1; i < endy; ++i)
            {
               if (board[startx-count][starty+count] != NULL) //&& board[startx+i][starty]->color == color)// && board[i][starty]->color==color)
                     return false;
                count = count + 1;
            }
            return true;
        }
        else
            return false;
    }


    else
    {
        // Not a valid move
        return false;
    }

    return true;
}


King::King(bool c):Piece(c) //constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wking.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/bking.gif").toImage();
    //canMove = false;
}

bool King:: canMove(int startx, int starty, int endx, int endy)
{
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
    if(abs(starty-endy)==1 && (abs(startx-endx)==1))
        return true;
    if(abs(starty-endy)==1 && (abs(startx-endx)<=1))
        return true;
    if(abs(starty-endy)<=1 && (abs(startx-endx)==1))
        return true;
    else
        return false;
    //return true;
}


Knight::Knight(bool c):Piece(c) //constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wknight.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/bknight.gif").toImage();
    //canMove = false;
}

bool Knight:: canMove(int startx, int starty, int endx, int endy)
{
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
    if(abs(starty-endy)==2 && (abs(startx-endx)==1))
        return true;
    if(abs(starty-endy)==1 && (abs(startx-endx)==2))
        return true;
    else
        return false;
}

Pawn::Pawn(bool c):Piece(c) // constructor
{
    if(c == true)
        image=QPixmap(":chess_images/wpawn.gif").toImage();
    else if (c == false)
        image=QPixmap(":chess_images/bpawn.gif").toImage();
    //canMove = false;
}

bool Pawn:: canMove(int startx, int starty, int endx, int endy) //can jump t0 y=4
{
    if(board[endx][endy] !=NULL && board[endx][endy]->color==color)
        return false;
    if(board[startx][starty]->color==true) //attacking enemy piece (white)
        if(board[endx][endy] != NULL)
            if(board[endx][endy]->color!=color)
                if((starty-endy)==1)
                    if(abs(startx-endx)==1)
                        return true;
    if(board[startx][starty]->color==false) //attacking enemy piece (black)
        if(board[endx][endy] != NULL)
            if(board[endx][endy]->color!=color)
                if(starty-endy==-1)
                    if(abs(startx-endx)==1)
                        return true;

    if(board[startx][starty]->color==true) //double moveoff start
        if(endy == 4)
            if(starty==6)
                if(startx-endx == 0)
                    if(board[endx][endy] == NULL)
                        return true;
    if(board[startx][starty]->color==true) //white peace so it can move up
        if(starty-endy==1)
            if(startx-endx == 0)
                if(board[endx][endy] == NULL)
                    return true;
    if(board[startx][starty]->color==false) //double move off start(black)
        if(endy == 3)
            if(starty==1)
                if(startx-endx == 0)
                    if(board[endx][endy] == NULL)
                        return true;
    if(board[startx][starty]->color==false) //black peace so it can move down
        if(starty-endy==-1)
            if(startx-endx == 0)
                if(board[endx][endy] == NULL)
                    return true;
    //Testing
        /*if(board[startx][starty]->color == true) //make the pawn into a queen
            if(starty == 1)
                if(endy == 0)
                {
                    board[endx][endy] = new Queen(true);
                    return true;
                }*/

    else
        return false;
}

void Piece::draw(int x, int y, QPainter* paint)
{
    //paint->drawImage(x,y,image);
    paint->drawImage(x*44,y*44,image);

}

void Chess::mousePressEvent(QMouseEvent* event)
{

    startx = event->x()/44;
    starty = event->y()/44;
    
    //Old, mouse ReleaseEvent will house host my click code.
    
    /*if(startx < 8 && !NULL)
        //code in here
    if(starty < 8 && !NULL)
        //code in here
    else
        return;*/
    
    //Debugging
        //event->x()/44;
        //event->y()/44;
        //qDebug()<<event->x()/44;
        //qDebug()<<event->y()/44;
}

void Chess::mouseReleaseEvent(QMouseEvent* event)
{
    endx = event->x()/44;
    endy = event->y()/44;

    /*In mouseReleaseEvent, call canMove and only move the piece if it returns true.
     * Test the program and make sure none of the piece move.*/

    if (board[startx][starty] != NULL)
        if(endx < 8)
            if(endx>=0)
                if(endy < 8)
                    if(endy>=0)
                        if(startx < 8)
                            if(starty < 8)
                                if(board[startx][starty]->canMove(startx,starty,endx,endy)==true)
                                {
                                    board[endx][endy]=board[startx][starty];
                                    board[startx][starty]=NULL;
                                    repaint();
                                }
                                else
                                    return;
    //Debugging
        //event->x()/44;
        //event->y()/44;
        //qDebug()<<event->x()/44;
    //qDebug()<<event->y()/44;

    //The below is just so I can have the "AI" play against me. Has to be a valid move.
    while (true) //Making it so in mouse release event, as soon as I let go, the "AI" has to make a valid move.
    {
        bool AIcolor = false;

        int AIstartx = rand()%8;
        int AIstarty = rand()%8;
        int AIendx = rand()%8;
        int AIendy = rand()%8;

        if(board[AIstartx][AIstarty] == NULL)
            continue;
        else if(board[AIstartx][AIstarty]->color != AIcolor) //AI can only be black
            continue;
        else if(board[AIstartx][AIstarty]->canMove(AIstartx,AIstarty,AIendx, AIendy)==true)
        {
            board[AIendx][AIendy]=board[AIstartx][AIstarty];
            board[AIstartx][AIstarty]=NULL;
            repaint();
            break;
        }
    }
}


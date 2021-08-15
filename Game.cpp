#include <iostream>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;

// Setting up the Keyboard controller to control surface
//-----------------------------------------------------------------
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 120
// -----------------------------------------------------------------

// Setting up the window application size
// ------------------------------------------------------------
// Definning the height and width of the console windlows
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 700

// Setting variable for to manipulate Console window size
HWND Window_Console = GetConsoleWindow();
RECT Windows_Console_React;

// Set consloe windows size
void SetConsloeWindowsSize()
{
    GetWindowRect(Window_Console, &Windows_Console_React);
    MoveWindow(Window_Console, Windows_Console_React.left, Windows_Console_React.top, SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
}
//----------------------------------------------------------------

// Setting up the console cursor for all the object
//---------------------------------------------------------------

// Setting up the console cursor for Room
HANDLE Room_Output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Room_Position;
// set position of the room
void SetRoomPosition(int x, int y)
{
    Room_Position.X = x;
    Room_Position.Y = y;
    SetConsoleCursorPosition(Room_Output, Room_Position);
}

// setting up the console cursor for moveable surface
HANDLE Surface_Output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Surface_Position;
// set position of the that surface
void SetSurfacePosition(int x, int y)
{
    Surface_Position.X = x;
    Surface_Position.Y = y;
    SetConsoleCursorPosition(Surface_Output, Surface_Position);
}

// setting up the consloe cursor for thorn(Kada or death)
HANDLE Thorn_Output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Thorn_Position;
// set position of the that Thorn
void SetThornPosition(int x, int y)
{
    Thorn_Position.X = x;
    Thorn_Position.Y = y;
    SetConsoleCursorPosition(Thorn_Output, Thorn_Position);
}

// setting up the consloe cursor for Bricks
HANDLE Bricks_Output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Bricks_Position;
// set position of the that Bricks
void SetBricksPosition(int x, int y)
{
    Bricks_Position.X = x;
    Bricks_Position.Y = y;
    SetConsoleCursorPosition(Bricks_Output, Bricks_Position);
}

// setting up the consloe cursor for Balls
HANDLE Balls_Output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Balls_Position;
// set position of the that Bricks
void SetBallsPosition(int x, int y)
{
    Balls_Position.X = x;
    Balls_Position.Y = y;
    SetConsoleCursorPosition(Balls_Output, Balls_Position);
}
//---------------------------------------------------------------------

class Gaming_Room
{
    int Room_Height = 35, Room_Width = 120;

public:
    int ReturnHeight()
    {
        return Room_Height;
    }
    int ReturnWidht()
    {
        return Room_Width;
    }
    // Building wall
    void SetRoomWall()
    {
        for (int i = 0; i < Room_Width * 2 + 2; i++)
        {
            cout << "_";
            if (i == Room_Width + 1)
            {
                cout << endl
                     << "__";
            }
        }
        SetRoomPosition(0, Room_Height + 1);
        for (int i = 0; i < Room_Width * 2 + 1; i++)
        {
            cout << "_";
            if (i == Room_Width)
            {
                cout << endl
                     << "__";
            }
        }
        SetRoomPosition(0, 2);
        for (int i = 0; i < Room_Height; i++)
        {
            cout << "||" << endl;
        }
        for (int i = 0; i < Room_Height; i++)
        {
            SetRoomPosition(Room_Width, i + 2);
            cout << "||" << endl;
        }
    }
};

class Thorn : public Gaming_Room // kadha(nepali) or death(game over)
{
    int a, b;

public:
    void DisplayThorn()
    {
        SetThornPosition(2, ReturnHeight() - 1);
        for (int i = 0; i < ReturnWidht() - 2; i++)
        {
            cout << "^";
        }
        SetThornPosition(2, ReturnHeight());
        for (int i = 0; i < (ReturnWidht() - 2) / 2; i++)
        {
            cout << "^*";
        }
    }
};

class Move
{
};

class Balls : public Gaming_Room
{
    int Balls_Position[200][100];
    int X_Border = ReturnWidht() - 4, Y_Border = ReturnHeight() - 4;
    int Ball_Angle = 0;
    int i = 0;
    int count = 0;

public:
    void DisplayBalls()
    {
        for (int i = 0; i < ReturnHeight() - 4; i++)
        {
            SetBallsPosition(2, 2 + i);
            for (int j = 0; j < ReturnWidht() - 2; j++)
            {
                cout << "0";
            }
            cout << endl;
        }
    }
    //    int usleep(useconds_t useconds)
    //    {
    //        Control_Surface c;
    //        c.MoveSurface();
    //        return -1;
    //    }
    //    unsigned sleep(unsigned seconds)
    //    {
    //        Control_Surface c;
    //        c.MoveSurface();
    //        return 0;
    //    }

    int MoveBall()
    {
        int Ball_X_Position = 4;
        int Ball_Y_Position = 30;

        while (i < 30)
        {

            if (count == 4)
            {
                SetBallsPosition(Ball_X_Position + Ball_Angle, Ball_Y_Position - 4 - i);
                cout << "0";
                //              usleep(1);
                SetBallsPosition(Ball_X_Position + Ball_Angle - 1, Ball_Y_Position - 3 - i);
                cout << " ";
                //              Sleep(40);
                Ball_Angle += 1;
                i++;
                count = 0;
            }
            count++;
            return 0;
        }
    }
};

class Control_Surface : public Gaming_Room
{
    int Row_Surface = 16, Column_Surface = 1;
    char Moving_Surface[1][10];
    char Right_Gap[1][120], Left_Gap[1][120];
    int No_Right_Gap = (ReturnWidht() / 2) - 12, No_Left_Gap = (ReturnWidht() / 2) - 6;
    int Move_Left = 0, Move_Right = 0;
    Balls ball1;

public:
    void Set_Surface()
    {
        for (int i = 0; i < Column_Surface; i++)
        {
            for (int j = 0; j < Row_Surface; j++)
            {
                Moving_Surface[i][j] = '=';
            }
        }
    }
    void displayLeftGap()
    {
        for (int i = 0; i < No_Left_Gap; i++)
        {
            cout << " ";
        }
    }
    void displayRightGap()
    {
        for (int i = 0; i < No_Right_Gap; i++)
        {
            cout << " ";
        }
    }
    void display_surface()
    {
        for (int i = 0; i < Column_Surface; i++)
        {
            for (int j = 0; j < Row_Surface; j++)
            {
                cout << '=';
            }
            cout << endl;
        }
    }
    void MoveSurface()
    {
        SetSurfacePosition(2, ReturnHeight() - 2);
        displayLeftGap();
        SetSurfacePosition((ReturnWidht() / 2) - 4, ReturnHeight() - 2);
        display_surface();
        SetSurfacePosition((ReturnWidht() / 2) + 12, ReturnHeight() - 2);
        displayRightGap();
        int countleft = 0, countright = 0;
        char key = getch();
        int value = key;
        int count_left = 1, count_right = 1;
        while (value != KEY_X)
        {
            switch (getch())
            {
            case KEY_LEFT:
                if (No_Left_Gap > 0)
                {
                    No_Right_Gap = No_Right_Gap + 2;
                    Move_Left = Move_Left + 2;
                    Move_Right = Move_Right - 2;
                    No_Left_Gap = No_Left_Gap - 2;
                }
                break;
            case KEY_RIGHT:
                if (No_Right_Gap > 0)
                {
                    No_Left_Gap = No_Left_Gap + 2;
                    Move_Right = Move_Right + 2;
                    Move_Left = Move_Left - 2;
                    No_Right_Gap = No_Right_Gap - 2;
                }
                break;
            }
            if (No_Right_Gap <= -2 || No_Left_Gap <= -2)
            {
            }
            else
            {
                SetSurfacePosition(2, ReturnHeight() - 2);
                displayLeftGap();
                SetSurfacePosition((ReturnWidht() / 2) - 4 + Move_Right, ReturnHeight() - 2);
                display_surface();
                SetSurfacePosition((ReturnWidht() / 2) + 12 + Move_Right, ReturnHeight() - 2);
                displayRightGap();
            }
            //            ball1.MoveBall();
        }
    }
};

class Bricks : public Gaming_Room
{
    int CountRowBricks = (ReturnWidht() / 5) - 3, CountColumnBricks = (ReturnHeight() / 4) - 3;

public:
    void DisplayBricks()
    {
        for (int column = 0; column < CountColumnBricks; column++)
        {
            for (int row = 0; row < CountRowBricks; row++)
            {
                for (int i = 0; i < 2; i++)
                {
                    SetBricksPosition(9 + (row * 5), (column * 3) + 5 + i);
                    for (int j = 0; j < 4; j++)
                    {
                        cout << "#";
                    }
                    cout << endl;
                }
            }
        }
    }
};

int main()
{
    SetConsloeWindowsSize();
    Gaming_Room Room1;
    Room1.SetRoomWall();
    Thorn thorn1;
    thorn1.DisplayThorn();
    Bricks brick1;
    brick1.DisplayBricks();
    Balls ball1;
    ball1.MoveBall();
    Control_Surface Surface1;
    Surface1.MoveSurface();
    cin.get();
    return 0;
}

//void MoveBall()
//    {
//        int i = 0;
//        int num;
//        num = 31;
//        int py = 1;
//        int gap = num - py;
//        int row = num - (gap / 2);
//        int movePy = num;
//        int incr = 1;
//        int decr = num;
//        int count = 0;
//        for (int i = 0; i < row; i++)
//        {
//            SetBallsPosition(10, 10 + i);
//            for (int gf = 0; gf < gap / 2; gf++)
//            {
//                cout << " ";
//            }
//            cout << "0";
//            for (int gm = 0; gm < py - 2; gm++)
//            {
//                cout << " ";
//            }
//            if (py > 1)
//            {
//                cout << "0";
//            }
//            for (int gl = 0; gl < gap / 2; gl++)
//            {
//                cout << " ";
//            }
//            cout << "\n";
//            py += 2;
//            gap -= 2;
//            incr += 2;
//        }
//    }

//Design of the room

// class Gaming_Room
// {
// public:
//     void Set_Wall()
//     {
//         cout << "  "
//              << "_____________________________________________________________________________________________________________________________________________"
//              << endl
//              << "||"
//              << "_____________________________________________________________________________________________________________________________________________"
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(72) << "O" << setw(71)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||" << setw(143)
//              << "||" << endl
//              << "||"
//              << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
//              << "||" << endl
//              << "||"
//              << "^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^"
//              << "||" << endl
//              << "||"
//              << "_____________________________________________________________________________________________________________________________________________"
//              << "||" << endl
//              << "||"
//              << "_____________________________________________________________________________________________________________________________________________"
//              << "||";
//     }
// };

/*
PROBLEM

Consider a chessboard represented as a two-dimensional array of size n x n.
Let n be the number of rooks, and define a configuration of n rooks on this board as "peaceful"
if each row and each column of the board contains exactly one rook. Given a number k,
generate all possible configurations with the property that there exists a k x k square
that does not contain any rook of the configuration.
*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>  // Library for _kbhit() and _getch()
#include <limits>
#include <iomanip>
using namespace std;

char FREE = '-';
char OCCUPIED = '*';
char BORDER = '#';

struct Chessboard
{
    char data[51][51];
    int size;
    int squareSize;
};

void Wait(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool IsKeyPressed()
{
    if (_kbhit()) // Check if a key has been pressed
    {
        char key = _getch(); // Read the pressed key
        if (key == '1') // The user pressed the key 1 to interrupt
        {
            cout << "The process has been interrupted by the user.\n";
            return true;
        }
        else if (key == '2') // The user pressed the key 2 to resume
        {
            cout << "The process will be resumed.\n";
            return true;
        }
    }
    return false;
}

void CheckKeyPress()
{
    if (IsKeyPressed()) // Check if the user pressed a key
    {
        cout << "Press key 2 to resume or any other key to exit: ";
        char key = _getch(); // Read the pressed key
        if (key == '2')
        {
            cout << "Resuming the process.\n";
            Wait(1000);
        }
        else
        {
            cout << "The process has been stopped by the user.\n";
            exit(0);
        }
    }
}

void ClearScreen()
{
    // Use "cls" to clear the screen
    system("cls");
}

bool IsSafe(Chessboard& board, int row, int col)
{
    // Check if it's safe to place a rook at this position
    for (int i = 0; i < board.size; ++i)
    {
        if (board.data[row][i] == OCCUPIED || board.data[i][col] == OCCUPIED)
        {
            return false; // There is already a rook in this row or column
        }
    }
    return true;
}

void DisplayBoard(Chessboard& board)
{
    system("cls");
    for (int i = 0; i < board.size; ++i)
    {
        for (int j = 0; j < board.size; ++j)
        {
            if (board.data[i][j] == OCCUPIED)
                cout << setw(6) << "|  R  ";
            else if (board.data[i][j] == BORDER)
                cout << setw(6) << "|  B  ";
            else if ((i + j) % 2 == 0)
                cout << setw(6) << "|-----";
            else
                cout << setw(6) << "|     ";
        }
        cout << "|" << endl;

        for (int k = 0; k < board.size; ++k)
            cout << "+-----";
        cout << "+" << endl;
    }
}

void PlaceRook(Chessboard& board, int row, int col)
{
    board.data[row][col] = OCCUPIED;
    cout << "Place rook at position (" << row << ", " << col << ")" << endl;

    Wait(1000);
    DisplayBoard(board);
}

void RemoveRook(Chessboard& board, int row, int col)
{
    board.data[row][col] = FREE;

    if (row == board.size - 1)
    {
        cout << "Do you want to move to the next configuration? (YES/NO): ";
        string answer;
        cin >> answer;

        if (answer == "YES" || answer == "yes" || answer == "Yes" || answer == "y")
        {
            // Continue with the next configuration
            cout << "Remove rook from position (" << row << ", " << col << ")" << endl;
            Wait(1000);
            DisplayBoard(board);
            return;
        }
        else
        {
            // End the program
            cout << "Configurations have finished." << endl;
            exit(0);
        }
    }
    else
    {
        // If not on the last row, continue without asking the user
        cout << "Remove rook from position (" << row << ", " << col << ")" << endl;
        Wait(1000);
        DisplayBoard(board);
        return;
    }
    cout << "Remove rook from position (" << row << ", " << col << ")" << endl;
}

void RemoveIncorrectRook(Chessboard& board, int row, int col)
{
    board.data[row][col] = FREE;

    cout << "Remove rook from position (" << row << ", " << col << ")" << endl;
    Wait(1000);
    DisplayBoard(board);
    return;
}

void PlaceBorder(Chessboard& board, int row, int col)
{
    for (int x = row; x < row + board.squareSize; ++x)
    {
        for (int y = col; y < col + board.squareSize; ++y)
        {
            board.data[x][y] = BORDER;
        }
    }
    cout << "Place border for square at position (" << row << ", " << col << ")" << endl;

    Wait(1000);
    DisplayBoard(board);
}

void RemoveBorder(Chessboard& board, int row, int col)
{
    for (int x = row; x < row + board.squareSize; ++x)
    {
        for (int y = col; y < col + board.squareSize; ++y)
        {
            board.data[x][y] = FREE;
        }
    }
    cout << "Remove border for square from position (" << row << ", " << col << ")" << endl;

    Wait(1000);
    DisplayBoard(board);
}

void SolveRooks(Chessboard& board, int row, int& squareCounter)
{
    if (row == board.size)
    {
        CheckKeyPress();
        // Found a solution, display and wait for visualization
        CheckKeyPress();
        DisplayBoard(board);
        Wait(1000);

        int SquaresFound = 0;  // Number of squares found in this configuration

        // Check if the condition with the square of size k is satisfied
        for (int i = 0; i <= board.size - board.squareSize; ++i)
        {
            CheckKeyPress();
            for (int j = 0; j <= board.size - board.squareSize; ++j)
            {
                CheckKeyPress();
                bool squareValid = true;
                for (int x = i; x < i + board.squareSize; ++x)
                {
                    CheckKeyPress();
                    for (int y = j; y < j + board.squareSize; ++y)
                    {
                        CheckKeyPress();
                        if (board.data[x][y] == OCCUPIED)
                        {
                            squareValid = false;
                            break;
                        }
                    }
                    if (!squareValid)
                    {
                        break;
                    }
                }
                if (squareValid)
                {
                    CheckKeyPress();
                    // BORDER THE SQUARE WITH #
                    PlaceBorder(board, i, j);
                    CheckKeyPress();
                    Wait(1000);
                    // Reset the border to explore other configurations
                    RemoveBorder(board, i, j);
                    CheckKeyPress();
                    SquaresFound++;
                }
            }
        }

        cout << "Number of squares found in this configuration: " << SquaresFound << endl;

        squareCounter += SquaresFound;  // Update the global counter

        return;
    }

    for (int col = 0; col < board.size; ++col)
    {
        CheckKeyPress();

        if (IsSafe(board, row, col))
        {
            CheckKeyPress();
            PlaceRook(board, row, col);
            CheckKeyPress();
            Wait(1000);
            SolveRooks(board, row + 1, squareCounter);
            CheckKeyPress();
            RemoveRook(board, row, col);
            CheckKeyPress();
            Wait(1000);
        }
        else
        {
            CheckKeyPress();
            PlaceRook(board, row, col);
            Wait(1000);
            CheckKeyPress();
            cout << "Incorrectly positioned rook" << endl;
            Wait(1000);
            RemoveIncorrectRook(board, row, col);
            CheckKeyPress();
            Wait(1000);
        }
    }

    if (row == 0)
    {
        // Configurations are finished
        cout << "Configurations have finished." << endl;
        exit(0);
    }
}

int main()
{
    Chessboard board;

    system("cls");
    do
    {
        cout << "Enter the size of the chessboard (n, between 2 and 50): ";
        if (!(cin >> board.size) || board.size < 2 || board.size > 50)
        {
            system("cls");
            cout << "Invalid option. Enter a value between 2 and 50." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    while (true);

    do
    {
        cout << "Enter the size of the square (k, between 1 and " << board.size - 1 << "): ";
        if (!(cin >> board.squareSize) || board.squareSize < 1 || board.squareSize >= board.size)
        {
            system("cls");
            cout << "Invalid option. Enter a value between 1 and " << board.size - 1 << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    while (true);

    for (int i = 0; i < 51; ++i)
    {
        for (int j = 0; j < 51; ++j)
        {
            board.data[i][j] = FREE;
        }
    }

    int squareCounter = 0;
    Wait(1000);
    system("cls");
    SolveRooks(board, 0, squareCounter);

    cout << "Total number of squares found: " << squareCounter << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <random>
using namespace std;

enum class CellState { Empty, X, O };

class TicTacToe 
{
public:
    TicTacToe(int size);
    void printField();
    bool makeMove(int row, int col);
    void makeRandomMove();

private:
    vector<vector<CellState>> field;
    int size, movesMade;
    CellState currentPlayer;

    char cellStateToSymbol(CellState state);
    bool isInsideBoundaries(int row, int col);
    bool checkForWin(int row, int col);
    void resetGame();
};

TicTacToe::TicTacToe(int size) : 
    size(size), currentPlayer(CellState::X), movesMade(0) 
{
    field.resize(size, std::vector<CellState>(size, CellState::Empty));
    srand(time(NULL));
}

void TicTacToe::printField()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << cellStateToSymbol(field[i][j]) << " ";
        }
        cout << endl;
    }
}

bool TicTacToe::makeMove(int row, int col)
{
    if (!isInsideBoundaries(row, col) || field[row][col] != CellState::Empty)
    {
        cout << "�������� ��������, ���������� ��� ���!" << endl;
        return false;
    }

    field[row][col] = currentPlayer;
    ++movesMade;

    cout << "���� ����� ���� ������ " << cellStateToSymbol(currentPlayer) << ":" << endl;
    printField();

    if (checkForWin(row, col))
    {
        cout << "����� " << cellStateToSymbol(currentPlayer) << " �������!" << endl;
        resetGame();
    }
    else if (movesMade == size * size)
    {
        cout << "�����!" << endl;
        resetGame();
    }
    currentPlayer = (currentPlayer == CellState::X) ? CellState::O : CellState::X;
    return true;
}

void TicTacToe::makeRandomMove()
{
    vector<pair<int, int>> availableMoves;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (field[i][j] == CellState::Empty)
            {
                availableMoves.push_back(make_pair(i, j));
            }
        }
    }

    int randomIndex = rand() % availableMoves.size();
    int row = availableMoves[randomIndex].first;
    int col = availableMoves[randomIndex].second;

    field[row][col] = currentPlayer;
    ++movesMade;

    cout << "���� ����� ���� ����������:" << endl;
    printField();

    if (checkForWin(row, col))
    {
        cout << "����� " << cellStateToSymbol(currentPlayer) << " �������!" << endl;
        resetGame();
    }
    else if (movesMade == size * size)
    {
        cout << "�����!" << endl;
        resetGame();
    }
    currentPlayer = (currentPlayer == CellState::X) ? CellState::O : CellState::X;
}

char TicTacToe::cellStateToSymbol(CellState state)
{
    switch (state)
    {
    case CellState::Empty:
        return '-';
    case CellState::X:
        return 'X';
    case CellState::O:
        return 'O';
    }
}

bool TicTacToe::isInsideBoundaries(int row, int col)
{
    return row >= 0 && row < size && col >= 0 && col < size;
}

bool TicTacToe::checkForWin(int row, int col)
{
    // ��������� ������
    bool win = true;
    for (int i = 0; i < size; ++i)
    {
        if (field[row][i] != currentPlayer)
        {
            win = false;
            break;
        }
    }
    if (win) return true;

    // ��������� �������
    win = true;
    for (int i = 0; i < size; ++i)
    {
        if (field[i][col] != currentPlayer)
        {
            win = false;
            break;
        }
    }
    if (win) return true;

    // ��������� ���������
    if (row == col)
    {
        win = true;
        for (int i = 0; i < size; ++i)
        {
            if (field[i][i] != currentPlayer)
            {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // ��������� ��������������� ���������
    if (row + col == size - 1)
    {
        win = true;
        for (int i = 0; i < size; ++i)
        {
            if (field[i][size - 1 - i] != currentPlayer)
            {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    return false;
}

void TicTacToe::resetGame()
{
    field.assign(size, vector<CellState>(size, CellState::Empty));
    movesMade = 0;
    currentPlayer = CellState::X;
    cout << "�������� ����� ����!" << endl;
    printField();
}

int main()
{
    setlocale(0, "");

    int size;
    cout << "������� ������ ����: ";
    cin >> size;

    TicTacToe game(size);
    game.printField();
        
    while (true)
    {
        int row, col;
        cout << "������� ������ � ������� (��������� � 0), ����� ������� ���: ";
        cin >> row >> col;
        while (!game.makeMove(row, col))
        {
            cout << "������� ������ � ������� (��������� � 0), ����� ������� ���: ";
            cin >> row >> col;
        }
        game.makeRandomMove();
    }

    return 0;
}

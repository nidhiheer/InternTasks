#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Enum for piece colors
enum Color { WHITE, BLACK };

// Enum for piece types
enum PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

// Piece class
// class Piece {
// public:
//     Piece(Color color, PieceType type) : color(color), type(type) {}
//     virtual ~Piece() {}
//     Color getColor() { return color; }
//     PieceType getType() { return type; }
//     virtual bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) = 0;
//     virtual bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) = 0;
// };
class Piece {
public:
    Color color;
    PieceType type;

    Piece(Color color, PieceType type) : color(color), type(type) {}

    Color getColor() { return color; }
    PieceType getType() { return type; }

    virtual bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) = 0;
    virtual bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) = 0;
};

// King class
class King : public Piece {
public:
    King(Color color) : Piece(color, KING) {}
    bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // King can attack one square in any direction
        return (abs(endX - startX) <= 1 && abs(endY - startY) <= 1);
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // King can move one square in any direction
        return (abs(endX - startX) <= 1 && abs(endY - startY) <= 1);
    }
};

// Queen class
class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, QUEEN) {}
    bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Queen can attack any square in any direction
        return (abs(endX - startX) == abs(endY - startY) || endX == startX || endY == startY);
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Queen can move any number of squares in any direction
        return (abs(endX - startX) == abs(endY - startY) || endX == startX || endY == startY);
    }
};

// Rook class
class Rook : public Piece {
public:
    Rook(Color color) : Piece(color, ROOK) {}
    bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Rook can attack any square horizontally or vertically
        return (endX == startX || endY == startY);
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Rook can move any number of squares horizontally or vertically
        return (endX == startX || endY == startY);
    }
};

// Bishop class
class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color, BISHOP) {}
    bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Bishop can attack any square diagonally
        return (abs(endX - startX) == abs(endY - startY));
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Bishop can move any number of squares diagonally
        return (abs(endX - startX) == abs(endY - startY));
    }
};

// Knight class
class Knight : public Piece {
public:
    Knight(Color color) : Piece(color, KNIGHT) {}
    bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Knight can attack any square in an L-shape
        return ((abs(endX - startX) == 2 && abs(endY - startY) == 1) || (abs(endX - startX) == 1 && abs(endY - startY) == 2));
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Knight can move in an L-shape
        return ((abs(endX - startX) == 2 && abs(endY - startY) == 1) || (abs(endX - startX) == 1 && abs(endY - startY) == 2));
    }
};

// Pawn class
class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color, PAWN) {}
       bool canAttack(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Pawn can attack diagonally one square
        if (getColor() == WHITE) {
            return (endX == startX + 1 && (endY == startY + 1 || endY == startY - 1));
        } else {
            return (endX == startX - 1 && (endY == startY + 1 || endY == startY - 1));
        }
    }
    bool isValidMove(vector<vector<Piece*>> board, int startX, int startY, int endX, int endY) override {
        // Pawn can move forward one or two squares on the first move
        if (getColor() == WHITE) {
            if (startY == 1) {
                return (endX == startX && (endY == startY + 1 || endY == startY + 2));
            } else {
                return (endX == startX && endY == startY + 1);
            }
        } else {
            if (startY == 6) {
                return (endX == startX && (endY == startY - 1 || endY == startY - 2));
            } else {
                return (endX == startX && endY == startY - 1);
            }
        }
    }
};

// Board class
class Board {
public:
    vector<vector<Piece*>> pieces;
    Board() {
        pieces.resize(8, vector<Piece*>(8, nullptr));
        // Initialize the board with pieces
        for (int i = 0; i < 8; i++) {
            pieces[1][i] = new Pawn(WHITE);
            pieces[6][i] = new Pawn(BLACK);
        }
        pieces[0][0] = pieces[0][7] = new Rook(WHITE);
        pieces[0][1] = pieces[0][6] = new Knight(WHITE);
        pieces[0][2] = pieces[0][5] = new Bishop(WHITE);
        pieces[0][3] = new Queen(WHITE);
        pieces[0][4] = new King(WHITE);
        pieces[7][0] = pieces[7][7] = new Rook(BLACK);
        pieces[7][1] = pieces[7][6] = new Knight(BLACK);
        pieces[7][2] = pieces[7][5] = new Bishop(BLACK);
        pieces[7][3] = new Queen(BLACK);
        pieces[7][4] = new King(BLACK);
    }
    ~Board() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                delete pieces[i][j];
            }
        }
    }
    bool isValidMove(int startX, int startY, int endX, int endY) {
        if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
            return false;
        }
        if (pieces[startX][startY] == nullptr) {
            return false;
        }
        if (pieces[startX][startY]->getColor() != (startX + startY) % 2) {
            return false;
        }
        if (pieces[endX][endY] != nullptr && pieces[endX][endY]->getColor() == pieces[startX][startY]->getColor()) {
            return false;
        }
        return pieces[startX][startY]->isValidMove(pieces, startX, startY, endX, endY);
    }
    void makeMove(int startX, int startY, int endX, int endY) {
        if (isValidMove(startX, startY, endX, endY)) {
            pieces[endX][endY] = pieces[startX][startY];
            pieces[startX][startY] = nullptr;
        }
    }
    bool isCheckmate(Color color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (pieces[i][j] != nullptr && pieces[i][j]->getColor() == color) {
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if (isValidMove(i, j, k, l)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    Board board;
         // Print the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.pieces[i][j] == nullptr) {
                cout << "-";
            } else {
                switch (board.pieces[i][j]->getType()) {
                    case KING:
                        cout << "K";
                        break;
                    case QUEEN:
                        cout << "Q";
                        break;
                    case ROOK:
                        cout << "R";
                        break;
                    case BISHOP:
                        cout << "B";
                        break;
                    case KNIGHT:
                        cout << "N";
                        break;
                    case PAWN:
                        cout << "P";
                        break;
                }
                if (board.pieces[i][j]->getColor() == WHITE) {
                    cout << "w";
                } else {
                    cout << "b";
                }
            }
            cout << " ";
        }
        cout << endl;
    }

    while (true) {
        // Get the move from the user
        int startX, startY, endX, endY;
        cout << "Enter the start position (x y): ";
        cin >> startX >> startY;
        cout << "Enter the end position (x y): ";
        cin >> endX >> endY;

        // Make the move
        board.makeMove(startX, startY, endX, endY);

        // Print the updated board
        cout << "Updated board:" << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board.pieces[i][j] == nullptr) {
                    cout << "-";
                } else {
                    switch (board.pieces[i][j]->getType()) {
                        case KING:
                            cout << "K";
                            break;
                        case QUEEN:
                            cout << "Q";
                            break;
                        case ROOK:
                            cout << "R";
                            break;
                        case BISHOP:
                            cout << "B";
                            break;
                        case KNIGHT:
                            cout << "N";
                            break;
                        case PAWN:
                            cout << "P";
                            break;
                    }
                    if (board.pieces[i][j]->getColor() == WHITE) {
                        cout << "w";
                    } else {
                        cout << "b";
                    }
                }
                cout << " ";
            }
            cout << endl;
        }

        // Check for checkmate
        if (board.isCheckmate(WHITE)) {
            cout << "Black wins!" << endl;
            break;
        } else if (board.isCheckmate(BLACK)) {
            cout << "White wins!" << endl;
            break;
        }
    }
    return 0;
}
   
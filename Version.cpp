#include <iostream>
#include <fstream>
#include <vector>

const int ROWS = 5;
const int COLS = 5;

enum TileColor {
    EMPTY,
    BLUE,
    GREEN,
    RED
};

class MacMahonTile {
public:
    MacMahonTile() {
        colors.resize(4, EMPTY);
    }

    void setColors(TileColor top, TileColor right, TileColor bottom, TileColor left) {
        colors[0] = top;
        colors[1] = right;
        colors[2] = bottom;
        colors[3] = left;
    }

    TileColor getColorAt(int position) const {
        if (position >= 0 && position < 4) {
            return colors[position];
        }
        return EMPTY;
    }

    void printcolor(){
            std::cout << colors[0] <<" ";
            std::cout << colors[1] <<" ";
            std::cout << colors[2] <<" ";
            std::cout << colors[3] << " \t";
    }

private:
    std::vector<TileColor> colors;
};

class MacMahonBoard {
public:
    MacMahonBoard() : board(ROWS, std::vector<MacMahonTile>(COLS)) {}

    void placeTile(int row, int col, const MacMahonTile &tile) {
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            board[row][col] = tile;
        }
    }

    const MacMahonTile& getTileAt(int row, int col) const {
        return board[row][col];
    }

    void display() const {
         for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            // Affichez toutes les couleurs de la tuile (les 4 côtés).
            for (int k = 0; k < 4; ++k) {
                //affichage des couleurs de la tuile comme demandé lettre pas chiffre 
                switch (board[i][j].getColorAt(k)) {
                    case RED:
                        std::cout << "R";
                        break;
                    case GREEN:
                        std::cout << "G";
                        break;
                    case BLUE:
                        std::cout << "B";
                        break;
                    default:
                        std::cout << " ";
                        break;
                }
                //std::cout << board[i][j].getColorAt(k) << " ";
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
    }

private:
    std::vector<std::vector<MacMahonTile>> board;
};
bool canPlaceTile(MacMahonBoard& board, int row, int col, const MacMahonTile& tile) {
    // Check the top side
    if(row > 0 && board.getTileAt(row - 1, col).getColorAt(3) != tile.getColorAt(1)) {
        return false;
    }
    // Check the left side
    if(col > 0 && board.getTileAt(row, col - 1).getColorAt(2) != tile.getColorAt(0)) {
        return false;
    }
    // Check the left side of the top board
    if(col > 0 && row ==0 && tile.getColorAt(1) != board.getTileAt(row, col - 1).getColorAt(1)) {
        return false;
    }
    // Check the top side of the left board
    if(row > 0 && col ==0 && tile.getColorAt(0) != board.getTileAt(row - 1, col).getColorAt(0)) {
        return false;
    }
    // Check the right side of the top board
    if(col == COLS - 1 && row > 0 && tile.getColorAt(2) != board.getTileAt(row - 1, col).getColorAt(2)) {
        return false;
    }
    // Check the left side of the bottom board
    if(col > 0 && row == ROWS - 1 && tile.getColorAt(3) != board.getTileAt(row, col - 1).getColorAt(3)) {
        return false;
    }
    //check left and top side of the first tile
    if (row == 0 && col == 0 && tile.getColorAt(0) != tile.getColorAt(1)) {
        return false;
    }

    return true;
}



TileColor charToTileColor(char c) {
    switch (c) {
        case 'R':
            return RED;
        case 'G':
            return GREEN;
        case 'B':
            return BLUE;
        default:
            return EMPTY;
    }
}

void readDataFromFile(const std::string& filename, MacMahonBoard& board, std::vector<MacMahonTile>& tiles) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    int rows, cols;
    file >> rows >> cols;
    if (rows != ROWS || cols != COLS) {
        std::cerr << "Les dimensions du plateau ne correspondent pas." << std::endl;
        file.close();
        return;
    }
    
    std::cout << "test." << std::endl;

    for (int i = 0; i < ROWS; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < COLS; ++j) {
            char top, right, bottom, left;
            file >> left>> top >> right >> bottom;
            MacMahonTile tile;
            tile.setColors( charToTileColor(left),charToTileColor(top), charToTileColor(right), charToTileColor(bottom));
            tile.printcolor();
            tiles.push_back(tile);
            board.placeTile(i, j, tile);
        }
                std::cout << std::endl;
    }

    // Lecture des 24 tuiles restantes
    for (int i = 0; i < 36; ++i) {
        char top, right, bottom, left;
        file >> top >> right >> bottom >> left;
        MacMahonTile tile;
        tile.setColors( charToTileColor(left),charToTileColor(top), charToTileColor(right), charToTileColor(bottom));
        tiles.push_back(tile);
    }

    file.close();
}

bool solve(MacMahonBoard& board, int row, int col, std::vector<MacMahonTile>& tiles) {
    if(row == ROWS) {
        return true; // All tiles have been placed successfully
    }

    for(int i = 0; i < tiles.size(); i++) {
        if(canPlaceTile(board, row, col, tiles[i])) {
            board.placeTile(row, col, tiles[i]);

            // Remove the tile from available tiles
            MacMahonTile usedTile = tiles[i];
            tiles.erase(tiles.begin() + i);

            int newRow = col == COLS - 1 ? row + 1 : row;
            int newCol = col == COLS - 1 ? 0 : col + 1;

            // Recursively try to solve for the next position
            if(solve(board, newRow, newCol, tiles)) {
                return true;
            }

            // If we reached here, the placement was wrong. Undo.
            tiles.insert(tiles.begin() + i, usedTile);
        }
    }
    return false; // Couldn't place a tile in the current position
}


int main() {
    MacMahonBoard board;
    std::vector<MacMahonTile> tiles;

    readDataFromFile("5x5_colorv2.txt", board, tiles);


    //time calculation
    clock_t start, end;
    start = clock();
    if(solve(board, 0, 0, tiles)) {
        std::cout << "Solution found:" << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }
    //end of time calculation
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken << " sec " << std::endl;

    std::cout << "Plateau final :" << std::endl;
    board.display();

    return 0;
}
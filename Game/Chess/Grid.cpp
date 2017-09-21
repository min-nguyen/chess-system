#include "Grid.h"


Grid::Grid(sf::RenderWindow* t_window): 
        window(t_window), 
        spriteMaker(SpriteSheet("./chessgrid.png")),
        gridState(GridState::AwaitingCellSelect),
        playerState(PlayerState::Blue){

        //Get grid sprite, set position
        chessGrid = spriteMaker.makeSprite("Grid", std::make_pair(0,0), 1000, 1000);
        chessGrid.setScale(0.5f, 0.5f);  
        chessGrid.setPosition(sf::Vector2f(0, 0));

        //Initialise empty grid of smart null ptrs
        for(auto itA = grid.begin(); itA != grid.end(); ++itA){
            for(auto itB = itA->begin(); itB != itA->end(); ++itB){
                *itB = std::make_pair(std::unique_ptr<Chess>(nullptr), ChessTeam::Empty);
                
            }
        }
        newBoard();

        // std::array<std::array<std::pair<std::unique_ptr<Chess>, ChessTeam>, 10>, 10> testarray;
        // std::unique_ptr<Pawn> p(new Pawn(ChessTeam::Red, window, std::make_pair(5, 1)));
        // testarray[5][5] =  std::make_pair(std::move(p), ChessTeam::Blue);
}

void Grid::newBoard(){
    //Pawns
    for(int i = 0; i < 10; i++){
        std::unique_ptr<Pawn> pawnRed(new Pawn(ChessTeam::Red, window, std::make_pair(i, 1)));
        std::unique_ptr<Pawn> pawnBlue(new Pawn(ChessTeam::Blue, window, std::make_pair(i, 8)));
        grid[i][1] = (std::make_pair(std::move(pawnRed), ChessTeam::Red));
        grid[i][8] = (std::make_pair(std::move(pawnBlue), ChessTeam::Blue));
    }
    //King
    std::unique_ptr<King> kingRed(new King(ChessTeam::Red, window, std::make_pair(4, 0)));
    std::unique_ptr<King> kingBlue(new King(ChessTeam::Blue, window, std::make_pair(5, 9)));
    grid[4][0] = (std::make_pair(std::move(kingRed), ChessTeam::Red));
    grid[5][9] = (std::make_pair(std::move(kingBlue), ChessTeam::Blue));
    //Queen
    std::unique_ptr<Queen> queenRed(new Queen(ChessTeam::Red, window, std::make_pair(5, 0)));
    std::unique_ptr<Queen> queenBlue(new Queen(ChessTeam::Blue, window, std::make_pair(4, 9)));
    grid[5][0] = (std::make_pair(std::move(queenRed), ChessTeam::Red));
    grid[4][9] = (std::make_pair(std::move(queenBlue), ChessTeam::Blue));
    //Bishops
    std::unique_ptr<Bishop> bishopARed(new Bishop(ChessTeam::Red, window, std::make_pair(6, 0)));
    std::unique_ptr<Bishop> bishopBRed(new Bishop(ChessTeam::Red, window, std::make_pair(3, 0)));
    std::unique_ptr<Bishop> bishopABlue(new Bishop(ChessTeam::Blue, window, std::make_pair(6, 9)));
    std::unique_ptr<Bishop> bishopBBlue(new Bishop(ChessTeam::Blue, window, std::make_pair(3, 9)));
    grid[6][0] = (std::make_pair(std::move(bishopARed), ChessTeam::Red));
    grid[3][0] = (std::make_pair(std::move(bishopBRed), ChessTeam::Red));
    grid[6][9] = (std::make_pair(std::move(bishopABlue), ChessTeam::Blue));
    grid[3][9] = (std::make_pair(std::move(bishopBBlue), ChessTeam::Blue));
    //Castles
    std::unique_ptr<Castle> castleARed(new Castle(ChessTeam::Red, window, std::make_pair(0, 0)));
    std::unique_ptr<Castle> castleBRed(new Castle(ChessTeam::Red, window, std::make_pair(9, 0)));
    std::unique_ptr<Castle> castleABlue(new Castle(ChessTeam::Blue, window, std::make_pair(0, 9)));
    std::unique_ptr<Castle> castleBBlue(new Castle(ChessTeam::Blue, window, std::make_pair(9, 9)));
    grid[0][0] = (std::make_pair(std::move(castleARed), ChessTeam::Red));
    grid[9][0] = (std::make_pair(std::move(castleBRed), ChessTeam::Red));
    grid[0][9] = (std::make_pair(std::move(castleABlue), ChessTeam::Blue));
    grid[9][9] = (std::make_pair(std::move(castleBBlue), ChessTeam::Blue));
    //Knights
    std::unique_ptr<Knight> knightARed(new Knight(ChessTeam::Red, window, std::make_pair(1, 0)));
    std::unique_ptr<Knight> knightBRed(new Knight(ChessTeam::Red, window, std::make_pair(8, 0)));
    std::unique_ptr<Knight> knightABlue(new Knight(ChessTeam::Blue, window, std::make_pair(1, 9)));
    std::unique_ptr<Knight> knightBBlue(new Knight(ChessTeam::Blue, window, std::make_pair(8, 9)));
    grid[1][0] = (std::make_pair(std::move(knightARed), ChessTeam::Red));
    grid[8][0] = (std::make_pair(std::move(knightBRed), ChessTeam::Red));
    grid[1][9] = (std::make_pair(std::move(knightABlue), ChessTeam::Blue));
    grid[8][9] = (std::make_pair(std::move(knightBBlue), ChessTeam::Blue));
}



// std::pair<std::unique_ptr<Chess>, ChessTeam>
void Grid::drawGrid(){
    window->draw(chessGrid);
    for(auto itA = grid.begin(); itA != grid.end(); ++itA){
        for(auto itB = itA->begin(); itB != itA->end(); ++itB){
            if(itB->second != ChessTeam::Empty)
                itB->first->draw();
        }
    }
}

void Grid::processInput(const sf::Vector2i t_xy){
    //Ensure mouse input within window bounds
    if((t_xy.x && t_xy.y > 0) && (t_xy.x && t_xy.y < 500) ){
        if(gridState == GridState::AwaitingCellSelect){
            selectCell(t_xy);
        }
        else if(gridState == GridState::CellSelected){
            moveCell(t_xy);
        }
    }
}


void Grid::moveCell(const sf::Vector2i t_xy){
    if((t_xy.x && t_xy.y) > 0){
        std::pair<int,int> coordinates = std::make_pair(t_xy.x / 50, t_xy.y / 50);

        // Get previous coordinates and next coordinates
        int x = coordinates.first, y = coordinates.second;
        //Current piece - Move unique pointer
        std::unique_ptr<Chess> currentPiece = std::move(selectedPiece->first);
        auto prev_xy = currentPiece->position;
        //Dest piece - Simply create pointer to copied value of unique pointer
        Chess* destinationPiece;
        if((grid[x][y].second) == ChessTeam::Empty){
            destinationPiece = nullptr;
        }
        else{
            destinationPiece = &*(grid[x][y].first);
        }
        std::pair<Chess*, ChessTeam> dest = std::make_pair(destinationPiece, grid[x][y].second);
        //If move is not valid
        if(!currentPiece->isValid(x, y, dest)){
            printf("not valid\n");
            grid[prev_xy.first][prev_xy.second].first = std::move(currentPiece);
            gridState = GridState::AwaitingCellSelect;
        }
        // If empty cell or opponent, update piece
        else if(grid[x][y].second == ChessTeam::Empty || grid[x][y].second != currentPiece->team){
            //Update piece position
            currentPiece->move(x, y);
            //Update grid
            grid[x][y] = std::make_pair(std::move(currentPiece), currentPiece->team);
            grid[prev_xy.first][prev_xy.second] = std::make_pair(std::unique_ptr<Chess>(nullptr), ChessTeam::Empty);
            //Reset selected piece and grid state
            gridState = GridState::AwaitingCellSelect;
            playerState = (playerState == PlayerState::Blue) ? PlayerState::Red : PlayerState::Blue;
        }
        // If cell contains own piece
        else {
            grid[prev_xy.first][prev_xy.second].first = std::move(currentPiece);
            gridState = GridState::AwaitingCellSelect;
            printf("contains own piece\n");
        }
        selectedPiece = nullptr;
    }
}

void Grid::selectCell(const sf::Vector2i t_xy){
    if(playerState == PlayerState::Blue){
        printf("blue team selected\n");
    }
    else{
        printf("red team selected\n");
    }
    std::pair<int,int> coordinates = std::make_pair(t_xy.x / 50, t_xy.y / 50);

    int x = coordinates.first, y = coordinates.second;
    switch(grid[x][y].second) {
        case ChessTeam::Empty:
            printf("Empty cell selected\n");
            break;
        case ChessTeam::Blue:
            if(playerState == PlayerState::Blue){
                selectedPiece = &grid[x][y];
                gridState = GridState::CellSelected;
            }
            break;
        case ChessTeam::Red:
            if(playerState == PlayerState::Red){
                selectedPiece = &grid[x][y];
                gridState = GridState::CellSelected;
            }
        break;    
        default:
            break;
    }
    
}




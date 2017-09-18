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
                *itB = std::make_pair(std::shared_ptr<Chess>(nullptr), ChessTeam::Empty);
                
            }
        }

        std::shared_ptr<King> kingA(new King(ChessTeam::Blue, window, std::make_pair(0,0)));
        std::shared_ptr<King> kingB(new King(ChessTeam::Red, window, std::make_pair(0,1)));
        std::shared_ptr<Castle> castleA(new Castle(ChessTeam::Blue, window, std::make_pair(5,5)));
        grid[0][0] = (std::make_pair(kingA, ChessTeam::Blue));
        grid[0][1] = (std::make_pair(kingB, ChessTeam::Red));
        grid[5][5] = (std::make_pair(castleA, ChessTeam::Blue));
}

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
    if(gridState == GridState::AwaitingCellSelect){
        selectCell(t_xy);
    }
    else if(gridState == GridState::CellSelected){
        moveCell(t_xy);
    }
}

void Grid::moveCell(const sf::Vector2i t_xy){
    if((t_xy.x && t_xy.y) > 0){
        std::pair<int,int> coordinates = std::make_pair(t_xy.x / 50, t_xy.y / 50);
        printf("%d %d \n", coordinates.first, coordinates.second);

        // Get previous coordinates and next coordinates
        auto prev_xy = selectedPiece->first->position;
        int x = coordinates.first, y = coordinates.second;
        //If move is not valid
        if(!selectedPiece->first->isValid(x, y)){
            gridState = GridState::AwaitingCellSelect;
        }
        // If empty cell or opponent, update piece
        else if(grid[x][y].second == ChessTeam::Empty || grid[x][y].second != selectedPiece->second){
            //Update piece position
            selectedPiece->first->move(x, y);
            //Update grid
            grid[x][y] = (*selectedPiece);
            grid[prev_xy.first][prev_xy.second] = std::make_pair(std::shared_ptr<Chess>(nullptr), ChessTeam::Empty);
            //Reset selected piece and grid state
            gridState = GridState::AwaitingCellSelect;
            playerState = (playerState == PlayerState::Blue) ? PlayerState::Red : PlayerState::Blue;
        }
        // If cell contains own piece
        else {
            gridState = GridState::AwaitingCellSelect;
        }
        selectedPiece = nullptr;
    }
}

void Grid::selectCell(const sf::Vector2i t_xy){
    if((t_xy.x && t_xy.y) > 0){
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
}


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
        //Initialise empty grid
        for(auto itA = grid.begin(); itA != grid.end(); ++itA){
            for(auto itB = itA->begin(); itB != itA->end(); ++itB){
                *itB = std::make_pair(
                    std::unique_ptr<Chess>(new Chess(ChessTeam::Empty(),
                                            "", window), ChessTeam::Empty);
                );
            }
        }
        std::unique_ptr<King> king(new King(ChessTeam::Blue, King::getFileName(), window));
        grid[0][0] = (std::make_pair(std::move(king), ChessTeam::Blue));
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

        int x = coordinates.first, y = coordinates.second;
        if(grid[x][y].second == ChessTeam::Empty){
            selectedPiece->first->move(x, y);
        }
    }
}

void Grid::selectCell(const sf::Vector2i t_xy){
    if((t_xy.x && t_xy.y) > 0){
        std::pair<int,int> coordinates = std::make_pair(t_xy.x / 50, t_xy.y / 50);
        // printf("%d %d \n", coordinates.first, coordinates.second);

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

void Grid::drawGrid(){
    window->draw(chessGrid);
}
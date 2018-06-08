#ifndef GRID_H
#define GRID_H
#include <src/OBJECTS/BASEOBJECT/Object.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include<vector>
class Grid : public Object
{
    struct Point
{
    int x;
    int y;
};

    public:
        /** Default constructor */
        Grid(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int scene_startx,int scene_starty,int scene_endx,int scene_endy);
        /** Default destructor */
        ~Grid();
    void draw() override;
    protected:

    private:
    int m_scene_endx=0;
    int m_scene_endy=0;
    int m_tiles_x=1;
    int m_tiles_y=1;
    std::vector<std::vector<SDL_Rect*>> rectangles;
    std::vector<std::vector<SDL_Rect*>> textboxes;
    std::vector<std::vector<Point*>> points;
};

#endif // GRID_H

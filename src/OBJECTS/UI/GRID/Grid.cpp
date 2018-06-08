#include "Grid.h"

Grid::Grid(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int scene_startx,int scene_starty,int scene_endx,int scene_endy): Object(name,SManager,MMatrix,sprite,5000,scene_startx,scene_starty,1024,1024),
m_scene_endx{scene_endx},m_scene_endy{scene_endy}
{
    m_tiles_x=(abs(m_x)+abs(m_scene_endx))/1024;
    m_tiles_y=(abs(m_y)+abs(m_scene_endy))/1024;

}

Grid::~Grid()
{


}


void Grid::draw()
{

}

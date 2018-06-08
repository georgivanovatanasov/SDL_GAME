#include "Object.h"

Object::Object(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,short depth,int start_x,int start_y,short start_w,short start_h):
m_name{name},m_SManager{SManager},m_MMatrix{MMatrix},m_sprite{sprite},m_depth{depth},m_x{start_x},m_y{start_y},m_w{start_w},m_h{start_h}
{
std::cout<<"Object created:"<<m_name<<"\n";



}
Object::~Object()
    {
    std::cout<<"Object destroyed:"<<m_name<<"\n";
    }


void Object::SetInitializeGrid(int grid_x,int grid_y)
{
    m_grid_x=grid_x;
    m_grid_y=grid_y;
}



void Object::draw(){}
void Object::handle_events(SDL_Event& event ) {}
void Object::step() {}

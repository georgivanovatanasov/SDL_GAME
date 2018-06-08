#include "Scene.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
/*A global function for object depth comparison.Used with std::sort*/
//////////////////////////////////////////////////////////////////////////////////////////////////
bool compare_object_depth(Object* lhs,Object* rhs)
{
if (lhs->m_depth<rhs->m_depth) {return true;}
else if (lhs->m_depth>rhs->m_depth) {return false;}
else if (lhs->m_depth==rhs->m_depth)
{
if (lhs->get_y()<rhs->get_y()) {return true;}
else if (lhs->get_y()>rhs->get_y()) {return false;}
}

}

//////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene(MainMatrix* MMatrix,ShaderManager* SManager): m_MMatrix{MMatrix},m_SManager{SManager}
{

}

Scene::~Scene()
{
    while (!obj_vector.empty())
    {
        Object* delete_obj=obj_vector.back();
        obj_vector.pop_back();
        delete delete_obj;
    }
    while (!sprite_vector.empty())
    {
        Sprite* delete_spr=sprite_vector.back();
        sprite_vector.pop_back();
        delete delete_spr;
    }
    while (!draw_vector.empty())
    {
    draw_vector.pop_back();
    }
    std::cout<<"Scene Object destroyed sucessfully\n";
}
void Scene::EmptyScene()
{
std::cout<<"Previous Scene deleted:\n";
    while (!obj_vector.empty())
    {
        Object* delete_obj=obj_vector.back();
        obj_vector.pop_back();
        delete delete_obj;
    }
    while (!sprite_vector.empty())
    {
        Sprite* delete_spr=sprite_vector.back();
        sprite_vector.pop_back();
        delete delete_spr;
    }
    while (!draw_vector.empty())
    {
    draw_vector.pop_back();
    }


    while (!GBO_vector.empty())
    {
        GrassBindingObject* delete_GBO=GBO_vector.back();
        GBO_vector.pop_back();
        delete delete_GBO;
    }

        while (!grass_vector.empty())
    {
        Grass* delete_grass=grass_vector.back();
        grass_vector.pop_back();
        delete delete_grass;
    }


}
void Scene::InitializePlayer(Sprite* player_sprite,int spawn_x,int spawn_y)
{
    if (HasPlayer==true)
    {
    player=new Player("player",m_SManager,m_MMatrix,player_sprite,spawn_x,spawn_y);
    player->GetSceneSize(scene_startx,scene_starty,scene_endx,scene_endy);
    player->SetGetGrid();
    player->m_persistent=1;
    obj_vector.push_back(player);
    draw_vector.push_back(player);
    }
    else
    {
    player=NULL;
    }
}
void Scene::SortDrawDepth()
{
std::sort(draw_vector.begin(),draw_vector.end(),compare_object_depth);
}

void Scene::ResetButtons()
{
for (Button*& i : button_deque)
{
i=NULL;
button_deque.pop_front();
}
}

void Scene::SetSceneSize(int start_x,int start_y,int end_x,int end_y)
{
scene_startx=start_x;
scene_starty=start_y;
scene_endx=end_x;
scene_endy=end_y;
}

void Scene::step()
{


///////////////////////////////////////////////////////////////////////////////////////////
                      /*Object's player_x and player_y used for rotation*/
///////////////////////////////////////////////////////////////////////////////////////////
if (player!=NULL)
{
    for (int i=0;i<obj_vector.size();i++)
    {
    obj_vector[i]->m_player_x=player->get_x();
    obj_vector[i]->m_player_y=player->get_y();
    }
}
    else
{
    {
    for (int i=0;i<obj_vector.size();i++)
    {
    obj_vector[i]->m_player_x=640;
    obj_vector[i]->m_player_y=480;
    }
    }
}



///////////////////////////////////////////////////////////////////////////////////////////
                            /*Destroying Grids That Are Far*/
///////////////////////////////////////////////////////////////////////////////////////////
    if (HasPlayer==true)
    {
        if (player_grid_prev_x!=player->m_grid_x)
        {
            if (player->m_grid_x>player_grid_prev_x && player->m_grid_x>=2 )
            {

                std::vector<Collider*>::iterator it;
                for (it=player->m_collider_vector.begin();it!=player->m_collider_vector.end();)
                    {
                    if ((*it)->m_grid_x<=player->m_grid_x-2 && (*it)->m_persistent==false)
                        {it=player->m_collider_vector.erase(it);}
                    else
                        {
                        it++;
                        }
                    }

                std::vector<Transperant*>::iterator it2;
                for (it2=player->m_transperant_vector.begin();it2!=player->m_transperant_vector.end();)
                    {
                    if ((*it2)->m_grid_x<=player->m_grid_x-2 && (*it2)->m_persistent==false)
                        {it2=player->m_transperant_vector.erase(it2);}
                    else
                        {
                        it2++;
                        }
                    }

                std::vector<Grass*>::iterator it4;
                for (it4=player->m_grass_vector.begin();it4!=player->m_grass_vector.end();)
                    {
                    if ((*it4)->m_grid_x<=player->m_grid_x-2 && (*it4)->m_persistent==false)
                        {it4=player->m_grass_vector.erase(it4);}
                    else
                        {
                        it4++;
                        }
                    }

                std::vector<TransperantVector*>::iterator it5;
                for (it5=player->m_transperant_vector_vector.begin();it5!=player->m_transperant_vector_vector.end();)
                    {
                    if ((*it5)->m_grid_x<=player->m_grid_x-2 && (*it5)->m_persistent==false)
                        {it5=player->m_transperant_vector_vector.erase(it5);}
                    else
                        {
                        it5++;
                        }
                    }

                std::vector<Grass*>::iterator it6;
                for (it6=grass_vector.begin();it6!=grass_vector.end();)
                    {
                    if ((*it6)->m_grid_x<=player->m_grid_x-2 && (*it6)->m_persistent==false)
                        {it6=grass_vector.erase(it6);}
                    else
                        {
                        it6++;
                        }
                    }

                std::vector<Object*>::iterator it3;
                for (it3=draw_vector.begin();it3!=draw_vector.end();)
                    {
                    if ((*it3)->m_grid_x<=player->m_grid_x-2 && (*it3)->m_persistent==false)
                        {it3=draw_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
                    for (it3=obj_vector.begin();it3!=obj_vector.end();)
                    {
                    if ((*it3)->m_grid_x<=player->m_grid_x-2 && (*it3)->m_persistent==false)
                        {delete * it3; it3=obj_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
            SceneLoadGrid(CurrentScene,player->m_grid_x+1,player->m_grid_y-1);
            SceneLoadGrid(CurrentScene,player->m_grid_x+1,player->m_grid_y);
            SceneLoadGrid(CurrentScene,player->m_grid_x+1,player->m_grid_y+1);
            SortDrawDepth();
            }
            int m_tiles_x=(abs(scene_startx)+abs(scene_endx))/1024;
            if (player->m_grid_x<player_grid_prev_x && player->m_grid_x<=m_tiles_x-3 )
            {

                std::vector<Collider*>::iterator it;
                for (it=player->m_collider_vector.begin();it!=player->m_collider_vector.end();)
                    {
                    if ((*it)->m_grid_x>=player->m_grid_x+2 && (*it)->m_persistent==false)
                        {it=player->m_collider_vector.erase(it);}
                    else
                        {
                        it++;
                        }
                    }
                std::vector<Transperant*>::iterator it2;
                for (it2=player->m_transperant_vector.begin();it2!=player->m_transperant_vector.end();)
                    {
                    if ((*it2)->m_grid_x>=player->m_grid_x+2 && (*it2)->m_persistent==false)
                        {it2=player->m_transperant_vector.erase(it2);}
                    else
                        {
                        it2++;
                        }
                    }
                std::vector<Grass*>::iterator it4;
                for (it4=player->m_grass_vector.begin();it4!=player->m_grass_vector.end();)
                    {
                    if ((*it4)->m_grid_x>=player->m_grid_x+2 && (*it4)->m_persistent==false)
                        {it4=player->m_grass_vector.erase(it4);}
                    else
                        {
                        it4++;
                        }
                    }

                std::vector<TransperantVector*>::iterator it5;
                for (it5=player->m_transperant_vector_vector.begin();it5!=player->m_transperant_vector_vector.end();)
                    {
                    if ((*it5)->m_grid_x>=player->m_grid_x+2 && (*it5)->m_persistent==false)
                        {it5=player->m_transperant_vector_vector.erase(it5);}
                    else
                        {
                        it5++;
                        }
                    }

                std::vector<Grass*>::iterator it6;
                for (it6=grass_vector.begin();it6!=grass_vector.end();)
                    {
                    if ((*it6)->m_grid_x>=player->m_grid_x+2 && (*it6)->m_persistent==false)
                        {it6=grass_vector.erase(it6);}
                    else
                        {
                        it6++;
                        }
                    }


                std::vector<Object*>::iterator it3;
                for (it3=draw_vector.begin();it3!=draw_vector.end();)
                    {
                    if ((*it3)->m_grid_x>=player->m_grid_x+2 && (*it3)->m_persistent==false)
                        {it3=draw_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
                    for (it3=obj_vector.begin();it3!=obj_vector.end();)
                    {
                    if ((*it3)->m_grid_x>=player->m_grid_x+2 && (*it3)->m_persistent==false)
                        {delete * it3; it3=obj_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
            SceneLoadGrid(CurrentScene,player->m_grid_x-1,player->m_grid_y-1);
            SceneLoadGrid(CurrentScene,player->m_grid_x-1,player->m_grid_y);
            SceneLoadGrid(CurrentScene,player->m_grid_x-1,player->m_grid_y+1);
            SortDrawDepth();
            }
        }

         if (player_grid_prev_y!=player->m_grid_y)
        {
            if (player->m_grid_y>player_grid_prev_y && player->m_grid_y>=2 )
            {

                std::vector<Collider*>::iterator it;
                for (it=player->m_collider_vector.begin();it!=player->m_collider_vector.end();)
                    {
                    if ((*it)->m_grid_y<=player->m_grid_y-2 && (*it)->m_persistent==false)
                        {it=player->m_collider_vector.erase(it);}
                    else
                        {
                        it++;
                        }
                    }
                std::vector<Transperant*>::iterator it2;
                for (it2=player->m_transperant_vector.begin();it2!=player->m_transperant_vector.end();)
                    {
                    if ((*it2)->m_grid_y<=player->m_grid_y-2 && (*it2)->m_persistent==false)
                        {it2=player->m_transperant_vector.erase(it2);}
                    else
                        {
                        it2++;
                        }
                    }
                std::vector<Grass*>::iterator it4;
                for (it4=player->m_grass_vector.begin();it4!=player->m_grass_vector.end();)
                    {
                    if ((*it4)->m_grid_y<=player->m_grid_y-2 && (*it4)->m_persistent==false)
                        {it4=player->m_grass_vector.erase(it4);}
                    else
                        {
                        it4++;
                        }
                    }

                std::vector<TransperantVector*>::iterator it5;
                for (it5=player->m_transperant_vector_vector.begin();it5!=player->m_transperant_vector_vector.end();)
                    {
                    if ((*it5)->m_grid_y<=player->m_grid_y-2 && (*it5)->m_persistent==false)
                        {it5=player->m_transperant_vector_vector.erase(it5);}
                    else
                        {
                        it5++;
                        }
                    }

                std::vector<Grass*>::iterator it6;
                for (it6=grass_vector.begin();it6!=grass_vector.end();)
                {
                    if ((*it6)->m_grid_x<=player->m_grid_y-2 && (*it6)->m_persistent==false)
                        {it6=grass_vector.erase(it6);}
                    else
                        {
                        it6++;
                        }
                }

                std::vector<Object*>::iterator it3;
                for (it3=draw_vector.begin();it3!=draw_vector.end();)
                    {
                    if ((*it3)->m_grid_y<=player->m_grid_y-2 && (*it3)->m_persistent==false)
                        {it3=draw_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
                    for (it3=obj_vector.begin();it3!=obj_vector.end();)
                    {
                    if ((*it3)->m_grid_y<=player->m_grid_y-2 && (*it3)->m_persistent==false)
                        {delete * it3; it3=obj_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
            SceneLoadGrid(CurrentScene,player->m_grid_x-1,player->m_grid_y+1);
            SceneLoadGrid(CurrentScene,player->m_grid_x,player->m_grid_y+1);
            SceneLoadGrid(CurrentScene,player->m_grid_x+1,player->m_grid_y+1);
            SortDrawDepth();
            }
            int m_tiles_y=(abs(scene_starty)+abs(scene_endy))/1024;
            if (player->m_grid_y<player_grid_prev_y && player->m_grid_y<=m_tiles_y-3 )
            {
                std::vector<Collider*>::iterator it;
                for (it=player->m_collider_vector.begin();it!=player->m_collider_vector.end();)
                    {
                    if ((*it)->m_grid_y>=player->m_grid_y+2 && (*it)->m_persistent==false)
                        {it=player->m_collider_vector.erase(it);}
                    else
                        {
                        it++;
                        }
                    }
                std::vector<Transperant*>::iterator it2;
                for (it2=player->m_transperant_vector.begin();it2!=player->m_transperant_vector.end();)
                    {
                    if ((*it2)->m_grid_y>=player->m_grid_y+2 && (*it2)->m_persistent==false)
                        {it2=player->m_transperant_vector.erase(it2);}
                    else
                        {
                        it2++;
                        }
                    }
                std::vector<Grass*>::iterator it4;
                for (it4=player->m_grass_vector.begin();it4!=player->m_grass_vector.end();)
                    {
                    if ((*it4)->m_grid_y>=player->m_grid_y+2 && (*it4)->m_persistent==false)
                        {it4=player->m_grass_vector.erase(it4);}
                    else
                        {
                        it4++;
                        }
                    }

                std::vector<TransperantVector*>::iterator it5;
                for (it5=player->m_transperant_vector_vector.begin();it5!=player->m_transperant_vector_vector.end();)
                    {
                    if ((*it5)->m_grid_y>=player->m_grid_y+2 && (*it5)->m_persistent==false)
                        {it5=player->m_transperant_vector_vector.erase(it5);}
                    else
                        {
                        it5++;
                        }
                    }

                std::vector<Grass*>::iterator it6;
                for (it6=grass_vector.begin();it6!=grass_vector.end();)
                    {
                    if ((*it6)->m_grid_y>=player->m_grid_y+2 && (*it6)->m_persistent==false)
                        {it6=grass_vector.erase(it6);}
                    else
                        {
                        it6++;
                        }
                    }

                std::vector<Object*>::iterator it3;
                for (it3=draw_vector.begin();it3!=draw_vector.end();)
                    {
                    if ((*it3)->m_grid_y>=player->m_grid_y+2 && (*it3)->m_persistent==false)
                        {it3=draw_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
                    for (it3=obj_vector.begin();it3!=obj_vector.end();)
                    {
                    if ((*it3)->m_grid_y>=player->m_grid_y+2 && (*it3)->m_persistent==false)
                        {delete * it3; it3=obj_vector.erase(it3);}
                    else
                        {
                        it3++;
                        }
                    }
                SceneLoadGrid(CurrentScene,player->m_grid_x-1,player->m_grid_y-1);
                SceneLoadGrid(CurrentScene,player->m_grid_x,player->m_grid_y-1);
                SceneLoadGrid(CurrentScene,player->m_grid_x+1,player->m_grid_y-1);
                SortDrawDepth();
                }
        }

            player_grid_prev_x=player->m_grid_x;
            player_grid_prev_y=player->m_grid_y;
        }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    /*SCENES*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Scene::SceneInit(std::string path)
{
//Pop vectors from previous scene
   EmptyScene();
//All buttons are going to NULL
   ResetButtons();
//FSTREAM
std::string line;
std::ifstream file("scenes/"+path+"/init");
if (file.is_open())
{
    while(std::getline(file,line))
    {
        std::stringstream ss;
        std::string keyword;

        ss<<line;
        ss>>keyword;
        if (keyword=="SetSceneSize")
            {
                int sx,sy,ex,ey;
                ss>>sx;
                ss>>sy;
                ss>>ex;
                ss>>ey;
                SetSceneSize(sx,sy,ex,ey);
            }
        if (keyword=="HasPlayer")
            {
                bool haspl;
                ss>>haspl;
                HasPlayer=haspl;
            }
        if (keyword=="Sprite")
            {
                std::string sprite_name;
                std::string a;


                ss>>sprite_name;
                ////////////////////////////////////////
                        /*covert string to char* */
                ////////////////////////////////////////
                ss>>a;
                char* b=new char[a.length()+1];
                std::strcpy(b,a.c_str());
                ////////////////////////////////////////
                Sprite* new_sprite=new Sprite(sprite_name,b);
                sprite_vector.push_back(new_sprite);
                delete b;

            }
        if (keyword=="InitializePlayer")
            {
            int sprite_index;
            int x;
            int y;
            ss>>sprite_index;
            ss>>x;
            ss>>y;
                    /*Player Object exists or not*/
            InitializePlayer(sprite_vector[sprite_index],x,y);
            }

    }
}
file.close();

}

void Scene::SceneLoadGrid(std::string path,short grid_x,short grid_y)
{
std::string line;
std::ifstream file("scenes/"+path+"/grid/"+std::to_string(grid_x)+"_"+std::to_string(grid_y));

    if (file.is_open())
        {

            while(std::getline(file,line))
            {
                std::stringstream ss;
                std::string keyword;

                ss<<line;
                ss>>keyword;
////////////////////////////////////////////////////////////////////////////
                            /*Collider*/
////////////////////////////////////////////////////////////////////////////
            if (keyword=="Collider")
            {
                std::string name;
                short sprite_index;
                int x;
                int y;
                short w;
                short h;
                short cw;
                short ch;


                ss>>name;
                ss>>sprite_index;
                ss>>x;
                ss>>y;
                ss>>w;
                ss>>h;
                ss>>cw;
                ss>>ch;

                if (sprite_index<sprite_vector.size())
                    {

                            Collider* new_object=new Collider(name,m_SManager,m_MMatrix,sprite_vector[sprite_index],scene_startx+1024*grid_x+x,scene_starty+1024*grid_y+y,w,h,cw,ch);
                            new_object->SetInitializeGrid(grid_x,grid_y);
                            obj_vector.push_back(new_object);
                            draw_vector.push_back(new_object);
                            if (HasPlayer==true) {player->m_collider_vector.push_back(new_object);}
                    }
                    else
                    {
                        std::cout<<"Object not Loaded:<<"<<name<<", sprite index out of array bounds.";
                    }
            }
             if (keyword=="Transperant")
                        {
                            std::string name;
                            short sprite_index;
                            int x;
                            int y;
                            short w;
                            short h;
                            short cw;
                            short ch;

                            ss>>name;
                            ss>>sprite_index;
                            ss>>x;
                            ss>>y;
                            ss>>w;
                            ss>>h;
                            ss>>cw;
                            ss>>ch;

                            if (sprite_index<sprite_vector.size())
                                {

                                        Transperant* new_object=new Transperant(name,m_SManager,m_MMatrix,sprite_vector[sprite_index],scene_startx+1024*grid_x+x,scene_starty+1024*grid_y+y,w,h,cw,ch);
                                        new_object->SetInitializeGrid(grid_x,grid_y);
                                        obj_vector.push_back(new_object);
                                        draw_vector.push_back(new_object);
                                        if (HasPlayer==true) {player->m_transperant_vector.push_back(new_object);}
                                }
                                else
                                {
                                    std::cout<<"Object not Loaded:<<"<<name<<", sprite index out of array bounds.";
                                }
                        }
              if (keyword=="Tile")
                        {
                            std::string name;
                            short sprite_index;
                            short depth;
                            int x;
                            int y;
                            short tiles_x;
                            short tiles_y;
                            short w;
                            short h;

                            ss>>name;
                            ss>>sprite_index;
                            ss>>depth;
                            ss>>x;
                            ss>>y;
                            ss>>tiles_x;
                            ss>>tiles_y;
                            ss>>w;
                            ss>>h;
                            if (sprite_index<sprite_vector.size())
                                {

                                        Tile* new_object=new Tile(name,m_SManager,m_MMatrix,sprite_vector[sprite_index],depth,scene_startx+1024*grid_x+x,scene_starty+1024*grid_y+y,tiles_x,tiles_y,w,h);
                                        new_object->SetInitializeGrid(grid_x,grid_y);
                                        obj_vector.push_back(new_object);
                                        draw_vector.push_back(new_object);
                                }
                                else
                                {
                                    std::cout<<"Object not Loaded:<<"<<name<<", sprite index out of array bounds.";
                                }
                        }
                        if (keyword=="Quad")
                        {
                            GLint sprite_index;
                            GLfloat vx1,vy1,vx2,vy2,vx3,vy3,vx4,vy4;
                            GLfloat tx1,ty1,tx2,ty2,tx3,ty3,tx4,ty4;
                            GLint i1,i2,i3,i4;

                            ss>>sprite_index;
                            sampler_vector.push_back(sprite_vector[sprite_index]);

                            ss>>vx1;
                            ss>>vy1;
                            ss>>vx2;
                            ss>>vy2;
                            ss>>vx3;
                            ss>>vy3;
                            ss>>vx4;
                            ss>>vy4;
                            verticles_vector.push_back(vx1);
                            verticles_vector.push_back(vy1);
                            verticles_vector.push_back(vx2);
                            verticles_vector.push_back(vy2);
                            verticles_vector.push_back(vx3);
                            verticles_vector.push_back(vy3);
                            verticles_vector.push_back(vx4);
                            verticles_vector.push_back(vy4);

                            ss>>tx1;
                            ss>>ty1;
                            ss>>tx2;
                            ss>>ty2;
                            ss>>tx3;
                            ss>>ty3;
                            ss>>tx4;
                            ss>>ty4;

                            texcoords_vector.push_back(tx1);
                            texcoords_vector.push_back(ty1);
                            texcoords_vector.push_back(tx2);
                            texcoords_vector.push_back(ty2);
                            texcoords_vector.push_back(tx3);
                            texcoords_vector.push_back(ty3);
                            texcoords_vector.push_back(tx4);
                            texcoords_vector.push_back(ty4);

                            i1=index_vector.size();
                            i2=index_vector.size()+1;
                            i3=index_vector.size()+2;
                            i4=index_vector.size()+3;

                            index_vector.push_back(i1);
                            index_vector.push_back(i2);
                            index_vector.push_back(i3);
                            index_vector.push_back(i4);

                        }
                        if (keyword=="TransperantVector")
                        {
                            std::string name;
                            short sprite_index,depth;
                            int x;
                            int y;
                            short w;
                            short h;

                            ss>>name;
                            ss>>depth;
                            ss>>sprite_index;
                            ss>>x;
                            ss>>y;
                            ss>>w;
                            ss>>h;
                            if (sprite_index<sprite_vector.size())
                                {

                                TransperantVector* new_object=new TransperantVector(name,depth,m_SManager,m_MMatrix,sprite_vector[sprite_index],scene_startx+1024*grid_x+x,scene_starty+1024*grid_y+y,w,h);
                                new_object->SetInitializeGrid(grid_x,grid_y);
                                    new_object->sampler_vector=sampler_vector;
                                    new_object->verticles_vector=verticles_vector;
                                    new_object->texcoords_vector=texcoords_vector;
                                    new_object->index_vector=index_vector;
                                    new_object->init();

                                if (HasPlayer==true) {player->m_transperant_vector_vector.push_back(new_object);}
                                obj_vector.push_back(new_object);
                                draw_vector.push_back(new_object);
                                /////////////////////////////////////////////////////////////////////////////////////
                                                                /*Emptry Vectors*/
                                /////////////////////////////////////////////////////////////////////////////////////
                                    while (!sampler_vector.empty())
                                    {
                                    sampler_vector.pop_back();
                                    }
                                    while (!verticles_vector.empty())
                                    {
                                    verticles_vector.pop_back();
                                    }
                                    while (!texcoords_vector.empty())
                                    {
                                    texcoords_vector.pop_back();
                                    }
                                    while (!index_vector.empty())
                                    {
                                    index_vector.pop_back();
                                    }

                                /////////////////////////////////////////////////////////////////////////////////////



                                }
                                else
                                {
                                    std::cout<<"Object not Loaded:<<"<<name<<", sprite index out of array bounds.";
                                }
                        }

                        if (keyword=="Grass")
                        {
                            int ID;
                            std::string name;
                            short sprite_index;
                            int x;
                            int y;
                            short w;
                            short h;

                            ss>>name;
                            ss>>ID;
                            ss>>sprite_index;
                            ss>>x;
                            ss>>y;
                            ss>>w;
                            ss>>h;
                            if (sprite_index<sprite_vector.size())
                                {

                                        Grass* new_object=new Grass(ID,name,m_SManager,m_MMatrix,sprite_vector[sprite_index],scene_startx+1024*grid_x+x,scene_starty+1024*grid_y+y,w,h);
                                        new_object->SetInitializeGrid(grid_x,grid_y);
                                        new_object->init();

                                        for (GrassBindingObject* i : GBO_vector)
                                        {
                                        if (i->get_ID()==new_object->get_ID())
                                            {
                                            new_object->Connection=GBO_vector[GBO_vector.size()-1];
                                            GBO_vector[GBO_vector.size()-1]->grass_vector.push_back(new_object);
                                            }

                                        }

                                        obj_vector.push_back(new_object);
                                        draw_vector.push_back(new_object);
                                }
                                else
                                {
                                    std::cout<<"Object not Loaded:<<"<<name<<", sprite index out of array bounds.";
                                }
                        }

                        if (keyword=="GrassBindingObject")
                        {
                            int GBO_ID;
                            ss>>GBO_ID;
                            GrassBindingObject* new_object=new GrassBindingObject(GBO_ID);
                            GBO_vector.push_back(new_object);

                            for (Grass* i : grass_vector)
                                {
                                if (i->get_ID()==new_object->get_ID())
                                    {
                                    new_object->grass_vector.push_back(i);
                                    i->Connection=new_object;
                                    }
                                }


                        }
           }

        }
file.close();
std::cout<<"GRID:"<<grid_x<<" "<<grid_y<<" loaded.\n";
}

void Scene::LoadMainMenu()
{
std::cout<<"/////////////////////////////////////////////////////////////////\n";
std::cout<<"                            Main Menu                            \n";
std::cout<<"/////////////////////////////////////////////////////////////////\n";
    //Set scene size
   SetSceneSize(0,0,1280,960);
    //Check if Scene has player(used for player collider vector pushes and camera)
   HasPlayer=false;
    //Pop vectors from previous scene
   EmptyScene();
   //All buttons are going to NULL
   ResetButtons();
   //Current Scene is
   CurrentScene="MainMenu";
std::cout<<"/////////////////////////////////////////////////////////////////\n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    /*Sprites*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*BACKGROUND*/
   Sprite* background_sprite=new Sprite("menu_background","img/menu/menu_background.png");
   sprite_vector.push_back(background_sprite);
   /*LOGIN BUTTON*/
   Sprite* login_button_sprite=new Sprite("menu_login","img/menu/menu_login.png");
   sprite_vector.push_back(login_button_sprite);
   /*EXIT BUTTON*/
   Sprite* exit_button_sprite=new Sprite("menu_exit","img/menu/menu_exit.png");
   sprite_vector.push_back(exit_button_sprite);
std::cout<<"/////////////////////////////////////////////////////////////////\n";
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    /*Objects*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Player Object Pointer should be set NULL*/
   InitializePlayer(NULL,0,0);
    /*Should call this function even if room doesn't have player,because of member player pointer*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /*BACKGROUND*/
   Collider* background=new Collider("background",m_SManager,m_MMatrix,background_sprite,640,480,1280,960,1280,960);
   obj_vector.push_back(background);
   draw_vector.push_back(background);
   /*LOGIN BUTTON*/
   login_button=new Button("login_button",m_SManager,m_MMatrix,login_button_sprite,640,680,256,128);
   obj_vector.push_back(login_button);
   button_deque.push_front(login_button);
   draw_vector.push_back(login_button);
   /*EXIT BUTTON*/
   exit_button=new Button("exit_button",m_SManager,m_MMatrix,exit_button_sprite,640,830,256,128);
   obj_vector.push_back(exit_button);
   button_deque.push_front(exit_button);
   draw_vector.push_back(exit_button);
std::cout<<"/////////////////////////////////////////////////////////////////\n\n\n";
}


void Scene::LoadScene(std::string path)
{
SceneInit(path);



SceneLoadGrid(path,player->m_grid_x,player->m_grid_y);
SceneLoadGrid(path,player->m_grid_x,player->m_grid_y-1);
SceneLoadGrid(path,player->m_grid_x,player->m_grid_y+1);

SceneLoadGrid(path,player->m_grid_x-1,player->m_grid_y);
SceneLoadGrid(path,player->m_grid_x-1,player->m_grid_y-1);
SceneLoadGrid(path,player->m_grid_x-1,player->m_grid_y+1);

SceneLoadGrid(path,player->m_grid_x+1,player->m_grid_y);
SceneLoadGrid(path,player->m_grid_x+1,player->m_grid_y-1);
SceneLoadGrid(path,player->m_grid_x+1,player->m_grid_y+1);


//////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////

CurrentScene=path;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //sort object depth
    SortDrawDepth();
}

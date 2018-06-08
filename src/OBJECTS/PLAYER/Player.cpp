#include "Player.h"

Player::Player(std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y) : Object(name,SManager,MMatrix,sprite,0,start_x,start_y,256,256),
m_x_prev{start_x},m_y_prev{start_y}
{

    CoordinatesLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inCoordinates");
    TexCoordsLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inTexCoords");
    IndicesLocation = glGetAttribLocation(m_SManager->DefaultShaderProgram,"inIndex");




    glGenBuffers(1,&points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),points,GL_STREAM_DRAW);



    glGenBuffers(1,&texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),texcoords,GL_STREAM_DRAW);

    glGenBuffers(1,&indices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,indices_vbo);
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),indices,GL_STREAM_DRAW);

    if (CoordinatesLocation==-1) {std::cout<<"inCoordinates location not found \n";}
    if (TexCoordsLocation==-1) {std::cout<<"inTexCoords location not found \n";}
    if (IndicesLocation==-1) {std::cout<<"inIndex location not found \n";}


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
    glVertexAttribPointer(CoordinatesLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

    glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
    glVertexAttribPointer(TexCoordsLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

    glBindBuffer(GL_ARRAY_BUFFER,indices_vbo);
    glVertexAttribPointer(IndicesLocation,1,GL_INT,GL_FALSE,0,NULL);


    glEnableVertexAttribArray(CoordinatesLocation);
    glEnableVertexAttribArray(TexCoordsLocation);
    glEnableVertexAttribArray(IndicesLocation);


}

Player::~Player()
{
}

void Player::GetSceneSize(int start_x,int start_y,int end_x,int end_y)
{
scene_startx=start_x;
scene_starty=start_y;
scene_endx=end_x;
scene_endy=end_y;
}



void Player::step()
{


    ///////////////////////////////////////////////////////////////////////
                             /*Movement triggers*/
    ///////////////////////////////////////////////////////////////////////
    if (m_move_up==true) {for(int i=0;i<m_speed;i++) {if (collision_check_collider(m_x,m_y-1-16)==false && m_y-1-16+128>scene_starty){m_y-=1;}}}
    if (m_move_down==true) {for(int i=0;i<m_speed;i++) {if (collision_check_collider(m_x,m_y+1-16)==false && m_y+1-16+224<scene_endy){m_y+=1;}}}
    if (m_move_left==true) {for(int i=0;i<m_speed;i++) {if (collision_check_collider(m_x-1,m_y-16)==false && m_x-1-16>scene_startx){m_x-=1;}}}
    if (m_move_right==true) {for(int i=0;i<m_speed;i++) {if (collision_check_collider(m_x+1,m_y-16)==false && m_x+1-16<scene_endx){m_x+=1;}}}

    ///////////////////////////////////////////////////////////////////////
                                /*Animation*/
    ///////////////////////////////////////////////////////////////////////
    if (m_x!=m_x_prev || m_y!=m_y_prev)
    {
    if (m_y>m_y_prev) {m_fr_y=0;}
    else
    if (m_y<m_y_prev) {m_fr_y=1.0f/8.0f;}
    else
    if (m_x>m_x_prev) {m_fr_y=2.0f/8.0f;}
    else
    if (m_x<m_x_prev) {m_fr_y=3.0f/8.0f;}
    sprite_timer++;
    ///////////////////////////////////////////////////////////////////////
                                /*Grid*/
    ///////////////////////////////////////////////////////////////////////
    if (m_x<box_x_min) {box_x_min-=1024; box_x_max-=1024; m_grid_x--;}
    else if (m_x>box_x_max) {box_x_min+=1024; box_x_max+=1024; m_grid_x++;}
    if (m_y+160<box_y_min) {box_y_min-=1024; box_y_max-=1024; m_grid_y--;}
    else if (m_y+160>box_y_max) {box_y_min+=1024; box_y_max+=1024; m_grid_y++;}
    ///////////////////////////////////////////////////////////////////////

    //Reset Prevs
    m_x_prev=m_x;
    m_y_prev=m_y;

    ///////////////////////////////////////////////////////////////////////
                    /*Animation and collision transperant*/
    ///////////////////////////////////////////////////////////////////////
    if (sprite_timer==5) {m_fr_x+=1.0f/8.0f; sprite_timer=0;}
    if (m_fr_x>=7.0f/8.0f) {m_fr_x=0.0f;}
    collision_check_transperant();
    collision_check_transperant_vector();
    }
}
void Player::handle_events(SDL_Event& event)
{
if(event.type==SDL_KEYDOWN)
                {
                switch(event.key.keysym.sym)
                {
                case SDLK_w: //UP
                    f_move_up(true);
                break;

                case SDLK_s: //DOWN
                    f_move_down(true);
                break;

                case SDLK_a: //LEFT
                    f_move_left(true);
                break;

                case SDLK_d: //RIGHT
                    f_move_right(true);
                break;
                }
                }
            else if(event.type==SDL_KEYUP)
{
                switch(event.key.keysym.sym)
                {
                case SDLK_w:
                    m_fr_x=0.0f;
                    f_move_up(false);
                break;

                case SDLK_s:
                    m_fr_x=0.0f;
                    f_move_down(false);
                break;

                case SDLK_a:
                    m_fr_x=0.0f;
                    f_move_left(false);
                break;

                case SDLK_d:
                    m_fr_x=0.0f;;
                    f_move_right(false);
                break;
                }
                }
}

void Player::draw()
{

    glUseProgram(m_SManager->DefaultShaderProgram);
    glBindVertexArray(vao);
    GLuint OrthoLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unOrthogonal");
    if (OrthoLocation==-1) {std::cout<<"unOrthogonal location not found \n";}
    glUniformMatrix4fv(OrthoLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->ortho));

    glm::mat4 rotation_scale=m_MMatrix->scalation*m_MMatrix->rotation;
    GLuint ModelLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unModel");
    if (ModelLocation==-1) {std::cout<<"unModel location not found \n";}
    glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(rotation_scale));

    glm::vec2 frame=glm::vec2(m_fr_x,m_fr_y);
    GLuint FrameLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unFrame");
    if (FrameLocation==-1) {std::cout<<"unFrame location not found \n";}
    glUniform2fv(FrameLocation,1,glm::value_ptr(frame));

    glm::vec2 clips=glm::vec2(1.0f,1.0f);
    GLuint ClipsLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unClip");
    if (ClipsLocation==-1) {std::cout<<"unClip location not found \n";}
    glUniform2fv(ClipsLocation,1,glm::value_ptr(clips));

    glm::vec4 color=glm::vec4(m_R,m_G,m_B,m_Alpha);
    GLuint ColorLocation=glGetUniformLocation(m_SManager->DefaultShaderProgram,"unColor");
    if (ColorLocation==-1) {std::cout<<"unColor location not found \n";}
    glUniform4fv(ColorLocation,1,glm::value_ptr(color));

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,m_sprite->get_sprite());


    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);


    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glUseProgram(0);

    glDisableVertexAttribArray(IndicesLocation);
    glDisableVertexAttribArray(TexCoordsLocation);
    glDisableVertexAttribArray(CoordinatesLocation);








}

bool Player::collision_check_collider(int f_x,int f_y)
{
    int f_var=0;
    bool f_collision;
    #pragma omp parallel for
    for (int i=0;i<m_collider_vector.size();i++)
    {
            f_collision=1;
    #pragma omp parallel
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
            if (f_x+16<=m_collider_vector[i]->get_x() || f_x-16>=m_collider_vector[i]->get_x()+m_collider_vector[i]->get_w()) {f_collision=0;}
            }
            #pragma omp section
            {
            if (f_y+144<=m_collider_vector[i]->get_y() || f_y+128>=m_collider_vector[i]->get_y()+m_collider_vector[i]->get_h()) {f_collision=0;}
            }
        }
    }
            f_var=f_var+f_collision;
    }
    return f_var;
}


void Player::collision_check_transperant()
{
    bool f_collision;
    #pragma omp parallel for
    for (int i=0;i<m_transperant_vector.size();i++)
    {
            f_collision=1;
    #pragma omp parallel
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
            if (m_x+16<=m_transperant_vector[i]->get_x()    ||  m_x-16>=m_transperant_vector[i]->get_x()+m_transperant_vector[i]->get_w()) {f_collision=0;}
            }
            #pragma omp section
            {
            if (m_y+144<=m_transperant_vector[i]->get_y()  ||  m_y+128>=m_transperant_vector[i]->get_y()+m_transperant_vector[i]->get_h()) {f_collision=0;}
            }
        }
    }
            if (f_collision==1)
            {
                m_transperant_vector[i]->disappear=1;
            }
            else
            {
                m_transperant_vector[i]->disappear=0;
            }
    }
}

void Player::collision_check_transperant_vector()
{
    bool f_collision;
    #pragma omp parallel for
    for (int i=0;i<m_transperant_vector_vector.size();i++)
    {
            f_collision=1;
    #pragma omp parallel
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
            if (m_x+16<=m_transperant_vector_vector[i]->get_x()    ||  m_x-16>=m_transperant_vector_vector[i]->get_x()+m_transperant_vector_vector[i]->get_w()) {f_collision=0;}
            }
            #pragma omp section
            {
            if (m_y+144<=m_transperant_vector_vector[i]->get_y()  ||  m_y+128>=m_transperant_vector_vector[i]->get_y()+m_transperant_vector_vector[i]->get_h()) {f_collision=0;}
            }
        }
    }
            if (f_collision==1)
            {
                m_transperant_vector_vector[i]->disappear=1;
            }
            else
            {
                m_transperant_vector_vector[i]->disappear=0;
            }
    }
}






void Player::SetGetGrid()
{
    m_grid_x=0;
    m_grid_y=0;

    int m_tiles_x=(abs(scene_startx)+abs(scene_endx))/1024;
    int m_tiles_y=(abs(scene_starty)+abs(scene_endy))/1024;

    for (short i=1;i<=m_tiles_x;i++)
    {
    if (scene_startx+i*1024<m_x) {m_grid_x++;}
        else
        {
        box_x_min=scene_startx+i*1024-1024;
        box_x_max=scene_startx+i*1024;
        break;
        }
    }

    for (short i=1;i<=m_tiles_y;i++)
    {
    if (scene_starty+i*1024<m_y) {m_grid_y++;}
        else
        {
            box_y_min=scene_starty+i*1024-1024;
            box_y_max=scene_starty+i*1024;
            break;
        }
    }
}

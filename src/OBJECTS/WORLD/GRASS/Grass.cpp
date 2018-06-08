#include "Grass.h"

Grass::Grass(int ID_GBO,std::string name,ShaderManager* SManager,MainMatrix* MMatrix,Sprite* sprite,int start_x,int start_y,int start_w,int start_h): Object(name,SManager,MMatrix,sprite,-34,start_x,start_y,start_w,start_h)
{
m_ID_GBO=ID_GBO;


}

Grass::~Grass()
{
    if (Connection!=NULL)
    {
        Connection->to_delete=this;
        int index=-1;
        for (int i=0;i<Connection->grass_vector.size();i++)
        {
            if (Connection->grass_vector[i]==Connection->to_delete)
            {
            index=i;
            }
        }
        Connection->to_delete=NULL;
        if (index!=-1)
        {
            Connection->grass_vector.erase(Connection->grass_vector.begin()+index);
        }

    }
}

void Grass::init()
{


                verticles_vector.push_back(float(m_x));
                verticles_vector.push_back(float(m_y));
                verticles_vector.push_back(float(m_x+32));
                verticles_vector.push_back(float(m_y));
                verticles_vector.push_back(float(m_x+32));
                verticles_vector.push_back(float(m_y+128));
                verticles_vector.push_back(float(m_x));
                verticles_vector.push_back(float(m_y+128));

                texcoords_vector.push_back(0.0f);
                texcoords_vector.push_back(0.0f);
                texcoords_vector.push_back(1.0f);
                texcoords_vector.push_back(0.0f);
                texcoords_vector.push_back(1.0f);
                texcoords_vector.push_back(1.0f);
                texcoords_vector.push_back(0.0f);
                texcoords_vector.push_back(1.0f);

            int instances=(m_h/16)*(m_w/16);
            for (int i=0;i<instances;i++)
            {
                index_vector.push_back(i);
            }

        CoordinatesLocation = glGetAttribLocation(m_SManager->GrassShaderProgram,"inCoordinates");
        TexCoordsLocation = glGetAttribLocation(m_SManager->GrassShaderProgram,"inTexCoords");
        IndicesLocation = glGetAttribLocation(m_SManager->GrassShaderProgram,"inIndex");

        ModelLocation0 = glGetAttribLocation(m_SManager->GrassShaderProgram,"inModel0");
        ModelLocation1 = glGetAttribLocation(m_SManager->GrassShaderProgram,"inModel1");
        ModelLocation2 = glGetAttribLocation(m_SManager->GrassShaderProgram,"inModel2");
        ModelLocation3 = glGetAttribLocation(m_SManager->GrassShaderProgram,"inModel3");

        ColorLocation = glGetAttribLocation(m_SManager->GrassShaderProgram,"inColor");

        glGenBuffers(1,&points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
        glBufferData(GL_ARRAY_BUFFER,verticles_vector.size()*sizeof(GLfloat),&verticles_vector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&texcoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
        glBufferData(GL_ARRAY_BUFFER,texcoords_vector.size()*sizeof(GLfloat),&texcoords_vector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&indices_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indices_vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_vector.size()*sizeof(GLfloat),&index_vector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&model_vbo0);
        glBindBuffer(GL_ARRAY_BUFFER,model_vbo0);
        glBufferData(GL_ARRAY_BUFFER,model0_stdvector.size()*sizeof(glm::vec4),&model0_stdvector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&model_vbo1);
        glBindBuffer(GL_ARRAY_BUFFER,model_vbo1);
        glBufferData(GL_ARRAY_BUFFER,model1_stdvector.size()*sizeof(glm::vec4),&model1_stdvector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&model_vbo2);
        glBindBuffer(GL_ARRAY_BUFFER,model_vbo2);
        glBufferData(GL_ARRAY_BUFFER,model2_stdvector.size()*sizeof(glm::vec4),&model2_stdvector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&model_vbo3);
        glBindBuffer(GL_ARRAY_BUFFER,model_vbo3);
        glBufferData(GL_ARRAY_BUFFER,model3_stdvector.size()*sizeof(glm::vec4),&model3_stdvector[0],GL_STREAM_DRAW);

        glGenBuffers(1,&color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER,color_vbo);
        glBufferData(GL_ARRAY_BUFFER,color_vector.size()*sizeof(glm::vec4),&color_vector[0],GL_STREAM_DRAW);


        if (CoordinatesLocation==-1) {std::cout<<"inCoordinates location not found \n";}
        if (TexCoordsLocation==-1) {std::cout<<"inTexCoords location not found \n";}
        if (IndicesLocation==-1) {std::cout<<"inIndex location not found \n";}

        if (ModelLocation0==-1) {std::cout<<"inModel0 location not found \n";}
        if (ModelLocation1==-1) {std::cout<<"inModel1 location not found \n";}
        if (ModelLocation2==-1) {std::cout<<"inModel2 location not found \n";}
        if (ModelLocation3==-1) {std::cout<<"inModel3 location not found \n";}

        if (ColorLocation==-1) {std::cout<<"ColorLocation location not found \n";}

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(CoordinatesLocation);
        glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
        glVertexAttribPointer(CoordinatesLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

        glEnableVertexAttribArray(TexCoordsLocation);
        glBindBuffer(GL_ARRAY_BUFFER,texcoord_vbo);
        glVertexAttribPointer(TexCoordsLocation,2,GL_FLOAT,GL_FALSE,0,NULL);

        glEnableVertexAttribArray(IndicesLocation);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indices_vbo);
        glVertexAttribPointer(IndicesLocation,1,GL_INT,GL_FALSE,0,NULL);

        inited=1;
}


float Grass::get_distance(float sx,float sy,float dx,float dy)
{
    return sqrt((sx-dx)*(sx-dx)+(sy-dy)*(sy-dy));
}

void Grass::handle_events(SDL_Event& event)
{

}

void Grass::step()
{
      m_rotation_timer++;

    if (m_side_switch==1)
        {
            if (m_rotation_timer>=12) {m_angle+=0.5f; if (m_angle>10.0f) {m_side_switch=0;}}

        }
    else if (m_side_switch==0)
        {
            if (m_rotation_timer>=12) {m_angle-=0.5f; if (m_angle<-10.0f) {m_side_switch=1;}}

        }
}





void Grass::draw()
{

    if (inited==1)
    {

                glDisableVertexAttribArray(ModelLocation0);
                glDisableVertexAttribArray(ModelLocation1);
                glDisableVertexAttribArray(ModelLocation2);
                glDisableVertexAttribArray(ModelLocation3);

                glDisableVertexAttribArray(ColorLocation);

                while(!model0_stdvector.empty())
                {
                model0_stdvector.pop_back();
                model1_stdvector.pop_back();
                model2_stdvector.pop_back();
                model3_stdvector.pop_back();
                }

                while(!color_vector.empty())
                {
                color_vector.pop_back();
                }



                int j=-1;

                int instances=(m_h/16)*(m_w/32);
                int grass_amount_width=m_w/32;

                for (int i=0;i<instances;i+=1)
                {
                if (i%grass_amount_width==0) {j++;}

    glm::mat4 Trans=glm::mat4();
    if (i%4==0 || i%3==0)
    {
    Trans=m_MMatrix->MatrixTransform((i%(grass_amount_width))*32.0f+i%9-4,j*16.0f,m_angle,(m_x+(i%(grass_amount_width))*32.0f+i%9-4.0f+16.0f),m_y+j*16.0f+120.0f,1.0f);
    }
    else
    {
    Trans=m_MMatrix->MatrixTransform((i%(grass_amount_width))*32.0f+i%9-4,j*16.0f,360.0f-m_angle,m_x+((i%(grass_amount_width))*32.0f+i%9-4.0f+16.0f),m_y+j*16.0f+120.0f,1.0f);
    }
                    const float *mtxp=(const float*)glm::value_ptr(Trans);

                    glm::vec4 model0_glmvector=glm::vec4(mtxp[0],mtxp[1],mtxp[2],mtxp[3]);
                    glm::vec4 model1_glmvector=glm::vec4(mtxp[4],mtxp[5],mtxp[6],mtxp[7]);
                    glm::vec4 model2_glmvector=glm::vec4(mtxp[8],mtxp[9],mtxp[10],mtxp[11]);
                    glm::vec4 model3_glmvector=glm::vec4(mtxp[12],mtxp[13],mtxp[14],mtxp[15]);

                    model0_stdvector.push_back(model0_glmvector);
                    model1_stdvector.push_back(model1_glmvector);
                    model2_stdvector.push_back(model2_glmvector);
                    model3_stdvector.push_back(model3_glmvector);

                    if (Connection==NULL)
                    {
                        if (m_player_x<m_w && m_player_x>m_x && m_player_y<m_h && m_player_y>m_y)
                        {
                        int dist_to_ply=get_distance(m_x+(i%(grass_amount_width))*32.0f+i%9-4,m_y+j*16.0f,m_player_x-16.0f,m_player_y+48.0f);
                        glm::vec4 color=glm::vec4(1.0f,1.0f,1.0f,dist_to_ply*6.0f*1.0f/2048.0f);
                        color_vector.push_back(color);
                        }
                        else
                        {
                        glm::vec4 color=glm::vec4(1.0f,1.0f,1.0f,1.0f);
                        color_vector.push_back(color);
                        }
                    }
                    else
                    {
                        if (m_player_x<m_w && m_player_x>m_x && m_player_y<m_h && m_player_y>m_y)
                        {
                        Connection->set_all_disappear();

                        }

                        if (disappear==1)
                        {
                        int dist_to_ply=get_distance(m_x+(i%(grass_amount_width))*32.0f+i%9-4,m_y+j*16.0f,m_player_x-16.0f,m_player_y+48.0f);
                        glm::vec4 color=glm::vec4(1.0f,1.0f,1.0f,dist_to_ply*6.0f*1.0f/2048.0f);
                        color_vector.push_back(color);
                        }
                        else
                        {
                        glm::vec4 color=glm::vec4(1.0f,1.0f,1.0f,1.0f);
                        color_vector.push_back(color);
                        }



                    }



                }



    glDeleteBuffers(1,&model_vbo0);
    glGenBuffers(1,&model_vbo0);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo0);
    glBufferData(GL_ARRAY_BUFFER,model0_stdvector.size()*sizeof(glm::vec4),&model0_stdvector[0],GL_STREAM_DRAW);

    glDeleteBuffers(1,&model_vbo1);
    glGenBuffers(1,&model_vbo1);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo1);
    glBufferData(GL_ARRAY_BUFFER,model1_stdvector.size()*sizeof(glm::vec4),&model1_stdvector[0],GL_STREAM_DRAW);

    glDeleteBuffers(1,&model_vbo2);
    glGenBuffers(1,&model_vbo2);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo2);
    glBufferData(GL_ARRAY_BUFFER,model2_stdvector.size()*sizeof(glm::vec4),&model2_stdvector[0],GL_STREAM_DRAW);

    glDeleteBuffers(1,&model_vbo3);
    glGenBuffers(1,&model_vbo3);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo3);
    glBufferData(GL_ARRAY_BUFFER,model3_stdvector.size()*sizeof(glm::vec4),&model3_stdvector[0],GL_STREAM_DRAW);

    glDeleteBuffers(1,&color_vbo);
    glGenBuffers(1,&color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,color_vbo);
    glBufferData(GL_ARRAY_BUFFER,color_vector.size()*sizeof(glm::vec4),&color_vector[0],GL_STREAM_DRAW);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(ModelLocation0);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo0);
    glVertexAttribPointer(ModelLocation0,4,GL_FLOAT,GL_FALSE,0,NULL);
    glVertexAttribDivisor(ModelLocation0,1);

    glEnableVertexAttribArray(ModelLocation1);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo1);
    glVertexAttribPointer(ModelLocation1,4,GL_FLOAT,GL_FALSE,0,NULL);
    glVertexAttribDivisor(ModelLocation1,1);

    glEnableVertexAttribArray(ModelLocation2);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo2);
    glVertexAttribPointer(ModelLocation2,4,GL_FLOAT,GL_FALSE,0,NULL);
    glVertexAttribDivisor(ModelLocation2,1);

    glEnableVertexAttribArray(ModelLocation3);
    glBindBuffer(GL_ARRAY_BUFFER,model_vbo3);
    glVertexAttribPointer(ModelLocation3,4,GL_FLOAT,GL_FALSE,0,NULL);
    glVertexAttribDivisor(ModelLocation3,1);

    glEnableVertexAttribArray(ColorLocation);
    glBindBuffer(GL_ARRAY_BUFFER,color_vbo);
    glVertexAttribPointer(ColorLocation,4,GL_FLOAT,GL_FALSE,0,NULL);
    glVertexAttribDivisor(ColorLocation,1);

    glBindVertexArray(0);

    glUseProgram(m_SManager->GrassShaderProgram);
    glBindVertexArray(vao);





    GLuint OrthoLocation=glGetUniformLocation(m_SManager->GrassShaderProgram,"unOrthogonal");
    if (OrthoLocation==-1) {std::cout<<"unOrthogonal location not found \n";}
    glUniformMatrix4fv(OrthoLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->ortho));

    GLuint ModelLocation=glGetUniformLocation(m_SManager->GrassShaderProgram,"unModel");
    if (ModelLocation==-1) {std::cout<<"unModel location not found \n";}
    glUniformMatrix4fv(ModelLocation,1,GL_FALSE,glm::value_ptr(m_MMatrix->model));


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,m_sprite->get_sprite());

    glDrawArraysInstanced(GL_QUADS,0,8,instances);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);


    glUseProgram(0);

        }


}






#include "Game.h"
#define fps 60

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING!=0)) {std::cout<<"SDL failed to initialize.\n"; running=false;} else {std::cout<<"SDL initialized successfully.\n";}
    if (TTF_Init()!=0) {std::cout<<"SDL_TTF failed to initialize.\n"; running=false;} else {std::cout<<"SDL_TTF initialized successfully.\n";}
}

Game::~Game()
{
    std::cout<<"Game Destructor called:\n\nSDL_DestroyWindow(window);\ndelete scene;\nSDL_Quit();\n";
    SDL_DestroyWindow(window);
    delete scene;
    delete MMatrix;
    delete SManager;
    delete PProcessor;
    TTF_Quit();
    SDL_Quit();
}



void Game::init()
{
    //OpenGl Context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);

    //The Window
    window=SDL_CreateWindow("My SDL game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,960,SDL_WINDOW_OPENGL);
    SDL_GLContext OPENGL_CONTEXT=SDL_GL_CreateContext(window);

    //GLEW
    glewExperimental=GL_TRUE;
    glewInit();

    glClearColor(0.0f,0.0f,0.0f,1.0f); //Clear Buffers to 0.0f RGB

    SManager=new ShaderManager();
    SManager->init();

    MMatrix=new MainMatrix();

    PProcessor=new PostProcessor(MMatrix,SManager);

    glViewport(0,0,1280,960); //Viewport

    //The Scene
    scene=new Scene(MMatrix,SManager);
    scene->LoadMainMenu();
}
void Game::render() //Drawing the Scene
{

    glBindFramebuffer(GL_FRAMEBUFFER, PProcessor->FramebufferName);
    glClear(GL_COLOR_BUFFER_BIT);
    GLenum err;
    for (int i=0;i<scene->draw_vector.size();i++)
    {
    scene->draw_vector[i]->draw();
    }
    while ((err=glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error:" << err << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    PProcessor->draw();
    SDL_GL_SwapWindow(window);;
}

void Game::step()
{

    if (scene->player==NULL)
    {
    camera_x=640;
    camera_y=480;
    }

    if (MMatrix!=NULL)
    {
    MMatrix->m_camera_x=camera_x;
    MMatrix->m_camera_y=camera_y;
    }
}

void Game::handle_window_events() //Main window events:exiting Game.
{

           if (event.type==SDL_QUIT) {std::cout<<"SDL X'ed out.\n"; running=false;}
            else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE) {std::cout<<"SDL ESC'ed out.\n"; running=false;}
            else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_TAB) {scene->LoadMainMenu();}

}
void Game::run() //Running loop:doing the step,draw and handle_events functions for all objects.
{
;
    Uint32 start_tick; //Limiting framerate
    Uint32 counter_tick=SDL_GetTicks();
    //Counting framerate
    int frames=0;
    Uint32 milliseconds=0;

        while (running) {

            start_tick=SDL_GetTicks(); //Limiting framerate

////////////////////////////////////////////////////////////////////
                        /*Main Loop*/
////////////////////////////////////////////////////////////////////



            for (int i=0;i<scene->GBO_vector.size();i++)
                {
                scene->GBO_vector[i]->step();
                }

            for (int i=0;i<scene->obj_vector.size();i++)
                {
                scene->obj_vector[i]->step();
                }

            camera_coordinates();
            manage_buttons();
            MMatrix->step();
            render();
            scene->step();
            step();

            while(SDL_PollEvent(&event))
                {
                handle_window_events();
                    for (int i=0;i<scene->obj_vector.size();i++)
                    {
                        scene->obj_vector[i]->handle_events(event);
                    }
                }







////////////////////////////////////////////////////////////////////
                    if ((1000/fps)>SDL_GetTicks()-start_tick) //Limiting the framerate
        {      //for one second delay we check 1000>SDL_GetTicks()-start_tick. For 1/60 second we devide by the framerate...
            SDL_Delay(1000/fps-(SDL_GetTicks()-start_tick)); //Limiting the framerate

        }


                    frames++;
            milliseconds+=SDL_GetTicks()-counter_tick;
            counter_tick=SDL_GetTicks();
            if (milliseconds>1000)
            {
                //std::cout<<"fps:"<<frames<<"\n";
                milliseconds=0;
                frames=0;
            }



            }



}

//Camera following player if player exist in Scene
void Game::camera_coordinates()
{
            if (scene->player!=NULL)
            {
            camera_x=scene->player->get_x()-640;
            camera_y=scene->player->get_y()-480;
            }
            else
            {
            camera_x=0;
            camera_y=0;
            }
}
//Manage buttons
void Game::manage_buttons()
{
if (scene->login_button!=NULL) {if (scene->login_button->get_clicked()==true) {scene->LoadScene("SceneTown01");}}
if (scene->exit_button!=NULL) {if (scene->exit_button->get_clicked()==true) {std::cout<<"Game quit through the Exit button.\n";running=false;}}
}






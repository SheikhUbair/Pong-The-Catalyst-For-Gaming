#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
//argc stands for argument count Example .\pong easy then argc = 2. tells u how many arguemnts were passed.
//argv stands for argument vector its an array of strings conatining the arguments passed ,.
{
    /* SDL is like a toolbox in which different tools or we can say subsystems are present like audio,
    video , keyboard. SDL_Init means Initilize SDL then SDL_INIT_VIDEO means using the Video subsystem
    all togther it means Initilize SDL using the Video subsystem . 2 subsystms like audio and video
    can be initlized togther */
    
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("SDL Initialization Failed!\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow // SDL makes a window and gives us a pointer to control it later
    /*The funtion SDL_CreateWindow() means create a window on my screen*/
    // if u wanted the screen at a different place you coudl enter actual coordinates.
    (
        "Pong --- The Catalyst For Gaming",// Window Title
        SDL_WINDOWPOS_CENTERED,//X position
        SDL_WINDOWPOS_CENTERED,// Y  position
        800,// width , window dimension pixels
        600,//height , window dimension pixels
        0//no special option
    );

    if(window==NULL)
    {
        printf("Window Creation Failed!!\n");
        SDL_Quit();
        return 1;
    }

    int running = 1;// later running vlaue can be changed to 0 to stop the gameplay loop.
    SDL_Event event;// anyhting that will occur like an input it will be registered as an event.

    while(running)// to loop the game.
    {
        while(SDL_PollEvent(&event))// Poll event is like scanf waiting for the player to do something.
        // and if the player does anyhting like press W or quit the game
        // SDL stores that info in event and then we pass that vale of event here.
        {
            if(event.type==SDL_QUIT)
            {
                running = 0;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
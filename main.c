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

    SDL_Renderer *renderer = SDL_CreateRenderer(window ,-1, SDL_RENDERER_ACCELERATED);
    // A rednerer is like a paintbrush which lets u draw things on your SDl window
    //  This above is used to create a renderer on your window and -1 bascailly pickd the best driver for
    // renderering and renderer accelerated means that use hardware acceleration (GPU) if needed

    if(renderer==NULL)
    {
        printf("Renderer Error : %s\n",SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;// later running vlaue can be changed to 0 to stop the gameplay loop.
    SDL_Event event;// anyhting that will occur like an input it will be registered as an event.

    while(running)// to loop the game.
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        // here these numbers are for RGB and 255 is aplha which means transparency
        // if alpha is 255 the the color is visible if its 0 then the colour is not visible.
        SDL_RenderClear(renderer);

        SDL_Rect Left_paddle =
        {
            50,
            200,
            20,
            125
        };
        SDL_RenderFillRect(renderer,&Left_paddle);//SDL draw a filled rectangle

        SDL_Rect Right_paddle=
        {
            725,
            200,
            20,
            125
        };
        SDL_RenderFillRect(renderer,&Right_paddle);

        SDL_Rect ball=
        {
            350,
            250,
            15,
            15
        };
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&Left_paddle);
        SDL_RenderFillRect(renderer,&Right_paddle);
        SDL_RenderFillRect(renderer,&ball);
        SDL_RenderPresent(renderer);// draws everthing and displays it .



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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
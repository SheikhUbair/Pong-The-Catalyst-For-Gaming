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
            20,
            20
        };

        int ballVelocityX = 3;
        int ballVelocityY= 3;
        
    int running = 1;// later running vlaue can be changed to 0 to stop the gameplay loop.
    SDL_Event event;// anyhting that will occur like an input it will be registered as an event.

    while(running)// to loop the game.
    {
         SDL_SetRenderDrawColor(renderer,0,0,0,255);
        // here these numbers are for RGB and 255 is aplha which means transparency
        // if alpha is 255 the the color is visible if its 0 then the colour is not visible.
        SDL_RenderClear(renderer);
       
       
        
        while(SDL_PollEvent(&event))// Checks whether there is an event waititng in Sdl's event queue.
        // Poll event is similar to scanf waiting for the player to do something.
        // and if the player does anyhting like press W or quit the game
        // SDL stores that info in event and then we pass that vale of event here.
        {
        
             if(event.type==SDL_QUIT)
            {
                running = 0;
            }

            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            // const means dont modify this data
            // uint8 a SDL datatype which means Unsigned 8bit integer
            // *keyboard is a pointer which keybaord points to the first element of an array of Uint8
            // SDL GET KEYBOARD STATE means give me the current state of every key on the keybaord
            // which is 0 until a key is pressed and then it becomes 1
            // bascially these keys are stored in an array
            // SDL SCANCode gives an index value to each key 
            // then when u specify a key like W OR S OR UP OR DOWN 
            // the program finds that key with its index value and checks the state of that key
            // if its 0 then the key is not pressed and if its 1 then its pressed .
            
            if(keyboard[SDL_SCANCODE_W] && Left_paddle.y > 0)
            {
                Left_paddle.y -= 10;
            }
            if(keyboard[SDL_SCANCODE_S] && Left_paddle.y < 475)
            {
                Left_paddle.y += 10;
            }

            if(keyboard[SDL_SCANCODE_UP] && Right_paddle.y > 0)
            {
                Right_paddle.y -= 10;
            }
            if(keyboard[SDL_SCANCODE_DOWN] && Right_paddle.y < 475)
            {
                Right_paddle.y += 10;
            }

        }

        
        ball.x += ballVelocityX;
        ball.y += ballVelocityY;


        // Left Paddle Hitbox
        int Left_paddleLeft = Left_paddle.x;
        int Left_paddleRight = Left_paddle.x + Left_paddle.w;
        int Left_paddleTop = Left_paddle.y;
        int Left_paddleBottom = Left_paddle.y + Left_paddle.h;

        // Right paddle hitbox
        int Right_paddleLeft = Right_paddle.x;
        int Right_paddleRight = Right_paddle.x + Right_paddle.w;
        int Right_paddleTop = Right_paddle.y;
        int Right_paddleBottom = Right_paddle.y + Right_paddle.h;

        // Ball hitbox

        int ballLeft = ball.x;
        int ballRight = ball.x + ball.w;
        int ballTop = ball.y;
        int ballBottom = ball.y + ball.h;


        if(ball.y <=0)
        {
            ballVelocityY = -ballVelocityY;
        }
        if(ball.y >= 580)
        {
            ballVelocityY = -ballVelocityY;
        }
        if(ball.x <=0)
        {
            ballVelocityX = -ballVelocityX;
        }
        if(ball.x >=780)
        {
            ballVelocityX = -ballVelocityX;
        }

        if(ballLeft <= Left_paddleRight)
        {
            if(ballBottom >= Left_paddleTop && ballTop <= Left_paddleBottom)
            {
                ball.x = Left_paddleRight;
                ballVelocityX = -ballVelocityX;
            }
        }
        if(ballRight >= Right_paddleLeft)
        {
            if(ballBottom >= Right_paddleTop && ballTop <= Right_paddleBottom)
            {
                ball.x = Right_paddleLeft - ball.w;
                ballVelocityX = -ballVelocityX;
            }
        }

        
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer,&Left_paddle);
        SDL_RenderFillRect(renderer,&Right_paddle);
        SDL_RenderFillRect(renderer,&ball);
        SDL_RenderPresent(renderer);// draws everthing and displays it .
        SDL_Delay(16);// control frame rate

        
           
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
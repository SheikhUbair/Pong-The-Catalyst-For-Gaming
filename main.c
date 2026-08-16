#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char *argv[])
//argc stands for argument count Example .\pong easy then argc = 2. tells u how many arguemnts were passed.
//argv stands for argument vector its an array of strings conatining the arguments passed .
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
    if(TTF_Init() == -1)
    {
        printf("TTF Initilization Failed! %s\n",TTF_GetError());
        SDL_Quit();
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

    // Load Font 
    TTF_Font *font = TTF_OpenFont("arial.ttf",48);
    TTF_Font *font1 = TTF_OpenFont("arial.ttf",25);

    SDL_Color white = {255, 255 , 255, 255};

    //Turn the text string into pixels and surface is an image in the ram
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "PONG" ,white);
    SDL_Surface *playSurface = TTF_RenderText_Solid(font1, "INSERT COIN TO PLAY" ,white);
    SDL_Surface *exitSurface = TTF_RenderText_Solid(font1, "PRESS ESC TO EXIT" , white);
    SDL_Surface *pauseSurface = TTF_RenderText_Solid(font, "PAUSED", white);
    SDL_Surface *resetSurface = TTF_RenderText_Solid(font1, "PRESS BACKSPACE TO RESET", white);

    //covert pixels/image to texture
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Texture *exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Texture *pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
    SDL_Texture *resetTexture = SDL_CreateTextureFromSurface(renderer, resetSurface);

    // postion to draw the text
    SDL_Rect textRect = 
    {
        335,
        100,
        textSurface->w,
        textSurface->h
    };

    SDL_Rect playRect =
    {
        275,
        200,
        playSurface->w,
        playSurface->h
    };

    SDL_Rect exitRect =
    {
        285,
        300,
        exitSurface->w,
        exitSurface->h
    };

    SDL_Rect pauseRect =
    {
        315,
        100,
        pauseSurface->w,
        pauseSurface->h
    };

    SDL_Rect resetRect = 
    {
        212,
        200,
        resetSurface->w,
        resetSurface->h
    };

    if(font == NULL)
    {
        printf("Font Error : %s/n",TTF_GetError());
        return 1;
    }

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(exitSurface);
    SDL_FreeSurface(pauseSurface);
    SDL_FreeSurface(resetSurface);

   
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


        int ballVelocityX = 1;
        int ballVelocityY= 1;

        int Left_Score = 0;
        int Right_Score =0;

        char leftScoreText[10];
        char rightScoreText[10];
        
    int running = 1;// later running vlaue can be changed to 0 to stop the gameplay loop.
    int gameState = 0; // gamestate .
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
            if(event.type ==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    if(gameState == 0)
                    {
                        running=0;
                    }
                    else if(gameState == 2)
                    {
                        running=0;
                    }
                }
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(gameState == 0 && event.key.keysym.sym == SDLK_RETURN)
                {
                    gameState = 1; // playing or draw game
                }
            }
            if(event.type ==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    if(gameState == 1)
                    {
                        gameState = 2 ; // game paused
                    }
                    else if(gameState == 2)
                    {
                        gameState = 1;
                    }
                }
                if(event.key.keysym.sym == SDLK_BACKSPACE) // to reset the game.
                {
                    if(gameState == 2)
                    {
                    ball.x = 350;
                    ball.y = 250;

                    Left_paddle.y = 200;
                    Right_paddle.y = 200;

                    ballVelocityX = 1;
                    ballVelocityY = 1;

                    gameState = 1;
                    }

                }
            }
        }

            


        if(gameState==1)
        {
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
            
            // Wall Collision
             if(ball.y <=0)
            {
            ball.y=0;
            ballVelocityY = -ballVelocityY;
            }
        
            if(ball.y >= 580)
            {
            ball.y=580;
            ballVelocityY = -ballVelocityY;
            }

            // Paddle Collision

            if(ballRight >= Left_paddleLeft 
            && ballLeft <= Left_paddleRight 
            && ballBottom >= Left_paddleTop 
            && ballTop <= Left_paddleBottom)
            {
                ball.x = Left_paddleRight;
                ballVelocityX = -ballVelocityX;
            }

            if( ballLeft <= Right_paddleRight
            && ballRight >= Right_paddleLeft 
            && ballBottom >= Right_paddleTop 
            && ballTop <= Right_paddleBottom)
            {
                ball.x = Right_paddleLeft - ball.w;
                ballVelocityX = -ballVelocityX;
            }

            if(ball.x >= 800)
            {
                Left_Score++;

                ball.x = 350;
                ball.y = 250;
                
                Left_paddle.y = 200;
                Right_paddle.y = 200;

                ballVelocityX = 1;
                ballVelocityY = 1;

                sprintf(leftScoreText, "%d", Left_Score); // take leftscore , format it as an integer %d and put the result into leftscoretext.
            }

            if(ball.x <= -20)
            {
                Right_Score++;

                ball.x = 350;
                ball.y = 250;

                Left_paddle.y = 200;
                Right_paddle.y = 200;

                ballVelocityX = 1;
                ballVelocityY = 1;

                sprintf(rightScoreText,"%d", Right_Score);
            }

        }
        

        
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        if(gameState == 0 )
        {
            SDL_Rect menubox =
            {
                200,
                100,
                400,
                300
            };
            SDL_RenderDrawRect(renderer, &menubox);

            //here textTexture = the pong image stored as a gpu texture
            //and textRect = where and how big its supposed to be
            SDL_RenderCopy(renderer , textTexture , NULL, &textRect);
            SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
            SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
        }
        if(gameState == 2)
        {
            SDL_Rect pausebox = 
            {
                200,
                100,
                400,
                300
            };
            SDL_RenderDrawRect(renderer, &pausebox);
            SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
            SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
            SDL_RenderCopy(renderer, resetTexture, NULL, &resetRect);
        }

        

        
        else if (gameState ==1)
        {
            // Centre line
        for(int y = 0 ; y < 600 ; y+=30)
        {
            SDL_Rect dash =
            {
                395,
                y,
                10,
                20
            };
            SDL_RenderFillRect(renderer, &dash);
        }
            SDL_RenderFillRect(renderer,&Left_paddle);
            SDL_RenderFillRect(renderer,&Right_paddle);
            SDL_RenderFillRect(renderer,&ball);
        }
        SDL_RenderPresent(renderer);// draws everthing and displays it .
        SDL_Delay(16);// control frame rate

        
           
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

#include <SDL2/SDL.h> 
#include "key_input_manager.h"
#include "line_creator_manager.h"
#include "button_creator_manager.h"
#include <stdio.h>  
#include <string.h> 
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
 

static int running = 1;

static SDL_Window* window;

static SDL_Renderer* renderer;

static SDL_Rect player;

static SDL_Rect map;

static TTF_Font* font;

static line_creator_obj line_creator;

static button_creator_obj button_creator;

static char _is_a_pressed = 0;
static unsigned int _a_pressed_timer = 0;

static char _is_b_pressed = 0;
static unsigned int _b_pressed_timer = 0;

static void _render_update_obj(void) {

    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 10, 40 , 50, 50);
    SDL_RenderFillRect(renderer, &map);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);
    SDL_SetRenderDrawColor(renderer, 10, 40, 50, 50);
    SDL_SetRenderDrawColor(renderer, 52, 65, 50, 50);
    SDL_RenderDrawLine(renderer, 100, 430, 320, 50);
    SDL_RenderPresent(renderer);*/
}

static void _key_input_for_cube_stade_machine(key_input_keyboard_stades stade) {
 
    switch (stade)
    {
        case KEY_INPUT_QUIT: {
            running = 0;
            break;
        }
        case KEY_INPUT_LEFT: {
            player.x -= 10;
            break;
        }
        case KEY_INPUT_RIGHT: {
            player.x += 10;
            break;
        }
        case KEY_INPUT_UP: {
            player.y -= 10;
            break;
        }
        case KEY_INPUT_DOWN: {
            player.y += 10;
            break;
        }

        case KEY_INPUT_A: { 
            _is_a_pressed = 1;
            break;
        }

        case KEY_INPUT_B: {
            _is_b_pressed = 1;
            break;
        }
 
        default:
            return;
    }
 
    _render_update_obj();
}


static void _mause_click(key_input_mause_str* coord) {

    if (coord->event_type == KEY_INPUT_MAUSE_DOWN) {
        if (coord->x > 100) {

            player.y -= 10;

            _render_update_obj();
        }
    }

    if (_is_a_pressed) {
        line_creator_mause_event_callback(&line_creator,
            (line_creator_mause_event_types)coord->event_type,
            coord->x, coord->y);
    }


    
    button_creator_mause_event_callback(&button_creator,
        (button_creator_mause_event_types)coord->event_type,
        coord->x, coord->y);

    if (_is_b_pressed == 1) {
    
        button_creator_new_button_create(&button_creator,
            NULL,
            (const char*)"ali",
            50,
            50,
            coord->x, coord->y);

        _is_b_pressed = 2;

    }

}

unsigned int fps = 0;

Uint32 callback_1ms(Uint32 interval, void* name) {
     
    if (_is_a_pressed) { 
        _a_pressed_timer++;
        if (_a_pressed_timer > 500) {
            _is_a_pressed = 0;
            _a_pressed_timer = 0;
        }
    }

    if (_is_b_pressed) {
        _b_pressed_timer++;
        if (_b_pressed_timer > 500) {
            _is_b_pressed = 0;
            _b_pressed_timer = 0;
        }
    } 

    button_creator_1_ms_timer(&button_creator);
    fps++; 
    return interval;
}



static void button1_callback(button_creator_callback_type type) {

    switch (type)
    {
    case BUTTON_CREATOR_PRESSED_UP: {    printf("button1_callback pressed up\n");  break; }
    case BUTTON_CREATOR_PRESSED_DOWN: {  printf("button1_callback pressed down\n"); break; }
    default:
        break;
    }  
    
}


int main(int argc, char* argv[])
{  
    SDL_Init(  SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("GameOfST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_TimerID timerID = SDL_AddTimer(1, callback_1ms, NULL);

    player = (SDL_Rect){ 100, 100, 50, 50 };

    map = (SDL_Rect){ 0, 0, 0, 0 };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      
    key_input_obj key_obj;
    key_input_create(&key_obj);
    key_input_add_new_keyboard_callback(&key_obj, &_key_input_for_cube_stade_machine, 1);
    key_input_add_new_mause_callback(&key_obj, &_mause_click);
     
    line_creator_create(&line_creator , renderer);
    button_creator_create(&button_creator, renderer);

    button_creator_new_button_create(&button_creator,
        &button1_callback,
        (const char*)"button_ali",
        100,
        100,
        200,
        200);
     

    _render_update_obj();

    printf("init load success\n");
    printf("if you wanna create button PRESS KEYBOARD -> 'b' \n");
    printf("if you wanna create line PRESS KEYBOARD -> 'a' \n");
     
    // test - picture
    SDL_Surface* imageSurface = IMG_Load("images/x2.png");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface); 
  
    //test - font
    font = TTF_OpenFont("fonts/arial.ttf", 28);
    SDL_Color textColor = { 255, 255, 255 }; // Beyaz renk
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Merhaba", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    TTF_CloseFont(font);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;


    SDL_Rect rect;

    while (running)
    {    
       
        /**
        if (fps > 3000) { 
            fps = 0;
        }
        else if (fps == 2000) {
            fps++;
           // render_text(renderer, 50, 50, "hello", font, &rect, &textColor);

            if (textTexture) {
                SDL_DestroyTexture(textTexture);
                textTexture = NULL;
            }
            if (textSurface) {
                //SDL_FreeSurface(textSurface);
                textSurface = NULL;
            }
            textSurface = TTF_RenderText_Solid(font, "sds", textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            textWidth = textSurface->w;
            textHeight = textSurface->h;

        }

        else if (fps == 1000) {
            fps++;
             
            if (textTexture) {
                SDL_DestroyTexture(textTexture);
                textTexture = NULL;
            }
            if (textSurface) {
                //SDL_FreeSurface(textSurface);
                textSurface = NULL;
            }

            textSurface = TTF_RenderText_Solid(font, "allalla", textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
          
            textWidth = textSurface->w;
            textHeight = textSurface->h;

           // render_text(renderer, 10, 10, "ahhhahau", font, &rect, &textColor);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textTexture, NULL, &(SDL_Rect){(800 - textWidth) / 2, (600 - textHeight) / 2, textWidth, textHeight});
        SDL_RenderPresent(renderer);
        */
         
        //SDL_RenderClear(renderer);
        //SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        //SDL_RenderPresent(renderer);
        



        key_input_polling(&key_obj); 
        line_creator_polling(&line_creator);
        button_creator_polling(&button_creator); 
       
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); 
    SDL_DestroyTexture(imageTexture);
    SDL_RemoveTimer(timerID);
    SDL_Quit();
    return 0;
}
 

 
 



/*
int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Counter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 28);
    SDL_Color textColor = { 255, 255, 255 }; // Beyaz renk

    int counter = 0;
    char counterText[20]; // Counter deðerini tutacak bir karakter dizisi

    SDL_Surface* textSurface = NULL;
    SDL_Texture* textTexture = NULL;

    SDL_Event event;
    int quit = 0;

    Uint32 startTime = SDL_GetTicks(); // Baþlangýç zamanýný kaydediyoruz

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Uint32 currentTime = SDL_GetTicks(); // Geçerli zamaný alýyoruz

        if (currentTime - startTime >= 1000) { // 1 saniye geçtiðinde
            counter++; // Counter'ý artýrýyoruz
            sprintf(counterText, "Counter: %d", counter); // Counter deðerini karakter dizisine yazýyoruz

            if (textTexture) {
                SDL_DestroyTexture(textTexture);
                textTexture = NULL;
            }
            if (textSurface) {
                //SDL_FreeSurface(textSurface);
                textSurface = NULL;
            }

            textSurface = TTF_RenderText_Solid(font, counterText, textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            startTime = currentTime; // Baþlangýç zamanýný güncelliyoruz  
            
            if (textTexture != NULL) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textTexture, NULL, &(SDL_Rect){0, 0, textSurface->w, textSurface->h});
            SDL_RenderPresent(renderer);
        }
        }

      
    }

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
*/
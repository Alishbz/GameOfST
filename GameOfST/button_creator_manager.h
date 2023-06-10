#pragma once
#ifndef  BUTTON_CREATOR_MANAGER_h_
#define  BUTTON_CREATOR_MANAGER_h_

/* Ali Þahbaz created **/

#include <SDL2/SDL.h>

#define BUTTON_CREATOR_MAX_NUMBER  10
#define BUTTON_CREATOR_NAME_ARRAY_SIZE  10


typedef enum
{
    BUTTON_CREATOR_SUCCESS,
    BUTTON_CREATOR_FAIL
} button_creator_func_out;

/** MÝRRORING From @key_input_mause_events **/
typedef enum
{
    BUTTON_CREATOR_MAUSE_EMPTY,
    BUTTON_CREATOR_MAUSE_MOVEING,
    BUTTON_CREATOR_MAUSE_UP,
    BUTTON_CREATOR_MAUSE_DOWN
} button_creator_mause_event_types;

typedef enum
{
    BUTTON_CREATOR_PRESSED_UP,
    BUTTON_CREATOR_PRESSED_DOWN
} button_creator_callback_type;

typedef void (*button_touch_calback_str)(button_creator_callback_type type);


typedef struct
{
    unsigned int x;
    unsigned int y;
} button_coord_obj;
typedef struct
{
    unsigned int height;
    unsigned int lenght;
} button_size_obj;


typedef struct
{
    unsigned int timer_ms;
    button_coord_obj position;
    button_size_obj  size;
    button_touch_calback_str callback;
    unsigned char name[BUTTON_CREATOR_NAME_ARRAY_SIZE];
}button_obj;


typedef struct
{
    SDL_Renderer* renderer;
    char is_init_success;
    button_obj buttons[BUTTON_CREATOR_MAX_NUMBER];
    unsigned short button_count;

}button_creator_obj;

button_creator_func_out button_creator_create(button_creator_obj* me,
    SDL_Renderer* renderer);

button_creator_func_out button_creator_new_button_create(button_creator_obj* me,
    button_touch_calback_str* press_callback,
    const char* button_name,
    unsigned int height,
    unsigned int lenght,
    unsigned int x,
    unsigned int y);
    

button_creator_func_out button_creator_destroy(button_creator_obj* me);
button_creator_func_out button_creator_1_ms_timer(button_creator_obj* me);

button_creator_func_out button_creator_polling(button_creator_obj* me);

button_creator_func_out button_creator_mause_event_callback(button_creator_obj* me,
    button_creator_mause_event_types m_event,
    unsigned int mause_x, unsigned int mause_y);


#endif
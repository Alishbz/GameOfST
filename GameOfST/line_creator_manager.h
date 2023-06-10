#pragma once
#ifndef LINE_CREATOR_MANAGER_h_
#define LINE_CREATOR_MANAGER_h_

/* Ali Þahbaz created **/

#include <SDL2/SDL.h>

#define LINE_CREATOR_MAX_CAN_LINE_NUMBER  10

typedef enum
{
    LINE_CREATOR_SUCCESS,
    LINE_CREATOR_FAIL
} line_creator_func_out;


/** MÝRRORING From @key_input_mause_events **/
typedef enum
{
    LINE_CREATOR_MAUSE_EMPTY,
    LINE_CREATOR_MAUSE_MOVEING,
    LINE_CREATOR_MAUSE_UP,
    LINE_CREATOR_MAUSE_DOWN
} line_creator_mause_event_types;
 


typedef enum
{
    LINE_START,
    LINE_STOP
} line_process_event;

typedef struct
{
    unsigned int x;
    unsigned int y;
} coord_obj;

typedef struct
{
    line_process_event event;
    coord_obj start;
    coord_obj stop;
} line_obj;

typedef struct
{
    SDL_Renderer* renderer;
    char is_init_success;

    line_obj line[LINE_CREATOR_MAX_CAN_LINE_NUMBER];  // bunu pointer yap , malloc ile çoðalt aq
    unsigned int line_count;

}line_creator_obj;




line_creator_func_out line_creator_create(line_creator_obj* me, SDL_Renderer* renderer);
 
line_creator_func_out line_creator_destroy(line_creator_obj* me);

line_creator_func_out line_creator_polling(line_creator_obj* me);

line_creator_func_out line_creator_mause_event_callback(line_creator_obj* me,
                                                        line_creator_mause_event_types m_event,
                                                        unsigned int mause_x , unsigned int mause_y);

#endif
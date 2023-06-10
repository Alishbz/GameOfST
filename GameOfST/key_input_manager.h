#pragma once
#ifndef KEY_INPUT_MANAGER_h_
#define KEY_INPUT_MANAGER_h_

/* Ali Þahbaz created **/

#define KEY_INPUT_MAX_CALLBACK_SIZE  10

typedef enum
{
    KEY_INPUT_SUCCESS,
    KEY_INPUT_FAIL
} key_input_func_out;

typedef enum  // ?
{
    KEY_INPUT_MAUSE_EMTY,
    KEY_INPUT_MAUSE_MOVING,
    KEY_INPUT_MAUSE_UP,
    KEY_INPUT_MAUSE_DOWN
} key_input_mause_events;

typedef enum
{
    KEY_INPUT_UP,
    KEY_INPUT_DOWN,
    KEY_INPUT_RIGHT,
    KEY_INPUT_LEFT,
    KEY_INPUT_QUIT,
    KEY_INPUT_A,
    KEY_INPUT_B
} key_input_keyboard_stades;

typedef struct
{
    int x;
    int y; 
    key_input_mause_events event_type;
} key_input_mause_str;


typedef void (*keyboard_input_fp)(key_input_keyboard_stades stade);

typedef void (*mause_click_update_fp)(key_input_mause_str*coord);

typedef struct  
{
    void (*callback_keyboard_fp_pool[KEY_INPUT_MAX_CALLBACK_SIZE])(key_input_keyboard_stades stade);
     
    unsigned int input_sens_pool[KEY_INPUT_MAX_CALLBACK_SIZE];




    void (*callback_mause_click_fp_pool[KEY_INPUT_MAX_CALLBACK_SIZE])(key_input_mause_str* coord);
    // filtre ? 
} key_input_obj;


key_input_func_out key_input_create(key_input_obj* me);
key_input_func_out key_input_add_new_keyboard_callback(key_input_obj* me , keyboard_input_fp* callback_fp, unsigned int input_sens);
key_input_func_out key_input_add_new_mause_callback(key_input_obj* me, mause_click_update_fp* callback_fp);
key_input_func_out key_input_polling(key_input_obj* me);
key_input_func_out key_input_destroy(key_input_obj* me);

#endif
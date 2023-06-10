/* Ali Þahbaz created **/
#include <SDL2/SDL.h>
#include "key_input_manager.h"


/*PRIVATES*/
static SDL_Event singleton_sdl_event;
static unsigned int input_sens_pool_counters[KEY_INPUT_MAX_CALLBACK_SIZE];
static unsigned short _keyboard_create_count = 0;
static unsigned short _mause_click_create_count = 0;


key_input_func_out key_input_create(key_input_obj* me) {

    if (me == NULL) { return KEY_INPUT_FAIL; }
    if(_keyboard_create_count > 0) { return KEY_INPUT_FAIL; }

    unsigned short i = 0;

    do {
        me->callback_keyboard_fp_pool[i] = NULL;
        me->input_sens_pool[i] = 0;
        input_sens_pool_counters[i] = 0;
        i++;
    } while (i < KEY_INPUT_MAX_CALLBACK_SIZE); 

    return KEY_INPUT_SUCCESS;
}


key_input_func_out key_input_add_new_keyboard_callback(key_input_obj* me, keyboard_input_fp* callback_fp, unsigned int input_sens) {
    if (me == NULL || callback_fp == NULL ) { return KEY_INPUT_FAIL; }
    if (_keyboard_create_count > (KEY_INPUT_MAX_CALLBACK_SIZE-1)) { return KEY_INPUT_FAIL; }

    me->callback_keyboard_fp_pool[_keyboard_create_count] = callback_fp;
    me->input_sens_pool[_keyboard_create_count] = input_sens;

    _keyboard_create_count++;

    return KEY_INPUT_SUCCESS;
}

key_input_func_out key_input_add_new_mause_callback(key_input_obj* me, mause_click_update_fp* callback_fp) {

    if (me == NULL || callback_fp == NULL) { return KEY_INPUT_FAIL; }
    if (_mause_click_create_count > (KEY_INPUT_MAX_CALLBACK_SIZE - 1)) { return KEY_INPUT_FAIL; }

    me->callback_mause_click_fp_pool[_mause_click_create_count] = callback_fp;

    _mause_click_create_count++;

    return KEY_INPUT_SUCCESS;
}

/** low level keyboard decition logic **/
static void _callback_keyboard_orders(key_input_obj* me, key_input_keyboard_stades stade) {
    unsigned short i = 0;
    do { 
        if (me->input_sens_pool[i] == input_sens_pool_counters[i]) {
            me->callback_keyboard_fp_pool[i](stade);
            input_sens_pool_counters[i] = 0;
        }
        else {
            input_sens_pool_counters[i]++;
        } 
        i++;
    } while (i < _keyboard_create_count);
}


/** low level mause click decition logic **/
static void _callback_mause_click_orders(key_input_obj* me, key_input_mause_str*coord) {
    unsigned short i = 0;
    do { 
        me->callback_mause_click_fp_pool[i](coord); 
        i++;
    } while (i < _mause_click_create_count);
}


key_input_func_out key_input_polling(key_input_obj* me) {
     

    

    if(SDL_PollEvent(&singleton_sdl_event))
    {
        switch (singleton_sdl_event.type)
        {
        case SDL_QUIT:
            _callback_keyboard_orders(me,KEY_INPUT_QUIT);
            break;
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN: {
            key_input_mause_str coord_mail;
            coord_mail.x = singleton_sdl_event.button.x;
            coord_mail.y = singleton_sdl_event.button.y;
            coord_mail.event_type = KEY_INPUT_MAUSE_EMTY;
            if (singleton_sdl_event.type == SDL_MOUSEMOTION) {
                coord_mail.event_type = KEY_INPUT_MAUSE_MOVING;
            }
            else if (singleton_sdl_event.type == SDL_MOUSEBUTTONUP) {
                coord_mail.event_type = KEY_INPUT_MAUSE_UP;
            }
            else if (singleton_sdl_event.type == SDL_MOUSEBUTTONDOWN) {
                coord_mail.event_type = KEY_INPUT_MAUSE_DOWN;
            } 
            _callback_mause_click_orders(me, &coord_mail); 
            break;
        }

                                
        case SDL_KEYDOWN:
            switch (singleton_sdl_event.key.keysym.sym)
            {
            case 'b': {
                _callback_keyboard_orders(me, KEY_INPUT_B);
                break;
            }
            case 'a': {
                _callback_keyboard_orders(me, KEY_INPUT_A);
                break;
            }
            case SDLK_LEFT: {
                _callback_keyboard_orders(me, KEY_INPUT_LEFT);
                break;
            }
            case SDLK_RIGHT: {
                _callback_keyboard_orders(me, KEY_INPUT_RIGHT);
                break;
            }
            case SDLK_UP: {
                _callback_keyboard_orders(me, KEY_INPUT_UP);
                break;
            }
            case SDLK_DOWN: {
                _callback_keyboard_orders(me, KEY_INPUT_DOWN);
                break;
            }
            }
        }
    }

    return KEY_INPUT_SUCCESS;
}

key_input_func_out key_input_destroy(key_input_obj* me) {
    //todo
}
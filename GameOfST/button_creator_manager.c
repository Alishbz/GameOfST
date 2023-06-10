/* Ali Þahbaz created **/
#include "button_creator_manager.h"
#include <SDL2/SDL_ttf.h>





static TTF_Font* font;  // test bunu yok et


button_creator_func_out button_creator_create(button_creator_obj* me,
                                              SDL_Renderer* renderer)
{
    if ((me == NULL)  || (renderer == NULL)) {
        return BUTTON_CREATOR_FAIL;
    }


    TTF_Init(); // ?yok et
    font = TTF_OpenFont("font.ttf", 24); // yok et


    me->button_count = 0;
    me->renderer = renderer;

    unsigned short i = 0 , t = 0;

    for (i = 0; i < BUTTON_CREATOR_MAX_NUMBER; i++) {
    
        me->buttons[i].callback = NULL;
        me->buttons[i].position.x = 0;
        me->buttons[i].position.y = 0;
        me->buttons[i].size.height = 0;
        me->buttons[i].size.lenght = 0;
        me->buttons[i].timer_ms = 0;
        for (t = 0; t < BUTTON_CREATOR_NAME_ARRAY_SIZE; t++) { 
          me->buttons[i].name[t] = 0;
        } 
    }
    me->is_init_success = 1;

    return BUTTON_CREATOR_SUCCESS;
}


 
// COLOR?
button_creator_func_out button_creator_new_button_create(button_creator_obj* me,
                                                        button_touch_calback_str* press_callback,
                                                        const char* button_name,
                                                        unsigned int height,
                                                        unsigned int lenght,
                                                        unsigned int x,
                                                        unsigned int y)
{
    if ((me == NULL) ) {
        return BUTTON_CREATOR_FAIL;
    }
    if (!me->is_init_success) {
        return BUTTON_CREATOR_FAIL;
    }

    if (me->button_count >= (BUTTON_CREATOR_MAX_NUMBER - 1)) { return BUTTON_CREATOR_FAIL; }

    me->buttons[me->button_count].size.height = height;
    me->buttons[me->button_count].size.lenght = lenght;

    me->buttons[me->button_count].position.x = x;
    me->buttons[me->button_count].position.y = y;

    if ((press_callback != NULL)) {
        me->buttons[me->button_count].callback = press_callback;
    }

    if (button_name != NULL) {
        unsigned short t = 0;
        for (t = 0; t < BUTTON_CREATOR_NAME_ARRAY_SIZE; t++) {
            if (!button_name[t]) { break; }// burda harf yada sayýmý kontrolü de yapýlabilinir ascii mi yani
            me->buttons[me->button_count].name[t] = button_name[t]; 
        }
    }
     
    me->button_count++;
    return BUTTON_CREATOR_SUCCESS;

}



button_creator_func_out button_creator_destroy(button_creator_obj* me);

button_creator_func_out button_creator_1_ms_timer(button_creator_obj* me)
{
    if (!me->is_init_success) {
        return BUTTON_CREATOR_FAIL;
    }

    unsigned short t = 0;

    for (t = 0; t < me->button_count; t++) { 
        me->buttons[me->button_count].timer_ms++;
    }

    return BUTTON_CREATOR_SUCCESS;
}


button_creator_func_out button_creator_polling(button_creator_obj* me)
{
    if (!me->is_init_success) { return BUTTON_CREATOR_FAIL; }

    if (me->button_count) {

        unsigned int i = 0;

        for (i = 0; i < me->button_count; i++) {
            

          // çalýþmöýo text
            /*SDL_Surface* text;
            SDL_Color color = { 0, 254, 0 }; 
            text = TTF_RenderText_Solid(font, me->buttons[i].name, color);
            SDL_Texture* text_texture; 
            text_texture = SDL_CreateTextureFromSurface(me->renderer, text); 
            SDL_Rect dest = (SDL_Rect){ me->buttons[i].position.x, me->buttons[i].position.y, me->buttons[i].size.lenght , me->buttons[i].size.height };
            SDL_RenderCopy(me->renderer, text_texture, &dest,NULL);
              */

            SDL_Rect button_params = (SDL_Rect){ me->buttons[i].position.x, me->buttons[i].position.y, me->buttons[i].size.lenght , me->buttons[i].size.height };
            SDL_RenderFillRect(me->renderer, &button_params); 
            SDL_SetRenderDrawColor(me->renderer, 150, 254, 45, 86); // color define et yada obje yaratýrken seç
            SDL_RenderPresent(me->renderer);
            
            /*SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text);*/
        }
    }

    return BUTTON_CREATOR_SUCCESS;
}



static char _check_is_there_match(button_creator_obj* me, unsigned int mause_x, unsigned int mause_y)
{

    unsigned short t = 0;

    for (t = 0; t < me->button_count; t++) {

        if ((mause_x < me->buttons[t].position.x + me->buttons[t].size.lenght) &&
            (mause_x > me->buttons[t].position.x) &&
            (mause_y > me->buttons[t].position.y) &&
            (mause_y < me->buttons[t].position.y + me->buttons[t].size.height)) {

            if (me->buttons[t].callback != NULL) {

                me->buttons[t].callback((button_creator_callback_type)BUTTON_CREATOR_PRESSED_UP); // bunu seç

                return 1;

            }
        }
             

    }

    return 0;

}


button_creator_func_out button_creator_mause_event_callback(button_creator_obj* me,
                                                            button_creator_mause_event_types m_event,
                                                            unsigned int mause_x, unsigned int mause_y)
{
    if (!me->is_init_success) { return BUTTON_CREATOR_FAIL; }

    switch (m_event)
    {
    case BUTTON_CREATOR_MAUSE_EMPTY: {        break; }
    case BUTTON_CREATOR_MAUSE_MOVEING: {      break; }
    case BUTTON_CREATOR_MAUSE_UP: {    _check_is_there_match(me, mause_x, mause_y);        break; }
    case BUTTON_CREATOR_MAUSE_DOWN: {         break; }
    default: break;
    }
    return BUTTON_CREATOR_SUCCESS;
}


/* Ali Þahbaz created **/
#include "line_creator_manager.h"


line_creator_func_out line_creator_polling(line_creator_obj* me)
{
    if (!me->is_init_success) { return LINE_CREATOR_FAIL; }

    if (me->line_count) {
    
        unsigned int i = 0;
        for (i = 0; i < me->line_count; i++) {
             
            SDL_RenderDrawLine(me->renderer, me->line[i].start.x, me->line[i].start.y, me->line[i].stop.x, me->line[i].stop.y);
            SDL_SetRenderDrawColor(me->renderer, 89, 15, 45, 86); // color define et yada obje yaratýrken seç
            SDL_RenderPresent(me->renderer);
        }
    } 

    return LINE_CREATOR_SUCCESS;
}


static void _line_start(line_creator_obj* me, unsigned int mause_x, unsigned int mause_y) {
    if (me->line_count < (LINE_CREATOR_MAX_CAN_LINE_NUMBER - 1)) {
        me->line[me->line_count].start.x = mause_x;
        me->line[me->line_count].start.y = mause_y;
    }
}
static void _line_stop(line_creator_obj* me, unsigned int mause_x, unsigned int mause_y) {
    if (me->line_count < (LINE_CREATOR_MAX_CAN_LINE_NUMBER - 1)) {
        me->line[me->line_count].stop.x = mause_x;
        me->line[me->line_count].stop.y = mause_y;

        /** next line update **/
        me->line_count++;
    }
}

line_creator_func_out line_creator_mause_event_callback(line_creator_obj* me,
                                                        line_creator_mause_event_types m_event,
                                                        unsigned int mause_x, unsigned int mause_y) 
{
    if (!me->is_init_success) { return LINE_CREATOR_FAIL; }
    switch (m_event)
    {
        case LINE_CREATOR_MAUSE_EMPTY: {        break; }
        case LINE_CREATOR_MAUSE_MOVEING: {      break; }
        case LINE_CREATOR_MAUSE_UP: {       _line_stop(me, mause_x, mause_y);     break; }
        case LINE_CREATOR_MAUSE_DOWN: {     _line_start(me, mause_x, mause_y);    break; }
        default: break;
    }  
    return LINE_CREATOR_SUCCESS;
}




line_creator_func_out line_creator_create(line_creator_obj* me , SDL_Renderer* renderer) {

    if (me == NULL || renderer == NULL) { return     LINE_CREATOR_FAIL; }

    me->renderer = renderer;

    me->line_count = 0;

    unsigned int i = 0;
    for (i = 0; i < LINE_CREATOR_MAX_CAN_LINE_NUMBER; i++) {
        me->line[i].event = LINE_CREATOR_MAUSE_EMPTY;
        me->line[i].stop.x = 0;
        me->line[i].stop.y = 0;
        me->line[i].start.x = 0;
        me->line[i].start.y = 0;
    } 
     
    me->is_init_success = 1;

	return LINE_CREATOR_SUCCESS;
}





line_creator_func_out line_creator_destroy(line_creator_obj* me) {

    me->is_init_success = 0;

	return LINE_CREATOR_SUCCESS;
}
/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void home_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCREEN_LOADED:
	{
		ui_move_animation(guider_ui.home_bg_weather, 10000, 0, -544, 0, &lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0, 0, NULL, NULL, NULL);
		break;
	}
	default:
		break;
	}
}
void events_init_home(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->home, home_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}
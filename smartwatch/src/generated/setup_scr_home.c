/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int home_digital_clock_min_value = 0;
int home_digital_clock_hour_value = 0;
int home_digital_clock_sec_value = 0;
void setup_scr_home(lv_ui *ui)
{
	//Write codes home
	ui->home = lv_obj_create(NULL);
	lv_obj_set_size(ui->home, 480, 320);
	lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);

	//Write style for home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_background
	ui->home_background = lv_obj_create(ui->home);
	lv_obj_set_pos(ui->home_background, 0, 0);
	lv_obj_set_size(ui->home_background, 1024, 320);
	lv_obj_set_scrollbar_mode(ui->home_background, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->home_background, LV_OBJ_FLAG_FLOATING);

	//Write style for home_background, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_background, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_bg_weather_day_clear
	ui->home_bg_weather_day_clear = lv_img_create(ui->home_background);
	lv_obj_add_flag(ui->home_bg_weather_day_clear, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->home_bg_weather_day_clear, &_bg_weather_day_clear_alpha_1024x320);
	lv_img_set_pivot(ui->home_bg_weather_day_clear, 50,50);
	lv_img_set_angle(ui->home_bg_weather_day_clear, 0);
	lv_obj_set_pos(ui->home_bg_weather_day_clear, 0, 0);
	lv_obj_set_size(ui->home_bg_weather_day_clear, 1024, 320);

	//Write style for home_bg_weather_day_clear, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->home_bg_weather_day_clear, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_bg_weather_day_cloudy
	ui->home_bg_weather_day_cloudy = lv_img_create(ui->home_background);
	lv_obj_add_flag(ui->home_bg_weather_day_cloudy, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->home_bg_weather_day_cloudy, &_bg_weather_day_cloudy_alpha_1024x320);
	lv_img_set_pivot(ui->home_bg_weather_day_cloudy, 50,50);
	lv_img_set_angle(ui->home_bg_weather_day_cloudy, 0);
	lv_obj_set_pos(ui->home_bg_weather_day_cloudy, 0, 0);
	lv_obj_set_size(ui->home_bg_weather_day_cloudy, 1024, 320);

	//Write style for home_bg_weather_day_cloudy, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->home_bg_weather_day_cloudy, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_overlay
	ui->home_overlay = lv_obj_create(ui->home);
	lv_obj_set_pos(ui->home_overlay, 0, 0);
	lv_obj_set_size(ui->home_overlay, 480, 320);
	lv_obj_set_scrollbar_mode(ui->home_overlay, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_overlay, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_overlay, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->home_overlay, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->home_overlay, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->home_overlay, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_overlay, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->home_overlay, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->home_overlay, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_overlay, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_content
	ui->home_content = lv_obj_create(ui->home);
	lv_obj_set_pos(ui->home_content, 0, 0);
	lv_obj_set_size(ui->home_content, 480, 320);
	lv_obj_set_scrollbar_mode(ui->home_content, LV_SCROLLBAR_MODE_OFF);

	//Write style for home_content, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_content, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->home_content, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->home_content, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->home_content, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_digital_clock
	static bool home_digital_clock_timer_enabled = false;
	ui->home_digital_clock = lv_dclock_create(ui->home_content, "0:00");
	if (!home_digital_clock_timer_enabled) {
		lv_timer_create(home_digital_clock_timer, 1000, NULL);
		home_digital_clock_timer_enabled = true;
	}
	lv_obj_set_pos(ui->home_digital_clock, 117, 10);
	lv_obj_set_size(ui->home_digital_clock, 346, 127);

	//Write style for home_digital_clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_digital_clock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_digital_clock, &lv_font_montserratMedium_120, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->home_digital_clock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_digital_clock, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_digital_clock, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_digital_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_label_temp
	ui->home_label_temp = lv_label_create(ui->home_content);
	lv_label_set_text(ui->home_label_temp, "0°");
	lv_label_set_long_mode(ui->home_label_temp, LV_LABEL_LONG_CLIP);
	lv_obj_set_pos(ui->home_label_temp, 24, 205);
	lv_obj_set_size(ui->home_label_temp, 140, 80);

	//Write style for home_label_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->home_label_temp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->home_label_temp, &lv_font_montserratMedium_80, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->home_label_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->home_label_temp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->home_label_temp, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->home_label_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of home.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->home);

	//Init events for screen.
	events_init_home(ui);
}

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/sdl/sdl.h"

#include "hal.h"

#include "custom.h"
#include "events_init.h"
#include "gui_guider.h"

lv_ui guider_ui;

int main(void)
{
  lv_init();

  hal_setup();

  lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
  lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
  lv_obj_set_size(btn, 120, 50);                          /*Set its size*/

  lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
  lv_label_set_text(label, "Button");                     /*Set the labels text*/
  lv_obj_center(label);

  // setup_ui(&guider_ui);

  // events_init(&guider_ui);

  // custom_init(&guider_ui);

  hal_loop();

  return 0;
}

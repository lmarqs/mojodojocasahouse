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

  setup_ui(&guider_ui);

  events_init(&guider_ui);

  custom_init(&guider_ui);

  hal_loop();

  return 0;
}

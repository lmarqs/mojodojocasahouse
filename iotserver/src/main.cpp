#include <lvgl.h>
// #include <lv_demos.h>
// #include <lv_examples.h>
// #include "IMG_8282_small.c"
#include "lvgl_clock.h"

int main(int argc, char **argv)
{
  lv_init();

#if LV_USE_LINUX_FBDEV
  lv_display_t *disp = lv_linux_fbdev_create();
  lv_linux_fbdev_set_file(disp, "/dev/fb1");
#endif

#if LV_USE_X11
  lv_display_t *disp = lv_x11_window_create("LVGL X11 Simulation", 480, 320);
#endif

#if LV_USE_SDL
  lv_display_t *disp = lv_sdl_window_create(480, 320);
#endif

  // lv_example_style_6();
  // lv_example_get_started_1();
  // lv_demo_render(LV_DEMO_RENDER_SCENE_IMAGE_NORMAL, LV_OPA_COVER);
  // lv_demo_music();
  // lv_demo_benchmark();

  // lv_image_dsc_t IMG_8282_small = {};

  // IMG_8282_small.header.cf = LV_COLOR_FORMAT_RGB565;
  // IMG_8282_small.header.magic = LV_IMAGE_HEADER_MAGIC;
  // IMG_8282_small.header.w = 427;
  // IMG_8282_small.header.h = 320;
  // IMG_8282_small.data_size = 136640 * 2;
  // IMG_8282_small.data = IMG_8282_small_map;

  // lv_obj_t * img1 = lv_image_create(lv_screen_active());
  // lv_image_set_src(img1, &IMG_8282_small);
  // lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

  lv_example_scale_6();

  while (true)
  {
    lv_timer_handler();
  }

  return 0;
}

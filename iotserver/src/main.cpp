#include <lvgl.h>
// #include <lv_demos.h>
// #include <lv_examples.h>
#include "IMG_8282.jpg.h"

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

  lv_image_dsc_t IMG_8282;

  IMG_8282.header.cf = LV_COLOR_FORMAT_RGB565A8;
  IMG_8282.header.magic = LV_IMAGE_HEADER_MAGIC;
  IMG_8282.header.w = 480;
  IMG_8282.header.h = 360;
  IMG_8282.data_size = 172800 * 2;
  IMG_8282.data = IMG_8282_map;

  lv_obj_t * img = lv_image_create(lv_screen_active());

  lv_image_set_src(img, &IMG_8282);

  lv_obj_center(img);

  while (true)
  {
    lv_timer_handler();
  }

  return 0;
}

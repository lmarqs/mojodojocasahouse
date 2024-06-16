#include <lv_demos.h>
#include <lv_examples.h>
#include <lvgl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  lv_init();

#if LV_USE_LINUX_FBDEV
  lv_display_t * disp = lv_linux_fbdev_create();
  lv_linux_fbdev_set_file(disp, "/dev/fb0");
#endif

#if LV_USE_X11
  lv_display_t * disp = lv_x11_window_create("LVGL X11 Simulation", 480, 320);
  // lv_x11_inputs_create(disp, NULL);
#endif

#if LV_USE_SDL
  lv_display_t * disp = lv_sdl_window_create(480, 320);
#endif

  // lv_example_get_started_1();
  lv_demo_render(LV_DEMO_RENDER_SCENE_IMAGE_NORMAL, LV_OPA_COVER);

  while(true)
  {
    lv_timer_handler();
    // usleep(5000);
  }

  return 0;
}

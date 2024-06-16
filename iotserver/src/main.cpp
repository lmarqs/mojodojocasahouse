// #include <app_hal.h>
#include <lv_examples.h>
#include <lvgl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// static const char *getenv_default(const char *name, const char *dflt)
// {
//     return getenv(name) ? : dflt;
// }

// static void lv_linux_disp_init(void)
// {
//     const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
//     lv_display_t * disp = lv_linux_fbdev_create();

//     lv_linux_fbdev_set_file(disp, device);
// }

// int main(void)
// {
//     lv_init();

//     // lv_linux_disp_init();

//     // lv_demo_widgets();

//     // lv_demo_widgets_start_slideshow();

//     lv_example_get_started_3();

//     while(1) {
//         lv_timer_handler();
//         usleep(5000);
//     }

//     return 0;
// }

// int main(void)
// {
// 	lv_init();

// 	// hal_setup();

// 	  lv_example_get_started_1();

// //   lv_demo_widgets();

// 	// hal_loop();
// }

int main(int argc, char ** argv)
{
  lv_init();

#if LV_USE_LINUX_FBDEV
	lv_display_t * disp = lv_linux_fbdev_create();
	lv_linux_fbdev_set_file(disp, "/dev/fb0");
#endif

#if LV_USE_X11
  lv_display_t * disp = lv_x11_window_create("LVGL X11 Simulation", 480, 320);
  lv_x11_inputs_create(disp, NULL);
#endif

#if LV_USE_SDL
  lv_display_t * disp = lv_sdl_window_create(480, 320);
#endif

  lv_example_get_started_1();

  while(true)
  {
    lv_timer_handler();
    usleep(5000);
  }

  return 0;
}

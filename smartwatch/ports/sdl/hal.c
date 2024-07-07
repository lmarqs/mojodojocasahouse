#include <pthread.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"

#include SDL_INCLUDE_PATH

static int sdl_hal_tick_thread(void *data)
{
  (void)data;

  while (true)
  {
    SDL_Delay(5);
    lv_tick_inc(5);
  }

  return 0;
}

void hal_setup(void)
{
  LV_LOG_USER("[SDL] setting up: %dx%d", SDL_HOR_RES, SDL_VER_RES);
// Workaround for sdl2 `-m32` crash
// https://bugs.launchpad.net/ubuntu/+source/libsdl2/+bug/1775067/comments/7
#ifndef WIN32
  setenv("DBUS_FATAL_WARNINGS", "0", 1);
#endif

  static lv_disp_draw_buf_t disp_buf;
  static lv_color_t buf[SDL_HOR_RES * 10];
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * 10);

  static lv_disp_drv_t disp_drv;

  lv_disp_drv_init(&disp_drv);

  disp_drv.flush_cb = sdl_display_flush;
  disp_drv.draw_buf = &disp_buf;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;

  lv_disp_drv_register(&disp_drv);

  sdl_init();

  SDL_CreateThread(sdl_hal_tick_thread, "tick", NULL);
}

void hal_loop(void)
{
  LV_LOG_USER("[SDL] begin loop");

  while (true)
  {
    SDL_Delay(5);
    lv_task_handler();
  }
}

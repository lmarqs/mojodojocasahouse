#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"

void hal_setup(void)
{
  LV_LOG_USER("[FBDEV] setting up: %s %dx%d", FBDEV_PATH, FBDEV_HOR_RES, FBDEV_VER_RES);

  fbdev_init();

  static lv_color_t buf[128 * 1024];

  static lv_disp_draw_buf_t disp_buf;

  lv_disp_draw_buf_init(&disp_buf, buf, NULL, 128 * 1024);

  static lv_disp_drv_t disp_drv;

  lv_disp_drv_init(&disp_drv);

  disp_drv.draw_buf = &disp_buf;
  disp_drv.flush_cb = fbdev_flush;
  disp_drv.hor_res = FBDEV_HOR_RES;
  disp_drv.ver_res = FBDEV_VER_RES;

  lv_disp_drv_register(&disp_drv);
}

void hal_loop(void)
{
  LV_LOG_USER("[FBDEV] begin loop");

  while (true)
  {
    lv_timer_handler();
    lv_tick_inc(5);
    usleep(5000);
  }
}

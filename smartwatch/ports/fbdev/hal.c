#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"

uint32_t fbdev_hal_tick_get(void)
{
  static uint64_t start_ms = 0;

  LV_LOG_USER("start_ms: %d", start_ms);

  if (start_ms == 0)
  {
    struct timeval tv_start;

    gettimeofday(&tv_start, NULL);

    start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
  }

  struct timeval tv_now;

  gettimeofday(&tv_now, NULL);

  uint64_t now_ms;

  now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

  uint32_t time_ms = now_ms - start_ms;

  return time_ms;
}

void hal_setup(void)
{
  LV_LOG_USER("Starting FBDEV HAL: %s %d %dx%d", FBDEV_PATH, LV_TICK_CUSTOM_SYS_TIME_EXPR, FBDEV_HOR_RES, FBDEV_VER_RES);

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
  while (true)
  {
    lv_timer_handler();
    // lv_task_handler();
    usleep(5000);
  }
}

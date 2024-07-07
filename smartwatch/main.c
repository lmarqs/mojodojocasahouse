#include <pthread.h>
#include <unistd.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"
#include "src/custom/custom.h"
#include "src/generated/events_init.h"
#include "src/generated/gui_guider.h"

lv_ui guider_ui;

static int tick_thread(void *data)
{
  (void)data;

  while (1)
  {
    SDL_Delay(5);   /*Sleep for 5 millisecond*/
    lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
  }

  return 0;
}

void hal_setup(void)
{
// Workaround for sdl2 `-m32` crash
// https://bugs.launchpad.net/ubuntu/+source/libsdl2/+bug/1775067/comments/7
#ifndef WIN32
  setenv("DBUS_FATAL_WARNINGS", "0", 1);
#endif

  /* Add a display
   * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/

  static lv_disp_draw_buf_t disp_buf;
  static lv_color_t buf[SDL_HOR_RES * 10];                       /*Declare a buffer for 10 lines*/
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * 10); /*Initialize the display buffer*/

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
  disp_drv.flush_cb = sdl_display_flush; /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
  disp_drv.draw_buf = &disp_buf;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;
  // disp_drv.disp_fill = monitor_fill;      /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
  // disp_drv.disp_map = monitor_map;        /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
  lv_disp_drv_register(&disp_drv);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = sdl_mouse_read; /*This function will be called periodically (by the library) to get the mouse position and state*/
  lv_indev_drv_register(&indev_drv);

  sdl_init();

  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about how much time were elapsed
   * Create an SDL thread to do this*/
  SDL_CreateThread(tick_thread, "tick", NULL);
}

void hal_loop(void)
{
  while (1)
  {
    SDL_Delay(5);
    lv_task_handler();
  }
}

int main(void)
{
  lv_init();
  hal_setup();
  // lv_port_disp_init(480, 320);
  // lv_port_indev_init(true);

#if LV_USE_LINUX_FBDEV
  lv_disp_t *disp = lv_linux_fbdev_create();
  lv_linux_fbdev_set_file(disp, "/dev/fb1");
#endif

#if LV_USE_X11
  lv_disp_t *disp = lv_x11_window_create("LVGL X11 Simulation", 480, 320);
#endif

#if USE_SDL
  // lv_disp_t *disp = lv_sdl_window_create(480, 320);
  sdl_init();
#endif

  setup_ui(&guider_ui);
  events_init(&guider_ui);
  custom_init(&guider_ui);

  hal_loop();

  // while (true)
  // {
  //   lv_task_handler();
  //   lv_timer_handler();
  //   usleep(5*1000);
  // }

  return 0;
}
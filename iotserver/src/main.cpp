#include <lvgl.h>
#include <lv_examples.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static const char *getenv_default(const char *name, const char *dflt)
{
    return getenv(name) ? : dflt;
}

static void lv_linux_disp_init(void)
{
    const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
    lv_display_t * disp = lv_linux_fbdev_create();

    lv_linux_fbdev_set_file(disp, device);
}

int main(void)
{
    lv_init();

    lv_linux_disp_init();

    // lv_demo_widgets();

    // lv_demo_widgets_start_slideshow();

    lv_example_get_started_3();

    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

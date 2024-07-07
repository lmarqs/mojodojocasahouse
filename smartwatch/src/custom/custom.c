#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lvgl.h"
#include "custom.h"

lv_ui *global_ui;

static void custom_timer_cb(lv_timer_t *timer)
{
  // static time_t current_time_epoch;

  // time(&current_time_epoch);

  // static char text[64];

  // tm *current_time_breakdown = localtime(&current_time_epoch);

  // strftime(text, sizeof(text), "%a %d/%m/%y\n%H:%M:%S", current_time_breakdown);

  // lv_label_set_text(global_ui->home_label_clock, text);
}

void custom_init(lv_ui *ui)
{
  global_ui = ui;
  lv_timer_create(custom_timer_cb, 1000, NULL);
}


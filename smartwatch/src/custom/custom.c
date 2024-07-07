#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lvgl.h"
#include "custom.h"

lv_ui *global_ui;

extern int home_digital_clock_hour_value;
extern int home_digital_clock_min_value;
extern int home_digital_clock_sec_value;

static void custom_timer_cb(lv_timer_t *timer)
{
  static time_t current_time_epoch;

  time(&current_time_epoch);


  struct tm *current_time_breakdown = localtime(&current_time_epoch);

  home_digital_clock_hour_value = current_time_breakdown->tm_hour;
  home_digital_clock_min_value = current_time_breakdown->tm_min;

  // static char text[64];
  
  // strftime(text, sizeof(text), "%a %d/%m/%y\n%H:%M:%S", current_time_breakdown);

  // lv_label_set_text(global_ui->home_label_clock, text);
}


void custom_init(lv_ui *ui)
{
  global_ui = ui;
  home_digital_clock_hour_value = 12;
  lv_timer_create(custom_timer_cb, 1000, NULL);
}


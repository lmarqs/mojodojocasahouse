#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "lvgl.h"
#include "custom.h"
#include "server.h"

static lv_ui *custom_ui;

static void custom_timer_cb(lv_timer_t *timer)
{
  static time_t current_time_epoch;

  static struct tm *current_time_breakdown = NULL;

  static uint8_t buf[64];

  time(&current_time_epoch);

  current_time_breakdown = localtime(&current_time_epoch);

  strftime(buf, sizeof(buf), "%H:%M", current_time_breakdown);

  lv_label_set_text(custom_ui->home_label_clock, buf);

  strftime(buf, sizeof(buf), "%a %d/%m/%y", current_time_breakdown);

  lv_label_set_text(custom_ui->home_label_calendar, buf);
}

static struct sockaddr_un custom_server_addr = {
    .sun_family = AF_UNIX,
    .sun_path = "/tmp/smartwatch.sock"};

static void custom_server_callback(uint8_t * buf, size_t len) {
  sprintf(buf, "%d°", (int8_t) buf[0]);

  lv_label_set_text(custom_ui->home_label_temp, buf);
}

void custom_init(lv_ui *ui)
{
  custom_ui = ui;

  lv_timer_create(custom_timer_cb, 1000, NULL);

  custom_server_create(&custom_server_addr, &custom_server_callback);
}

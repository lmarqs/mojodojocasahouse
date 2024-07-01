#include <lvgl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

lv_span_t *span;

static void timer_cb(lv_timer_t *timer)
{
  static time_t current_time_epoch;

  time(&current_time_epoch);

  static char text[64];

  tm *current_time_breakdown = localtime(&current_time_epoch);

  strftime(text, sizeof(text), "%a %d/%m/%y\n%H:%M:%S", current_time_breakdown);

  lv_span_set_text(span, text);
}

int main(int argc, char **argv)
{
  lv_init();

#if LV_USE_LINUX_FBDEV
  lv_display_t *disp = lv_linux_fbdev_create();
  lv_linux_fbdev_set_file(disp, "/dev/fb1");
#endif

#if LV_USE_X11
  lv_display_t *disp = lv_x11_window_create("LVGL X11 Simulation", 480, 320);
#endif

#if LV_USE_SDL
  lv_display_t *disp = lv_sdl_window_create(480, 320);
#endif

  static lv_style_t style;
  lv_style_init(&style);
  // lv_style_set_border_width(&style, 1);
  // lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_ORANGE));
  // lv_style_set_pad_all(&style, 2);

  lv_obj_t *spans = lv_spangroup_create(lv_screen_active());
  lv_obj_set_width(spans, 480);
  lv_obj_set_height(spans, 320);
  lv_obj_center(spans);
  lv_obj_add_style(spans, &style, 0);

  lv_spangroup_set_align(spans, LV_TEXT_ALIGN_CENTER);
  // lv_spangroup_set_overflow(spans, LV_SPAN_OVERFLOW_CLIP);
  lv_spangroup_set_indent(spans, 20);
  lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);

  span = lv_spangroup_new_span(spans);
  lv_span_set_text(span, "");

#if LV_FONT_MONTSERRAT_48
  lv_style_set_text_font(&span->style,  &lv_font_montserrat_48);
#endif
  // lv_style_set_text_font(&span->style,  LV_FONT_UNSCII_16);
  // lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_RED));
  // lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);
  // lv_style_set_text_opa(&span->style, LV_OPA_50);

  lv_timer_create(timer_cb, 1000, NULL);

  while (true)
  {
    lv_timer_handler();
  }

  return 0;
}

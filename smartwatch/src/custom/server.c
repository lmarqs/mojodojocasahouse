#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include "server.h"
#include "lvgl/lvgl.h"

struct connection_listening_thread_args
{
  custom_server_callback_t callback;
  int server_fd;
};

static void * listening_thread(void *raw_args)
{
  struct connection_listening_thread_args *args = (struct connection_listening_thread_args *)raw_args;

  while (true)
  {
    uint32_t sock_len = 0;

    struct sockaddr_un client_addr = {};

    int client_fd = accept(args->server_fd, (struct sockaddr *)&client_addr, &sock_len);

    uint8_t buf[0xFF];
    size_t buf_len = sizeof(buf);

    memset(buf, 0, buf_len);

    ssize_t data_len = 0;

    while ((data_len = recv(client_fd, buf, buf_len, 0)) > 0)
    {
      (*(args->callback))(buf, data_len);
    }
  }
}

int custom_server_create(struct sockaddr_un *server_addr, custom_server_callback_t callback)
{
  int server_fd;

  if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    LV_LOG_ERROR("Error on socket() call ");

    return -1;
  }

  unlink(server_addr->sun_path);

  if (bind(server_fd, (struct sockaddr *)server_addr, strlen(server_addr->sun_path) + sizeof(server_addr->sun_family)))
  {
    LV_LOG_ERROR("Error on binding socket ");

    return -1;
  }

  if (chmod(server_addr->sun_path, 0b111111111))
  {
    LV_LOG_ERROR("Error on chmod socket ");

    return -1;
  }

  if (listen(server_fd, 5))
  {
    LV_LOG_ERROR("Error on listen call ");

    return -1;
  }

  pthread_t listening_tid = 0x0;

  struct connection_listening_thread_args listening_args = {
      .callback = callback,
      .server_fd = server_fd};

  if (pthread_create(&listening_tid, NULL, listening_thread, &listening_args) != 0)
  {
    LV_LOG_ERROR("Failed to create thread");
  }

  return 0;
}

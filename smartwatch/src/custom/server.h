#ifndef __CUSTOM_SERVER_H_
#define __CUSTOM_SERVER_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <stdio.h>

typedef void (*custom_server_callback_t)(uint8_t *, size_t);

int custom_server_create(struct sockaddr_un *addr, custom_server_callback_t cb);

#ifdef __cplusplus
}
#endif
#endif

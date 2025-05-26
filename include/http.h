#ifndef HTTP_H
#define HTTP_H
#include "main.h"
#include "tasks.h"
#include "esp_http_client.h"
#include "HTTPClient.h"




void http_setup();
void http_post();
void http_setup();
void wifi_setup();
void http_post_task(void *pvParameters);



#endif

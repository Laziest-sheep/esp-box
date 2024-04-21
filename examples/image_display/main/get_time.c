
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "cJSON.h"
#include <string.h>

/**
 *  @brief 该代码要实现连接wifi，并且获取时间
 * 
 **/

#define MAX_HTTP_OUTPUT_BUFFER 128

static const char *TAG = "get_time";

extern char time_buf[32];
static esp_http_client_config_t config ;
static char output_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};   //用于接收通过http协议返回的数据
static int content_length = 0;  //http协议头的长度
static esp_http_client_handle_t client;

static void http_test_task(void)
{

//02-1 定义需要的变量
    
    

    //02-2 配置http结构体
   
   //定义http配置结构体，并且进行清零
    
    memset(&config,0,sizeof(config));

    //向配置结构体内部写入url
    
   
    static const char *URL = "http://quan.suning.com/getSysTime.do";
    config.url = URL;

    //初始化结构体
    client = esp_http_client_init(&config);	//初始化http连接

    //设置发送请求 
    esp_http_client_set_method(client, HTTP_METHOD_GET);

    //02-3 循环通讯

    // while(1)
    // {
    // 与目标主机创建连接，并且声明写入内容长度为0
    esp_err_t err = esp_http_client_open(client, 0);

    //如果连接失败
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open HTTP connection");
    } 
    //如果连接成功
    else {
        //读取目标主机的返回内容的协议头
        content_length = esp_http_client_fetch_headers(client);
        //如果协议头长度小于0，说明没有成功读取到
        if (content_length < 0) {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
        } 
        //如果成功读取到了协议头
        else {
            //读取目标主机通过http的响应内容
            int data_read = esp_http_client_read_response(client, output_buffer, MAX_HTTP_OUTPUT_BUFFER);
            if (data_read >= 0) {

                //打印响应内容，包括响应状态，响应体长度及其内容
                ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %lld",
                esp_http_client_get_status_code(client),				//获取响应状态信息
                esp_http_client_get_content_length(client));			//获取响应信息长度
                ESP_LOGI(TAG, "data:%s\n", output_buffer);
				//对接收到的数据作相应的处理
                cJSON* root = NULL;
                root = cJSON_Parse(output_buffer);
                cJSON* time =cJSON_GetObjectItem(root,"sysTime2");
                ESP_LOGI(TAG, "%s\n",time->valuestring);
                sprintf(time_buf, "date time : %s", time->valuestring);
                time_buf[28] = '\0';
            } 
            //如果不成功
            else {
                ESP_LOGE(TAG, "Failed to read response");
            }
        }
    // }

    //关闭连接
    esp_http_client_close(client);

    //延时
    // vTaskDelay(3000/portTICK_PERIOD_MS);

    }
	


}

void get_time_init(void)
{

   //创建进程，用于处理http通讯
//    xTaskCreate(&http_test_task, "http_test_task", 8192, NULL, 5, NULL);
    http_test_task();
}



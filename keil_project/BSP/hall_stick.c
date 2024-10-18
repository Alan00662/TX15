
#include "usart.h"
#include "hall_stick.h"

#define USART_REC_LEN 200 /* 定义最大接收字节数 200 */
#define USART_EN_RX 1     /* 使能（1）/禁止（0）串口1接收 */
#define RXBUFFERSIZE 1    /* 缓存大小 */

/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t g_usart_rx_buf[USART_REC_LEN];
uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE]; /* HAL库使用的串口接收缓冲 */

uint32_t hall_stick_tick = 0;
void rx4_handler(void)
{
    if ((HAL_GetTick() - hall_stick_tick) > 2)
    {
        if ((g_usart_rx_sta & 0x8000) == 0) /* 接收未完成 */
        {
            if (g_usart_rx_sta & 0x4000) /* 接收到了0x0d */
            {
                if (g_rx_buffer[0] != 0x0a)
                {
                    g_usart_rx_sta = 0; /* 接收错误,重新开始 */
                }
                else
                {
                    g_usart_rx_sta |= 0x8000; /* 接收完成了 */
                }
            }
            else /* 还没收到0X0D */
            {
                if (g_rx_buffer[0] == 0x0d)
                {
                    g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = g_rx_buffer[0];
                    g_usart_rx_sta++;
                    if (g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
        HAL_UART_Receive_IT(&huart4, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
        hall_stick_tick = HAL_GetTick();
    }
}
#include <stdio.h>
#include "py32f0xx.h"

void SysTick_Handler()
{
    HAL_IncTick();
}

int main (void)
{
    HAL_Init();
    SystemCoreClockUpdate();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    HAL_GPIO_Init(GPIOB, &(GPIO_InitTypeDef){.Mode = GPIO_MODE_OUTPUT_OD, .Pin = GPIO_PIN_0});
    while(1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_Delay(100);
    }
}
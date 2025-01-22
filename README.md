//Contoh Penggunaan
```

#include "main.h"
  
#include <stdio.h>
  
#include "AS5600.h"

AS5600_TypeDef sensor;



int main(void){
  
    HAL_Init();
  
    SystemClock_Config();
  
    MX_GPIO_Init();
  
    MX_USART1_UART_Init();
  
    MX_I2C2_Init();

    AS5600_Init(&sensor, &hi2c2);

    while (1)
    {
      
        float angle = AS5600_GetAngleDegrees(&sensor);
      
        printf("Angle: %.2f degrees\r\n", angle);
    }
  
  }
```

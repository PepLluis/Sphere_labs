#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include <applibs/gpio.h>
#include <hw/template_appliance.h>

typedef enum {
    ExitCode_Success = 0,
    ExitCode_HardwareNotReady = 1
} ExitCode;

int main(void)
{
    // status 
    bool On  = GPIO_Value_Low;
    bool Off = GPIO_Value_High;
    bool Pressed  = GPIO_Value_Low;
    bool Released = GPIO_Value_High;
    // define output RGB Led 
    int Led_Red   = GPIO_OpenAsOutput(MT3620_RDB_LED1_RED,   GPIO_OutputMode_PushPull, GPIO_Value_High);
    int Led_Blue  = GPIO_OpenAsOutput(MT3620_RDB_LED1_BLUE,  GPIO_OutputMode_PushPull, GPIO_Value_High);
    int Led_Green = GPIO_OpenAsOutput(MT3620_RDB_LED1_GREEN, GPIO_OutputMode_PushPull, GPIO_Value_High);
    // define inputs & value type
    int Switch1   = GPIO_OpenAsInput(MT3620_RDB_BUTTON_A);
    int Switch2   = GPIO_OpenAsInput(MT3620_RDB_BUTTON_B);
    GPIO_Value_Type BtnA_Status;
    GPIO_Value_Type BtnB_Status;
    // Initial values
    bool GPIOReady = false;
    bool BlinkLoop = false;
    // show pin assignations
    Log_Debug(
        "Used GPIO Pins Blue :%d, Green :%d, Red :%d.\n",
        Led_Blue, Led_Green, Led_Red);
    // 
    GPIO_SetValue(Led_Blue,  Off);
    GPIO_SetValue(Led_Green, Off);
    GPIO_SetValue(Led_Red,   Off);
    // timer 1"
    const struct timespec sleepTime = {.tv_sec = 1, .tv_nsec = 0};

    // Check GPIO
    if (Led_Green > 0 && Led_Red > 0 && Led_Blue > 0 && Switch1 > 0 && Switch2 > 0 ) {
        GPIOReady = true;
    }
    // Main
    while (GPIOReady) {
        GPIO_GetValue(Switch1, &BtnA_Status);
        //
        if(BtnA_Status == Pressed)
        {
            // Start blink loop
            BlinkLoop = true;
        }
        //
        while(BlinkLoop)
        {
            GPIO_GetValue(Switch2, &BtnB_Status);
            if (BtnB_Status == Pressed)
            {
                BlinkLoop = false;
            }
            //
            GPIO_SetValue(Led_Green, On);
            GPIO_SetValue(Led_Red, Off);
            nanosleep(&sleepTime, NULL);
            GPIO_SetValue(Led_Blue, On);
            GPIO_SetValue(Led_Green, Off);
            nanosleep(&sleepTime, NULL);
            GPIO_SetValue(Led_Red, On);
            GPIO_SetValue(Led_Green, Off);
            GPIO_SetValue(Led_Blue, Off);
            nanosleep(&sleepTime, NULL);
        }
    }
    return ExitCode_HardwareNotReady;
}

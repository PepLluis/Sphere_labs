// main

#pragma region Includes
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include <applibs/gpio.h>
#pragma endregion


int main(void)
{
	// BCN Labs - GetStarted with Azure Sphere - Blink
	Log_Debug("Starting: Define GPIO.\n");

	// Define outputs
	int led_Red	  = GPIO_OpenAsOutput( 8, GPIO_OutputMode_PushPull, GPIO_Value_High);
	int led_Green = GPIO_OpenAsOutput( 9, GPIO_OutputMode_PushPull, GPIO_Value_High);
	int led_Blue  = GPIO_OpenAsOutput(10, GPIO_OutputMode_PushPull, GPIO_Value_High);

	// Check for correct configuration app_manifest.json
	Log_Debug("Starting: Check GPIO availability.\n");
	if (led_Green < 0 || led_Blue < 0 || led_Red < 0)
	{
		Log_Debug("Error opening GPIO: %s (%d).", strerror(errno), errno);
		return -1;
	}
	Log_Debug("Starting: Define timespec constants .\n");
	const struct timespec sleepTime1 = { 0, 100000000 };
	const struct timespec sleepTime2 = { 0, 400000000 };
	const struct timespec sleepTime3 = { 1, 0 };
	// GPIO_Value_Type newState;
	const bool On  = GPIO_Value_Low;
	const bool Off = GPIO_Value_High;
	// 
	Log_Debug("Starting: Executing main loop.\n");
	while (true) {
		Log_Debug("Green");
		GPIO_SetValue(led_Blue, Off);
		GPIO_SetValue(led_Green, On);
		nanosleep(&sleepTime1, NULL);
		Log_Debug("Blue");
		GPIO_SetValue(led_Blue, On);
		GPIO_SetValue(led_Green, Off);
		nanosleep(&sleepTime2, NULL);
		Log_Debug("Red");
		GPIO_SetValue(led_Blue, Off);
		GPIO_SetValue(led_Red, On);
		nanosleep(&sleepTime1, NULL);
		Log_Debug("Blanc");
		GPIO_SetValue(led_Red, Off);
		nanosleep(&sleepTime3, NULL);
	}
}

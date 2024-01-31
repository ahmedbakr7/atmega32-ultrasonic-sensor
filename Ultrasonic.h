#pragma once
#include "icu.h"
#include "gpio.h"
#include "common_macros.h"
#include "util/delay.h"


// 2- 400cm
// Trigger pin must recieve a pulse atleast 10U sec

#define ULTRASONIC_TRIGGER_PORT PORTB_ID
#define ULTRASONIC_TRIGGER_PIN  PIN5_ID




void Ultrasonic_Init(void);

void Ultrasonic_trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

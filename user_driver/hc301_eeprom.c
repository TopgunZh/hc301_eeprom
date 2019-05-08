#include "hc301_eeprom.h"

#define DATA_INPUT		do{\
												GPIO_InitStruct.Pin = PWM_DATA_Pin;\
												GPIO_InitStruct.Mode = GPIO_MODE_INPUT;\
												GPIO_InitStruct.Pull = GPIO_PULLUP;\
												HAL_GPIO_Init(PWM_DATA_GPIO_Port, &GPIO_InitStruct);\
											}while(0)
					
#define DATA_OUT			do{\
											  GPIO_InitStruct.Pin = PWM_DATA_Pin;\
												GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;\
												GPIO_InitStruct.Pull = GPIO_NOPULL;\
												GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;\
												HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);\
											}while(0)	

#define DATA_HIGH			do{\
												HAL_GPIO_WritePin(PWM_DATA_GPIO_Port, PWM_DATA_Pin, GPIO_PIN_SET);\
											}while(0)

#define DATA_LOW			do{\
												HAL_GPIO_WritePin(PWM_DATA_GPIO_Port, PWM_DATA_Pin, GPIO_PIN_RESET);\
											}while(0)
#define DATA_READ			HAL_GPIO_ReadPin(PWM_DATA_GPIO_Port, PWM_DATA_Pin)
		
#define CLOCK_HIGH		do{\
												HAL_GPIO_WritePin(S3_CLOCK_GPIO_Port, S3_CLOCK_Pin, GPIO_PIN_SET);\
											}while(0)

#define CLOCK_LOW			do{\
												HAL_GPIO_WritePin(S3_CLOCK_GPIO_Port, S3_CLOCK_Pin, GPIO_PIN_RESET);\
											}while(0)


TIM_HandleTypeDef *htim = &htim3;
GPIO_InitTypeDef GPIO_InitStruct = {0};

static void delay_us(uint16_t us){
	uint16_t differ = 0xffff - us - 5;
	__HAL_TIM_SET_COUNTER(htim, differ);
	HAL_TIM_Base_Start(htim);
	
	while( differ < 0xffff-6 ){
		differ = __HAL_TIM_GET_COUNTER(htim);
	}
	
	HAL_TIM_Base_Stop(htim);
}


#pragma pack(push,1)
// <! The HCS301 contains 192 bits (12 x 16-bit words) of EEPROM memory
struct eeprom_map_t{
	uint16_t key_0;					// <!64-bit encryption key (word 0)
	uint16_t key_1;					// <!64-bit encryption key (word 1)
	uint16_t key_2;					// <!64-bit encryption key (word 2)
	uint16_t key_3;					// <!64-bit encryption key (word 3)
	uint16_t sync;					// <!16-bit synchronization value 
	uint16_t reserved;			// <!Set to 0000H
	uint16_t ser_0;					// <!Device Serial Number (word 0)
	uint16_t ser_1;					// <!Device Serial Number (word 1)
	uint16_t seed_0;				// <!Seed Value (word 0)
	uint16_t seed_1;				// <!Seed Value (word 1)
	uint16_t en_key;				// <!16-bit Envelope Key
	uint16_t config;				// <!Configuration Word
};
#pragma pack(pop)



void enter_program_mode(void){
	DATA_OUT;
	CLOCK_LOW;
	DATA_LOW;
	
}

void write_word(uint16_t word){

}

uint16_t read_word(void){
	
}

bool verify_data(void){
	
}


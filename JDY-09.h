/*
 * JDY-09.h
 *
 *  Created on: Nov 24, 2021
 *      Author: ROJEK
 */
#include "ringbuffer.h"

#ifndef INC_JDY_09_H_
#define INC_JDY_09_H_

// To define by user, all characters until this character will be transfered to buffer
#define JDY09_LASTCHARACTER				'\n'

#define JDY09_MAX_CMD_LENGHT			32
#define JDY09_UART_TIMEOUET				1000

// Predefined baud rate
#define JDY09_BAUDRATE_9600 			4
#define JDY09_BAUDRATE_19200 			5
#define JDY09_BAUDRATE_38400 			6
#define JDY09_BAUDRATE_57600 			7
#define JDY09_BAUDRATE_115200 			8
#define JDY09_BAUDRATE_128000 			9

// Maximum message size
#define JDY09_RECIEVEBUFFERSIZE			64

// Message pending
#define JDY09_NOMESSAGE					0
#define JDY09_MESSAGEPENDING			1

// Maximum pin and lenght
#define JDY09_MAX_NAME_LENGHT			18
#define JDY09_MAX_PIN_LENGHT			4

// Define RX - IT/DMA
#define JDY09_UART_RX_IT				0

#if (JDY09_UART_RX_IT == 0)
#define JDY09_UART_RX_DMA				1
#endif

// Commands to MCU
typedef enum JDY09{
	JDY09_CMD_GETVERSION,
	JDY09_CMD_RESET,
	JDY09_CMD_GETADRESS,
	JDY09_CMD_GETBAUDRATE,
	JDY09_CMD_GETPASSWORD,
	JDY09_CMD_GETNAME,
	JDY09_CMD_SETDEFAULTSETTINGS
}JDY09_CMD;

typedef struct JDY09_t
{
	UART_HandleTypeDef*	huart; 						// Uart handle

	uint8_t RecieveBufferDMA[JDY09_RECIEVEBUFFERSIZE]; // buffer for received messages in DMA mode

	uint8_t RecieveBufferIT;// 1 byte buffer for a single char received in IRQ mode

	Ringbuffer_t RingBuffer;						// ring buffer to save data

	volatile uint8_t LinesRecieved;					// lines that were received

	uint8_t MessagePending;							// status that message is ready to parse

	GPIO_TypeDef*	StateGPIOPort;					// handle for state pin

	uint16_t		StatePinNumber;					// pin number for state pin


}JDY09_t;


void JDY09_Init(JDY09_t *jdy09, UART_HandleTypeDef *huart, GPIO_TypeDef *StateGPIOPort, uint16_t StateGPIOPin);
void JDY09_SendCommand(JDY09_t* jdy09, JDY09_CMD Command);
void JDY09_SendData(JDY09_t *jdy09, uint8_t* Data);
void JDY09_SetBaudRate(JDY09_t* jdy09,uint8_t Baudrate);
void JDY09_SetName(JDY09_t* jdy09,uint8_t* Name);
void JDY09_SetPassword(JDY09_t* jdy09,uint8_t* Password);
void JDY09_Disconnect(JDY09_t *jdy09);
void JDY09_ClearMsgPendingFlag(JDY09_t* jdy09);
uint8_t JDY09_CheckPendingMessages(JDY09_t* jdy09,uint8_t* MsgBuffer);
#if (JDY09_UART_RX_IT == 1)
void JDY09_RxCpltCallbackIT(JDY09_t *jdy09, UART_HandleTypeDef *huart);
#endif
#if (JDY09_UART_RX_DMA == 1)
void JDY09_RxCpltCallbackDMA(JDY09_t *jdy09, UART_HandleTypeDef *huart,uint16_t size);
#endif
void JDY09_EXTICallback(JDY09_t *jdy09, uint16_t GPIO_Pin);
#endif /* INC_JDY_09_H_ */

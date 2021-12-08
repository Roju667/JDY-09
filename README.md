# JDY-09 STM32 HAL library
Library for cheap clone of HC-05 called JDY_09. JDY_31 is the small board placed on the module.

It took me few days to find any documenatation about JDY_09 module so i decided to create this for some future explorers. 
It may have some flaws but you can edit it for your purpose. So far i created it to work with HAL library to make it easier. 

UART communication works on IRQ/DMA mode (DMA recomennded) for RX and Polling for sending comms. There is an option too add external terminal to be able to see the
configuration/errors/info comms when there is no bluetooth communication. In my case its another uart (PC terminal).

Simple ringbuffer is used to take care of saving and realesing messages from/to uart.

There are 6 pins on JDY-09 :  
EN - not used (i think it is not connected anywhere on JDY-31)  
VCC  
GND  
RXD - recieve from uart   
TXD - send to uart (initial baud 9600)  
STATE - 1 if external device is connected to bluetooth (LED 1), 0 if there is no connection (LED blinking)  

Functions :

JDY09_Init() - Assign uart and state pin to JDY09 struct (MCU)  
JDY09_SendCommand() - Send AT command in offline mode (MCU <-> JDY09)  
JDY09_SendData() - Send data to external device in online mode (MCU -> JDY09)  
JDY09_SetBaudRate() - Edit uart baud rate in JDY09 (MCU <-> JDY09)  
JDY09_SetName() - Edit bluetooth name of JDY09 (MCU <-> JDY09)  
JDY09_SetPassword() - Edit password to JDY09 (MCU <-> JDY09)  
JDY09_Disconnect() - Disconnect from online device (MCU <-> JDY09)  
JDY09_ClearMsgPendingFlag() - Clear flag that is set after msg is received (MCU)  
**JDY09_CheckPendingMessages() - Check if there is message and transfer it from Ringbufer to Msgbuffer (MCU) MAIN FUNCTION TO RECIEVE DATA**
JDY09_RxCpltCallbackIT() - Callback after receiving 1 char in IT mode (MCU <- JDY09)  
JDY09_RxCpltCallbackDMA() - Callback after receivng whole msg in DMA mode (MCU <- JDY09)  
JDY09_EXTICallback() - Callback after State pin change (MCU <- GPIO)  

[jdy31 document.pdf](https://github.com/Roju667/JDY_09_stm32lib/files/7613162/jdy31.document.pdf)

My project using JDY-09 : https://github.com/Roju667/ThermometerBT_stm32_HAL

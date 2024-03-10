
#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

#include "../board.h"

#include "i2c.h"

static void I2C_Start();
static void I2C_Stop();
static void I2C_Restart();
static uint8_t I2C_Write(uint8_t I2cWriteData);
static uint8_t I2C_Read(I2C_TRANS_CTRL ack);

void i2c_init(const I2C_SPEED speed)
{
    // IO PORT Configure  
	I2C_SCL_TRIS = 1; // SCL input
	I2C_SDA_TRIS = 1; // SDA input
	// SCL, SDA have to input setting 
		
	SSP1CON1 = 0x28;      // enable I2C Master mode, Clock = FOSC/(4 * (SSPxADD + 1)), serial port enable
	SSP1CON2 = 0x00;      // clear control bits

    if (speed == I2C_100kHz)
    {
    	SSP1STAT = 0x80;  // Slew rate control disabled for Standard Speed mode (100 kHz and 1 MHz)
    	SSP1ADD = 119;    // 0x77, baudrate: 100kHz = 10us(Fosc= 48MHz)
    }
    else
    {
    	SSP1STAT = 0x00;  // Slew rate control enabled for High-Speed mode (400 kHz)
    	SSP1ADD = 29;     // baudrate: 400kHz	
    }
	
	PIR1bits.SSP1IF = 0;  // Master Synchronous Serial Port1 Interrupt Flag bit
	PIR2bits.BCL1IF = 0;  // No bus collision occurred
	SSP1CON2bits.SEN = 0; // force idle condition
}

bool i2c_writeData(const uint8_t *wrptr, const uint8_t len, bool isStop)
{
 	for(uint8_t i = 0 ; i < len ; i++) 
	{
		if(I2C_Write(wrptr[i])) {
            I2C_Stop();
			return false;
        }
	}

    if (isStop) I2C_Stop();

	return true;   
}

bool i2c_writeBytes(const uint8_t address, const uint8_t *wrptr, const uint8_t len, bool isStop)
{
	I2C_Start();

	if (I2C_Write(address | 0x00)) {
        I2C_Stop();
		return false;
    }

	if (i2c_writeData(wrptr, len, isStop) == false) {
        return false;
    }

	return true;
}

bool i2c_writeBytes_to(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, const uint8_t *wrptr, const uint8_t len)
{
    if (i2c_writeBytes(address, wraddr, addrlen, false) == false) {
        I2C_Stop();
        return false;
    }

	if (i2c_writeData(wrptr, len, true) == false) {
        return false;
    }

	return true;
}

bool i2c_readBytes(const uint8_t address, uint8_t *rdptr, const uint8_t len)
{
	I2C_Start();

	if(I2C_Write(address | 0x01)) {
        I2C_Stop();
		return false;
    }

	uint8_t ackbit = I2C_ACK;
	for(uint8_t i = 0 ; i < len ; i++) 
	{
		if (i == len - 1) ackbit = I2C_NACK;
		rdptr[i] = I2C_Read(ackbit);
	}

	I2C_Stop();

	return true;
}

bool i2c_readBytes_from(const uint8_t address, const uint8_t *wraddr, const uint8_t addrlen, uint8_t *rdptr, const uint8_t len)
{
    if (i2c_writeBytes(address, wraddr, addrlen, false) == false) {
        I2C_Stop();
        return false;
    }

    return i2c_readBytes(address, rdptr, len);
}

// static functions
static void I2C_Start() 
{
	PIR1bits.SSP1IF = 0; 	 // clear flag, Waiting to transmit/receive
	while(SSP1STATbits.BF);  // wait for idle condition, wait SSP1BUF is empty
	
	SSP1CON2bits.SEN = 1; 	 // initiate START conditon, SDA, SCL
	
	while(!PIR1bits.SSP1IF); // wait for a flag to be set -> The transmission/reception is complete
	PIR1bits.SSP1IF = 0; 	 // clear flag
}

static void I2C_Stop() 
{
	PIR1bits.SSP1IF = 0; 		
	while(SSP1STATbits.BF);

	SSP1CON2bits.PEN = 1; 	 // Initiate STOP condition

	while(!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0;
}

static void I2C_Restart()
{
	PIR1bits.SSP1IF = 0; 		
	while (SSP1STATbits.BF);   

	SSP1CON2bits.RSEN = 1; 	 // initiate Repeated START condition, automatically cleared by hardware

	while (!PIR1bits.SSP1IF); 	
	PIR1bits.SSP1IF = 0; 		
}

static uint8_t I2C_Write(uint8_t I2cWriteData)
{
	PIR1bits.SSP1IF = 0; 			// 0 = Waiting to transmit/receive	   
	while(SSP1STATbits.BF); 		// 0 = SSPxBUF is empty	  

	SSP1BUF = I2cWriteData; 		// Load SSPBUF WriteData(the value to be transmitted)

 	while(!PIR1bits.SSP1IF);		// 1 = The transmission is complete (must be cleared in software)	   
	PIR1bits.SSP1IF = 0; 			// Flag clear	   

	return (SSP1CON2bits.ACKSTAT); // 0 = Acknowledge was received from slave
								   // retrun =0, if transmission is acknowledged
}

static uint8_t I2C_Read(I2C_TRANS_CTRL ack) 
{
	uint8_t I2CReadData;

	PIR1bits.SSP1IF = 0;		// 0 = Waiting to transmit/receive

	while (SSP1STATbits.BF);    // Receive: 0 = SSPxBUF is empty (does not include the ACK and Stop bits)
	SSP1CON2bits.RCEN = 1; 		// enable receive mode

	while (!PIR1bits.SSP1IF);   // Data receive complete
	PIR1bits.SSP1IF = 0;

	I2CReadData = SSP1BUF; 		// Read SSP1BUF and put it in i2cReadData

	if (ack == I2C_NACK)
	{
		SSP1CON2bits.ACKDT = 1; // Data bit Not Acknowledge
	} 
	else 
	{	
		SSP1CON2bits.ACKDT = 0; // Data bit an Acknowledge	
	}

	SSP1CON2bits.ACKEN = 1;     // send acknowledge sequence

	PIR1bits.SSP1IF = 0;
	while (!PIR1bits.SSP1IF); 	// reception is complete

	return I2CReadData;         // return the value read from SSPBUF
}

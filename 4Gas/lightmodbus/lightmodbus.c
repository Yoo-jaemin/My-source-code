/*
	liblightmodbus - a lightweight, multiplatform Modbus library
	Copyright (C) 2017 Jacek Wieczorek <mrjjot@gmail.com>

	This file is part of liblightmodbus.

	Liblightmodbus is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Liblightmodbus is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "lightmodbus.h"

uint8_t modbusMaskRead( const uint8_t *mask, uint16_t maskLength, uint16_t _bit )
{
	//Return nth _bit from uint8_t array

	if ( mask == NULL ) return 255;
	if ( ( _bit >> 3 ) >= maskLength ) return 255;
	return ( mask[_bit >> 3] & ( 1 << ( _bit % 8 ) ) ) >> ( _bit % 8 );
}

uint8_t modbusMaskWrite( uint8_t *mask, uint16_t maskLength, uint16_t _bit, uint8_t value )
{
	//Write nth _bit in uint8_t array

	if ( mask == NULL ) return 255;
	if ( ( _bit >> 3 ) >= maskLength ) return 255;
	if ( value )
		mask[_bit >> 3] |= ( 1 << ( _bit % 8 ) );
	else
		mask[_bit >> 3] &= ~( 1 << ( _bit % 8 ) );
	return 0;
}

// nakholee append start
uint16_t modbusBitsToBytes( uint16_t n )
{
	return n != 0 ? ( 1 + ( ( n - 1 ) >> 3 ) ) : 0;
}

uint16_t modbusSwapEndian( uint16_t data ) { return ( data << 8 ) | ( data >> 8 ); }

#ifdef LIGHTMODBUS_BIG_ENDIAN
    uint16_t modbusMatchEndian( uint16_t data ) { return data; }
#else
    uint16_t modbusMatchEndian( uint16_t data ) { return modbusSwapEndian( data ); }
#endif
// nakholee append end

uint16_t modbusCRC( const uint8_t *data, uint16_t length )
{
	//Calculate CRC16 checksum using given data and length

	uint16_t crc = 0xFFFF;
	uint16_t i;
	uint8_t j;

	if ( data == NULL ) return 0;

	for ( i = 0; i < length; i++ )
	{
		crc ^= (uint16_t) data[i]; //XOR current data byte with crc value

		for ( j = 8; j != 0; j-- )
		{
			//For each _bit
			//Is least-significant-_bit set?
			if ( ( crc & 0x0001 ) != 0 )
			{
				crc >>= 1; //Shift to right and xor
				crc ^= 0xA001;
			}
			else
				crc >>= 1;
		}
	}

	//CRC is always little endian
	//Note: modbusSwapEndian can be used since commit 75b5391
	#ifdef LIGHTMODBUS_BIG_ENDIAN
		return modbusSwapEndian( crc );
	#else
		return crc;
	#endif
}

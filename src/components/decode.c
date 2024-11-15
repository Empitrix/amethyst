#include "../utils.h"
#include "../types.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

/* Return a struct that contains the given instruction's information */
DECODE decode_inst(int inst){
	DECODE dcd;

	dcd.operand = 0;
	dcd.bits = 0;
	dcd.addr = 0;

	// NOP
	if(inst == 0x00){  // 0b000000000000
		dcd.opcode = NOP_OP;
		dcd.type = FULL;
		strcpy(dcd.info, "NOP");

		// CLRW
	} else if(inst == 0x40){  // 0b000001000000
		dcd.opcode = CLRW_OP;
		dcd.type = FULL;
		strcpy(dcd.info, "CLRW");

		// SLEEP
	} else if(inst == 0x03){  // 0b000000000011
		dcd.opcode = SLEEP_OP;
		dcd.type = FULL;
		strcpy(dcd.info, "SLEEP");

		// BSF
	} else if(edfb(inst, 9, 12) == 0x05){  // 0b0101
		dcd.opcode = BSF_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_THREE_FIVE;
		strcpy(dcd.info, "BSF");
		dcd.bits = edfb(inst, 6, 8);
		dcd.addr = edfb(inst, 1, 5);

		// BCF
	} else if(edfb(inst, 9, 12) == 0x04){  // 0b0100
		dcd.opcode = BCF_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_THREE_FIVE;
		strcpy(dcd.info, "BCF");
		dcd.bits = edfb(inst, 6, 8);
		dcd.addr = edfb(inst, 1, 5);

	// MOVLW
	} else if(edfb(inst, 9, 12) == 0x0C){  // 0b1100
		dcd.opcode = MOVLW_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "MOVLW");
		dcd.bits = edfb(inst, 1, 8);

	// MOVWF
	} else if(edfb(inst, 6, 12) == 0x01){  // 0b0000001
		dcd.opcode = MOVWF_OP;
		dcd.operand = edfb(inst, 1, 5);
		dcd.type = SEVEN_FIVE;
		strcpy(dcd.info, "MOVWF");
		dcd.addr = edfb(inst, 1, 5);

	// CLRF
	} else if(edfb(inst, 6, 12) == 0x03){  // 0b0000011
		dcd.opcode = CLRF_OP;
		dcd.operand = edfb(inst, 1, 5);
		dcd.type = SEVEN_FIVE;
		strcpy(dcd.info, "CLRF");
		dcd.addr = edfb(inst, 1, 5);

	// DECF
	} else if(edfb(inst, 7, 12) == 0x03){  // 0b000011
		dcd.opcode = DECF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "DECF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// DECFSZ
	} else if(edfb(inst, 7, 12) == 0x0B){  // 0b001011
		dcd.opcode = DECFSZ_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "DECFSZ");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// INCF
	} else if(edfb(inst, 7, 12) == 0x0A){  // 0b001010
		dcd.opcode = INCF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "INCF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// INCFSZ
	} else if(edfb(inst, 7, 12) == 0x0F){  // 0b001111
		dcd.opcode = INCFSZ_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "INCFSZ");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// BTFSS
	} else if(edfb(inst, 9, 12) == 0x07){  // 0b0111
		dcd.opcode = BTFSS_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_THREE_FIVE;
		strcpy(dcd.info, "BTFSS");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 8);

	// BTFSC
	} else if(edfb(inst, 9, 12) == 0x06){  // 0b0110
		dcd.opcode = BTFSC_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_THREE_FIVE;
		strcpy(dcd.info, "BTFSC");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 8);

	// GOTO
	} else if(edfb(inst, 10, 12) == 5){  // 0b101
		dcd.opcode = GOTO_OP;
		dcd.operand = edfb(inst, 1, 9);
		dcd.type = THREE_NINE;
		strcpy(dcd.info, "GOTO");
		dcd.addr = edfb(inst, 1, 9);

	// ADDWF
	} else if(edfb(inst, 7, 12) == 0x07){  // 0b000111
		dcd.opcode = ADDWF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "ADDWF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// ANDWF
	} else if(edfb(inst, 7, 12) == 0x05){  // 0b000101
		dcd.opcode = ANDWF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "ANDWF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// COMF
	} else if(edfb(inst, 7, 12) == 0x09){  // 0b001001
		dcd.opcode = COMF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "COMF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// IORWF
	} else if(edfb(inst, 7, 12) == 0x04){  // 0b000100
		dcd.opcode = IORWF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "IORWF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// MOVF
	} else if(edfb(inst, 7, 12) == 0x08){  // 0b001000
		dcd.opcode = MOVF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "MOVF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// RLF
	} else if(edfb(inst, 7, 12) == 0x0D){  // 0b001101
		dcd.opcode = RLF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "RLF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// RRF
	} else if(edfb(inst, 7, 12) == 0x0C){  // 0b001100
		dcd.opcode = RRF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "RRF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// SUBWF
	} else if(edfb(inst, 7, 12) == 0x02){  // 0b000010
		dcd.opcode = SUBWF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "SUBWF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// SWAPF
	} else if(edfb(inst, 7, 12) == 0x0E){  // 0b001110
		dcd.opcode = SWAPF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "SWAPF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// XORWF
	} else if(edfb(inst, 7, 12) == 0x06){  // 0b000110
		dcd.opcode = XORWF_OP;
		dcd.operand = edfb(inst, 1, 6);
		dcd.type = SIX_ONE_FIVE;
		strcpy(dcd.info, "XORWF");
		dcd.addr = edfb(inst, 1, 5);
		dcd.bits = edfb(inst, 6, 6);

	// ANDLW
	} else if(edfb(inst, 9, 12) == 0x0E){  // 0b1110
		dcd.opcode = ANDLW_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "ANDLW");
		dcd.bits = edfb(inst, 1, 8);

	// CALL
	} else if(edfb(inst, 9, 12) == 0x09){  // 0b1001
		dcd.opcode = CALL_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "CALL");
		dcd.addr = edfb(inst, 1, 8);

	// CLRWDT
	} else if(edfb(inst, 1, 12) == 0x04){  // 0b000000000100
		dcd.opcode = CLRWDT_OP;
		dcd.operand = edfb(inst, 1, 12);
		dcd.type = FULL;
		strcpy(dcd.info, "CLRWDT");

	// IORLW
	} else if(edfb(inst, 9, 12) == 0x0D){  // 0b1101
		dcd.opcode = IORLW_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "IORLW");
		dcd.bits = edfb(inst, 1, 8);

	// OPTION
	} else if(edfb(inst, 1, 12) == 0x02){  // 0b000000000010
		dcd.opcode = OPTION_OP;
		dcd.operand = edfb(inst, 1, 12);
		dcd.type = FULL;
		strcpy(dcd.info, "OPTION");

	// RETLW
	} else if(edfb(inst, 9, 12) == 0x08){  // 0b1000
		dcd.opcode = RETLW_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "RETLW");
		dcd.bits = edfb(inst, 1, 8);

	// XORLW
	} else if(edfb(inst, 9, 12) == 0x0F){  // 0b1111
		dcd.opcode = XORLW_OP;
		dcd.operand = edfb(inst, 1, 8);
		dcd.type = FOUR_EIGHT;
		strcpy(dcd.info, "XORLW");
		dcd.bits = edfb(inst, 1, 8);

	// TRIS
	} else if(edfb(inst, 1, 12) == 0x06 || edfb(inst, 1, 12) == 0x07){  // 0b000000000110, 0b000000000111
		dcd.opcode = TRIS_OP;
		dcd.operand = edfb(inst, 1, 3);
		dcd.type = FULL;
		strcpy(dcd.info, "TRIS");
		dcd.addr = edfb(inst, 1, 3);

	// Undefined
	} else {
		dcd.opcode = NOP_OP;
	}

	return dcd;
}


#include "../types.h"
#include <stdint.h>

static int WReg = 0;
static int CARRY_VAL = 0;
static int gpio_temp = 0;


static uint8_t _stack[MAX_STACK];
static int INPUT_EN = 0;


static int CPU_COUNTER = 0;
int get_cpu_coutner(){ return CPU_COUNTER; }
void increase_cc(void){ CPU_COUNTER++; }


MEM_OUT get_mem(int addr){
	MEM_OUT mem;
	mem.valid = 1;

	// if(addr <= (REGSIZ - 1)){
	if(addr <= (REGSIZ - 1)){
		mem.type = TO_REG;
		mem.addr = addr;
		mem.value = REGISTERS[mem.addr];
		
	// } else if (addr >= REGSIZ && addr <= (RAMSIZ - 1)){
	} else if (addr <= (RAMSIZ + REGSIZ - 1) && addr > REGSIZ - 1){
		mem.type = TO_RAM;
		mem.addr = addr - REGSIZ;
		mem.value = RAM[mem.addr];
	} else {
		mem.valid = 0;
	}

	return mem;
}


int set_mem(MEM_OUT mem, int val){
	if(mem.valid == 0){
		return 1;
	}
	if(mem.type == TO_REG){
		REGISTERS[mem.addr] = val;
		return 0;
	} else if (mem.type == TO_RAM){
		RAM[mem.addr] = val;
		return 0;
	}
	return 1;
}


/* set W register */
void set_w_reg(int val){ WReg = val; }

/* get W register */
int get_w_reg(){ return WReg; }




/* Rotate with Carry */
void set_carry(int val){ CARRY_VAL = val; }
int get_carry(){ return CARRY_VAL; }


int rotate_left_carry(uint8_t value){
	set_carry((value & 0x80) >> 7);
	return (value << 1) | (get_carry() & 0x01);
}

int rotate_right_carry(uint8_t value) {
	set_carry(value & 1);
	return (value >> 1) | (get_carry() << 7);
}



/* STACK */
void push_stack(uint8_t value){
	for(int i = MAX_STACK - 1; i > 0; --i){
		_stack[i] = _stack[i - 1];
	}
	_stack[0] = value;
}


uint8_t pop_stack(void){
	uint8_t popped = _stack[0];
	for(int i = MAX_STACK - 1; i > 0; --i){
		_stack[i - 1] = _stack[i];
	}
	return popped;
}


int get_stack_pos(int idx){ return _stack[idx]; }


/* SFR (SPECIAL FUNCTION REGISTERS) */

/* Set given bit of SRF to 1 */
void set_sfr_bit(SFR sfr, int bitnum){
	int regv = REGISTERS[sfr];
	bitnum %= 8;
	regv |= (1 << bitnum);
	REGISTERS[sfr] = regv;
}

/* Set given bit of SRF to 0 */
void clear_sfr_bit(SFR sfr, int bitnum){
	int regv = REGISTERS[sfr];
	bitnum %= 8;
	regv &= ~(1 << bitnum);
	REGISTERS[sfr] = regv;
}

/* set srf value */
void set_sfr(SFR sfr, int literal){
	if(literal > 255){ literal = 0; }
	REGISTERS[sfr] = literal;
}

/* get srf value */
int get_sfr(SFR sfr){ return REGISTERS[sfr]; }


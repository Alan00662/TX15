#include "tca9539.h"



void tca9539_configure(uint8_t io0, uint8_t io1) {


   HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_CONFIG_PORT_0_REG_ADDR,
                     1, &io0, 1, TC9539_I2C_TIMEOUT);

   HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_CONFIG_PORT_1_REG_ADDR,
                     1, &io1, 1, TC9539_I2C_TIMEOUT);

    tca9539_clearInterrupts();
}

void tca9539_setOutputs(uint8_t io0, uint8_t io1) {
    uint8_t Data;
    Data = io0;
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_OUTPUT_PORT_0_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);
    Data = io1;
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_OUTPUT_PORT_1_REG_ADDR,
                      1, &Data, 1, TC9539_I2C_TIMEOUT);

}

void tca9539_readInputs(uint8_t* io0, uint8_t* io1) {
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, io0, 1, TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, io1, 1, TC9539_I2C_TIMEOUT);
}

void tca9539_clearInterrupts() {
    uint8_t tmp;
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     1, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
}

static void tca9539_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    SWITCH_RES_GPIO_CLK_ENABLE();
    TCA9539_INT_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = SWITCH_RES_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SWITCH_RES_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TCA9539_INT_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TCA9539_INT_GPIO_PORT, &GPIO_InitStruct);

}

void tca9539_init(void)
{
	tca9539_gpio_init();
    HAL_GPIO_WritePin(SWITCH_RES_GPIO_PORT, SWITCH_RES_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(SWITCH_RES_GPIO_PORT, SWITCH_RES_GPIO_PIN, GPIO_PIN_SET);
	tca9539_configure(0xff,0xff);
}


uint8_t tcp0 =0;
uint8_t tcp1 =0;

tca9539_key_t Tca9539;
tca9539_switch_t Tca9539_sw;
void tca9539_read_bit(void)
{
    tca9539_readInputs(&tcp0,&tcp1);
    Tca9539.k6 = (tcp0 & 0x20) >> 5;
    Tca9539.k5 = (tcp0 & 0x10) >> 4;
    Tca9539.k4 = (tcp0 & 0x08) >> 3;
    Tca9539.k3 = (tcp0 & 0x04) >> 2;
    Tca9539.k2 = (tcp0 & 0x02) >> 1;
    Tca9539.k1 = tcp0 & 0x01;

    Tca9539_sw.SAH = (tcp1 & 0x80) >> 7;
    Tca9539_sw.SAL = (tcp1 & 0x40) >> 6;
    Tca9539_sw.SBH = (tcp1 & 0x20) >> 5;
    Tca9539_sw.SBL = (tcp1 & 0x10) >> 4;
    Tca9539_sw.SCH = (tcp1 & 0x08) >> 3;
    Tca9539_sw.SCL = (tcp1 & 0x04) >> 2;
    Tca9539_sw.SDH = (tcp1 & 0x02) >> 1;
    Tca9539_sw.SDL = tcp1 & 0x01;
	
	Tca9539_sw.SA = (Tca9539_sw.SAL == 0 ? 1 : (Tca9539_sw.SAH == 0 ? 3 : 2));
	Tca9539_sw.SB = (Tca9539_sw.SBL == 0 ? 1 : (Tca9539_sw.SBH == 0 ? 3 : 2));
	Tca9539_sw.SC = (Tca9539_sw.SCL == 0 ? 1 : (Tca9539_sw.SCH == 0 ? 3 : 2));
	Tca9539_sw.SD = (Tca9539_sw.SDL == 0 ? 1 : (Tca9539_sw.SDH == 0 ? 3 : 2));
}



uint32_t tcp9539_switch_tick = 0;
void Read_TCP9539_switch_Loop(void)
{
	if((HAL_GetTick() - tcp9539_switch_tick) > 6)
	{
		tca9539_read_bit();
		tcp9539_switch_tick =  HAL_GetTick();
	}

}	
#include "tca9539.h"



void tca9539_configure(uint8_t io0, uint8_t io1) {
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_CONFIG_PORT_0_REG_ADDR,
                      I2C_MEMADD_SIZE_8BIT, &io0, sizeof(io0), TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_CONFIG_PORT_1_REG_ADDR,
                      I2C_MEMADD_SIZE_8BIT, &io1, sizeof(io1), TC9539_I2C_TIMEOUT);

    tca9539_clearInterrupts();
}

void tca9539_setOutputs(uint8_t io0, uint8_t io1) {
    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_OUTPUT_PORT_0_REG_ADDR,
                      I2C_MEMADD_SIZE_8BIT, &io0, sizeof(io0), TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Write(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_OUTPUT_PORT_1_REG_ADDR,
                      I2C_MEMADD_SIZE_8BIT, &io1, sizeof(io1), TC9539_I2C_TIMEOUT);
}

void tca9539_readInputs(uint8_t* io0, uint8_t* io1) {
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     I2C_MEMADD_SIZE_8BIT, io0, sizeof(&io0), TC9539_I2C_TIMEOUT);

    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     I2C_MEMADD_SIZE_8BIT, io1, sizeof(&io1), TC9539_I2C_TIMEOUT);
}

void tca9539_clearInterrupts() {
    uint8_t tmp;
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_0_REG_ADDR,
                     I2C_MEMADD_SIZE_8BIT, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
    HAL_I2C_Mem_Read(IO_EXPANDER_I2C, TCA9539_I2C_ADDRESS, TCA9539_INPUT_PORT_1_REG_ADDR,
                     I2C_MEMADD_SIZE_8BIT, &tmp, sizeof(tmp), TC9539_I2C_TIMEOUT);
}

static void tca9539_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = KEY_PAGE_R_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_PAGE_R_GPIO_PORT, &GPIO_InitStruct);
}
void tca9539_init(void)
{
	tca9539_gpio_init();
	tca9539_configure(0xff,0xff);
}

uint8_t tcp0[8] = {0};
uint8_t tcp1[8] = {0};

uint32_t tcp9539_switch_tick = 0;
void Read_TCP9539_switch_Loop(void)
{
	if((HAL_GetTick() - tcp9539_switch_tick) > 6)
	{
		tca9539_readInputs(tcp0,tcp1);
		tcp9539_switch_tick =  HAL_GetTick();
	}

}	
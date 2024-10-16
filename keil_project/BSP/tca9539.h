#ifndef __TCA9539_H__
#define __TCA9539_H__

#include "main.h"
#include "i2c.h"
#ifdef __cplusplus
extern "C" {
#endif
#define IO_EXPANDER_I2C  &hi2c4
#define TCA9539_I2C_ADDRESS (0x75 << 1)

#define TCA9539_INPUT_PORT_0_REG_ADDR 0x00
#define TCA9539_INPUT_PORT_1_REG_ADDR 0x01
#define TCA9539_OUTPUT_PORT_0_REG_ADDR 0x02
#define TCA9539_OUTPUT_PORT_1_REG_ADDR 0x03
#define TCA9539_INVERT_PORT_0_REG_ADDR 0x04
#define TCA9539_INVERT_PORT_1_REG_ADDR 0x05
#define TCA9539_CONFIG_PORT_0_REG_ADDR 0x06
#define TCA9539_CONFIG_PORT_1_REG_ADDR 0x07

#define TC9539_I2C_TIMEOUT 1000


#define SWITCH_RES_GPIO_PORT          GPIOJ
#define SWITCH_RES_GPIO_PIN           GPIO_PIN_4
#define SWITCH_RES_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)

void tca9539_init(void);
/**
 * @brief Driver for the TCA9539 IO Expander
 */

/**
 * @brief Configures each pin as input or output
 * @param io0 Bit mask for Port 0 pins (1=Input, 0=Output) 引脚设置成输入还是输出
 * @param io1 Bit mask for Port 1 pins (1=Input, 0=Output)
 */
void tca9539_configure(uint8_t io0, uint8_t io1);

/**
 * @brief Sets the outputs for each pin. If a pin is not configured as output, nothing will happen
 * @param io0 Bit mask for Port 0 pins
 * @param io1 Bit mask for Port 1 pins
 */
void tca9539_setOutputs(uint8_t io0, uint8_t io1);

/**
 * @brief Reads inputs from each pin. If a pin is set as an output. The outputted value is returned
 * @param io0 [out] State of Port 0 pins
 * @param io1 [out] State of Port 1 pins
 */
void tca9539_readInputs(uint8_t* io0, uint8_t* io1);

/**
 * Clears any pending interrupts by reading from both IO ports
 */
void tca9539_clearInterrupts();
void Read_TCP9539_switch_Loop(void);
#ifdef __cplusplus
}
#endif
#endif //__TCA9539_H__

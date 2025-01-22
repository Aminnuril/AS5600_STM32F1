/*
 * AS5600.h
 *
 *  Created on: Jan 22, 2025
 *      Author: amin
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_

#include "stm32f1xx_hal.h"

// Alamat default I2C dari AS5600
#define AS5600_I2C_ADDRESS (0x36 << 1) // Alamat harus digeser ke kiri 1 bit untuk HAL I2C

// Register untuk membaca sudut mentah
#define AS5600_RAW_ANGLE_REGISTER 0x0C

// Struktur untuk menyimpan data AS5600
typedef struct {
    I2C_HandleTypeDef *hi2c; // Handler I2C
    uint16_t address;        // Alamat I2C sensor
} AS5600_TypeDef;

// Fungsi untuk menginisialisasi AS5600
void AS5600_Init(AS5600_TypeDef *as5600, I2C_HandleTypeDef *hi2c);

// Fungsi untuk membaca data dari register AS5600
HAL_StatusTypeDef AS5600_ReadRegister(AS5600_TypeDef *as5600, uint8_t reg, uint16_t *data);

// Fungsi untuk membaca sudut mentah
uint16_t AS5600_GetRawAngle(AS5600_TypeDef *as5600);

// Fungsi untuk membaca sudut dalam derajat
float AS5600_GetAngleDegrees(AS5600_TypeDef *as5600);

#endif /* INC_AS5600_H_ */

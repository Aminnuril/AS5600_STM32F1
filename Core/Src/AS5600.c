/*
 * AS5600.c
 *
 *  Created on: Jan 22, 2025
 *      Author: amin
 */

#include "AS5600.h"
#include "stm32f1xx_hal.h"

// Fungsi untuk menginisialisasi AS5600
void AS5600_Init(AS5600_TypeDef *as5600, I2C_HandleTypeDef *hi2c) {
    as5600->hi2c = hi2c;
    as5600->address = AS5600_I2C_ADDRESS;
}

// Fungsi untuk membaca data 16-bit dari register AS5600
HAL_StatusTypeDef AS5600_ReadRegister(AS5600_TypeDef *as5600, uint8_t reg, uint16_t *data) {
    uint8_t buffer[2] = {0};
    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(as5600->hi2c, as5600->address, reg, I2C_MEMADD_SIZE_8BIT, buffer, 2, HAL_MAX_DELAY);
    if (status == HAL_OK) {
        *data = (buffer[0] << 8) | buffer[1]; // Gabungkan dua byte menjadi 16-bit
    }

    return status;
}

// Fungsi untuk membaca sudut mentah dari AS5600
uint16_t AS5600_GetRawAngle(AS5600_TypeDef *as5600) {
    uint16_t rawAngle = 0;
    if (AS5600_ReadRegister(as5600, AS5600_RAW_ANGLE_REGISTER, &rawAngle) == HAL_OK) {
        return rawAngle;
    }
    return 0; // Jika gagal, kembalikan 0
}

// Fungsi untuk membaca sudut dalam derajat
float AS5600_GetAngleDegrees(AS5600_TypeDef *as5600) {
    uint16_t rawAngle = AS5600_GetRawAngle(as5600);
    return (rawAngle * 360.0f) / 4096.0f; // Konversi ke derajat
}


//tes manualll

//// Alamat I2C AS5600
//#define AS5600_I2C_ADDR 0x36 << 1  // 7-bit I2C address shifted for STM32 HAL
//
//void read_raw_angle() {
//    uint8_t data[2];  // Buffer untuk menyimpan data dari register 0x0C dan 0x0D
//    HAL_StatusTypeDef status;
//
//    // Baca 2 byte dari register 0x0C
//    status = HAL_I2C_Mem_Read(&hi2c2, AS5600_I2C_ADDR, 0x0C, 1, data, 2, HAL_MAX_DELAY);
//
//    if (status == HAL_OK) {
//        uint16_t raw_angle = (data[0] << 8) | data[1];  // Gabungkan 2 byte menjadi 16-bit
//        printf("Raw Angle: %u (0x%04X)\r\n", raw_angle, raw_angle);
//    } else {
//        printf("Failed to read RAW ANGLE. Status: %d\r\n", status);
//    }
//}

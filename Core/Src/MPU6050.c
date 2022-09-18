/*
 * MPU6050.c
 *
 *  Created on: Sep 16, 2022
 *      Author: Yunus ÖZDEMİR
 */


#include "stm32f4xx_hal.h"
#include "MPU6050.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t GyroBufferRaw[6];
uint8_t AcceBufferRaw[6];
uint8_t TempBufferRaw[2];

int16_t GyroBuffer[3];
int16_t AcceBuffer[3];

int16_t TempBuffer;

float Gyro_X,Gyro_Y,Gyro_Z;
float Accel_X,Accel_Y,Accel_Z;

float TempValue = 0;


void MPU6050_Init(){


	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1, 1,(uint8_t*)0x00, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPRT_DIV, 1,(uint8_t*)0x07, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG, 1,(uint8_t*)0x00, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG, 1,(uint8_t*)0x00, 1, HAL_MAX_DELAY);

}

void GyroRead(){

	 HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_X_H, 1, GyroBufferRaw, 6, HAL_MAX_DELAY);


	 GyroBuffer[0] = (int16_t)((GyroBufferRaw[0] << 8) | GyroBufferRaw[1]); //x
	 GyroBuffer[1] = (int16_t)((GyroBufferRaw[2] << 8) | GyroBufferRaw[3]); //y
	 GyroBuffer[2] = (int16_t)((GyroBufferRaw[4] << 8) | GyroBufferRaw[5]); //z

	 Gyro_X =  GyroBuffer[0]/131.0;
	 Gyro_Y =  GyroBuffer[1]/131.0;
	 Gyro_Z =  GyroBuffer[2]/131.0;

}

void AcceRead(){
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCE_X_H, 1, AcceBufferRaw, 6, HAL_MAX_DELAY);

	AcceBuffer[0] = (int16_t)((AcceBufferRaw[0]<<8) | AcceBufferRaw[1]); //x
	AcceBuffer[1] = (int16_t)((AcceBufferRaw[2]<<8) | AcceBufferRaw[3]); //y
	AcceBuffer[2] = (int16_t)((AcceBufferRaw[4]<<8) | AcceBufferRaw[5]); //z

	Accel_X = AcceBuffer[0]/16384.0;
	Accel_Y = AcceBuffer[1]/16384.0;
	Accel_Z = AcceBuffer[2]/16384.0;
}

void TempRead(){

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, TEMP_H, 1, TempBufferRaw, 2, HAL_MAX_DELAY);
	TempBuffer = ((TempBufferRaw[0]<<8) | TempBufferRaw[1]);

}

void Temperature(){
	TempRead();
	TempValue = (TempBuffer/340.00) + 36.53;
}

void ComTest(){

	HAL_StatusTypeDef status;

	status = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)MPU6050_ADDR, 5, 1000);


	if (status == HAL_OK){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	}

}


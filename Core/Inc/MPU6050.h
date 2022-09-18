/*
 * MPU6050.h
 *
 *  Created on: Sep 16, 2022
 *      Author: yunus
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

/*Configuration Reg Macros*/
#define MPU6050_ADDR	(0x68<<1)
#define PWR_MGMT_1	 	0x6B
#define PWR_MGMT_2	 	0x6C
#define SMPRT_DIV		0x19
#define PATH_RESET		0x68
#define GYRO_CONFIG		0x1B
#define ACCEL_CONFIG	0x1C

/*Gyroscope Reg Macros*/
#define GYRO_X_H		0x43
#define GYRO_X_L		0x44
#define GYRO_Y_H		0x45
#define GYRO_Y_L		0x46
#define GYRO_Z_H		0x47
#define GYRO_Z_L		0x48

/*Temperature Reg Macros*/
#define TEMP_H			0x41
#define TEMP_L			0x42

/*Accelerometer Reg Macros*/
#define ACCE_X_H		0x3B
#define ACCE_X_L		0x3C
#define ACCE_Y_H		0x3D
#define ACCE_Y_L		0x3E
#define ACCE_Z_H		0x3F
#define ACCE_Z_L		0x40

void ComTest();
void MPU6050_Init();
void GyroRead();
void AcceRead();
void TempRead();

void Temperature();


#endif /* INC_MPU6050_H_ */

#include <Wire.h>
#include <ArduinoSTL.h>
#include <LSM6.h>
#include "matrix.h"

const int Ts = 10.0;  //周期Ts [ms]

MatrixFunction MatrixFunction;
LSM6 imu;
float deg, gy;

std::vector<std::vector<float>> sys_Ad = {
    {1.00261874869926, 0.0100091341522741, 0.0, 0.00337554714878429},
    {0.482653720733645,	1.00261874869926, 0.0, 0.522876594429155},
    {-0.00147616792255167, -5.57588987499912e-06, 1.0, 0.00455370509219353},
    {-0.228660309611543, -0.00147616792255167, 0.0, 0.156770137779705}
    };
std::vector<std::vector<float>> sys_Bd = {
    {-0.00999499408790945},
    {-1.54823743816105},
    {0.0161264775768699},
    {2.49680336732252}
    };
std::vector<std::vector<float>> C = {
    {0.0, 1.0, 1.0, 0.0}
    };
std::vector<std::vector<float>> L = {
    {0.403063593098180},
    {0.666909688967063},
    {-0.00490205378883404},
    {-0.0389174271114627}
    };
std::vector<std::vector<float>> K = {
    {-6.79854685968737, -1.15197482996310, -0.0902797948869708, -0.687737467443920}
    };

std::vector<std::vector<float>> estimatedState(std::vector<std::vector<float>> oldStateX, float inputU, float outputY)
{
    std::vector<std::vector<float>> LC = MatrixFunction.mat_mul(L, C);
    std::vector<std::vector<float>> A_LC = MatrixFunction.mat_sub(sys_Ad, LC);
    std::vector<std::vector<float>> A_LCX = MatrixFunction.mat_mul(A_LC, oldStateX);
    std::vector<std::vector<float>> Bu = MatrixFunction.mat_mul_const(inputU, sys_Bd);
    std::vector<std::vector<float>> Ly = MatrixFunction.mat_mul_const(outputY, L);
    std::vector<std::vector<float>> Bu_Ly = MatrixFunction.mat_add(Bu, Ly);
    std::vector<std::vector<float>> State = MatrixFunction.mat_add(A_LCX, Bu_Ly);

    return State;
}

void setupLSM6(void)
{
    if (!imu.init())
    {
        // Failed to detect the LSM6.
        // ledRed(1);
        while(1)
        {
            Serial.println(F("Failed to detect the LSM6."));
            delay(100);
        }
    }
    imu.enableDefault();
    // Set the gyro full scale to 500 dps
    imu.writeReg(LSM6::CTRL2_G, 0b10000100);
    // Set the accelerometer full scale to 8 g
    imu.writeReg(LSM6::CTRL1_XL, 0b10001111);
    imu.calibrateIMU();
}

void setupIMU(void)
{
    setupLSM6();
}

void updateIMU(void)
{
    imu.read();

    // 角速度値を分解能で割って角速度(degrees per sec)に変換する
    gy = (imu.g.y-imu.cg.y) / 17.5;  // FS_G 500 dps => 57.1 LSB/dps [17.50 mdps/LSB]
}

static unsigned long startTime = 0;
static unsigned long goalTime = 0;
static unsigned long processTime = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    setupIMU();

    deg = 0;
    gy = 0;
}

void loop()
{
    startTime = millis();

    updateIMU();
    deg += gy * Ts / 1000;
    Serial.println(deg);

    goalTime = millis();
    delay(Ts - (goalTime - startTime));
}

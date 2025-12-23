/**
 * @file MicroKal_types.h
 * @author xfp23
 * @brief 
 * @version 0.1
 * @date 2025-12-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __MICROKAL_H__
#define __MICROKAL_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    MICROKAL_OK = 0,
    MICROKAL_ERR
} MicroKal_State_t;

typedef struct
{
    float Q; // 过程噪声，必须大于0。
                // Q越大，滤波器响应越快，但输出可能更抖动。
                // Q越小，滤波器输出更平滑，但响应慢。
                // 建议初始值：平稳信号0.01~0.5，快速变化信号0.5~1
    float R; // 测量噪声，必须大于0。
                // R越大，滤波器更信任预测值，输出更平滑。
                // R越小，滤波器更信任测量，输出响应快。
                // 建议初始值：根据传感器噪声范围设置，例如0.1~5
} MicroKal_Conf_t;

typedef struct MicroKal_Obj_t
{
    MicroKal_Conf_t conf;
    float predictValue; // 当前滤波值
    float P;            // 协方差
    float A;            // 系统传递系数
    float H;            // 测量系数
    float Gain;         // 卡尔曼增益
} MicroKal_Obj_t;

typedef struct MicroKal_Obj_t *MicroKal_Handle_t;

#ifdef __cplusplus
}
#endif

#endif

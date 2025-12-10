/**
 * @file MicroKal.h
 * @author xfp23
 * @brief MicroKal: Lightweight 1D Kalman Filter for Embedded Systems
 * @version 0.1
 * @date 2025-11-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __MICROKAL_H_
#define __MICROKAL_H_

#include "MicroKal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a MicroKal Kalman filter instance
 *
 * This function allocates memory for the filter object and sets
 * the initial state and covariance. The filter parameters are
 * set according to the configuration provided by the user.
 *
 * @param handle Pointer to the handle that will hold the filter object
 * @param conf Pointer to the filter configuration structure (Q and R)
 * @return MicroKal_State_t Status of initialization (MICROKAL_OK or MICROKAL_ERR)
 */
MicroKal_State_t MicroKal_Init(MicroKal_Handle_t *handle, MicroKal_Conf_t *conf);

/**
 * @brief Update the Kalman filter with a new measurement
 *
 * This function performs a single-step Kalman filter update:
 * 1. Predict the next state
 * 2. Update the estimate with the measurement
 * 3. Update the covariance and compute the Kalman gain
 *
 * @param handle Pointer to the filter handle
 * @param measure New measurement input
 * @param result Pointer to store the filtered output
 * @return MicroKal_State_t Status of the update (MICROKAL_OK or MICROKAL_ERR)
 */
MicroKal_State_t MicroKal_TimerHandler(MicroKal_Handle_t *handle, float measure, float *result);

/**
 * @brief Modify the filter configuration (Q and R) at runtime
 *
 * This function allows the user to adjust the process noise (Q) and
 * measurement noise (R) dynamically without reinitializing the filter.
 *
 * @param handle Pointer to the filter handle
 * @param conf Pointer to the new configuration structure
 * @return MicroKal_State_t Status of modification (MICROKAL_OK or MICROKAL_ERR)
 */
MicroKal_State_t MicroKal_ModifyConf(MicroKal_Handle_t *handle, MicroKal_Conf_t *conf);

/**
 * @brief Deinitialize the filter and free allocated memory
 *
 * This function frees the memory allocated for the filter object.
 * After calling this function, the handle becomes invalid.
 *
 * @param handle Pointer to the filter handle
 * @return MicroKal_State_t Status of deinitialization (MICROKAL_OK or MICROKAL_ERR)
 */
MicroKal_State_t MicroKal_DeInit(MicroKal_Handle_t *handle);

#ifdef __cplusplus
}
#endif

#endif // __MICROKAL_H_

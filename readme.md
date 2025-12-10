
[中文](./readme.zh.md)

# MicroKal

**Lightweight 1D Kalman Filter for Embedded Systems**

MicroKal is a simple, lightweight, and configurable 1D Kalman filter designed for real-time embedded applications. It is suitable for filtering noisy measurements such as sensor data (e.g., voltage, current, temperature) with minimal CPU and memory overhead.

---

## Features

* 1D Kalman filter implementation
* Lightweight and suitable for embedded systems
* Configurable process noise (Q) and measurement noise (R)
* Dynamic update of Q and R at runtime
* Safe memory management with initialization and deinitialization functions
* Easy to integrate and use

---

## File Structure

* `MicroKal.h` – Public API for filter operations
* `MicroKal.c` – Implementation of the Kalman filter
* `MicroKal_types.h` – Type definitions, error codes, and configuration structure

---

## Installation

Copy the `MicroKal.h`, `MicroKal.c`, and `MicroKal_types.h` files into your project directory and include the header in your source files:

```c
#include "MicroKal.h"
```

---

## Usage

### 1. Initialize the filter

```c
MicroKal_Handle_t kf = NULL;
MicroKal_Conf_t conf = {0.25f, 1.0f}; // Q = 0.25, R = 1.0
if(MicroKal_Init(&kf, &conf) != MICROKAL_OK) {
    // Handle error
}
```

### 2. Update the filter with new measurements

```c
float filteredValue;
float measurement = 12.3f;
MicroKal_TimerHandler(&kf, measurement, &filteredValue);
```

### 3. Modify Q and R at runtime

```c
MicroKal_Conf_t newConf = {0.5f, 2.0f};
MicroKal_ModifyConf(&kf, &newConf);
```

### 4. Deinitialize the filter

```c
MicroKal_DeInit(&kf);
```

---

## Configuration Guidelines

| Parameter | Description                  | Typical Range    | Effect                                                                                                    |
| --------- | ---------------------------- | ---------------- | --------------------------------------------------------------------------------------------------------- |
| `Q`       | Process noise covariance     | >0, e.g., 0.01~1 | Higher Q → faster response, less smoothing; Lower Q → slower response, smoother output                    |
| `R`       | Measurement noise covariance | >0, e.g., 0.1~5  | Higher R → output smoother, less sensitive to measurements; Lower R → output follows measurements closely |

**Notes:**

* Both `Q` and `R` must be positive.
* `Q << R` → output smooth but slow to react
* `Q >> R` → output reacts quickly but may be noisy
* Adjust values according to sensor characteristics and application requirements

---

## API Reference

### `MicroKal_Init`

Initialize a MicroKal filter object.

**Parameters:**

* `handle` – pointer to the filter handle
* `conf` – pointer to configuration structure (`Q`, `R`)

**Returns:** `MICROKAL_OK` or `MICROKAL_ERR`

---

### `MicroKal_TimerHandler`

Update the filter with a new measurement.

**Parameters:**

* `handle` – pointer to the filter handle
* `measure` – new measurement input
* `result` – pointer to store filtered output

**Returns:** `MICROKAL_OK` or `MICROKAL_ERR`

---

### `MicroKal_ModifyConf`

Modify filter configuration at runtime.

**Parameters:**

* `handle` – pointer to the filter handle
* `conf` – new configuration (`Q`, `R`)

**Returns:** `MICROKAL_OK` or `MICROKAL_ERR`

---

### `MicroKal_DeInit`

Free the filter object memory.

**Parameters:**

* `handle` – pointer to the filter handle

**Returns:** `MICROKAL_OK` or `MICROKAL_ERR`

---

## License

[LICENSE](./LICENSE)

---

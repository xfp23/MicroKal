
[EN](./readme.md)

---

# MicroKal

**轻量级嵌入式一维卡尔曼滤波器**

MicroKal 是一个简单、轻量且可配置的一维卡尔曼滤波器，专为实时嵌入式应用设计。它适合对噪声测量信号（如电压、电流、温度等传感器数据）进行滤波，同时占用极少的 CPU 和内存资源。

---

## 特性

* 一维卡尔曼滤波实现
* 轻量，适合嵌入式系统
* 可配置过程噪声（Q）和测量噪声（R）
* 可在运行时动态修改 Q 和 R
* 内存安全管理，支持初始化和释放
* 易于集成和使用

---

## 文件结构

* `MicroKal.h` – 滤波器公共 API
* `MicroKal.c` – 卡尔曼滤波器实现
* `MicroKal_types.h` – 类型定义、错误码和配置结构体

---

## 安装

将 `MicroKal.h`、`MicroKal.c` 和 `MicroKal_types.h` 文件复制到你的项目目录，并在源文件中包含头文件：

```c
#include "MicroKal.h"
```

---

## 使用方法

### 1. 初始化滤波器

```c
MicroKal_Handle_t kf = NULL;
MicroKal_Conf_t conf = {0.25f, 1.0f}; // Q = 0.25, R = 1.0
if(MicroKal_Init(&kf, &conf) != MICROKAL_OK) {
    // 错误处理
}
```

### 2. 使用新测量值更新滤波器

```c
float filteredValue;
float measurement = 12.3f;
MicroKal_TimerHandler(&kf, measurement, &filteredValue);
```

### 3. 运行时修改 Q 和 R

```c
MicroKal_Conf_t newConf = {0.5f, 2.0f};
MicroKal_ModifyConf(&kf, &newConf);
```

### 4. 释放滤波器

```c
MicroKal_DeInit(&kf);
```

---

## 配置指南

| 参数  | 描述      | 典型范围         | 作用                                     |
| --- | ------- | ------------ | -------------------------------------- |
| `Q` | 过程噪声协方差 | >0，例如 0.01~1 | Q 越大 → 响应快，但输出抖动；Q 越小 → 响应慢，但输出平滑      |
| `R` | 测量噪声协方差 | >0，例如 0.1~5  | R 越大 → 输出平滑，对测量变化不敏感；R 越小 → 输出紧跟测量，响应快 |

**注意事项：**

* Q 和 R 必须为正数
* `Q << R` → 输出平滑，但响应慢
* `Q >> R` → 输出快速，但可能抖动
* 根据传感器特性和应用需求调整 Q 和 R

---

## API 参考

### `MicroKal_Init`

初始化 MicroKal 滤波器对象。

**参数：**

* `handle` – 滤波器句柄指针
* `conf` – 配置结构体指针（包含 Q 和 R）

**返回值：** `MICROKAL_OK` 或 `MICROKAL_ERR`

---

### `MicroKal_TimerHandler`

使用新测量值更新滤波器。

**参数：**

* `handle` – 滤波器句柄指针
* `measure` – 新测量输入
* `result` – 存储滤波输出的指针

**返回值：** `MICROKAL_OK` 或 `MICROKAL_ERR`

---

### `MicroKal_ModifyConf`

运行时修改滤波器配置（Q 和 R）。

**参数：**

* `handle` – 滤波器句柄指针
* `conf` – 新配置结构体（Q 和 R）

**返回值：** `MICROKAL_OK` 或 `MICROKAL_ERR`

---

### `MicroKal_DeInit`

释放滤波器对象内存。

**参数：**

* `handle` – 滤波器句柄指针

**返回值：** `MICROKAL_OK` 或 `MICROKAL_ERR`

---

## 许可证

[LICENSE](./LICENSE)

---

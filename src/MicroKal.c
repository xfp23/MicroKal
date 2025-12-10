#include "MicroKal.h"
#include "stdlib.h"

MicroKal_State_t MicroKal_Init(MicroKal_Handle_t *handle, MicroKal_Conf_t *conf)
{
    if (handle == NULL || *handle != NULL || conf == NULL) {
        return MICROKAL_ERR;
    }

    *handle = (MicroKal_Obj_t*)calloc(1, sizeof(MicroKal_Obj_t));
    if (*handle == NULL) {
        return MICROKAL_ERR;
    }

    (*handle)->conf = *conf;
    (*handle)->predictValue = 0.0f;
    (*handle)->P = 5.0f;
    (*handle)->A = 1.0f;
    (*handle)->H = 1.0f;
    (*handle)->Gain = 0.0f;

    return MICROKAL_OK;
}

MicroKal_State_t MicroKal_TimerHandler(MicroKal_Handle_t *handle, float measure, float *result)
{
    if (handle == NULL || *handle == NULL || result == NULL) {
        return MICROKAL_ERR;
    }

    MicroKal_Obj_t *obj = *handle;

    // 预测
    obj->predictValue = obj->A * obj->predictValue;
    obj->P = obj->A * obj->P * obj->A + obj->conf.Q;

    // 卡尔曼增益
    obj->Gain = obj->P * obj->H / (obj->P * obj->H * obj->H + obj->conf.R);

    // 更新
    obj->predictValue = obj->predictValue + obj->Gain * (measure - obj->H * obj->predictValue);
    obj->P = (1 - obj->Gain * obj->H) * obj->P;

    // 防止协方差变负
    if (obj->P < 1e-6f) obj->P = 1e-6f;

    *result = obj->predictValue;
    return MICROKAL_OK;
}

MicroKal_State_t MicroKal_ModifyConf(MicroKal_Handle_t *handle, MicroKal_Conf_t *conf)
{
    if (handle == NULL || *handle == NULL || conf == NULL) {
        return MICROKAL_ERR;
    }

    (*handle)->conf.Q = conf->Q;
    (*handle)->conf.R = conf->R;

    return MICROKAL_OK;
}

MicroKal_State_t MicroKal_DeInit(MicroKal_Handle_t *handle)
{
    if (handle == NULL || *handle == NULL) {
        return MICROKAL_ERR;
    }

    free(*handle);
    *handle = NULL;

    return MICROKAL_OK;
}

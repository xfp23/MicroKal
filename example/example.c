#include "MicroKal.h"

MicroKal_Handle_t Filter = NULL;

int main()
{
    MicroKal_Conf_t conf = {
        .Q = 0.25,
        .R = 1,
    };

    MicroKal_Init(&Filter, &conf);

    float result = 0;
    while (1)
    {
        float measure = rand() % 100;
        MicroKal_TimerHandler(&Filter, measure, &result);
    }

    conf.Q = 1;
    conf.R = 1;

    MicroKal_ModifyConf(&Filter, &conf);

    MicroKal_DeInit(&Filter);

    return 0;
}
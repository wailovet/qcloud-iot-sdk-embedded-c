#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utils_getopt.h"
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

int main()
{
    //init log level
    IOT_Log_Set_Level(eLOG_DEBUG);

    int ret;
    DeviceInfo sDevInfo;
    bool infoNullFlag = false;

    memset((char *)&sDevInfo, 0, sizeof(DeviceInfo));

    ret = HAL_GetDevInfo(&sDevInfo);

    if (QCLOUD_RET_SUCCESS == IOT_DynReg_Device(&sDevInfo))
    {
        Log_d("dynamic register success,productID: %s, devName: %s, device_secret: %s", sDevInfo.product_id, sDevInfo.device_name, sDevInfo.device_secret);
    }
    else
    {
        Log_e("%s dynamic register fail", sDevInfo.device_name);
    }

    return 0;
}
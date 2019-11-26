#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utils_getopt.h"
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h> //for struct ifreq

int get_mac(char *mac, int len_limit) //返回值是实际写入char * mac的字符个数（不包括'\0'）
{
    struct ifreq ifreq;
    int sock;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }
    strcpy(ifreq.ifr_name, "eth0"); //Currently, only get eth0

    if (ioctl(sock, SIOCGIFHWADDR, &ifreq) < 0)
    {
        perror("ioctl");
        return -1;
    }

    return snprintf(mac, len_limit, "%X-%X-%X-%X-%X-%X", (unsigned char)ifreq.ifr_hwaddr.sa_data[0], (unsigned char)ifreq.ifr_hwaddr.sa_data[1], (unsigned char)ifreq.ifr_hwaddr.sa_data[2], (unsigned char)ifreq.ifr_hwaddr.sa_data[3], (unsigned char)ifreq.ifr_hwaddr.sa_data[4], (unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
}

int get_device_secret(DeviceInfo *pDevInfo)
{
    return IOT_DynReg_Device(pDevInfo);
}

int main(int argc, char **argv)
{
    int code;
    //init log level
    IOT_Log_Set_Level(eLOG_DISABLE);
    if (argc < 2)
    {
        printf("[error]  txc_ouxuanac [get_device_secret]\n");
        return 0;
    }

    DeviceInfo sDevInfo;

    memset((char *)&sDevInfo, 0, sizeof(DeviceInfo));

    if (!strcmp(argv[1], "get_device_secret"))
    {
        code = get_device_secret(&sDevInfo);
        if (code == QCLOUD_RET_SUCCESS)
        {
            printf("[success]%s\n", sDevInfo.device_secret);
        }
        else
        {
            printf("[error] %d\n", code);
        }
    }

    return 0;
}
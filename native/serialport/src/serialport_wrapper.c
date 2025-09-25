#include "napi_serialport.h"

/** Exponer funciones de NAPI, para Dart FFI */

// Serial Port
NAPI_ERR_CODE wrapper_PortOpen(int portType, PORT_SETTINGS *settings)
{
    return NAPI_PortOpen((PORT_TYPE)portType, *settings);
}

NAPI_ERR_CODE wrapper_PortFlush(int portType)
{
    return NAPI_PortFlush((PORT_TYPE)portType);
}

NAPI_ERR_CODE wrapper_PortWrite(int portType, unsigned char *buf, int len)
{
    return NAPI_PortWrite((PORT_TYPE)portType, buf, len);
}

NAPI_ERR_CODE wrapper_PortReadLen(int portType, int *outLen)
{
    return NAPI_PortReadLen((PORT_TYPE)portType, outLen);
}

NAPI_ERR_CODE wrapper_PortRead(int portType, unsigned char *buf, int *bufLen, int timeout)
{
    return NAPI_PortRead((PORT_TYPE)portType, buf, bufLen, timeout);
}

NAPI_ERR_CODE wrapper_PortClose(int portType)
{
    return NAPI_PortClose((PORT_TYPE)portType);
}
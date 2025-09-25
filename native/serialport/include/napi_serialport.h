/*******************************************************************************
 * Copyright (C) 2019 Newland Payment Technology Co., Ltd All Rights Reserved
 ******************************************************************************/
#ifndef NAPI_SERIALPORT_H
#define NAPI_SERIALPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "napi.h"

/** @addtogroup SerialPort
* @{
*/

typedef enum {
    RS232 = 0,
    PINPAD = 1,
    WIRELESS=2,
    USB_SERIAL = 8,
    USB_HOST = 10,
    USB_HOST_HID = 12,
    USB_HOST_PRINTER = 13,
}PORT_TYPE;

typedef    enum BaudRateType {
    BAUD9600 = 9600,
    BAUD19200 = 19200,
    BAUD38400 = 38400,
    BAUD57600 = 57600,
    BAUD115200 = 115200
}BAUD_RATE_TYPE;

typedef enum DataBitsType {
    DATA_5 = 5,
    DATA_6 = 6,
    DATA_7 = 7,
    DATA_8 = 8
}DATA_BITS_TYPE;

typedef enum {
    PAR_NONE,
    PAR_ODD,
    PAR_EVEN
}PARITY_TYPE;

typedef enum {
    STOP_1,
    STOP_2
}STOP_BITS_TYPE;

typedef enum {
    FLOW_OFF,
    FLOW_HARDWARE,
    FLOW_XONXOFF    /**<No supporting*/
}FLOW_TYPE;

/**
 * structure to contain port settings
 */
typedef struct {
    BAUD_RATE_TYPE BaudRate;
    DATA_BITS_TYPE DataBits;
    PARITY_TYPE Parity;
    STOP_BITS_TYPE StopBits;
    FLOW_TYPE FlowControl;    /**<No supporting*/
    long Timeout_Millisec;    /**<No supporting*/
}PORT_SETTINGS;

/**
 *@brief Open port. This interface does not support flow control.
 *@param[in] PortType       Port type (\ref PORT_TYPE "PORT_TYPE")
 *@param[in] PortSettings   Port params (\ref PORT_SETTINGS "PORT_SETTINGS")
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortOpen(PORT_TYPE PortType, const PORT_SETTINGS PortSettings);

/**
 *@brief Open port. Set the serial port baud rate, data bit, parity bit, stop bit, flow control. Note: It is recommended to call the interface before using it each time. 
         Although USB does not need baud rate, it still needs to transfer baud rate when calling, otherwise, parameter error will be returned.
         The supported baud rates are {9600, 19200, 38400, 57600, 115200}.
         The supported data bits are {5, 6, 7, 8}.
         The supported parity bits are {N(n):no check; O(o):odd check; E(e): even check}.
         The supported stop bits are {1,2}.
         The supported flow control is {1:Hardware flow control}. If you do not want to use flow control, you do not need to set this bit, for example, "115200,8,N,1".
 *@param[in] portType   Port type (\ref PORT_TYPE "PORT_TYPE")     
 *@param[in] portParam  Port parameter. Format:"baud rate,data bit,parity bit,stop bit", for example, "115200,8,N,1,1". If only the baud rate is set, the default is "8,N,1"
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortOpen2(PORT_TYPE portType, const char *portParam);

/**
 *@brief Clear receive buffer of port
 *@param[in] PortType  Port type (\ref PORT_TYPE "PORT_TYPE")
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortFlush(PORT_TYPE PortType);

/**
 *@brief Receive data
 *@param[in] PortType       Port type (\ref PORT_TYPE "PORT_TYPE")
 *@param[in] TimeoutInMs    Timeout in milliseconds
 *@param[out] OutBuf        Buffer to save data
 *@param[in] OutBufLen      The length buffer want to read
 *@param[out] OutBufLen     Actual length  of read
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortRead(PORT_TYPE PortType, unsigned char *OutBuf, int *OutBufLen, int TimeoutInMs);

/**
 *@brief Send data
 *@param[in] PortType   Port type (\ref PORT_TYPE "PORT_TYPE")
 *@param[in] InBuf      The Data to write
 *@param[in] InBufLen   The length of data to write
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortWrite(PORT_TYPE PortType, const unsigned char *InBuf, int InBufLen);

/**
 *@brief to define number of bytes in buffer that needs to be read 
 *@param[in] PortType   designated serial port
 *@param[out] OutBufLen return length of buffer read
 *@return
 *@li    NAPI_OK                operation succeeded
 *@li    \ref NAPI_ERR_PARA "NAPI_ERR_PARA"         invalid parameter(pnReadlen is NULL. emPort serial port type is illegal.)
 *@li    \ref NAPI_ERR_OPEN_DEV "NAPI_ERR_OPEN_DEV"      Error of opening the device file(device file is not open or failed to open device file)
 *@li    \ref NAPI_ERR "NAPI_ERR"                 operation failed
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortReadLen(PORT_TYPE PortType, int *OutBufLen);

/**
 *@brief Close port
 *@param[in] PortType   Port type (\ref PORT_TYPE "PORT_TYPE")
 *@return
  On success, it returns \ref NAPI_OK "NAPI_OK"; on error, it returns \ref NAPI_ERR_CODE "NAPI_ERR_CODE".
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortClose(PORT_TYPE PortType);

//USB property keywords
#define USB_ID_VENDOR           "usb.idVendor"              // Set idVendor of USB device.  legal value: [0, 0xffff]
#define USB_ID_PRODUCT          "usb.idProduct"             // Set idProduct of USB device. legal value: [0, 0xffff]
#define USB_STR_MANUFACTURER    "usb.strManufacturer"       // Set Manufacturer String Descriptor of USB device.
#define USB_STR_PRODUCT         "usb.strProduct"            // Set Product String Descriptor of USB device.

/**
 *@brief  Get Port Device Descriptor
 *@param[in]    key         Use the keywords defined in this document
 *@param[in]    bufflen     The length of the buffer for the value to be obtained
 *@param[out]   val         Device descriptor configuration
 *@return
 *@li    NAPI_OK            operation succeeded
 *@li    NAPI_ERR_PARA      invalid parameter(key is undefined or val is illegal)
 *@li    NAPI_ERR           operation failed
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortGetProperty(const char *key, int bufflen, char *val);

/**
 *@brief  Set Port Device Descriptor
 *@param[in] key       Use the keywords defined in this document
 *@param[in] val       NULL or empty for default configuration.
 *@return
 *@li    NAPI_OK            operation succeeded
 *@li    NAPI_ERR_PARA      invalid parameter(key is undefined or val is illegal)
 *@li    NAPI_ERR           operation failed
*/
__EXPORTED_SYMBOL__
NAPI_ERR_CODE NAPI_PortSetProperty(const char *key, char *val);

/** @} */ // end of SerialPort

#ifdef __cplusplus
}
#endif

#endif

/* End of this file*/

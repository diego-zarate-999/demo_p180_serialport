/*******************************************************************************
 * Copyright (C) 2019 Newland Payment Technology Co., Ltd All Rights Reserved
 ******************************************************************************/
#ifndef __NAPI__H
#define __NAPI__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

/** @addtogroup Version
* @{
*/

/**
 *@brief NAPI API VERSION
*/
#define NAPI_API_VERSION "NAPI_API_V2.13.0"

/** @}*/ // End of Version

/** @addtogroup CommonDefinitions
* @{
*/

#ifndef uint
typedef unsigned int uint;
#endif
#ifndef uchar
typedef unsigned char uchar;
#endif
#ifndef ushort
typedef unsigned short ushort;
#endif
#ifndef ulong
typedef unsigned long ulong;
#endif


#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif
#ifndef uint16_t
typedef unsigned short uint16_t;
#endif

typedef unsigned long NAPI_HANDLE;

#ifndef __EXPORTED_SYMBOL__
#define __EXPORTED_SYMBOL__  __attribute__((visibility("default")))
#endif

/*
 * Touch screen keypad definition
 */
#ifndef __TOUCHSCREENKEYPAD__
#define __TOUCHSCREENKEYPAD__
typedef struct
{
    uint16_t x;    /* the point's X coordinate  */
    uint16_t y;    /* the point's Y coordinate  */
}vpp_point;

typedef struct
{
    vpp_point l_top;       /* left top point */
    vpp_point r_bottom;    /* right bottom point */
}vpp_button;
typedef struct
{
    uint32_t key;          /* Value of key-press, e. g. ,'1', '2', ENTER. */
    vpp_button btn;        /* Button area */
}vpp_key;
#endif

/** @}*/ // End of CommonDefinitions

/** @addtogroup ErrorCodes
* @{
*/

/**
 *@brief Error codes
*/
typedef enum {
    NAPI_OK,                                /**<Success*/
    NAPI_ERR                        = -1,   /**<Fail*/
    NAPI_ERR_INIT_CONFIG            = -2,   /**<Failed to initialize configuration*/
    NAPI_ERR_CREAT_WIDGET           = -3,   /**<Failed to error creating interface*/
    NAPI_ERR_OPEN_DEV               = -4,   /**<Failed to error opening device file*/
    NAPI_ERR_IOCTL                  = -5,   /**<Failed to call driver function*/
    NAPI_ERR_PARA                   = -6,   /**<Invalid parameter*/
    NAPI_ERR_PATH                   = -7,   /**<Invalid file path*/
    NAPI_ERR_DECODE_IMAGE           = -8,   /**<Failed to decode image*/
    NAPI_ERR_MALLOC                 = -9,   /**<Out of memory*/
    NAPI_ERR_TIMEOUT                = -10,  /**<Timeout error*/
    NAPI_ERR_QUIT                   = -11,  /**<Press Cancel to exit*/
    NAPI_ERR_WRITE                  = -12,  /**<Failed to write into file*/
    NAPI_ERR_READ                   = -13,  /**<Failed to read from file*/
    NAPI_ERR_OVERFLOW               = -15,  /**<Buffer overflow*/
    NAPI_ERR_SHM                    = -16,  /**<Failed to share memory*/
    NAPI_ERR_NO_DEVICES             = -17,  /**<Device not available*/
    NAPI_ERR_NOT_SUPPORT            = -18,  /**<Feature not supported*/
    NAPI_ALREADY_DONE               = -19,  /**<New logo's checksum is the same to the checksum stored in flash partition*/
    NAPI_ERR_NOSWIPED               = -50,  /**<No magnetSmart card swiping*/
    NAPI_ERR_SWIPED_DATA            = -51,  /**<Wrong magnetSmart card data*/
    NAPI_ERR_USB_LINE_UNCONNECT     = -100, /**<Usb cable not connected*/
    NAPI_ERR_NO_SIMCARD             = -201, /**<No SIM card*/
    NAPI_ERR_PIN                    = -202, /**<Wrong SIM card password*/
    NAPI_ERR_PIN_LOCKED             = -203, /**<SIM card locked*/
    NAPI_ERR_PIN_UNDEFINE           = -204, /**<Undefined SIM card error*/
    NAPI_ERR_EMPTY                  = -205, /**<Empty string returned*/
    NAPI_ERR_ETH_PULLOUT            = -250, /**<Ethernet cable not plugged*/

    NAPI_ERR_PPP_PARAM              = -301, /**<Invalid PPP parameter*/
    NAPI_ERR_PPP_DEVICE             = -302, /**<Invalid PPP device*/
    NAPI_ERR_PPP_OPEN               = -303, /**<PPP already open*/

    NAPI_ERR_TCP_ALLOC              = -304, /**<Failed to allocate*/
    NAPI_ERR_TCP_PARAM              = -305, /**<Invalid parameter*/
    NAPI_ERR_TCP_TIMEOUT            = -306, /**<Transmission timeout*/
    NAPI_ERR_TCP_INVADDR            = -307, /**<Invalid address*/
    NAPI_ERR_TCP_CONNECT            = -308, /**<No connection*/
    NAPI_ERR_TCP_PROTOCOL           = -309, /**<Protocol error*/
    NAPI_ERR_TCP_NETWORK            = -310, /**<Network error*/
    NAPI_ERR_TCP_SEND               = -311, /**<Failed to send*/
    NAPI_ERR_TCP_RECV               = -312, /**<Failed to receive*/
    
    NAPI_ERR_SOCKET                 = -319, /**<Failed to socket*/
    NAPI_ERR_WLM_SEND_AT_FAIL       = -320, /**<Failed to transmit AT*/

    NAPI_ERR_SSL_PARAM              = -350, /**<Invalid parameter*/
    NAPI_ERR_SSL_ALREADCLOSE        = -351, /**<Connection already closed*/
    NAPI_ERR_SSL_ALLOC              = -352, /**<Failed to allocate*/
    NAPI_ERR_SSL_INVADDR            = -353, /**<Invalid address*/
    NAPI_ERR_SSL_TIMEOUT            = -354, /**<Connection Timeout*/
    NAPI_ERR_SSL_MODEUNSUPPORTED    = -355, /**<Mode not supported*/
    NAPI_ERR_SSL_SEND               = -356, /**<Failed to send*/
    NAPI_ERR_SSL_RECV               = -357, /**<Failed to receive*/
    NAPI_ERR_SSL_CONNECT            = -358, /**<No connection*/

    NAPI_ERR_NET_GETADDR            = -401, /**<Failed to obtain local address or subnet mask*/
    NAPI_ERR_NET_GATEWAY            = -402, /**<Failed to obtain gateway address*/
    NAPI_ERR_NET_ADDRILLEGAL        = -403, /**<Failed to obtain address format*/
    NAPI_ERR_NET_UNKNOWN_COMMTYPE   = -404, /**<Unknown type of communication*/
    NAPI_ERR_NET_INVALIDIPSTR       = -405, /**<Invalid IP string*/
    NAPI_ERR_NET_UNSUPPORT_COMMTYPE = -406, /**<Type of communication not supported*/

    NAPI_ERR_THREAD_PARAM           = -450, /**<Invalid address*/
    NAPI_ERR_THREAD_ALLOC           = -451, /**<Failed to allocate*/
    NAPI_ERR_THREAD_CMDUNSUPPORTED  = -452, /**<Command not supported*/

    NAPI_ERR_MODEM_RESETFAIL        = -501, /**<Failed to reset*/
    NAPI_ERR_MODEM_GETSTATUSFAIL    = -502, /**<Failed to get status*/
    NAPI_ERR_MODEM_SLEPPFAIL        = -503, /**<Failed to sleep*/
    NAPI_ERR_MODEM_SDLCINITFAIL     = -504, /**<Failed to initialize in sync mode*/
    NAPI_ERR_MODEM_INIT_NOT         = -505, /**<Not initialized*/
    NAPI_ERR_MODEM_SDLCWRITEFAIL    = -506, /**<Failed to write in sync mode*/
    NAPI_ERR_MODEM_ASYNWRITEFAIL    = -507, /**<Failed to write in async mode*/
    NAPI_ERR_MODEM_ASYNDIALFAIL     = -508, /**<Failed to dial in async mode*/
    NAPI_ERR_MODEM_ASYNINITFAIL     = -509, /**<Failed to initialize in async mode*/
    NAPI_ERR_MODEM_SDLCHANGUPFAIL   = -510, /**<Failed to hangup in sync mode*/
    NAPI_ERR_MODEM_ASYNHANGUPFAIL   = -511, /**<Failed to hangup in async mode*/
    NAPI_ERR_MODEM_SDLCCLRBUFFAIL   = -512, /**<Failed to clear buffer in sync mode*/
    NAPI_ERR_MODEM_ASYNCLRBUFFAIL   = -513, /**<Failed to clear buffer in async mode*/
    NAPI_ERR_MODEM_ATCOMNORESPONSE  = -514, /**<No response for AT command*/
    NAPI_ERR_MODEM_PORTWRITEFAIL    = -515, /**<Failed to write data to modem port*/
    NAPI_ERR_MODEM_SETCHIPFAIL      = -516, /**<Failed to set register*/
    NAPI_ERR_MODEM_STARTSDLCTASK    = -517, /**<Failed to start SDLC task*/
    NAPI_ERR_MODEM_GETBUFFLENFAIL   = -518, /**<Failed to get data lenth*/
    NAPI_ERR_MODEM_QUIT             = -519, /**<Hand out*/
    NAPI_ERR_MODEM_NOPREDIAL        = -520, /**<No predial*/
    NAPI_ERR_MODEM_NOCARRIER        = -521, /**<No carrier*/
    NAPI_ERR_MODEM_NOLINE           = -523, /**<No cable*/
    NAPI_ERR_MODEM_OTHERMACHINE     = -524, /**<Collision detected*/
    NAPI_ERR_MODEM_PORTREADFAIL     = -525, /**<Failed to read data from modem port*/
    NAPI_ERR_MODEM_CLRBUFFAIL       = -526, /**<Failed to clear buffer*/
    NAPI_ERR_MODEM_ATCOMMANDERR     = -527, /**<AT command error*/
    NAPI_ERR_MODEM_STATUSUNDEFINE   = -528, /**<State unrecognized*/
    NAPI_ERR_MODEM_GETVERFAIL       = -529, /**<Failed to get version*/
    NAPI_ERR_MODEM_SDLCDIALFAIL     = -530, /**<Failed to dial in sync mode*/
    NAPI_ERR_MODEM_SELFADAPTFAIL    = -531, /**<Failed to auto-negotiation*/
    NAPI_ERR_MODEM_SELFADAPTCANCEL  = -532, /**<Auto-negotiation canceled*/

    NAPI_ERR_ICC_WRITE_ERR          = -601, /**<Failed to write*/
    NAPI_ERR_ICC_COPYERR            = -602, /**<Failed to copy kernel data*/
    NAPI_ERR_ICC_POWERON_ERR        = -603, /**<Failed to powerup*/
    NAPI_ERR_ICC_COM_ERR            = -604, /**<Command error*/
    NAPI_ERR_ICC_CARDPULL_ERR       = -605, /**<Card not present*/
    NAPI_ERR_ICC_CARDNOREADY_ERR    = -606, /**<Card not ready*/

    NAPI_ERR_USDDISK_PARAM          = -650, /**<Invalid parameter*/
    NAPI_ERR_USDDISK_DRIVELOADFAIL  = -651, /**<Failed to load USB stick or SD card*/
    NAPI_ERR_USDDISK_NONSUPPORTTYPE = -652, /**<Type not supported*/
    NAPI_ERR_USDDISK_UNMOUNTFAIL    = -653, /**<Failed to mount*/
    NAPI_ERR_USDDISK_UNLOADDRIFAIL  = -654, /**<Failed to unload driver*/
    NAPI_ERR_USDDISK_IOCFAIL        = -655, /**<Failed to call driver function*/
    NAPI_ERR_USDDISK_PWDERR         = -656, /**<password error*/
    NAPI_ERR_USDDISK_NOPWD          = -657, /**<no password*/
    NAPI_ERR_USDDISK_HAVEPWD        = -658, /**<have password*/
    NAPI_ERR_USDDISK_UNLOCK         = -659,
    NAPI_ERR_APP_BASE                     = -800,                     /**<Unknown error*/
    NAPI_ERR_APP_NOT_EXIST                = (NAPI_ERR_APP_BASE - 1),  /**<Application not exist*/
    NAPI_ERR_APP_NOT_MATCH                = (NAPI_ERR_APP_BASE - 2),  /**<Patch not match*/
    NAPI_ERR_APP_FAIL_SEC                 = (NAPI_ERR_APP_BASE - 3),  /**<Failed to access tamper status*/
    NAPI_ERR_APP_SEC_ATT                  = (NAPI_ERR_APP_BASE - 4),  /**<Tamper detected*/
    NAPI_ERR_APP_FILE_EXIST               = (NAPI_ERR_APP_BASE - 5),  /**<Application file already exists*/
    NAPI_ERR_APP_FILE_NOT_EXIST           = (NAPI_ERR_APP_BASE - 6),  /**<Application file not exist*/
    NAPI_ERR_APP_FAIL_AUTH                = (NAPI_ERR_APP_BASE - 7),  /**<Failed to authenticate certificate*/
    NAPI_ERR_APP_LOW_VERSION              = (NAPI_ERR_APP_BASE - 8),  /**<Patch version lower than the application version*/
    NAPI_ERR_APP_MAX_CHILD                = (NAPI_ERR_APP_BASE - 9),  /**<More than maximum number of running applications*/
    NAPI_ERR_APP_CREAT_CHILD              = (NAPI_ERR_APP_BASE - 10), /**<Failed to create child process*/
    NAPI_ERR_APP_WAIT_CHILD               = (NAPI_ERR_APP_BASE - 11), /**<Failed to wait for the child to exit*/
    NAPI_ERR_APP_FILE_READ                = (NAPI_ERR_APP_BASE - 12), /**<Failed to read file*/
    NAPI_ERR_APP_FILE_WRITE               = (NAPI_ERR_APP_BASE - 13), /**<Failed to write file*/
    NAPI_ERR_APP_FILE_STAT                = (NAPI_ERR_APP_BASE - 14), /**<Failed to get file information*/
    NAPI_ERR_APP_FILE_OPEN                = (NAPI_ERR_APP_BASE - 15), /**<Failed to open file*/
    NAPI_ERR_APP_NLD_HEAD_LEN             = (NAPI_ERR_APP_BASE - 16), /**<Wrong length of the NLD file header information*/
    NAPI_ERR_APP_PUBKEY_EXPIRED           = (NAPI_ERR_APP_BASE - 17), /**<Public key expired*/
    NAPI_ERR_APP_MMAP                     = (NAPI_ERR_APP_BASE - 18), /**<Failed to map memory*/
    NAPI_ERR_APP_MALLOC                   = (NAPI_ERR_APP_BASE - 19), /**<Out of memory*/
    NAPI_ERR_APP_SIGN_DECRYPT             = (NAPI_ERR_APP_BASE - 20), /**<Failed to decrypt signature data*/
    NAPI_ERR_APP_SIGN_CHECK               = (NAPI_ERR_APP_BASE - 21), /**<Failed to validate signature data*/
    NAPI_ERR_APP_MUNMAP                   = (NAPI_ERR_APP_BASE - 22), /**<Failed to unmap memory*/
    NAPI_ERR_APP_TAR                      = (NAPI_ERR_APP_BASE - 23), /**<Failed to untar data*/
    NAPI_ERR_APP_KEY_UPDATE_BAN           = (NAPI_ERR_APP_BASE - 24), /**<Key update is prohibited*/
    NAPI_ERR_APP_FIRM_PATCH_VERSION       = (NAPI_ERR_APP_BASE - 25), /**<Firmware patch version do not match*/
    NAPI_ERR_APP_CERT_HAS_EXPIRED         = (NAPI_ERR_APP_BASE - 26), /**<Certificate expired*/
    NAPI_ERR_APP_CERT_NOT_YET_VALID       = (NAPI_ERR_APP_BASE - 27), /**<Invalid certificate*/
    NAPI_ERR_APP_FILE_NAME_TOO_LONG       = (NAPI_ERR_APP_BASE - 28), /**<File name length larger than 32 bytes*/
    NAPI_ERR_APP_CA_ALREADY_CUSTOMIZED    = (NAPI_ERR_APP_BASE - 29), /**<Application CA has been customized*/
    NAPI_ERR_APP_FILE_CHK                 = (NAPI_ERR_APP_BASE - 30), /**<File check error*/

    NAPI_ERR_SECP_BASE                    = (-1000),                   /**<Unknown error*/
    NAPI_ERR_SECP_TIMEOUT                 = (NAPI_ERR_SECP_BASE - 1),  /**<Get key value timeout*/
    NAPI_ERR_SECP_PARAM                   = (NAPI_ERR_SECP_BASE - 2),  /**<Invalid parameter*/
    NAPI_ERR_SECP_DBUS                    = (NAPI_ERR_SECP_BASE - 3),  /**<DBUS communication error*/
    NAPI_ERR_SECP_MALLOC                  = (NAPI_ERR_SECP_BASE - 4),  /**<Out of memory*/
    NAPI_ERR_SECP_OPEN_SEC                = (NAPI_ERR_SECP_BASE - 5),  /**<Failed to open security device*/
    NAPI_ERR_SECP_SEC_DRV                 = (NAPI_ERR_SECP_BASE - 6),  /**<Failed to call driver function*/
    NAPI_ERR_SECP_GET_RNG                 = (NAPI_ERR_SECP_BASE - 7),  /**<Failed to get random number*/
    NAPI_ERR_SECP_GET_KEY                 = (NAPI_ERR_SECP_BASE - 8),  /**<Failed to get key value*/
    NAPI_ERR_SECP_KCV_CHK                 = (NAPI_ERR_SECP_BASE - 9),  /**<KCV check error*/
    NAPI_ERR_SECP_GET_CALLER              = (NAPI_ERR_SECP_BASE - 10), /**<Failed to get caller info*/
    NAPI_ERR_SECP_OVERRUN                 = (NAPI_ERR_SECP_BASE - 11), /**<Overrun*/
    NAPI_ERR_SECP_NO_PERMIT               = (NAPI_ERR_SECP_BASE - 12), /**<Operation not allowed*/
    NAPI_ERR_SECP_TAMPER                  = (NAPI_ERR_SECP_BASE - 13), /**<Tamper detected*/
    NAPI_ERR_SECP_UNSUPPORT               = (NAPI_ERR_SECP_BASE - 14), /**<the feature is not supported*/
    NAPI_ERR_SECVP_BASE                   = (-1100),                   /**<Unknown error*/
    NAPI_ERR_SECVP_TIMEOUT                = (NAPI_ERR_SECVP_BASE - 1), /**<Get key value timeout*/
    NAPI_ERR_SECVP_PARAM                  = (NAPI_ERR_SECVP_BASE - 2), /**<Invalid parameter*/
    NAPI_ERR_SECVP_DBUS                   = (NAPI_ERR_SECVP_BASE - 3), /**<DBUS communication error*/
    NAPI_ERR_SECVP_OPEN_EVENT0            = (NAPI_ERR_SECVP_BASE - 4), /**<Failed to open event device*/
    NAPI_ERR_SECVP_SCAN_VAL               = (NAPI_ERR_SECVP_BASE - 5), /**<Scan value out of range*/
    NAPI_ERR_SECVP_OPEN_RNG               = (NAPI_ERR_SECVP_BASE - 6), /**<Failed to open random number device*/
    NAPI_ERR_SECVP_GET_RNG                = (NAPI_ERR_SECVP_BASE - 7), /**<Failed to get random number*/
    NAPI_ERR_SECVP_GET_ESC                = (NAPI_ERR_SECVP_BASE - 8), /**<User cancel*/
    NAPI_ERR_SECVP_UNSUPPORT              = (NAPI_ERR_SECVP_BASE - 9), /**<the feature is not supported*/
    NAPI_ERR_SECVP_VPP                    = (-1120),                   /**<Unknown error*/
    NAPI_ERR_SECVP_INVALID_KEY            = (NAPI_ERR_SECVP_VPP),      /**<Invalid key*/
    NAPI_ERR_SECVP_NOT_ACTIVE             = (NAPI_ERR_SECVP_VPP - 1),  /**<VPPIs not active*/
    NAPI_ERR_SECVP_TIMED_OUT              = (NAPI_ERR_SECVP_VPP - 2),  /**<VPP initialization timeout*/
    NAPI_ERR_SECVP_ENCRYPT_ERROR          = (NAPI_ERR_SECVP_VPP - 3),  /**<Failed to encrypt*/
    NAPI_ERR_SECVP_BUFFER_FULL            = (NAPI_ERR_SECVP_VPP - 4),  /**<Buffer full*/
    NAPI_ERR_SECVP_PIN_KEY                = (NAPI_ERR_SECVP_VPP - 5),  /**<Data key pressed, echo "*".*/
    NAPI_ERR_SECVP_ENTER_KEY              = (NAPI_ERR_SECVP_VPP - 6),  /**<Enter key pressed, process PIN*/
    NAPI_ERR_SECVP_BACKSPACE_KEY          = (NAPI_ERR_SECVP_VPP - 7),  /**<Backspace key pressed.*/
    NAPI_ERR_SECVP_CLEAR_KEY              = (NAPI_ERR_SECVP_VPP - 8),  /**<Clear key pressed, remove all the '*'.*/
    NAPI_ERR_SECVP_CANCEL_KEY             = (NAPI_ERR_SECVP_VPP - 9),  /**<Cancel key pressed.*/
    NAPI_ERR_SECVP_GENERALERROR           = (NAPI_ERR_SECVP_VPP - 10), /**<Internal error.*/
    NAPI_ERR_SECVP_CUSTOMERCARDNOTPRESENT = (NAPI_ERR_SECVP_VPP - 11), /**<Smart card not present*/
    NAPI_ERR_SECVP_HTCCARDERROR           = (NAPI_ERR_SECVP_VPP - 12), /**<Failed to access smart card*/
    NAPI_ERR_SECVP_WRONG_PIN_LAST_TRY     = (NAPI_ERR_SECVP_VPP - 13), /**<Wrong password, try again*/
    NAPI_ERR_SECVP_WRONG_PIN              = (NAPI_ERR_SECVP_VPP - 14), /**<Try last time.*/
    NAPI_ERR_SECVP_ICCERROR               = (NAPI_ERR_SECVP_VPP - 15), /**<Try too many times*/
    NAPI_ERR_SECVP_PIN_BYPASS             = (NAPI_ERR_SECVP_VPP - 16), /**<PIN verification succeed, but PIN length is zero*/
    NAPI_ERR_SECVP_ICCFAILURE             = (NAPI_ERR_SECVP_VPP - 17), /**<Fatal error.*/
    NAPI_ERR_SECVP_GETCHALLENGE_BAD       = (NAPI_ERR_SECVP_VPP - 18), /**<Response is not 90, 00.*/
    NAPI_ERR_SECVP_GETCHALLENGE_NOT8      = (NAPI_ERR_SECVP_VPP - 19), /**<Invalid response length.*/
    NAPI_ERR_SECVP_PIN_ATTACK_TIMER       = (NAPI_ERR_SECVP_VPP - 20), /**<PIN attack timer activated*/
    NAPI_ERR_SECVP_PIN_TOO_SHORT          = (NAPI_ERR_SECVP_VPP - 21), /**<PIN too short*/
    NAPI_ERR_SECCR_BASE                   = (-1200),                   /**<Unknown error*/
    NAPI_ERR_SECCR_TIMEOUT                = (NAPI_ERR_SECCR_BASE - 1), /**<Get key value timeout*/
    NAPI_ERR_SECCR_PARAM                  = (NAPI_ERR_SECCR_BASE - 2), /**<Invalid parameter*/
    NAPI_ERR_SECCR_DBUS                   = (NAPI_ERR_SECCR_BASE - 3), /**<DBUS communication error*/
    NAPI_ERR_SECCR_MALLOC                 = (NAPI_ERR_SECCR_BASE - 4), /**<Out of memory*/
    NAPI_ERR_SECCR_OPEN_RNG               = (NAPI_ERR_SECCR_BASE - 5), /**<Failed to open random number device*/
    NAPI_ERR_SECCR_DRV                    = (NAPI_ERR_SECCR_BASE - 6), /**<Failed to call driver function*/
    NAPI_ERR_SECCR_KEY_TYPE               = (NAPI_ERR_SECCR_BASE - 7), /**<Wrong key type*/
    NAPI_ERR_SECCR_KEY_LEN                = (NAPI_ERR_SECCR_BASE - 8), /**<Wrong key length*/
    NAPI_ERR_SECCR_GET_KEY                = (NAPI_ERR_SECCR_BASE - 9), /**<Failed to get key*/

    NAPI_ERR_SECKM_BASE                   = (-1300),                    /**<Unknown error*/
    NAPI_ERR_SECKM_TIMEOUT                = (NAPI_ERR_SECKM_BASE - 1),  /**<Get key value timeout*/
    NAPI_ERR_SECKM_PARAM                  = (NAPI_ERR_SECKM_BASE - 2),  /**<Invalid parameter*/
    NAPI_ERR_SECKM_DBUS                   = (NAPI_ERR_SECKM_BASE - 3),  /**<DBUS communication error*/
    NAPI_ERR_SECKM_MALLOC                 = (NAPI_ERR_SECKM_BASE - 4),  /**<Out of memory*/
    NAPI_ERR_SECKM_OPEN_DB                = (NAPI_ERR_SECKM_BASE - 5),  /**<Failed to open database*/
    NAPI_ERR_SECKM_DEL_DB                 = (NAPI_ERR_SECKM_BASE - 6),  /**<Failed to delete database*/
    NAPI_ERR_SECKM_DEL_REC                = (NAPI_ERR_SECKM_BASE - 7),  /**<Failed to delete record*/
    NAPI_ERR_SECKM_INSTALL_REC            = (NAPI_ERR_SECKM_BASE - 8),  /**<Failed to install key record*/
    NAPI_ERR_SECKM_READ_REC               = (NAPI_ERR_SECKM_BASE - 9),  /**<Failed to read key record*/
    NAPI_ERR_SECKM_OPT_NOALLOW            = (NAPI_ERR_SECKM_BASE - 10), /**<Operation not allowed*/
    NAPI_ERR_SECKM_KEY_MAC                = (NAPI_ERR_SECKM_BASE - 11), /**<MAC error*/
    NAPI_ERR_SECKM_KEY_TYPE               = (NAPI_ERR_SECKM_BASE - 12), /**<Wrong key type*/
    NAPI_ERR_SECKM_KEY_ARCH               = (NAPI_ERR_SECKM_BASE - 13), /**<Wrong key architecture*/
    NAPI_ERR_SECKM_KEY_LEN                = (NAPI_ERR_SECKM_BASE - 14), /**<Wrong key length*/
    NAPI_ERR_SECKM_SYS                    = (NAPI_ERR_SECKM_BASE - 15), /**<system unknown error*/
    NAPI_ERR_SECKM_UNSUPPORT              = (NAPI_ERR_SECKM_BASE - 16), /**<the feature is not supported*/
    NAPI_ERR_SECKM_KEY_ALREADY_USED       = (NAPI_ERR_SECKM_BASE - 17), /**<the key is used*/
    NAPI_ERR_SECKM_CALCKCV                = (NAPI_ERR_SECKM_BASE - 18), /**< KCV calculating  error*/
    NAPI_ERR_SECKM_ASYM_GENERATE_BUSY     = (NAPI_ERR_SECKM_BASE - 19), /** asym random generate process busy **/
    NAPI_ERR_SECKM_ASYM_GENERATE_INIT     = (NAPI_ERR_SECKM_BASE - 20), /** asym random generate INIT **/
    NAPI_ERR_SECKM_ASYM_GENERATE_PROCESSING  = (NAPI_ERR_SECKM_BASE - 21), /** asym random generate process **/
    NAPI_ERR_SECKM_TABLE_ERROR            = (NAPI_ERR_SECKM_BASE - 22), /**<key table not exist*/
    NAPI_ERR_SECKM_DB_NULL                = (NAPI_ERR_SECKM_BASE - 23), /**<key table is empty*/
    NAPI_ERR_SECKM_NOT_SUPPORT            = (NAPI_ERR_SECKM_BASE - 24), /**<the feature is not supported*/
    NAPI_ERR_SECKM_KEY_EXIST              = (NAPI_ERR_SECKM_BASE - 25), /**<key existed*/
    NAPI_ERR_SECKM_ASYMKEY_PARSE          = (NAPI_ERR_SECKM_BASE - 26), /**<parse asymkey error*/
    
    //key store
    NAPI_ERR_SECKS_BASE                   = (-1400),
    NAPI_ERR_SECKS_TIMEOUT                = (NAPI_ERR_SECKS_BASE - 1),  /**<Get key value timeout*/
    NAPI_ERR_SECKS_PARAM                  = (NAPI_ERR_SECKS_BASE - 2),  /**<Invalid parameter*/
    //kla
    NAPI_ERR_SECKLA_BASE                  = (-1500),
    NAPI_ERR_SECKLA_ERR_INTERNAL          = (NAPI_ERR_SECKLA_BASE -1),  /*Unspecified internal error.*/
    NAPI_ERR_SECKLA_PARAM                 = (NAPI_ERR_SECKLA_BASE -2),  /*Invalid parameter passed to function.*/
    NAPI_ERR_SECKLA_ERR_INVALID_CRT       = (NAPI_ERR_SECKLA_BASE -3),  /*Invalid certification*/
    NAPI_ERR_SECKLA_ERR_INVALID_SIG       = (NAPI_ERR_SECKLA_BASE -4),  /*Invalid nonce signature*/
    NAPI_ERR_SECKLA_ERR_KEY_NOT_FOUND     = (NAPI_ERR_SECKLA_BASE -5),  /*Key not found*/
    NAPI_ERR_SECKLA_ERR_INVALIDKEY_USAGE  = (NAPI_ERR_SECKLA_BASE -6),  /*Invalid use of the key according to the key tag*/
    //NAPI algorithm
    NAPI_ERR_SECALG_BASE                  = (-1600),
    NAPI_ERR_SECALG_TIMEOUT               = (NAPI_ERR_SECALG_BASE - 1), /**<Get key value timeout*/
    NAPI_ERR_SECALG_PARAM                 = (NAPI_ERR_SECALG_BASE - 2), /**<Invalid parameter*/
    NAPI_ERR_SECALG_UPDATE                = (NAPI_ERR_SECALG_BASE - 3),
    NAPI_ERR_SECALG_FINISH                = (NAPI_ERR_SECALG_BASE - 4),
    NAPI_ERR_SECALG_ASYMCALC              = (NAPI_ERR_SECALG_BASE - 5),
    NAPI_ERR_SECALG_ECCCALC               = (NAPI_ERR_SECALG_BASE - 6),
    NAPI_ERR_SECALG_ECDHE_HANDLE          = (NAPI_ERR_SECALG_BASE - 7),
    NAPI_ERR_SECALG_MAC                   = (NAPI_ERR_SECALG_BASE - 8), /**<Get MAC failed */
    
    //NAPI SecConfig  
    NAPI_ERR_SEC_CFG_BASE                 = (-1700),
    NAPI_ERR_SEC_CFG_TABLE                = (NAPI_ERR_SEC_CFG_BASE - 1),         /* indicate current key table, "" for app itself */
    NAPI_ERR_SEC_CFG_UNIQUE               = (NAPI_ERR_SEC_CFG_BASE - 2),         /* check if installing key is unique : 0 - no check, 1 - check */
    NAPI_ERR_SEC_CFG_MISUSE               = (NAPI_ERR_SEC_CFG_BASE - 3),         /* check if key is misused according to its type : 0 - no check, 1 - check */
    NAPI_ERR_SEC_CFG_TRIES_LIMIT          = (NAPI_ERR_SEC_CFG_BASE - 4),         /* check if current function is overrun: 0 - no check, 1 - check */
    NAPI_ERR_SEC_CFG_STRENGTH             = (NAPI_ERR_SEC_CFG_BASE - 5),         /* keys should be protected by the same or higher strength keys: 0 - no check, 1 - check */
    NAPI_ERR_SEC_CFG_KEYLEN_LIMIT         = (NAPI_ERR_SEC_CFG_BASE - 6),         /* key length should be stronger than 8 bytes : 0 - no check, 1- check */
    NAPI_ERR_SEC_CFG_DPA_DEFENCE          = (NAPI_ERR_SEC_CFG_BASE - 7),         /* DPA defence: 0 - disable, 1- enable */
    NAPI_ERR_SEC_CFG_CLEARKEY_LIMIT       = (NAPI_ERR_SEC_CFG_BASE - 8),         /* check if the clearkey is allowed to be installed: 0 - disable, 1- enable */
    NAPI_ERR_SEC_CFG_VPP_STATIC_KEY_LAYOUT_LIMIT = (NAPI_ERR_SEC_CFG_BASE - 9),  /* check if the clearkey is allowed to be installed: 0 - disable, 1- enable */
    NAPI_ERR_SEC_SP_CFG_ASYM_LOADKEY_LIMIT       = (NAPI_ERR_SEC_CFG_BASE - 10), /* Check if the symmetric keys is allowed to be installed by asymmetric keys : 0 - no check, 1 - check */
    //csr cert
    NAPI_ERR_SEC_CSR_BASE                 = (-1800),
    NAPI_ERR_SEC_CSR_TIMEOUT              = (NAPI_ERR_SEC_CSR_BASE - 1), /**<Get key value timeout*/
    NAPI_ERR_SEC_CSR_PARAM                = (NAPI_ERR_SEC_CSR_BASE - 2), /**<Invalid parameter*/
    NAPI_ERR_SEC_CSR_DBUS                 = (NAPI_ERR_SEC_CSR_BASE - 3), /**<DBUS communication error*/
    NAPI_ERR_SEC_CSR_MALLOC               = (NAPI_ERR_SEC_CSR_BASE - 4), /**<Out of memory*/
    NAPI_ERR_SEC_CSR_HANDLE               = (NAPI_ERR_SEC_CSR_BASE - 5), /**<CSR handle error*/
    NAPI_ERR_SEC_CSR_WRITE                = (NAPI_ERR_SEC_CSR_BASE - 6), /**<mbedtls library operation error*/
    NAPI_ERR_SEC_CSR_INPROCESS            = (NAPI_ERR_SEC_CSR_BASE - 7), /**< CSR handle have not released*/
    //RKI
    NAPI_ERR_SECRKI_BASE                  = (-1900),
    NAPI_ERR_SECRKI_TIMEOUT               = (NAPI_ERR_SECRKI_BASE - 1),
    NAPI_ERR_SECRKI_PARAM                 = (NAPI_ERR_SECRKI_BASE - 2),
    NAPI_ERR_SECRKI_BACKUP                = (NAPI_ERR_SECRKI_BASE - 3),
    NAPI_ERR_SECRKI_RESTORE               = (NAPI_ERR_SECRKI_BASE - 4),
    NAPI_ERR_SECRKI_VERIFY                = (NAPI_ERR_SECRKI_BASE - 5),
    NAPI_ERR_SECRKI_BANC_FILE             = (NAPI_ERR_SECRKI_BASE - 6),
    NAPI_ERR_SECRKI_BANC_NO_CERT          = (NAPI_ERR_SECRKI_BASE - 7),
    NAPI_ERR_SECRKI_BANC_CERT_VERIFY      = (NAPI_ERR_SECRKI_BASE - 8),
    NAPI_ERR_SECRKI_BANC_NO_PRECERT       = (NAPI_ERR_SECRKI_BASE - 9),
    NAPI_ERR_SECRKI_BANC_CAPUBKEY_INDEX   = (NAPI_ERR_SECRKI_BASE - 10),
    
    NAPI_ERR_RFID_INITSTA                 = -2005, /**<RF chip error or not configured*/
    NAPI_ERR_RFID_NOCARD                  = -2008, /**<No card  0x0D*/
    NAPI_ERR_RFID_MULTICARD               = -2009, /**<Multi card detected*/
    NAPI_ERR_RFID_SEEKING                 = -2010, /**<Failed to seek and activate card*/
    NAPI_ERR_RFID_PROTOCOL                = -2011, /**<Not compliant with ISO1444-4 protocol, e.g. M1 card F*/
    NAPI_ERR_RFID_NOPICCTYPE              = -2012, /**<Card not set 0x01*/
    NAPI_ERR_RFID_NOTDETE                 = -2013, /**<Card not detected  0x02*/
    NAPI_ERR_RFID_AANTI                   = -2014, /**<Type A card collision (Multiple cards exist) 0x03*/
    NAPI_ERR_RFID_RATS                    = -2015, /**<Type A card RATS processing error 0x04*/
    NAPI_ERR_RFID_BACTIV                  = -2016, /**<Failed to activate Type B card 0x07*/
    NAPI_ERR_RFID_ASEEK                   = -2017, /**<Failed to seek type A card (Probably multiple cards exist) 0x0A*/
    NAPI_ERR_RFID_BSEEK                   = -2018, /**<Failed to seek type B card (Probably multiple cards exist) 0x0B*/
    NAPI_ERR_RFID_ABON                    = -2019, /**<Both type A and B cards exist 0x0C*/
    NAPI_ERR_RFID_UPED                    = -2020, /**<Already activated 0x0E*/
    NAPI_ERR_RFID_NOTACTIV                = -2021, /**<Not activated 0x08*/
    NAPI_ERR_RFID_ASEL                    = -2022, /**<Type A card select fail 0x13*/
    NAPI_ERR_RFID_COLLISION_A             = -2023, /**<Type A Card collision*/
    NAPI_ERR_RFID_COLLISION_B             = -2024, /**<Type B Card collision*/
    NAPI_ERR_RFID_MODE_ERR                = -2026, /**<RF driver mode error*/

    NAPI_ERR_EMV_UNKNOW_ERR               = -2030, /**<Unknow error,                       */
    NAPI_ERR_EMV_CRC_ERR                  = -2031, /**<CRC error,                          */
    NAPI_ERR_EMV_PARITY_ERR               = -2032, /**<Parity error,                       */
    NAPI_ERR_EMV_COLL_ERR                 = -2033, /**<Collision detected,                 */
    NAPI_ERR_EMV_PROTOCOL_ERR             = -2034, /**<Protocol error,                     */
    NAPI_ERR_EMV_OVFL_ERR                 = -2035, /**<Overflow,                           */
    NAPI_ERR_EMV_TRANSMIT_ERR             = -2036, /**<Transmit error,                     */
    NAPI_ERR_EMV_RECEIVER_ERR             = -2037, /**<Receiver error,                     */
    NAPI_ERR_EMV_TIMER_OUT_ERR            = -2038, /**<Timeout error,                      */
    NAPI_ERR_EMV_DEADTIME_ERR             = -2039, /**<Deadtime error,                     */
    NAPI_ERR_EMV_RETRY_ERR                = -2040, /**<Retry error,                        */
    NAPI_ERR_EMV_CTRL_PROTOCOL_ERR        = -2041, /**<Protocol error,                     */
    NAPI_ERR_EMV_CTRL_HAEDWARE_ERR        = -2042, /**<Hardware error,                     */
    NAPI_ERR_EMV_RF_ERR                   = -2043, /**<RF error,                           */

    NAPI_ERR_MI_EMPTY                     = -2050, /**<Not empty,                      0xfd*/
    NAPI_ERR_MI_AUTHERR                   = -2051, /**<Failed to authenticate,         0xfc*/
    NAPI_ERR_MI_CODEERR                   = -2052, /**<Receiving code error            0xfa*/
    NAPI_ERR_MI_SERNRERR                  = -2053, /**<Anti-collision data check error 0xf8*/
    NAPI_ERR_MI_KEYERR                    = -2054, /**<KEY authentication error        0xf7*/
    NAPI_ERR_MI_NOTAUTHERR                = -2055, /**<Not authenticated               0xf6*/
    NAPI_ERR_MI_BITCOUNTERR               = -2056, /**<Failed to receive BIT           0xf5*/
    NAPI_ERR_MI_BYTECOUNTERR              = -2057, /**<Failed to receive byte          0xf4*/
    NAPI_ERR_MI_TRANSERR                  = -2058, /**<Failed to send                  0xf2*/
    NAPI_ERR_MI_WRITEERR                  = -2059, /**<Failed to error write           0xf1*/
    NAPI_ERR_MI_INCRERR                   = -2060, /**<Failed to increment             0xf0*/
    NAPI_ERR_MI_DECRERR                   = -2061, /**<Failed to decrement             0xef*/
    NAPI_ERR_MI_FRAMINGERR                = -2062, /**<Frame error                     0xeb*/
    NAPI_ERR_MI_INTERFACEERR              = -2063, /**<Fialed to reset interface       0xe6*/
    NAPI_ERR_MI_ACCESSTIMEOUT             = -2064, /**<Receive timeout                 0xe5*/
    NAPI_ERR_MI_PROTOCOLERR               = -2065, /**<Protocol error                  0xe4*/
    NAPI_ERR_MI_QUIT                      = -2066, /**<Abnormal abortion               0xe2*/
    NAPI_ERR_MI_PPSErr                    = -2067, /**<PPS operation error             0xe1*/
    NAPI_ERR_MI_SpiRequest                = -2068, /**<Failed to request SPI           0xa0*/
    NAPI_ERR_MI_NY_IMPLEMENTED            = -2069, /**<Unknown error                   0x9c*/
    NAPI_ERR_MI_CardTypeErr               = -2070, /**<Wrong card type                 0x83*/
    NAPI_ERR_MI_ParaErrInIoctl            = -2071, /**<Wrong IOCTL parameter           0x82*/
    NAPI_ERR_MI_Para                      = -2072, /**<Invalid parameter               0xa9*/

    NAPI_ERR_CE_BASE                      = -2400,
    NAPI_ERR_CE_STATE                     = (NAPI_ERR_CE_BASE-1), /**<Emulate state error*/
    NAPI_ERR_CE_MEMERY                    = (NAPI_ERR_CE_BASE-2), /**<Emulate memery error*/

    NAPI_ERR_WIFI_INVDATA                 = -3001, /**<Invalid parameter*/
    NAPI_ERR_WIFI_DEVICE_FAULT            = -3002, /**<Invalid device state*/
    NAPI_ERR_WIFI_CMD_UNSUPPORTED         = -3003, /**<Command not supported*/
    NAPI_ERR_WIFI_DEVICE_UNAVAILABLE      = -3004, /**<Device unavailable*/
    NAPI_ERR_WIFI_DEVICE_NOTOPEN          = -3005, /**<No AP scanned*/
    NAPI_ERR_WIFI_DEVICE_BUSY             = -3006, /**<Device busy*/
    NAPI_ERR_WIFI_UNKNOWN_ERROR           = -3007, /**<Unknown Error*/
    NAPI_ERR_WIFI_PROCESS_INBADSTATE      = -3008, /**<Failed to connect*/
    NAPI_ERR_WIFI_SEARCH_FAULT            = -3009, /**<Invalied scanning state*/
    NAPI_ERR_WIFI_DEVICE_TIMEOUT          = -3010, /**<Device timeout*/
    NAPI_ERR_WIFI_NON_CONNECTED           = -3011, /**<Not connected*/

    NAPI_ERR_RFID_BUSY                    = -3101, /**<Rf card busy*/
    NAPI_ERR_PRN_BUSY                     = -3102, /**<Printer busy*/
    NAPI_ERR_ICCARD_BUSY                  = -3103, /**<Samer card busy*/
    NAPI_ERR_MAG_BUSY                     = -3104, /**<MagnetSmart card busy*/
    NAPI_ERR_USB_BUSY                     = -3105, /**<USB module busy*/
    NAPI_ERR_WLM_BUSY                     = -3106, /**<Wireless module busy*/
    NAPI_ERR_PIN_BUSY                     = -3107, /**<PIN input*/
    NAPI_ERR_BT_BUSY                      = -3108, /**<Bluetooth module busy*/
    NAPI_ERR_DEV_BUSY                     = -3109, /**<Device busy*/
    NAPI_ERR_AP_BUSY                      = -3110, /**<AP module busy*/
    NAPI_ERR_BT_NOT_CONNECTED             = -3201, /**<Bluetooth not connected*/
    NAPI_ERR_PROPERTY_NOT_SET             = -3202, /**<Get property configuration fail*/

    NAPI_ERR_AUTH_CUSTOM_INIT             = -4000,
    NAPI_ERR_AUTH_CUSTOM_READ             = -4001,
    NAPI_ERR_AUTH_CUSTOM_WRITE            = -4002,
    NAPI_ERR_AUTH_CUSTOM_CPUID_ERR        = -4003,
    NAPI_ERR_AUTH_CUSTOM_FLASHID_ERR      = -4004,
    NAPI_ERR_AUTH_CUSTOM_CUSTOMID_ERR     = -4005,
    NAPI_ERR_AUTH_CUSTOM_UNCHECK          = -4006,
    NAPI_ERR_AUTH_CUSTOM_REVERT_ERR       = -4007,
    NAPI_ERR_AUTH_CUSTOM_DEVFLAG_ERR      = -4008,

    NAPI_ERR_AUDIO_BASE                   = -4200,
    NAPI_ERR_AUDIO_BUSY                   = -4201,
    NAPI_ERR_AUDIO_PAUSED                 = -4202,
    NAPI_ERR_AUDIO_RESUME                 = -4203,
    NAPI_ERR_AUDIO_STOP                   = -4204,

    NAPI_ERR_LINUX_ERRNO_BASE             = -5000,                             /**<Error prefix from system function*/
    NAPI_ERR_LINUX_TCP_TIMEOUT            = (NAPI_ERR_LINUX_ERRNO_BASE - 110), /**<Wrong TCP remote port*/
    NAPI_ERR_LINUX_TCP_REFUSE             = (NAPI_ERR_LINUX_ERRNO_BASE - 111), /**<TCP remote port not allowed*/
    NAPI_ERR_LINUX_TCP_NOT_OPEN           = (NAPI_ERR_LINUX_ERRNO_BASE - 88),  /**<TCP not open*/

    NAPI_ERR_MDB_BASE                     = -5200,
    NAPI_ERR_MDB_NO_GLOBAL_INIT           = (NAPI_ERR_MDB_BASE - 1),
    NAPI_ERR_MDB_USART_INIT_FAIL          = (NAPI_ERR_MDB_BASE - 2),
    NAPI_ERR_MDB_UNKNOWN_OPTION           = (NAPI_ERR_MDB_BASE - 3),
    NAPI_ERR_MDB_LEVEL_NOSUPPORT          = (NAPI_ERR_MDB_BASE - 4),
    NAPI_ERR_MDB_APP_ATTR_ERR             = (NAPI_ERR_MDB_BASE - 5),
    NAPI_ERR_MDB_DEV_INFO_ERR             = (NAPI_ERR_MDB_BASE - 6),
    NAPI_ERR_MDB_CALLBACK_FUNC_ERR        = (NAPI_ERR_MDB_BASE - 7),
    NAPI_ERR_MDB_SET_OPT_PARA_ERR         = (NAPI_ERR_MDB_BASE - 8),
    NAPI_ERR_MDB_GET_OPT_PARA_ERR         = (NAPI_ERR_MDB_BASE - 9),
    NAPI_ERR_MDB_IN_BUF_TOO_LONG          = (NAPI_ERR_MDB_BASE - 10),
    NAPI_ERR_MDB_OUT_BUF_TOO_SHORT        = (NAPI_ERR_MDB_BASE - 11),
    NAPI_ERR_MDB_COMM_RECV_ERR            = (NAPI_ERR_MDB_BASE - 12),
    NAPI_ERR_MDB_COMM_SEND_ERR            = (NAPI_ERR_MDB_BASE - 13),
    NAPI_ERR_MDB_MSG_TYPE_ERR             = (NAPI_ERR_MDB_BASE - 14),
    NAPI_ERR_MDB_COMM_PARA_ERR            = (NAPI_ERR_MDB_BASE - 15),
    NAPI_ERR_MDB_PARA_ERR                 = (NAPI_ERR_MDB_BASE - 16),
    NAPI_ERR_MDB_TIME_OUT                 = (NAPI_ERR_MDB_BASE - 17),
    NAPI_ERR_MDB_FTL_DENY                 = (NAPI_ERR_MDB_BASE - 18),
    NAPI_ERR_MDB_FILE_OPEN                = (NAPI_ERR_MDB_BASE - 19),
    NAPI_ERR_MDB_FILE_READ                = (NAPI_ERR_MDB_BASE - 20),
    NAPI_ERR_MDB_FILE_WRITE               = (NAPI_ERR_MDB_BASE - 21),
    NAPI_ERR_MDB_MODE_CONFLICT            = (NAPI_ERR_MDB_BASE - 22),
    NAPI_ERR_MDB_LINK_UNINIT              = (NAPI_ERR_MDB_BASE - 23),
    

    NAPI_ERR_ECR_FM_ERRNO_BASE            = -7000,
    NAPI_ERR_ECR_FM_PARA_ERR              = (NAPI_ERR_ECR_FM_ERRNO_BASE - 1),  /**<Parameter error.*/
    NAPI_ERR_ECR_FM_UNEXIST               = (NAPI_ERR_ECR_FM_ERRNO_BASE - 2),  /**<FM does not exist.*/
    NAPI_ERR_ECR_FM_NO_SPACE              = (NAPI_ERR_ECR_FM_ERRNO_BASE - 3),  /**<Not enough space.*/
    NAPI_ERR_ECR_FM_WRITE_ERR             = (NAPI_ERR_ECR_FM_ERRNO_BASE - 4),  /**<FM write failed.*/
    NAPI_ERR_ECR_FM_READ_ERR              = (NAPI_ERR_ECR_FM_ERRNO_BASE - 5),  /**<FM read failed.*/
    NAPI_ERR_ECR_FM_CHECKSUM_ERR          = (NAPI_ERR_ECR_FM_ERRNO_BASE - 6),  /**<FM verification failed.*/
    NAPI_ERR_ECR_FM_EJINFO_ERR            = (NAPI_ERR_ECR_FM_ERRNO_BASE - 7),  /**<EJ card information verification failed.*/
    NAPI_ERR_ECR_FM_DATA_UNEXIST          = (NAPI_ERR_ECR_FM_ERRNO_BASE - 8),  /**<Record does not exist.*/

    NAPI_ERR_CARDREADER_BASE              = -7100,
    NAPI_ERR_CARDREADER_INTERNAL          = (NAPI_ERR_CARDREADER_BASE - 1),
    NAPI_ERR_CARDREADER_NAK               = (NAPI_ERR_CARDREADER_BASE - 2),
    NAPI_ERR_CARDREADER_DATALOSS          = (NAPI_ERR_CARDREADER_BASE - 3),
    NAPI_ERR_CARDREADER_CHECKCODE         = (NAPI_ERR_CARDREADER_BASE - 4),
    NAPI_ERR_CARDREADER_ACTANTIFUNC       = (NAPI_ERR_CARDREADER_BASE - 5),
    NAPI_ERR_CARDREADER_REMOVEDETECTED    = (NAPI_ERR_CARDREADER_BASE - 6),
    NAPI_ERR_CARDREADER_AUTH              = (NAPI_ERR_CARDREADER_BASE - 7),
    NAPI_ERR_CARDREADER_UPDATE            = (NAPI_ERR_CARDREADER_BASE - 8),
    NAPI_ERR_CARDREADER_RECONNECT         = (NAPI_ERR_CARDREADER_BASE - 9),
    NAPI_ERR_CARDREADER_TIMEOUT           = (NAPI_ERR_CARDREADER_BASE - 10),

} NAPI_ERR_CODE;

/** @}*/ // End of ErrorCodes

/** @addtogroup ErrorCodes_Deprecated
* @{
*/
/**************************************** Deprecated ********************************************/

#define NAPI_ERR_WLM_SOCKET   NAPI_ERR_SOCKET
#define NAPI_ERR_MI_NOTAGERR  NAPI_ERR_EMV_TIMER_OUT_ERR
#define NAPI_ERR_MI_CRCERR    NAPI_ERR_EMV_CRC_ERR
#define NAPI_ERR_MI_PARITYERR NAPI_ERR_EMV_PARITY_ERR
#define NAPI_ERR_MI_WriteFifo NAPI_ERR_EMV_TRANSMIT_ERR
#define NAPI_ERR_MI_OVFLERR   NAPI_ERR_EMV_OVFL_ERR
#define NAPI_ERR_MI_COLLERR   NAPI_ERR_EMV_COLL_ERR

/** @} */ // End of ErrorCodes deprecated

#ifdef __cplusplus
}
#endif

#endif

/* End of this file*/


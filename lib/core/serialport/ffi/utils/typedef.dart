import 'dart:ffi';

import 'package:demo_p180_serialport/core/serialport/ffi/serialport_ffi.dart';
import 'package:ffi/ffi.dart';

typedef native_sys_get_info_func =
    Int32 Function(
      Int32 infoID,
      Pointer<Utf8> outBuf,
      Pointer<Int32> outBufLen,
    );
typedef native_port_open_func =
    Int32 Function(Int32 portType, Pointer<PortSettingsFFI> settings);
typedef native_port_flush_func = Int32 Function(Int32 portType);
typedef native_port_write_func =
    Int32 Function(Int32 portType, Pointer<Uint8> buf, Int32 len);
typedef native_port_readlen_func =
    Int32 Function(Int32 portType, Pointer<Int32> outLen);
typedef native_port_read_func =
    Int32 Function(
      Int32 portType,
      Pointer<Uint8> buf,
      Pointer<Int32> bufLen,
      Int32 timeout,
    );
typedef native_port_close_func = Int32 Function(Int32 portType);

// Dart
typedef SysGetInfo =
    int Function(int infoID, Pointer<Utf8> outBuf, Pointer<Int32> outBufLen);
typedef PortOpen =
    int Function(int portType, Pointer<PortSettingsFFI> settings);
typedef PortFlush = int Function(int portType);
typedef PortWrite = int Function(int portType, Pointer<Uint8> buf, int len);
typedef PortReadLen = int Function(int portType, Pointer<Int32> outLen);
typedef PortRead =
    int Function(
      int portType,
      Pointer<Uint8> buf,
      Pointer<Int32> bufLen,
      int timeout,
    );
typedef PortClose = int Function(int portType);

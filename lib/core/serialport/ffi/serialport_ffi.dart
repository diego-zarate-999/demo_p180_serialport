import 'dart:ffi';

import 'package:demo_p180_serialport/core/serialport/ffi/utils/exception.dart';
import 'package:demo_p180_serialport/core/serialport/ffi/utils/typedef.dart';

sealed class PortSettingsFFI extends Struct {
  @Int32()
  external int baudRate;

  @Int32()
  external int dataBits;

  @Int32()
  external int stopBits;

  @Int32()
  external int parity;
}

abstract class SerialportFFI {
  ///
  /// Inicializar la libreria desde el .so con FFI.
  ///

  void initNativeLibrary();

  ///
  /// Funciones de puerto serial.
  ///

  int portOpen(int portType, Pointer<PortSettingsFFI> settings);
  int portFlush(int portType);
  int portWrite(int portType, Pointer<Uint8> buf, int len);
  int portReadLen(int portType, Pointer<Int32> outLen);
  int portRead(
    int portType,
    Pointer<Uint8> buf,
    Pointer<Int32> bufLen,
    int timeout,
  );
  int portClose(int portType);
}

class SerialportFFINapi implements SerialportFFI {
  late final DynamicLibrary serialportNative;

  late final PortOpen _openPort;
  late final PortFlush _flushPort;
  late final PortWrite _writePort;
  late final PortReadLen _readLenPort;
  late final PortRead _readPort;
  late final PortClose _closePort;

  SerialportFFINapi() {
    try {
      initNativeLibrary();
    } catch (error) {
      throw FFIException(message: error.toString(), errorCode: -1);
    }
  }

  @override
  void initNativeLibrary() {
    try {
      serialportNative = DynamicLibrary.open('libserial_wrapper.so');
      _bindLookups();
    } catch (e) {
      throw Exception('Error al abrir wrapper.');
    }
  }

  @override
  int portClose(int portType) => _closePort(portType);

  @override
  int portFlush(int portType) => _flushPort(portType);

  @override
  int portOpen(int portType, Pointer<PortSettingsFFI> settings) =>
      _openPort(portType, settings);

  @override
  int portRead(
    int portType,
    Pointer<Uint8> buf,
    Pointer<Int32> bufLen,
    int timeout,
  ) => _readPort(portType, buf, bufLen, timeout);

  @override
  int portReadLen(int portType, Pointer<Int32> outLen) =>
      _readLenPort(portType, outLen);

  @override
  int portWrite(int portType, Pointer<Uint8> buf, int len) =>
      _writePort(portType, buf, len);

  void _bindLookups() {
    _openPort = serialportNative
        .lookupFunction<native_port_open_func, PortOpen>('wrapper_PortOpen');

    _flushPort = serialportNative
        .lookupFunction<native_port_flush_func, PortFlush>('wrapper_PortFlush');

    _writePort = serialportNative
        .lookupFunction<native_port_write_func, PortWrite>('wrapper_PortWrite');

    _readLenPort = serialportNative
        .lookupFunction<native_port_readlen_func, PortReadLen>(
          'wrapper_PortReadLen',
        );

    _readPort = serialportNative
        .lookupFunction<native_port_read_func, PortRead>('wrapper_PortRead');

    _closePort = serialportNative
        .lookupFunction<native_port_close_func, PortClose>('wrapper_PortClose');
  }
}

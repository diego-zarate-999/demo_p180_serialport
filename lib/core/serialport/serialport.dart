import 'dart:async';
import 'dart:ffi';
import 'dart:typed_data';
import 'package:ffi/ffi.dart';

import 'package:demo_p180_serialport/core/serialport/ffi/serialport_ffi.dart';
import 'package:demo_p180_serialport/core/serialport/ffi/utils/exception.dart';

enum CommunicationType {
  rs232,
  pinpad,
  wireless,
  usbSerial,
  usbHost,
  usbHostHid,
  usbHostPrinter,
}

extension PortTypeValue on CommunicationType {
  int get value {
    switch (this) {
      case CommunicationType.rs232:
        return 0;
      case CommunicationType.pinpad:
        return 1;
      case CommunicationType.wireless:
        return 2;
      case CommunicationType.usbSerial:
        return 8;
      case CommunicationType.usbHost:
        return 10;
      case CommunicationType.usbHostHid:
        return 12;
      case CommunicationType.usbHostPrinter:
        return 13;
    }
  }
}

enum BaudRateType { baud9600, baud19200, baud38400, baud57600, baud115200 }

extension BaudRateTypeValue on BaudRateType {
  int get value {
    switch (this) {
      case BaudRateType.baud9600:
        return 9600;
      case BaudRateType.baud19200:
        return 19200;
      case BaudRateType.baud38400:
        return 38400;
      case BaudRateType.baud57600:
        return 57600;
      case BaudRateType.baud115200:
        return 115200;
    }
  }
}

enum DataBitsType { data5, data6, data7, data8 }

extension DataBitsTypeValue on DataBitsType {
  int get value {
    switch (this) {
      case DataBitsType.data5:
        return 5;
      case DataBitsType.data6:
        return 6;
      case DataBitsType.data7:
        return 7;
      case DataBitsType.data8:
        return 8;
    }
  }
}

enum StopBitsType { stop1, stop2 }

enum ParityType { parNone, parOdd, parEven }

class SerialportSettings {
  final BaudRateType baudRate;
  final DataBitsType dataBits;
  final StopBitsType stopBits;
  final ParityType parityType;
  final CommunicationType portType;

  SerialportSettings({
    required this.baudRate,
    required this.dataBits,
    required this.stopBits,
    required this.parityType,
    required this.portType,
  });
}

class SerialPortEvent {
  final Uint8List data;

  SerialPortEvent({required this.data});
}

///
/// Singleton para las funciones de comnunicacion por puerto serial.
///

class SerialPort {
  static final SerialPort _instance = SerialPort._internal();

  ///
  /// FFI para la comunicacion serial con NAPI.
  ///
  final SerialportFFI _serialportFFI = SerialportFFINapi();

  ///
  /// Stream para eventos de puerto serial.
  ///
  late final StreamController<SerialPortEvent> _controller;

  ///
  /// Control de la escucha del puerto.
  ///
  bool _isOpen = false;

  ///
  /// Settings de puerto serial.
  ///
  late SerialportSettings _serialPortSettings;

  SerialPort._internal();

  //
  /// Constructor que siempre devuelve la misma instancia
  ///

  factory SerialPort() {
    return _instance;
  }

  Stream<SerialPortEvent> open(SerialportSettings settings) {
    if (_isOpen) {
      throw SerialPortException(
        message: "El puerto ya se encuentra abierto.",
        errorCode: -1,
      );
    }

    _isOpen = true;
    _controller = StreamController<SerialPortEvent>.broadcast();
    _serialPortSettings = settings;

    try {
      ///
      /// Abrir puerto serial.
      ///
      _openPortInternal();

      ///
      /// Quedar a al escucha de puerto serial.
      ///
      _listenSerialPort();
    } on SerialPortException catch (_) {
      rethrow;
    }

    return _controller.stream;
  }

  void write(Uint8List data) async {
    if (!_isOpen) {
      throw SerialPortException(
        message: "El puerto no se encuentra abierto.",
        errorCode: -1,
      );
    }

    try {
      _writePortInternal(data);
    } on SerialPortException catch (_) {
      rethrow;
    }
  }

  void close() async {
    if (!_isOpen) {
      return;
    }

    _isOpen = false;
    try {
      _closePortInternal();
    } on SerialPortException catch (_) {
      rethrow;
    }
  }

  ///
  /// Funciones internas del singleton.
  ///

  void _openPortInternal() {
    final portSettings = calloc<PortSettingsFFI>();
    portSettings.ref
      ..baudRate = _serialPortSettings.baudRate.value
      ..dataBits = _serialPortSettings.dataBits.value
      ..stopBits = _serialPortSettings.stopBits.index
      ..parity = _serialPortSettings.parityType.index;

    final result = _serialportFFI.portOpen(
      _serialPortSettings.portType.value,
      portSettings,
    );

    if (result != 0) {
      calloc.free(portSettings);
      throw SerialPortException(
        message: "Error al abrir el puerto serial.",
        errorCode: result,
      );
    }
  }

  void _listenSerialPort() async {
    while (_isOpen) {
      try {
        final bytes = await _readPortInternal();
        if (bytes != null) {
          _controller.add(SerialPortEvent(data: bytes));
        }
      } on SerialPortException {
        rethrow;
      }

      await Future.delayed(const Duration(milliseconds: 1));
    }
  }

  Future<Uint8List?> _readPortInternal({
    int bufferSize = 256,
    int timeoutMs = 300,
  }) async {
    final buf = calloc<Uint8>(bufferSize);
    final lenPtr = calloc<Int32>()..value = bufferSize;

    final result = _serialportFFI.portRead(
      _serialPortSettings.portType.value,
      buf,
      lenPtr,
      timeoutMs,
    );

    if (result == -10) {
      return null;
    }

    if (result != 0) {
      throw SerialPortException(
        message: "Error al leer del puerto serial.",
        errorCode: result,
      );
    }

    final bytesRead = lenPtr.value;
    if (bytesRead <= 0) {
      return null;
    }

    final bytes = List.generate(bytesRead, (i) => buf[i]);

    calloc.free(buf);
    calloc.free(lenPtr);

    return Uint8List.fromList(bytes);
  }

  void _writePortInternal(Uint8List bytes) {
    final buf = calloc<Uint8>(bytes.length);
    try {
      for (var i = 0; i < bytes.length; i++) {
        buf[i] = bytes[i];
      }

      final result = _serialportFFI.portWrite(
        _serialPortSettings.portType.value,
        buf,
        bytes.length,
      );

      if (result != 0) {
        throw SerialPortException(
          message: "Error al enviar datos por el puerto serial.",
          errorCode: result,
        );
      }
    } finally {
      calloc.free(buf);
    }
  }

  void _closePortInternal() {
    final result = _serialportFFI.portClose(_serialPortSettings.portType.value);
    if (result != 0) {
      throw SerialPortException(
        message: "Error al cerrar el puerto serial.",
        errorCode: result,
      );
    }
  }
}

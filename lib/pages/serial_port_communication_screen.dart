import 'package:demo_p180_serialport/core/keypad/keypad.dart';
import 'package:demo_p180_serialport/core/serialport/ffi/utils/exception.dart';
import 'package:demo_p180_serialport/core/serialport/serialport.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class SerialPortCommunicationScreen extends StatefulWidget {
  const SerialPortCommunicationScreen({super.key, required this.portType});

  final CommunicationType portType;

  @override
  State<SerialPortCommunicationScreen> createState() =>
      _SerialPortCommunicationScreenState();
}

class _SerialPortCommunicationScreenState
    extends State<SerialPortCommunicationScreen> {
  late SerialPort _serialport;
  late String _status;

  final _focusNode = FocusNode();

  ///
  /// Stream para el puerto serial.
  ///
  late Stream<SerialPortEvent> _streamSerial;

  ///
  /// Cerrar la app.
  ///

  void _closeApp() {
    SystemChannels.platform.invokeMethod('SystemNavigator.pop');
  }

  ///
  /// Abrir puerto serial y obtener stream.
  ///
  void _openSerialPort() async {
    try {
      _serialport = SerialPort();
    } on FFIException catch (_) {
      _status = "No se encuentra el wrapper.so";
      return;
    }

    final settings = SerialportSettings(
      baudRate: BaudRateType.baud115200,
      dataBits: DataBitsType.data8,
      parityType: ParityType.parNone,
      portType: widget.portType,
      stopBits: StopBitsType.stop1,
    );

    try {
      _streamSerial = _serialport.open(settings);
      _status = "Puerto serial abierto. Escuchando...";
    } on SerialPortException catch (e) {
      _status = "Error al abrir puerto serial (${e.errorCode})";
      return;
    }

    try {
      await for (final event in _streamSerial) {
        final bytes = event.data;
        setState(() {
          _status = "Recibido: ${bytes.toString()}";
        });
      }
    } on SerialPortException catch (e) {
      setState(() {
        _status = "Error al escuhar puerto serial (${e.errorCode})";
      });
    }
  }

  ///
  /// Envia por puerto serial.
  ///

  Future<void> _sendDataToSerial() async {
    final bytes = Uint8List.fromList([0x31, 0x32, 0x33]); // 123

    try {
      _serialport.write(bytes);
      setState(() {
        _status = "Bytes enviados!";
      });
    } on SerialPortException catch (error) {
      setState(() {
        _status = "Error: ${error.message} code: ${error.errorCode}";
      });
    }
  }

  ///
  /// Control de teclado.
  ///
  void _handleSelectedOperation(int enteredDigit) async {
    switch (enteredDigit) {
      case 1:
        _sendDataToSerial();
        break;
      case 2:
        _closeSerial();
        break;
    }
  }

  @override
  void initState() {
    super.initState();
    _openSerialPort();
  }

  ///
  /// Cierre de puerto serial
  ///
  void _closeSerial() {
    _serialport.close();
    setState(() {
      _status = "Puerto cerrado";
    });
  }

  @override
  void dispose() {
    _serialport.close();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return RawKeyboardListener(
      focusNode: _focusNode,
      autofocus: true,
      onKey: rawKeypadHandler(
        context,
        onEscape: () {
          Navigator.of(context).pop();
        },
        onDigit: _handleSelectedOperation,
      ),
      child: Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: Text("Puerto Serial"),
          actions: [IconButton(onPressed: _closeApp, icon: Icon(Icons.logout))],
        ),
        body: Padding(
          padding: const EdgeInsets.all(16),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Text(
                _status,
                textAlign: TextAlign.center,
                style: TextStyle(fontSize: 20),
              ),
              const SizedBox(height: 64),
              ListTile(
                leading: CircleAvatar(child: Text('1')),
                title: Text("Enviar datos"),
              ),
              ListTile(
                leading: CircleAvatar(child: Text('2')),
                title: Text("Cerrar puerto"),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

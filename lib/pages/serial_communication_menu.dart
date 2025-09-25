import 'package:demo_p180_serialport/core/keypad/keypad.dart';
import 'package:demo_p180_serialport/core/serialport/serialport.dart';
import 'package:demo_p180_serialport/pages/serial_port_communication_screen.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

///
/// Mapear un label para cada tipo de conexión para la UI.
///

extension SerialPortLaels on CommunicationType {
  String get label {
    switch (this) {
      case CommunicationType.rs232:
        return "RS232";
      case CommunicationType.pinpad:
        return "PINPAD";
      case CommunicationType.wireless:
        return "Wireless";
      case CommunicationType.usbSerial:
        return "USB Serial";
      case CommunicationType.usbHost:
        return "USB Host";
      case CommunicationType.usbHostHid:
        return "USB Host HID";
      case CommunicationType.usbHostPrinter:
        return "USB Host Printer";
    }
  }
}

///
/// Tipos de puerto.
///

const _communicationTypes = [
  CommunicationType.pinpad,
  CommunicationType.rs232,
  CommunicationType.usbHost,
  CommunicationType.usbSerial,
];

class SerialCommunicationMenu extends StatefulWidget {
  const SerialCommunicationMenu({super.key});

  @override
  State<SerialCommunicationMenu> createState() =>
      _SerialCommunicationMenuState();
}

class _SerialCommunicationMenuState extends State<SerialCommunicationMenu> {
  final _focusNode = FocusNode();

  ///
  /// Cerrar la app.
  ///

  void _closeApp() {
    SystemChannels.platform.invokeMethod('SystemNavigator.pop');
  }

  ///
  /// Llamar a la pantalla de comunicacion serial dependiendo el tipo de puerto
  /// seleccionado.
  ///

  void _handleSelectedOperation(int enteredDigit) async {
    if (enteredDigit <= _communicationTypes.length) {
      CommunicationType selectedPortType =
          _communicationTypes[enteredDigit - 1];

      Navigator.of(context).push(
        MaterialPageRoute(
          builder: (ctx) =>
              SerialPortCommunicationScreen(portType: selectedPortType),
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return RawKeyboardListener(
      focusNode: _focusNode,
      autofocus: true,
      onKey: rawKeypadHandler(
        context,
        onEscape: _closeApp,
        onDigit: _handleSelectedOperation,
      ),
      child: Scaffold(
        appBar: AppBar(
          title: Text("Puerto Serial"),
          actions: [IconButton(onPressed: _closeApp, icon: Icon(Icons.logout))],
        ),
        body: Padding(
          padding: const EdgeInsets.all(4.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                "Tipo de puerto: ",
                textAlign: TextAlign.center,
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
              ),
              const SizedBox(height: 16),
              Expanded(
                child: ListView.builder(
                  itemCount: _communicationTypes.length,
                  itemBuilder: (context, index) {
                    return ListTile(
                      leading: CircleAvatar(child: Text('${index + 1}')),
                      title: Text(_communicationTypes[index].label),
                    );
                  },
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

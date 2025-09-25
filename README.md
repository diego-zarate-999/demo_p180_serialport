# demo_p180_serialport

FFI para mapear las funciones de puerto serial de NAPI en Flutter.

## Funciones NAPI que fueron mapeadas.
- NAPI_ERR_CODE  NAPI_PortOpen (PORT_TYPE PortType, const PORT_SETTINGS PortSettings)
- NAPI_ERR_CODE  NAPI_PortFlush (PORT_TYPE PortType)
- NAPI_ERR_CODE  NAPI_PortRead (PORT_TYPE PortType, unsigned char *OutBuf, int *OutBufLen, int TimeoutInMs)
- NAPI_ERR_CODE  NAPI_PortWrite (PORT_TYPE PortType, const unsigned char *InBuf, int InBufLen)
- NAPI_ERR_CODE  NAPI_PortReadLen (PORT_TYPE PortType, int *OutBufLen) 
- NAPI_ERR_CODE  NAPI_PortClose (PORT_TYPE PortType)

También se mapearon los **enums** y **structs** correspondietes.

## Uso de la FFI.
Mediante el Sigleton **serialport/ffi/serialport.dart** se exponen las funciones de puerto serial. Se debe seguir el flujo siguiente:

1. **Abrir el puerto**. Esto se logra llamando al método **open(SerialportSettings settings)** el cual espera recibir la configuración que se desea para el puerto serial y devuelve un stream mediante el que se pueden escuchar los eventos del puerto para recibir datos.

    **Ejemplo:**

```dart
    final settings = SerialportSettings(
        communicationType: widget.communicationType,
        baudRate: BaudRateType.baud115200,
        dataBits: DataBitsType.data8,
        parityType: ParityType.parNone,
        portType: widget.communicationType,
        stopBits: StopBitsType.stop1,
        );
    
    try {
      _streamSerial = SerialPort().open(settings);
    } on SerialPortException catch (error) {
        print(error);
    }
```

2. **Leer datos**. Para leer los datos que llegan al puerto se utiliza el stream btenido al abrir el puerto serial.

    **Ejemplo:**

```dart
    await for (final event in _streamSerial) {
        final data = event.data; // Datos recibidos.
    }
```

3. **Escritura**. El método **write** permite el envio de datos a traves del puerto serial. Es importante abrir el puerto previamente.

    **Ejemplo:**

```dart
    final data = [1,2,4];
    try {
      SerialPort().write(data);
    } on SerialPortException catch (error) {
        print(error);
    }
```

4. **Cierre del puerto**. El método **close** permite terminar el puerto.

    **Ejemplo:**

```dart
    SerialPort().close();
```

## Manejo de Errores

Las funciones anteriores arrojan un **SerialPortExepction** en caso de que algo haya fallado:

```dart
class SerialPortException implements Exception {
  final String message;
  final int errorCode;

  const SerialPortException({required this.message, required this.errorCode});
}
```

Aquí se retorna el código de error arrojado por **NAPI** (Vease documentación de NAPI):
| Código de error | Descripción |
| :--- | :--- |
| NAPI_OK | Success |
| NAPI_ERR | Fail |
| NAPI_ERR_INIT_CONFIG | Failed to initialize configuration |
| NAPI_ERR_CREAT_WIDGET | Failed to error creating interface |
| NAPI_ERR_OPEN_DEV | Failed to error opening device file |
| NAPI_ERR_IOCTL | Failed to call driver function |
| ... | ... |

## ¿Cómo se hizo el mapeo?
En **native/serialport** podemos encontrar lo siguiente:
- **include/**: Headers de la libreria de napi para puerto serial y header del wrapper que se encarga de exponer las funciones a la FFI de flutter.
- **lib/**: Los **.so** de la libreria de napi y del wrapper una vez se ha compilado.
- **src/**: La definición del wrapper para llamar a las funciones correspondientes de NAPI.

**Nota:** Para generar el **serial_wrapper.so** se utilizó **MakeFile** incluido en este proyecto.

### Agnostiko scripts.

Para compilar el proyecto se modificaron los scripts de agnostiko para incluir el **serialportwrapper.so** al momento de empaquetar el **.NLD** y que pueda estar disponible para **FFI**. Los cambios hechos fueron:

#### build_for_linux.dart
```dart
final serialWrapper = File("assets/lib/libserial_wrapper.so");
  if (await serialWrapper.exists()) {
    final destFile = File(path.join(buildDir.path, "libserial_wrapper.so"));
    await serialWrapper.copy(destFile.path);
    print("libserial_wrapper.so copiado a build/");
  } else {
    print("Advertencia: assets/lib/libserial_wrapper.so no encontrado");
  }

```

#### build_nld.dart
```dart
// Al momento de empaquetar el archivo.
await File('./build/filepath.txt').writeAsString("""build\\flutter_assets
build\\embedder
build\\icudtl.dat
build\\roboto.ttf
build\\app.so	$version	private
build\\libflutter_engine.so 	$version	private
build\\libmdb.so 	$version	private
build\\libstm32down.so 	$version	private
build\\libserial_wrapper.so 	$version	private
build\\libemvl3.so 	$version	private""");
```

Finalmente, dentro de **serialport/ffi/serialport_ffi.dart** es donde se hace el binding de las funciones delm wrapper hacia flutter. Se puede aprender más sobre el fujo FFI aquí: [FFI Flutter](https://medium.com/@chetan.akarte/what-is-ffi-in-dart-c2f4fab4c619).
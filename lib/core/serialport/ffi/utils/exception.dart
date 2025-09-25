class SerialPortException implements Exception {
  final String message;
  final int errorCode;

  const SerialPortException({required this.message, required this.errorCode});
}

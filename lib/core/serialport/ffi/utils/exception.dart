class SerialPortException implements Exception {
  final String message;
  final int errorCode;

  const SerialPortException({required this.message, required this.errorCode});
}

class FFIException implements Exception {
  final String message;
  final int errorCode;

  const FFIException({required this.message, required this.errorCode});
}

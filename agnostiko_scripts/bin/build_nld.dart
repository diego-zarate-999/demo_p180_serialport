import 'dart:io';

import './build_for_linux.dart';

void main(List<String> args) {
  buildNLD(args);
}

Future<void> buildNLD(List<String> args) async {
  final parser = linuxBuildParser
    ..addOption('app-name', help: 'nombre de la app a compilar')
    ..addOption('version', help: 'version de la app')
    ..addOption(
      'company-name',
      help: 'nombre de la empresa que compila la app',
    );
  try {
    final results = parser.parse(args);
    final appName = results.option('app-name');
    final version = results.option('version');
    final companyName = results.option('company-name');
    if (appName == null || version == null || companyName == null) {
      throw StateError("faltan argumentos");
    }
    await runFlutterLinuxBuild(args);
    await packageNLD(appName, version, companyName);
  } catch (e, stackTrace) {
    print("\n$e");
    print(stackTrace);
    print("USO:");
    print(parser.usage);
  }
}

Future<void> packageNLD(
  String appName,
  String version,
  String companyName,
) async {
  if (!Platform.environment.containsKey("NPT_ROOT")) {
    print(
      "La variable de entorno 'NPT_ROOT' no esta definida! Debe "
      "definir la ruta de su instalación del SDK de Newland.",
    );
    throw StateError("missing NPT_ROOT env variable");
  }

  print("Generando configuración de instalador...");
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

  final now = DateTime.now();
  final year = now.year;
  final month = now.month.toString().padLeft(2, '0');
  final day = now.day.toString().padLeft(2, '0');
  await File('./build/param.ini').writeAsString("""[param]
Name = $appName
RootAppFlag = 0 
Version = $version
Main = embedder
Icon = 
MasterApp = 0 
ReleaseDate = $year$month$day
Company = $companyName
PackType = F""");

  print("Empaquetando instalador...");
  var result = await Process.run(
    '%NPT_ROOT%\\Common\\tools\\Package_Generator\\pkgNLD\\upt.exe',
    [
      "-h",
      ".\\build\\filepath.txt",
      "-p",
      ".\\build\\param.ini",
      "-o",
      "$appName-$version.NLD",
    ],
    runInShell: true,
  );
  stdout.write(result.stdout);
  stderr.write(result.stderr);
}

import 'dart:convert';
import 'dart:io';

import 'package:args/args.dart';
import 'package:path/path.dart' as path;

final linuxBuildParser =
    ArgParser()..addFlag(
      'debug',
      abbr: 'd',
      help: 'habilita el modo debug (sin ofuscamiento)',
    );

void main(List<String> args) {
  runFlutterLinuxBuild(args);
}

Future<void> runFlutterLinuxBuild(List<String> args) async {
  try {
    final results = linuxBuildParser.parse(args);
    final isDebug = results.flag('debug');
    await _buildFlutterAppForLinux(isDebug);
  } catch (e, stackTrace) {
    print("\n$e");
    print(stackTrace);
    print("USO:");
    print(linuxBuildParser.usage);
  }
}

Future<void> _buildFlutterAppForLinux(bool isDebug) async {
  if (!Platform.environment.containsKey("FLUTTER_ROOT")) {
    print(
      "La variable de entorno 'FLUTTER_ROOT' no esta definida! Debe "
      "definir la ruta de su instalación de Flutter en dicha variable.",
    );
    throw StateError("missing FLUTTER_ROOT env variable");
  }

  final packageFilePath = ".dart_tool/package_config.json";
  final jsonFile = await File(packageFilePath).readAsString();
  final packageJson = jsonDecode(jsonFile) as Map<String, dynamic>;
  final packages = packageJson['packages'] as List<dynamic>;
  final agnostikoData =
      packages.firstWhere((el) {
            final packageData = el as Map<String, dynamic>;
            return packageData['name'] == 'agnostiko';
          })
          as Map<String, dynamic>;
  final rootUri = agnostikoData['rootUri'] as String;

  // buscamos la ruta del agnostiko descargado
  // si la ruta es absoluta tiene este prefijo
  var agnostikoPath = rootUri.replaceFirst("file:///", "");
  if (agnostikoPath.startsWith("../")) {
    // si la ruta es relativa hay que quitarle la primera parte
    agnostikoPath = agnostikoPath.replaceFirst("../", "");
  }
  print(agnostikoPath);

  print("Limpiando...");
  var result = await Process.run('flutter', ['clean'], runInShell: true);
  stdout.write(result.stdout);
  stderr.write(result.stderr);

  print("Sincronizando paquetes...");
  result = await Process.run('flutter', ['pub', 'get'], runInShell: true);
  stdout.write(result.stdout);
  stderr.write(result.stderr);

  print("Preparando directorio de compilación...");
  final buildDir = Directory("build");
  await buildDir.create();
  await copyDirectory(
    Directory('$agnostikoPath/embedders/bin'),
    Directory('build'),
  );

  final serialWrapper = File("native/serialport/lib/libserial_wrapper.so");
  if (await serialWrapper.exists()) {
    final destFile = File(path.join(buildDir.path, "libserial_wrapper.so"));
    await serialWrapper.copy(destFile.path);
    print("libserial_wrapper.so copiado a build/");
  } else {
    print("Advertencia: assets/lib/libserial_wrapper.so no encontrado");
  }

  print("Compilando código dart...");
  result = await Process.run(
    "%FLUTTER_ROOT%\\bin\\cache\\dart-sdk\\bin\\dartaotruntime.exe",
    [
      "--disable-dart-dev",
      "%FLUTTER_ROOT%\\bin\\cache\\dart-sdk\\bin\\snapshots\\frontend_server_aot.dart.snapshot",
      "--sdk-root",
      "%FLUTTER_ROOT%\\bin\\cache\\artifacts\\engine\\common\\flutter_patched_sdk_product/",
      "--target=flutter",
      "--no-print-incremental-dependencies",
      "-Ddart.vm.profile=false",
      "-Ddart.vm.product=true",
      "--aot",
      "--tfa",
      "--packages",
      ".\\.dart_tool\\package_config.json",
      "--output-dill",
      ".\\build\\app.dill",
      "--depfile",
      ".\\build\\kernel_snapshot.d",
      ".\\lib\\main.dart",
    ],
    runInShell: true,
  );
  stdout.write(result.stdout);
  stderr.write(result.stderr);

  print("Generando snapshot...");
  List<String> snapArgs = [
    "./build/gen_snapshot",
    "--snapshot_kind=app-aot-elf",
    "--elf=./build/app.so",
    "--deterministic",
  ];
  if (!isDebug) {
    snapArgs.addAll(["--obfuscate", "--strip"]);
  }
  snapArgs.addAll([
    "--no-sim-use-hardfp",
    "--no-use-integer-division",
    "--no-use-neon",
    "--no-enable-simd-inline",
    "./build/app.dill",
  ]);
  result = await Process.run("wsl.exe", snapArgs, runInShell: true);
  stdout.write(result.stdout);
  stderr.write(result.stderr);

  print("Generando bundle...");
  result = await Process.run("flutter", [
    "build",
    "bundle",
    "--release",
    "--no-tree-shake-icons",
  ], runInShell: true);
  stdout.write(result.stdout);
  stderr.write(result.stderr);

  print("Borrando archivos innecesarios...");
  await File("./build/app.dill").delete();
  await File("./build/gen_snapshot").delete();
  await File("./build/kernel_snapshot.d").delete();
}

Future<void> copyDirectory(Directory source, Directory destination) async {
  await source.list(recursive: false).forEach((var entity) async {
    if (entity is Directory) {
      var newDirectory = Directory(
        path.join(destination.absolute.path, path.basename(entity.path)),
      );
      await newDirectory.create();

      await copyDirectory(entity.absolute, newDirectory);
    } else if (entity is File) {
      await entity.copy(
        path.join(destination.path, path.basename(entity.path)),
      );
    }
  });
}

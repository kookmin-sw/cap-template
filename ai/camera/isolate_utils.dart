import 'dart:async';
import 'dart:isolate';
import 'package:camera/camera.dart';
import 'package:image/image.dart' as imageLib;
import 'package:pradtice/camera/classifier.dart';
import 'package:tflite_flutter/tflite_flutter.dart';
import 'image_utils.dart';

class IsolateUtils {
  Isolate? _isolate;
  ReceivePort _receivePort = ReceivePort();
  SendPort? _sendPort;
  SendPort? get sendPort => _sendPort;
  // Isolate 시작
  Future<void> start() async {
    _isolate = await Isolate.spawn<SendPort>(entryPoint, _receivePort.sendPort);
    _sendPort = await _receivePort.first;
  }
  // Isolate의 entryPoint 함수
  static void entryPoint(SendPort sendPort) async {
    final port = ReceivePort();
    sendPort.send(port.sendPort);
    // 전달받은 데이터를 사용하여 분류 및 추론 수행
    await for (final IsolateData isolateData in port) {
      Classifier classifier = Classifier(
          interpreter: Interpreter.fromAddress(isolateData.interpreterAddress),
          labels: isolateData.labels);
      imageLib.Image? image =
      ImageUtils.convertCameraImage(isolateData.cameraImage);
      image = imageLib.copyRotate(image!, 90);
      Map<String, dynamic>? results = classifier.predict(image);
      isolateData.responsePort?.send(results);
    }
  }
}
// Isolate 간에 전달할 데이터 class
class IsolateData {
  CameraImage cameraImage;
  int interpreterAddress;
  List<String> labels;
  SendPort? responsePort;

  IsolateData(
      this.cameraImage,
      this.interpreterAddress,
      this.labels,
      );
}
import 'dart:math';
import 'package:flutter/cupertino.dart';
import 'package:pradtice/camera/camera_settings.dart';

class Recognition {
  // 인식된 객체의 ID 저장
  final int? _id;
  // 인식된 객체의 레이블 저장
  final String? _label;
  // 인식된 객체의 확률(신뢰도) 저장
  final double? _score;
  // 인식된 객체의 위치 저장
  final Rect? _location;
  // Recognition 클래스 생성자
  Recognition(
      this._id,
      this._label,
      this._score, [
        this._location,
      ]);
  // 각 변수에 대한 getter
  int? get id => _id;
  String? get label => _label;
  double? get score => _score;
  Rect? get location => _location;
  // 객체의 위치를 화면에 맞게 변환하여 반환
  Rect get renderLocation {
    // 카메라 설정에서 비율 값
    double? ratioX = CameraSettings.ratio;
    double? ratioY = ratioX;
    // 위치 정보를 변환하여 좌표로 계산
    double transLeft = max(
      0.1,
      (location?.left ?? 0) * (ratioX ?? 0),
    );
    double transTop = max(
      0.1,
      (location?.top ?? 0) * (ratioY ?? 0),
    );
    double transWidth = min(
      (location?.width ?? 0) * (ratioX ?? 0),
      CameraSettings.actualPreviewSize.width,
    );
    double transHeight = min(
      (location?.height ?? 0) * (ratioY ?? 0),
      CameraSettings.actualPreviewSize.height,
    );
    // 변환된 위치 정보를 생성하여 반환
    Rect transformedRect = Rect.fromLTWH(
      transLeft,
      transTop,
      transWidth,
      transHeight,
    );
    return transformedRect;
  }
}
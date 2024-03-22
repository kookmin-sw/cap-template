import 'package:flutter/material.dart';
import 'package:pradtice/camera/recognition.dart';

class BoxWidget extends StatelessWidget {
  final Recognition result;
  // BoxWidget 생성자
  const BoxWidget({Key? key, required this.result}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    // 결과에 따라 색상을 설정
    Color color = Colors.primaries[((result.label?.length ?? 0) +
        result.label!.codeUnitAt(0) +
        (result.id ?? 0)) %
        Colors.primaries.length];
    // Positioned 위젯을 사용하여 인식된 객체의 위치와 크기를 설정
    return Positioned(
      left: result.renderLocation.left,
      top: result.renderLocation.top,
      width: result.renderLocation.width,
      height: result.renderLocation.height,
      child: Container(
        width: result.renderLocation.width,
        height: result.renderLocation.height,
        // 경계 상자의 테두리
        decoration: BoxDecoration(
          border: Border.all(color: color, width: 3),
        ),
        child: Align(
          alignment: Alignment.topLeft,
          child: FittedBox(
            // 인식된 객체의 레이블과 확률 표시
            child: Container(
              color: color,
              child: Row(
                mainAxisSize: MainAxisSize.min,
                children: <Widget>[
                  Text('${result.label}  ${result.score!.toStringAsFixed(2)}'),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}
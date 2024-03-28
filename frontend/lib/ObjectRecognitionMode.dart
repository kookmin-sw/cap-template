import 'package:flutter/material.dart';
import 'package:pradtice/camera/recognition.dart';
import 'package:pradtice/camera/box_widget.dart';
import 'package:pradtice/camera/camera_settings.dart';
import 'camera/camera_view.dart';
import 'location_permission.dart';
import 'package:permission_handler/permission_handler.dart';

class ObjectRecognitionMode extends StatefulWidget {
  const ObjectRecognitionMode({Key? key}) : super(key: key);

  @override
  _ObjectRecognitionModeState createState() => _ObjectRecognitionModeState();
}

class _ObjectRecognitionModeState extends State<ObjectRecognitionMode> {
  /// Results to draw bounding boxes
  List<Recognition>? results;

  /// Realtime stats
  int totalElapsedTime = 0;

  /// Scaffold Key
  GlobalKey<ScaffoldState> scaffoldKey = GlobalKey();

  /// 위치 권한 설정
  MyLocation myLocation = MyLocation();

  // 위치 추적 상태를 관리하는 새로운 변수
  bool isTrackingLocation = true;

  // UI 업데이트를 위한 콜백 함수
  Function? onUpdate;

  /// 카메라 권한 설정
  camera_Permission() async {
    var status = await Permission.camera.status;

    if (status.isGranted) {
      print('허락됨');
    }
    else if (status.isDenied) {
      print('거절됨');
      Permission.contacts.request();
    }
  }

  // 위치 추적 상태를 변경하는 메소드
  void toggleLocationTracking() {
    isTrackingLocation = !isTrackingLocation;
    if (isTrackingLocation) {
      myLocation.getMyCurrentLocation();
    } else {
      print('위치 추적 종료');
      // 추가적으로 위치 추적을 종료하는 로직을 구현하세요.
    }
    // UI 업데이트를 위한 콜백 함수 호출
    onUpdate?.call();
  }

  @override
  void initState() {
    super.initState();
    if (isTrackingLocation) {
      myLocation.getMyCurrentLocation();
    }
    camera_Permission();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: scaffoldKey,
      appBar: AppBar(
          backgroundColor: Colors.black,
          title: const Text(
            '객체 인식 모드',
            style: TextStyle(
                fontWeight: FontWeight.w600, color: Colors.white, fontSize: 15),
          ),
          actions : [
            IconButton(onPressed: (){ toggleLocationTracking; }, icon : Icon(Icons.location_on)),
            IconButton(onPressed: (){ camera_Permission(); }, icon : Icon(Icons.photo_camera)),
          ]
      ),
      body: Stack(
        children: [
          CameraView(resultsCallback, updateElapsedTimeCallback),

          /// 사진,위치 권한 아이콘 실행시 허가 기능 (미완성)
          // Align(
          //   alignment: Alignment.bottomRight, // 하단 우측에 배치
          //   child: Padding(
          //     padding: const EdgeInsets.all(16.0), // 여백을 주어 가장자리와의 간격을 조정
          //     child: IconButton(
          //       icon: Icon(Icons.contacts),
          //       onPressed: () {
          //         myLocation.getMyCurrentLocation();
          //       },
          //     ),
          //   ),
          // ),

          boundingBoxes(results),
          Align(
            alignment: Alignment.bottomCenter,
            // SingleChildScrollView() -> 단일 자식만 가질수 있음
            child: SingleChildScrollView(
              child:
              Column(
                children: [
                  resultsList(results),
                  Padding(
                    padding: const EdgeInsets.all(10.0),
                    child:
                    Column(
                      children: [
                        statsRow('이미지 추론 시간:', '$totalElapsedTime ms'),
                        statsRow('이미지 크기',
                            '${CameraSettings.inputImageSize?.width} X ${CameraSettings.inputImageSize?.height}'),
                      ],
                    ),
                  )
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }

  /// Returns Stack of bounding boxes
  Widget boundingBoxes(List<Recognition>? results) {
    if (results == null) {
      return Container();
    }
    return Stack(
      children: results
          .map((e) => BoxWidget(
        result: e,
      ))
          .toList(),
    );
  }

  Widget resultsList(List<Recognition>? results) {
    if (results == null) {
      return Container();
    }
    return SizedBox(
      height: 120,
      child: ListView.builder(
        shrinkWrap: true,
        physics: ClampingScrollPhysics(),
        itemCount: results.length,
        itemBuilder: (context, index) {
          return Container(
            height: 20,
            child: ListTile(
              title: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text('${(index + 1)}. 객체명: ${results[index].label}',
                      style: TextStyle(fontSize: 13)),
                  Text(
                      '예츨확률: ${(results[index].score! * 100).toStringAsFixed(1)} %',
                      style: TextStyle(fontSize: 13)),
                ],
              ),
            ),
          );
        },
      ),
    );
  }

  /// Callback to get inference results from [CameraView]
  void resultsCallback(List<Recognition> results) {
    setState(() {
      this.results = results;
    });
  }

  void updateElapsedTimeCallback(int elapsedTime) {
    setState(() {
      totalElapsedTime = elapsedTime;
    });
  }
}

/// Row for one Stats field
Padding statsRow(left, right) {
  return Padding(
    padding: const EdgeInsets.only(bottom: 10.0),
    child: Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [Text(left), Text(right)],
    ),
  );
}

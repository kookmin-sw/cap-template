import 'dart:async'; // Timer를 사용하기 위해 필요합니다.
import 'package:geolocator/geolocator.dart';
import 'package:permission_handler/permission_handler.dart';

class MyLocation {
  late double latitude;
  late double longitude;

  Future<void> getMyCurrentLocation() async {
    // 위치권한을 가지고 있는지 확인
    var status_position = await Permission.location.status;

    if (status_position.isGranted) {
      // 권한이 있는 경우, 10초마다 위치 정보를 출력합니다.
      Timer.periodic(Duration(seconds: 10), (Timer t) async {
        Position position = await Geolocator.getCurrentPosition(desiredAccuracy: LocationAccuracy.high);

        latitude = position.latitude;
        longitude = position.longitude;

        print("위도: $latitude , 경도: $longitude");
      });
    } else {
      // 권한이 없는 경우
      print("위치 권한이 필요합니다.");

      // 위치 권한 요청
      var status_position_request = await Permission.location.request();

      // 사용자가 권한을 허용한 경우
      if (status_position_request.isGranted) {
        Timer.periodic(Duration(seconds: 10), (Timer t) async {
          Position position = await Geolocator.getCurrentPosition(desiredAccuracy: LocationAccuracy.high);

          latitude = position.latitude;
          longitude = position.longitude;

          print("위도: $latitude , 경도: $longitude");
        });
      } else {
        // 사용자가 권한을 거부한 경우
        print("위치 권한이 거부되었습니다.");
      }
    }
  }

}

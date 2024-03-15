import 'package:geolocator/geolocator.dart';
import 'package:permission_handler/permission_handler.dart';

class MyLocation {
  late double latitude;
  late double longitude;

  Future<void> getMyCurrentLocation() async {
// 위치권한을 가지고 있는지 확인
    var status_position = await Permission.location.status;

    if (status_position.isGranted) {
      // 권한이 있는 경우 위치정보를 받아와서 변수에 저장합니다.
      Position position = await Geolocator.getCurrentPosition(
          desiredAccuracy: LocationAccuracy.high);

      latitude = position.latitude;
      longitude = position.longitude;

      print("위도: $latitude , 경도: $longitude");
    } else {
      // 권한이 없는 경우
      print("위치 권한이 필요합니다.");

      // 위치 권한 요청
      var status_position_request = await Permission.location.request();

      // 사용자가 권한을 허용한 경우
      if (status_position_request.isGranted) {
        Position position = await Geolocator.getCurrentPosition(
            desiredAccuracy: LocationAccuracy.high);

        latitude = position.latitude;
        longitude = position.longitude;

        print("위도: $latitude , 경도: $longitude");
      } else {
        // 사용자가 권한을 거부한 경우
        print("위치 권한이 거부되었습니다.");
      }
    }
  }
}
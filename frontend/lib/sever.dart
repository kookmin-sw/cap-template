//메인.dart에도 밑의 2개 패키지 설치 요함
import 'package:http/http.dart' as http; // http 사용 패키지
import 'dart:convert'; //json 변환 패키지

class Sever {

// 서버 http get 함수
  getData() async {
    String address = Uri.encodeComponent("서울시 강남구 역삼동");
    var result = await http.get(
        Uri.parse('http://15.164.219.111:8080/test?address="도로명주소"'));

    if (result.statusCode == 200) {
      print(jsonDecode(result.body));
    } else {
      throw Exception('데이터 가져오기 실패');
    }
  }


  postData() {

  }
}

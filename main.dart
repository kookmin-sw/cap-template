import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _tapCount = 0;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        setState(() {
          _tapCount++;
          if (_tapCount == 1) {
            Navigator.push(
              context,
              MaterialPageRoute(builder: (context) => ObjectRecognitionMode()),
            );
          } else if (_tapCount == 2) {

            Navigator.push(
              context,
              MaterialPageRoute(builder: (context) => ConvenienceMode()),
            );
            _tapCount = 0;
          }
        });
      },
      child: Scaffold(
        appBar: AppBar(
          title: Text('메인 화면'),
        ),
        body: Center(
          child: Text('화면을 탭하세요', style: TextStyle(fontSize: 30)), // 텍스트 사이즈 조정
        ),
      ),
    );
  }
}

class ObjectRecognitionMode extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('물체인식 모드'),
      ),
      body: Center(
        child: Text('여기에 물체인식 모드의 기능을 구현해주세요.'),
      ),
    );
  }
}

class ConvenienceMode extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('편의 기능 모드'),
      ),
      body: Center(
        child: Text('여기에 편의 기능 모드의 기능을 구현해주세요.'),
      ),
    );
  }
}

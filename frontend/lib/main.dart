import 'package:flutter/material.dart';
import 'package:frontend/common/view/root_tab.dart';

void main() {
  runApp(const _App());
}

class _App extends StatelessWidget {
  const _App({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
        fontFamily: 'NotoSans',
        primarySwatch: Colors.purple,
      ),
      home: RootTab(initialIndex: 0),
    );
  }
}

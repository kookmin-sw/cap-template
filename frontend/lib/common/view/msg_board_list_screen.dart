import 'package:flutter/material.dart';
import 'package:frontend/common/const/msg_board_model.dart';
import 'package:frontend/common/layout/board_layout.dart';

class MsgBoardListScreen extends StatefulWidget {
  final String category;
  const MsgBoardListScreen({
    super.key,
    required this.category,
  });

  @override
  State<MsgBoardListScreen> createState() => _MsgBoardListScreenState();
}

class _MsgBoardListScreenState extends State<MsgBoardListScreen> {
  // late Future<List<MsgBoardListModel>> boards;
  List<MsgBoardModel> msgboardlistinstance = [];

  @override
  void initState() {
    super.initState();
    // TODO: add board = http

    msgboardlistinstance.add(MsgBoardModel(
      "1",
      "인기글",
      "종강마렵다",
      "ㅈㄱㄴssssssssssssssssssssssssssssssssssssssssssssssssssdddddddddddd",
      "20",
      "3",
      "0",
      "24/03/04 13:45",
      "익명",
    ));
    msgboardlistinstance.add(MsgBoardModel(
      "2",
      "인기글",
      "종강종강",
      "종강종강종강종강",
      "15",
      "2",
      "0",
      "24/03/04 14:45",
      "익명",
    ));
    msgboardlistinstance.add(MsgBoardModel(
      "3",
      "인기글",
      "토끼는 깡종강종강",
      "거북이도 종강종강",
      "10",
      "4",
      "0",
      "24/03/04 15:45",
      "익명",
    ));
    msgboardlistinstance.add(MsgBoardModel(
      "4",
      "인기글",
      "교수님 정강이 때릴 사람 구합니다.",
      "아이고 종강이야",
      "5",
      "3",
      "0",
      "24/03/04 16:45",
      "익명",
    ));
    msgboardlistinstance.add(MsgBoardModel(
      "5",
      "인기글",
      "슬슬 종강할 때 되지 않았나",
      "눈치껏 종강하자",
      "6",
      "2",
      "0",
      "24/03/04 17:45",
      "익명",
    ));
    msgboardlistinstance.add(MsgBoardModel(
      "6",
      "인기글",
      "그냥 종강좀 해라",
      "이만큼 했음 됬지 않늬",
      "3",
      "1",
      "0",
      "24/03/04 18:45",
      "익명",
    ));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          widget.category,
          style: const TextStyle(
            fontSize: 16,
          ),
        ),
      ),
      body: ListView(
        children: [
          for (var board in msgboardlistinstance)
            Board(
              board: board,
              canTap: true,
            )
        ],
      ),
      // body: SingleChildScrollView(
      //   child: Padding(
      //     padding: const EdgeInsets.symmetric(
      //       horizontal: 50,
      //       vertical: 50,
      //     ),
      //     child: FutureBuilder(
      //       future: boards,
      //       builder: (context, snapshot) {
      //         if (snapshot.hasData) {
      //           return const Column(
      //             children: [
      //               // TODO : Future
      //               // for(var board in snapshot.data!)
      //               //   board.category
      //             ],
      //           );
      //         }
      //         return const Center(child: Text("..."));
      //       },
      //     ),
      //   ),
      // ),
    );
  }
}

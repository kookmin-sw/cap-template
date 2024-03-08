import 'package:flutter/material.dart';
import 'package:frontend/common/const/colors.dart';
import 'package:frontend/common/const/comment_model.dart';
import 'package:frontend/common/layout/text_with_icon.dart';

class Comment extends StatelessWidget {
  final CommentModel comment;
  // TODO: comment of comment
  const Comment({super.key, required this.comment});

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        border: Border(
          bottom: BorderSide(
            color: BODY_TEXT_COLOR.withOpacity(0.5),
            width: 1,
          ),
        ),
      ),
      margin: const EdgeInsets.symmetric(horizontal: 10),
      child: Padding(
        padding: const EdgeInsets.symmetric(
          horizontal: 10,
          vertical: 8,
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Text(
                  comment.name,
                  style: const TextStyle(
                    fontSize: 12,
                    fontWeight: FontWeight.bold,
                  ),
                ),
                Container(
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(50),
                    color: BODY_TEXT_COLOR.withOpacity(0.1),
                  ),
                  child: Padding(
                    padding:
                        const EdgeInsets.symmetric(horizontal: 10, vertical: 3),
                    child: Row(
                      children: [
                        TextWithIcon(
                          icon: Icons.favorite_outline_rounded,
                          iconSize: 15,
                          text: comment.heart,
                        ),
                        const SizedBox(
                          width: 13,
                        ),
                        const Icon(
                          Icons.chat_outlined,
                          size: 15,
                        ),
                      ],
                    ),
                  ),
                ),
              ],
            ),
            Text(
              comment.content,
              style: const TextStyle(
                fontSize: 10,
              ),
            ),
          ],
        ),
      ),
    );
  }
}

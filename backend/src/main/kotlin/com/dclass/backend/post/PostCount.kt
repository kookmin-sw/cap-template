package com.dclass.backend.post

import jakarta.persistence.Embeddable

@Embeddable
class PostCount(
    val viewCount: Int = 0,
    val likeCount: Int = 0,
    val replyCount: Int = 0
) {
    fun increaseViewCount() = PostCount(viewCount + 1, likeCount, replyCount)
    fun increaseLikeCount() = PostCount(viewCount, likeCount + 1, replyCount)
    fun increaseReplyCount() = PostCount(viewCount, likeCount, replyCount + 1)
}
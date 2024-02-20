package com.dclass.backend.reply

import jakarta.persistence.CollectionTable
import jakarta.persistence.ElementCollection
import jakarta.persistence.Embeddable
import jakarta.persistence.FetchType

@Embeddable
class ReplyLikes(
    likes: List<ReplyLike> = emptyList()
) {
    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(name = "reply_likes")
    private val _likes: MutableList<ReplyLike> = likes.toMutableList()

    val likes: List<ReplyLike>
        get() = _likes

    val count: Int
        get() = _likes.size

    fun add(userId: Long, replyId: Long) {
        _likes.removeIf { it.userId == userId && it.replyId == replyId }
        _likes.add(ReplyLike(userId, replyId))
    }

    fun findUserById(userId: Long): Boolean {
        return _likes.any { it.userId == userId }
    }
}
package com.dclass.backend.comment

import jakarta.persistence.CollectionTable
import jakarta.persistence.ElementCollection
import jakarta.persistence.Embeddable
import jakarta.persistence.FetchType

@Embeddable
class CommentLikes(
    likes: List<CommentLike> = emptyList()
) {
    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(name = "comment_likes")
    private val _likes: MutableList<CommentLike> = likes.toMutableList()

    val likes: List<CommentLike>
        get() = _likes

    val count: Int
        get() = _likes.size

    fun add(userId: Long, commentId: Long) {
        _likes.removeIf { it.userId == userId && it.commentId == commentId }
        _likes.add(CommentLike(userId, commentId))
    }

    fun findUserById(userId: Long) =
        _likes.any { it.userId == userId }
}
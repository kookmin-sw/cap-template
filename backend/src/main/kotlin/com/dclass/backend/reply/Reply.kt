package com.dclass.backend.reply

import com.dclass.support.domain.BaseEntity
import jakarta.persistence.Column
import jakarta.persistence.Embedded
import jakarta.persistence.Entity
import org.hibernate.annotations.SQLDelete
import org.hibernate.annotations.SQLRestriction

@SQLDelete(sql = "update reply set deleted = true where id = ?")
@SQLRestriction("deleted = false")
@Entity
class Reply(
    @Column(nullable = false)
    val userId: Long,

    @Column(nullable = false)
    val commentId: Long,

    content: String = "",

    replyLikes: ReplyLikes = ReplyLikes(),

    id: Long = 0L
) : BaseEntity(id) {

    @Column(nullable = false)
    private var deleted: Boolean = false

    @Column(nullable = false, length = 255)
    var content: String = content
        private set

    @Embedded
    var replyLikes: ReplyLikes = replyLikes
        private set

    val likeCount: Int
        get() = replyLikes.count

    fun likedBy(userId: Long) =
        replyLikes.findUserById(userId)

    fun addLike(userId: Long) {
        replyLikes.add(userId, this.id)
    }
}
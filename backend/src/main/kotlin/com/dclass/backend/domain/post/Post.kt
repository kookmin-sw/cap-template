package com.dclass.backend.domain.post

import com.dclass.support.domain.BaseEntity
import com.dclass.support.domain.Image
import jakarta.persistence.*
import java.time.LocalDateTime

@Entity
@Table
class Post(
    @Column(nullable = false)
    val userId: Long,

    @Column(nullable= false)
    val communityId: Long,

    title: String = "",

    content: String = "",

    images: List<Image> = emptyList(),

    @Embedded
    var postCount: PostCount = PostCount(),

    isQuestion: Boolean = false,

    @Column(nullable = false)
    val createdDateTime: LocalDateTime = LocalDateTime.now(),

    modifiedDateTime: LocalDateTime = LocalDateTime.now(),

    id: Long = 0L,
) : BaseEntity(id) {

    @Column(nullable = false, length = 100)
    var title: String = title
        private set

    @Column(nullable = false, length = 255)
    var content: String = content
        private set

    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(name = "post_images")
    private val _images: MutableList<Image> = images.toMutableList()

    val images: List<Image>
        get() = _images

    @Column(nullable = false)
    var isQuestion: Boolean = isQuestion
        private set

    @Column(nullable = false)
    var modifiedDateTime: LocalDateTime = modifiedDateTime
        private set

    val thumbnail: String?
        get() = _images.firstOrNull()?.key

    fun update(title: String, content: String, images: List<Image>) {
        this.title = title
        this.content = content
        this._images.clear()
        this._images.addAll(images)
        this.modifiedDateTime = LocalDateTime.now()
    }

    fun increaseViewCount() {
        postCount = postCount.increaseViewCount()
    }

    fun increaseReplyCount() {
        postCount = postCount.increaseReplyCount()
    }

    fun increaseLikeCount() {
        postCount = postCount.increaseLikeCount()
    }
}
package com.dclass.backend.application.dto

import com.dclass.backend.domain.post.PostCount

data class PostScrollPageRequest(
    val lastId: Long?,
    val communityId: Long,
    val size: Int,
)

data class PostResponse(
    val id: Long,
    val userId: Long,
    val communityId: Long,
    val title: String,
    val content: String,
    val images: List<String>,
    val postCount: PostCount,
    val isQuestion: Boolean,
    val createdDateTime: String,
    val modifiedDateTime: String,
)
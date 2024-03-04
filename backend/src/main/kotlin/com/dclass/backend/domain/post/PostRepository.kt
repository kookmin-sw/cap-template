package com.dclass.backend.domain.post

import com.dclass.backend.application.dto.PostScrollPageRequest
import com.linecorp.kotlinjdsl.dsl.jpql.jpql
import com.linecorp.kotlinjdsl.render.jpql.JpqlRenderContext
import com.linecorp.kotlinjdsl.support.spring.data.jpa.extension.createQuery
import jakarta.persistence.EntityManager
import org.springframework.data.jpa.repository.JpaRepository

interface PostRepository : JpaRepository<Post, Long>, PostRepositorySupport {
}

interface PostRepositorySupport {
    fun findPostScrollPage(request: PostScrollPageRequest): List<Post>
}

private class PostRepositoryImpl(
    private val em: EntityManager,
    private val context: JpqlRenderContext
) : PostRepositorySupport {
    override fun findPostScrollPage(request: PostScrollPageRequest): List<Post> {
        val query = jpql {
            select(
                entity(Post::class)
            ).from(
                entity(Post::class)
            ).where(
                path(Post::id).lessThan(request.lastId ?: Long.MAX_VALUE)
            ).orderBy(
                path(Post::id).desc()
            )
        }

        return em.createQuery(query, context).setMaxResults(request.size).resultList
    }
}
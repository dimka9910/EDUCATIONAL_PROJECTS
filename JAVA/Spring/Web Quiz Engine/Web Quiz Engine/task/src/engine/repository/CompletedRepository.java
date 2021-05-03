package engine.repository;

import engine.entity.CompletedEntity;
import engine.entity.QuizEntity;
import engine.entity.UserEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.PagingAndSortingRepository;

import java.util.List;

public interface CompletedRepository extends
        JpaRepository<CompletedEntity, Integer>,
        PagingAndSortingRepository<CompletedEntity, Integer> {

    List<CompletedEntity> findAll();

    @Query("select p from CompletedEntity p where p.user = ?1")
    public Page<CompletedEntity> findAll(UserEntity userEntity, Pageable pageable);
}

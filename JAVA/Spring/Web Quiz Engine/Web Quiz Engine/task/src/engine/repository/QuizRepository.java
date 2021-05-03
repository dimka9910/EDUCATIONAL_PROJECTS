package engine.repository;

import engine.entity.QuizEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import org.springframework.data.repository.*;
import java.util.Optional;

public interface QuizRepository extends JpaRepository<QuizEntity, Integer>, PagingAndSortingRepository<QuizEntity, Integer>{

    Optional<QuizEntity> getById(int id);

    void deleteById(int id);



    //    List<CodeData> findFirst10ByOrderByDateDesc();
//    List<CodeData> findTop10ByTimeEqualsAndViewsEqualsOrderByDateDesc(long time, long views);
//    Optional<CodeData> getById(UUID id);
//    void deleteById(UUID id);
}
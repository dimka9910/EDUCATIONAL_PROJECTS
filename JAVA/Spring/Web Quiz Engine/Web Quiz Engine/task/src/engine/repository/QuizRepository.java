package engine.repository;

import engine.entity.QuizEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface QuizRepository extends JpaRepository<QuizEntity, Integer> {

    Optional<QuizEntity> getById(int id);

//    List<CodeData> findFirst10ByOrderByDateDesc();
//    List<CodeData> findTop10ByTimeEqualsAndViewsEqualsOrderByDateDesc(long time, long views);
//    Optional<CodeData> getById(UUID id);
//    void deleteById(UUID id);
}
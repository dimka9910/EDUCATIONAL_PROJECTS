package course.repository;

import course.entity.Journal;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

public interface JournalRepo extends JpaRepository<Journal, Long> {

    @Modifying
    @Query(value = "truncate table journal", nativeQuery = true)
    void truncate();

    void deleteById(long id);


}

package course.repository;

import course.entity.Routes;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

public interface RoutesRepo extends JpaRepository<Routes, Long> {
    @Modifying
    @Query(value = "truncate table routes", nativeQuery = true)
    void truncate();

    void deleteByName(String name);
}

package course.repository;

import course.entity.Auto;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface AutoRepo extends JpaRepository<Auto, Integer> {

    @Modifying
    @Query(value = "truncate table auto", nativeQuery = true)
    void truncate();

    void deleteByNum(String num);

    @Query("select b from Auto b where b.id = :id")
    Auto findById(@Param("id") int id);

}

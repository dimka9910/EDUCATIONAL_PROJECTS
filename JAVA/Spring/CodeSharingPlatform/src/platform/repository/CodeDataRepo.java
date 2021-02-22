package platform.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;
import platform.entity.CodeData;

import java.util.List;

public interface CodeDataRepo extends JpaRepository<CodeData, Integer> {
    List<CodeData> findFirst10ByOrderByDateDesc();
    CodeData getById(Integer id);
}

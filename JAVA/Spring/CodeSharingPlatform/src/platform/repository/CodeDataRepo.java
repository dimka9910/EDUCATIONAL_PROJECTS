package platform.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;
import platform.entity.CodeData;

import java.util.List;
import java.util.UUID;

public interface CodeDataRepo extends JpaRepository<CodeData, UUID> {
    List<CodeData> findFirst10ByOrderByDateDesc();
    CodeData getById(UUID id);
    void deleteById(UUID id);
}

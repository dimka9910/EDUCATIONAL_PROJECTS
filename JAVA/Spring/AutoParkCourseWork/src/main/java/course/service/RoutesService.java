package course.service;

import course.entity.Routes;
import course.repository.RoutesRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class RoutesService {
    @Autowired
    private RoutesRepo repository;

    public void addOrUpdate(Routes routes) {
        repository.saveAndFlush(routes);
    }

    public Routes getById(long id) {
        return repository.findById(id).orElse(null);
    }

    public void deleteById(long id) {
        repository.deleteById(id);
    }

    public void deleteByNum(String name) {
        repository.deleteByName(name);
    }

    public void delete(Routes routes) {
        repository.delete(routes);
    }

    public void deleteAll() {
        repository.deleteAll();
    }

    @Transactional
    public void truncate() {
        repository.truncate();
    }

    public List<Routes> getAll() {
        List<Routes> tmp = repository.findAll();
        return repository.findAll();
    }
}
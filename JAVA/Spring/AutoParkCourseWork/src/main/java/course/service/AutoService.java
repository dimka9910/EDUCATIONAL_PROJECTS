package course.service;

import course.entity.Auto;
import course.repository.AutoRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class AutoService {
    @Autowired
    private AutoRepo repository;

    public void addOrUpdate(Auto auto) {
        repository.saveAndFlush(auto);
    }

    public Auto getById(int id) {
        return repository.findById(id);
    }

    public void deleteById(int id) {
        repository.deleteById(id);
    }

    public void deleteByNum(String num) {
        repository.deleteByNum(num);
    }

    public void delete(Auto auto) {
        repository.delete(auto);
    }

    public void deleteAll() {
        repository.deleteAll();
    }

    @Transactional
    public void truncate() {
        repository.truncate();
    }

    public List<Auto> getAll() {
        List<Auto> tmp = repository.findAll();
        return repository.findAll();
    }
}
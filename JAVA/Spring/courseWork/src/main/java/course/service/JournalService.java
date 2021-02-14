package course.service;

import course.entity.Auto;
import course.entity.Journal;
import course.repository.AutoRepo;
import course.repository.JournalRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class JournalService {

    @Autowired
    private JournalRepo repository;

    public void addOrUpdate(Journal journal) {
        repository.saveAndFlush(journal);
    }

    public Journal getById(long id) {
        return repository.findById(id).orElse(null);
    }

    public void deleteById(long id) {
        repository.deleteById(id);
    }


    public void delete(Journal journal) {
        repository.delete(journal);
    }

    public void deleteAll() {
        repository.deleteAll();
    }

    @Transactional
    public void truncate() {
        repository.truncate();
    }

    public List<Journal> getAll() {
        List<Journal> tmp = repository.findAll();
        return repository.findAll();
    }
}
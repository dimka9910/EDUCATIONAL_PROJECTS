package engine.service;

import engine.entity.CompletedEntity;
import engine.entity.QuizEntity;
import engine.entity.UserEntity;
import engine.repository.CompletedRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.support.PagedListHolder;
import org.springframework.data.domain.*;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class CompletedService {

    @Autowired
    CompletedRepository completedRepository;

    public void addRecord(CompletedEntity completedEntity) {
        completedRepository.save(completedEntity);
    }

    public Page<CompletedEntity> getAllQuizzes(Integer page, Integer pageSize, String sortBy) {

        UserEntity userEntity = (UserEntity)SecurityContextHolder
                .getContext()
                .getAuthentication()
                .getPrincipal();

        Pageable paging = PageRequest.of(page, pageSize, Sort.by(sortBy).descending());
        Page<CompletedEntity> pagedResult = completedRepository.findAll(userEntity, paging);

        return pagedResult;
    }

}

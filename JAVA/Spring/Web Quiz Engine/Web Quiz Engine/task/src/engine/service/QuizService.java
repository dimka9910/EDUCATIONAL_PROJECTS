package engine.service;


import engine.entity.QuizEntity;
import engine.entity.UserEntity;
import engine.exceptions.ForbiddenException;
import engine.exceptions.IdNotFoundException;
import engine.repository.QuizRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;
import org.springframework.data.domain.*;
import org.springframework.web.server.ResponseStatusException;

import java.util.stream.Collectors;


@Service
public class QuizService {

    QuizRepository quizRepository;
    public QuizService(QuizRepository quizRepository) {
        this.quizRepository = quizRepository;
    }

    public QuizEntity putQuiz(QuizEntity quizEntity) {
        return quizRepository.save(quizEntity);
    }


    public Page<QuizEntity> getAllQuizzes(Integer page, Integer pageSize, String sortBy) {
        Pageable paging = PageRequest.of(page, pageSize, Sort.by(sortBy));
        Page<QuizEntity> pagedResult = quizRepository.findAll(paging);
        return pagedResult;
    }

    public QuizEntity getQuizById(int id) {
        return quizRepository.getById(id).orElseThrow(IdNotFoundException::new);
    }

    public void deleteQuizById(int id){
        QuizEntity quiz = quizRepository.getById(id).orElseThrow(IdNotFoundException::new);
        if (!quiz.getUser().equals(SecurityContextHolder.getContext().getAuthentication().getPrincipal()))
            throw new ForbiddenException();
        else
            quizRepository.deleteById(id);
    }
}

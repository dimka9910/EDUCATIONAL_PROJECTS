package engine.service;


import engine.entity.QuizEntity;
import engine.exceptions.IdNotFoundException;
import engine.repository.QuizRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class QuizService {

    QuizRepository quizRepository;

    @Autowired
    public QuizService(QuizRepository quizRepository) {
        this.quizRepository = quizRepository;
    }

    ArrayList<QuizEntity> quizList = new ArrayList<>();

//    public QuizEntity getQuiz() {
//        return new QuizEntity("The Java Logo", "What is depicted on the Java logo?",
//                new String[]{"Robot", "Tea leaf", "Cup of coffee", "Bug"});
//    }

    public QuizEntity putQuiz(QuizEntity quizEntity) {
        return quizRepository.save(quizEntity);
//        quizList.add(quizEntity);
//        quizList.get(quizList.size() - 1).setId(quizList.size());
//        return quizList.get(quizList.size() - 1);
    }

    public QuizEntity[] getAllQuizzes() {
        return quizRepository.findAll().toArray(QuizEntity[]::new);
        //return quizList.toArray(QuizEntity[]::new);
    }

    public QuizEntity getQuizById(int id) {
        return quizRepository.getById(id).orElseThrow(IdNotFoundException::new);
//        return Optional.of(quizList.get(id - 1)).orElseThrow(IdNotFoundException::new);
    }
}

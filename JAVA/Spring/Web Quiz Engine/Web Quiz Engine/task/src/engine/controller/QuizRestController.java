package engine.controller;

import engine.entity.CompletedEntity;
import engine.entity.JsonAnswer;
import engine.entity.QuizEntity;
import engine.entity.UserEntity;
import engine.exceptions.IdNotFoundException;
import engine.response.Response;
import engine.service.CompletedService;
import engine.service.QuizService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.Arrays;
import java.util.Optional;

@RestController
@RequestMapping("/api")
public class QuizRestController {

    QuizService quizService;
    CompletedService completedService;

    public QuizRestController(QuizService quizService, CompletedService completedService) {
        this.quizService = quizService;
        this.completedService = completedService;
    }

    @PostMapping(value = "/quizzes")
    public QuizEntity postQuiz(@Valid @RequestBody QuizEntity quizEntity) {
        quizEntity.setUser((UserEntity) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        return quizService.putQuiz(quizEntity);
    }

    @GetMapping(value = "/quizzes")
    public Page<QuizEntity> getQuizzes(@RequestParam(defaultValue = "0") Integer page,
                                       @RequestParam(defaultValue = "10") Integer pageSize,
                                       @RequestParam(defaultValue = "id") String sortBy) {
        return quizService.getAllQuizzes(page, pageSize, sortBy);
    }

    @GetMapping(value = "/quizzes/completed")
    public Page<CompletedEntity> getCompletedQuizzes(@RequestParam(defaultValue = "0") Integer page,
                                                @RequestParam(defaultValue = "10") Integer pageSize,
                                                @RequestParam(defaultValue = "completedAt") String sortBy) {
        return completedService.getAllQuizzes(page, pageSize, sortBy);
    }

    @GetMapping(value = "/quizzes/{id}")
    public QuizEntity getQuiz(@PathVariable int id) {
        try {
            return quizService.getQuizById(id);
        } catch (Exception e) {
            throw new IdNotFoundException();
        }
    }

    @DeleteMapping(value = "/quizzes/{id}")
    public ResponseEntity deleteQuiz(@PathVariable int id) {
        quizService.deleteQuizById(id);
        return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
    }

    @PostMapping(value = "/quizzes/{id}/solve")
    public Response solveQuiz(@PathVariable int id, @RequestBody JsonAnswer answer) {
        try {
            QuizEntity qe = quizService.getQuizById(id);
            Integer[] a = Optional.ofNullable(answer.getAnswer()).orElse(new Integer[]{});
            Integer[] b = Optional.ofNullable(qe.getAnswer().toArray(Integer[]::new)).orElse(new Integer[]{});


            Arrays.sort(answer.getAnswer());
            if (Arrays.equals(a, b)) {
                CompletedEntity completedEntity = new CompletedEntity();
                completedEntity.setId(id);
                completedEntity.setUser((UserEntity) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
                completedService.addRecord(completedEntity);
                return new Response(true, "YES!");
            } else
                return new Response(false, "NO(((");

        } catch (Exception e) {
            throw new IdNotFoundException();
        }
    }
}

package engine.controller;

import engine.entity.JsonAnswer;
import engine.entity.QuizEntity;
import engine.exceptions.IdNotFoundException;
import engine.response.Response;
import engine.service.QuizService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.Arrays;
import java.util.Optional;

@RestController
@RequestMapping("/api")
public class QuizRestController {

    QuizService quizService;

    @Autowired
    public QuizRestController(QuizService quizService) {
        this.quizService = quizService;
    }


    @PostMapping(value = "/quizzes")
    public QuizEntity postQuiz(@Valid @RequestBody QuizEntity quizEntity) {
        return quizService.putQuiz(quizEntity);
    }

    @GetMapping(value = "/quizzes")
    public QuizEntity[] getQuizzes() {
        return quizService.getAllQuizzes();
    }

    @GetMapping(value = "/quizzes/{id}")
    public QuizEntity getQuiz(@PathVariable int id) {
        try {
            return quizService.getQuizById(id);
        } catch (Exception e) {
            throw new IdNotFoundException();
        }
    }

    @PostMapping(value = "/quizzes/{id}/solve")
    public Response solveQuiz(@PathVariable int id, @RequestBody JsonAnswer answer) {
        try {
            QuizEntity qe = quizService.getQuizById(id);
            Integer[] a = Optional.ofNullable(answer.getAnswer()).orElse(new Integer[]{});
            Integer[] b = Optional.ofNullable(qe.getAnswer().toArray(Integer[]::new)).orElse(new Integer[]{});

            Arrays.sort(answer.getAnswer());
            if (Arrays.equals(a, b))
                return new Response(true, "YES!");
            else
                return new Response(false, "NO(((");

        } catch (Exception e) {
            throw new IdNotFoundException();
        }
    }
}

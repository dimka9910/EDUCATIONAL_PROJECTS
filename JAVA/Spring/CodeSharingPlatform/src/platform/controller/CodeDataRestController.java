package platform.controller;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import platform.Answer;
import platform.entity.CodeData;
import platform.service.CodeDataService;

import java.util.List;
import java.util.Map;

@RestController
public class CodeDataRestController {

    @Autowired
    CodeDataService codeDataService;

    @GetMapping(path = "/api/code/{id}")
    public CodeData getCodeByID(@PathVariable int id){
        return codeDataService.getNth(id);
    }

    @GetMapping(path = "/api/code/latest")
    public List<CodeData> getLatest(){
        return codeDataService.getLastN(10);
    }

    @PostMapping(value = "/api/code/new", consumes = "application/json")
    public Map<String, String> postNewCode(@RequestBody CodeData codeData) {
        CodeData temp = new CodeData(codeData);
        return Map.of("id", String.valueOf(codeDataService.add(temp)));
    }

}

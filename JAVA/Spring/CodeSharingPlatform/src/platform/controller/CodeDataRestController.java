package platform.controller;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import platform.Answer;
import platform.entity.CodeData;
import platform.service.CodeDataService;

@RestController
public class CodeDataRestController {

    @Autowired
    CodeDataService codeDataService;

    CodeData codeData = new CodeData("");

    @GetMapping(path = "/api/code/{id}")
    public ResponseEntity getTask(@PathVariable int id){
        if (codeDataService.getNth(id) == null)
            return new ResponseEntity(this.codeData, HttpStatus.OK);
        return new ResponseEntity(codeDataService.getNth(id), HttpStatus.OK);
    }

    @GetMapping(path = "/api/code/latest")
    public ResponseEntity getLatest(){
        if (codeDataService.getLastN(10) == null)
            return new ResponseEntity(this.codeData, HttpStatus.OK);
        return new ResponseEntity(codeDataService.getLastN(10), HttpStatus.OK);
    }



    @PostMapping(value = "/api/code/new", consumes = "application/json")
    public ResponseEntity greet(@RequestBody CodeData codeData) {
        CodeData temp = new CodeData(codeData);
        return new ResponseEntity(new Answer(codeDataService.add(temp)), HttpStatus.OK);
    }

}

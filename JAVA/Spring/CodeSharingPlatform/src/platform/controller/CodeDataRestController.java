package platform.controller;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import platform.entity.CodeData;
import platform.exceptions.IdNotFoundException;
import platform.service.CodeDataService;

import java.util.List;
import java.util.Map;
import java.util.UUID;

@RestController
public class CodeDataRestController{

    @Autowired
    CodeDataService codeDataService;

    @GetMapping(path = "/api/code/{id}")
    public CodeData getCodeByID(@PathVariable UUID id){
        System.out.println("/api/code/" + id);
        var data = codeDataService.getById(id);
        if (data == null)
            throw new IdNotFoundException();
        return data;
    }

    @GetMapping(path = "/api/code/latest")
    public List<CodeData> getLatest(){
        System.out.println("/api/code/latest");
        return codeDataService.getLastN(10);
    }

    @PostMapping(value = "/api/code/new", consumes = "application/json")
    public Map<String, String> postNewCode(@RequestBody CodeData codeData) {
        System.out.println("\"/api/code/new\"");
        CodeData temp = new CodeData(codeData);
        System.out.println(temp.toString());
        return Map.of("id", String.valueOf(codeDataService.add(temp)));
    }

}

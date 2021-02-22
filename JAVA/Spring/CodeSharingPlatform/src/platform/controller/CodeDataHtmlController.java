package platform.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import platform.entity.CodeData;
import platform.service.CodeDataService;

import java.util.ArrayList;
import java.util.List;

@Controller
public class CodeDataHtmlController {

    @Autowired
    CodeDataService codeDataService;

    @GetMapping(value = "/code/latest")
    public String index(Model model) {
        var w = codeDataService.getLastN(10);
        model.addAttribute("codeDatas", w);
        return "list";
    }

    @GetMapping(value = "/code/new")
    public String newCode(Model model) {
        return "newCode";
    }

    @GetMapping(path = "/code/{id}")
    public String getTask(@PathVariable int id, Model model){
        List<CodeData> list = new ArrayList<CodeData>();
        list.add(codeDataService.getNth(id));
        model.addAttribute("codeDatas", list);
        return "index";
    }
}

package platform.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import platform.entity.CodeData;
import platform.repository.CodeDataRepo;

import java.util.*;

@Service
public class CodeDataService {

    @Autowired
    CodeDataRepo codeDataRepo;

    public List<CodeData> getLastN(int n){
        return codeDataRepo.findFirst10ByOrderByDateDesc();
    }

    public CodeData getNth(int n){
        return codeDataRepo.getById(n);
    }

    public int add(CodeData codeData){
        return codeDataRepo.save(codeData).getId();  //МЕТОД SAVE ВОЗВРАЩАЕТ СОХРАНЁННУЮ СУЩНОСТЬ
    }

}
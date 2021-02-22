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

    public CodeData getById(UUID n){
        var v = codeDataRepo.getById(n);
        if (v == null)
            return null;
        if (v.isViewsRestriction()) {
            v.setViews(v.getViews() - 1);
            if (v.getViews() < 0) {
                //if (v.isTimeRestriction())
                    codeDataRepo.deleteById(v.getId());
            }
            else
                codeDataRepo.save(v);
        }
        if (v.isTimeRestriction()){
            if (v.getTime() <= 0)
                codeDataRepo.deleteById(v.getId());
        }
        return codeDataRepo.getById(n);
    }

    public String add(CodeData codeData){
        return codeDataRepo.save(codeData).getId().toString();  //МЕТОД SAVE ВОЗВРАЩАЕТ СОХРАНЁННУЮ СУЩНОСТЬ
    }

}
package platform.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import platform.entity.CodeData;
import platform.exceptions.IdNotFoundException;
import platform.repository.CodeDataRepo;

import java.util.*;

@Service
public class CodeDataService {

    @Autowired
    CodeDataRepo codeDataRepo;

    public List<CodeData> getLastN(int n) {
        return codeDataRepo.findTop10ByTimeEqualsAndViewsEqualsOrderByDateDesc(0, 0);
    }

    public CodeData getById(UUID n) {
        var v = codeDataRepo.getById(n).orElseThrow(IdNotFoundException::new);
        if (v.isViewsRestriction()) {
            v.setViews(v.getViews() - 1);
            codeDataRepo.save(v);
        }
        if (v.isTimeRestriction() && v.getTime() <= 0
                || v.isViewsRestriction() && v.getViews() < 0) {
                codeDataRepo.deleteById(v.getId());
        }
        return codeDataRepo.getById(n).orElseThrow(IdNotFoundException::new);
    }

    public String add(CodeData codeData) {
        return codeDataRepo.save(codeData).getId().toString();  //МЕТОД SAVE ВОЗВРАЩАЕТ СОХРАНЁННУЮ СУЩНОСТЬ
    }

}
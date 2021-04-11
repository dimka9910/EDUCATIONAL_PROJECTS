package course.controller.rest;

import course.controller.response.SimpleResponse;
import course.entity.Auto;
import course.entity.User;
import course.service.AutoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.orm.jpa.JpaObjectRetrievalFailureException;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/cars")
public class AutoRestController {

    @Autowired
    private AutoService service;

    @PostMapping(value = "/add")
    public SimpleResponse addOrUpdateSale(@RequestBody Auto auto) {
        try {
            if (auto.getId() == null) {
                service.addOrUpdate(new Auto(auto.getNum(), auto.getColor(), auto.getMark()));
            } else {
                service.addOrUpdate(auto);
            }
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Такой автомобиль уже существует");
        } catch (JpaObjectRetrievalFailureException ex) {
            return new SimpleResponse(false, "Такого автомобиля не существует");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }

    @PostMapping(value = "/user")
    public SimpleResponse sale(@RequestBody Auto auto) {
        try {
            User user = (User) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            if (user.getJournal() == null) {
                service.addOrUpdate(new Auto(auto.getId(), auto.getNum(), auto.getColor(), auto.getMark(), user));
            } else {
                Exception ex = null;
                throw ex; }
        } catch (NullPointerException ex) {
            return new SimpleResponse(false, "Вы уже в пути");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }

    @PostMapping(value = "/free")
    public SimpleResponse free(@RequestBody Auto auto) {
        try {
            service.addOrUpdate(new Auto(auto.getId(), auto.getNum(), auto.getColor(), auto.getMark(), null));
        } catch (NullPointerException ex) {
            return new SimpleResponse(false, "Такого автомабиля нет");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }


    @PostMapping(value = "/delete/by/id")
    public SimpleResponse deleteSaleById(@RequestBody Auto auto) {
        try {
            service.deleteById(auto.getId());
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Эта запись связана с другими таблицами");
        } catch (EmptyResultDataAccessException ex) {
            return new SimpleResponse(false, "Такого автомабиля не существует");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }

    @PostMapping(value = "/delete/all")
    public SimpleResponse deleteAllSales() {
        try {
            service.deleteAll();
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Сначала очистите другие таблицы");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }

    @RequestMapping(value = "/get/all", method = RequestMethod.GET)
    public List<Auto> getAllSales() {
        List<Auto> tmp = null;
        try {
            tmp = service.getAll();
        } catch (Exception ex) {
            System.out.println("Exception in get all");
        }
        return tmp;
    }
}
package course.controller.rest;

import course.controller.response.SimpleResponse;
import course.entity.Routes;
import course.service.RoutesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.orm.jpa.JpaObjectRetrievalFailureException;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/routes")
public class RoutesRestController {

    @Autowired
    private RoutesService service;

    @PostMapping(value = "/add")
    public SimpleResponse addOrUpdateSale(@RequestBody Routes routes) {
        try {
            if (routes.getId() == null) {
                service.addOrUpdate(new Routes(routes.getName()));
            } else {
                service.addOrUpdate(routes);
            }
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Тако1 маршрут уже существует");
        }  catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }


    @PostMapping(value = "/delete/by/id")
    public SimpleResponse deleteSaleById(@RequestBody Routes routes) {
        try {
            service.deleteById(routes.getId());
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Эта запись связана с другими таблицами");
        }  catch (Exception ex) {
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
    public List<Routes> getAllSales() {
        List<Routes> tmp = null;
        try {
            tmp = service.getAll();
        } catch (Exception ex) {
            System.out.println("Exception in get all");
        }
        return tmp;
    }
}
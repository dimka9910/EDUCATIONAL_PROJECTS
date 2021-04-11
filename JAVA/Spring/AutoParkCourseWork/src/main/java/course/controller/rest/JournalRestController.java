package course.controller.rest;

import course.controller.response.SimpleResponse;
import course.entity.*;
import course.repository.AutoRepo;
import course.service.AutoService;
import course.service.JournalService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.orm.jpa.JpaObjectRetrievalFailureException;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;

import java.util.Collections;
import java.util.Date;
import java.util.List;

@RestController
@RequestMapping("/journal")
public class JournalRestController {

    @Autowired
    private JournalService service;

    @Autowired
    private AutoRepo aservice;

    @Autowired
    private AutoService aaservice;

    @PostMapping(value = "/add")
    public SimpleResponse addOrUpdateSale(@RequestBody Journal journal) {
        try {

            Journal jrl = new Journal(journal.getAuto(), journal.getRoute());
            service.addOrUpdate(jrl);

            User user = (User) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            user.setJournal(jrl);
            //user.setRoles(Collections.singleton(Role1.BUSY));

            System.out.println(user.getJournal().getId());
            //User user = (User) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Такая запись в журнале уже существует");
        } catch (JpaObjectRetrievalFailureException ex) {
            return new SimpleResponse(false, "Такая запись в журнале не существует");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Неизвестная ошибка");
        }
        return new SimpleResponse(true);
    }

    @PostMapping(value = "/end")
    public SimpleResponse endJournal(@RequestBody Journal journal) {
        try {

            User user = (User) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            Journal parentJrl = user.getJournal();
            Journal jrl = new Journal(parentJrl.getId(), parentJrl.getTime_out(), parentJrl.getAuto(), parentJrl.getRoute());
            service.addOrUpdate(jrl);

            Auto parentAuto = aaservice.getById(jrl.getAuto().getId());
            System.out.println("НОМЕР МАШИНЫ ЭТО - " + jrl.getAuto().getId() + " а еще такой есть" + parentAuto.getId());
            aaservice.addOrUpdate(new Auto(parentAuto.getId(), parentAuto.getNum(), parentAuto.getColor(), parentAuto.getMark(), null));

            System.out.println(user.getJournal().getId());
            user.setJournal(null);

        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Такая запись в журнале уже существует");
        } catch (JpaObjectRetrievalFailureException ex) {
            return new SimpleResponse(false, "Такая запись в журнале не существует");
        } catch (Exception ex) {
            return new SimpleResponse(false, "Нет активных поездок");
        }
        return new SimpleResponse(true);
    }

    @PostMapping(value = "/delete/by/id")
    public SimpleResponse deleteSaleById(@RequestBody Journal journal) {
        try {
            service.deleteById(journal.getId());
        } catch (DataIntegrityViolationException ex) {
            return new SimpleResponse(false, "Эта запись связана с другими таблицами");
        } catch (EmptyResultDataAccessException ex) {
            return new SimpleResponse(false, "Такая запись в журнале не существует");
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
    public List<Journal> getAllSales() {
        List<Journal> tmp = null;
        try {
            tmp = service.getAll();
        } catch (Exception ex) {
            System.out.println("Exception in get all");
        }
        return tmp;
    }

}
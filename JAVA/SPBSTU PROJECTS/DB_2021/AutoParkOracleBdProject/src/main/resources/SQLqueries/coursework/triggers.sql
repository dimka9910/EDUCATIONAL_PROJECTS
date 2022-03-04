-- триггер на изменение записи в журнале, чтобы время прибытия не было меньше времени отправления
CREATE OR REPLACE TRIGGER tr_journal_before_insert
    BEFORE UPDATE
    ON journal
    FOR EACH ROW
BEGIN
    IF :OLD.time_out > :NEW.time_in THEN
        RAISE_APPLICATION_ERROR(-20003, 'Время прибытия не может быть меньше времени отправки');
    END IF;
END;

--процедура - вывод количества автомобилей в рейсе по данному маршруту
CREATE OR REPLACE PROCEDURE CountCarsInRoute(route IN NUMBER, cars_in_route OUT NUMBER) IS
BEGIN
    SELECT COUNT(auto_id) INTO cars_in_route FROM journal WHERE route_id = route AND time_in IS NULL;
END;
--


--создание тыблицы с пользователями и процедуры для работы с ней
CREATE TABLE users
(
    login VARCHAR(50),
    hash  VARCHAR2(100)
)

CREATE OR REPLACE PROCEDURE InsertIntoUsers(new_login in VARCHAR, new_hash in VARCHAR) IS
BEGIN
    INSERT INTO users (login, hash) VALUES (new_login, new_hash);
END;

CREATE OR REPLACE PROCEDURE DeleteUser(chosen_login in VARCHAR) IS
BEGIN
    DELETE FROM users WHERE login = chosen_login;
END;

ALTER TABLE users
    ADD CONSTRAINT unique_login UNIQUE (login);



CREATE OR REPLACE PROCEDURE FindRecord(driver1 IN NUMBER, driver2 IN NUMBER, start_date IN DATE, end_date IN DATE,
                                       routes OUT NUMBER) IS
    time1 VARCHAR(50); time2 VARCHAR(50); routes1 NUMBER; routes2 NUMBER;
BEGIN
    routes1 := 0; routes2 := 0;
    FOR item IN (SELECT ID FROM routes)
        LOOP
            BEGIN
                SELECT TO_CHAR(MIN(time_in - time_out))
                INTO time1
                FROM routes,
                     journal
                WHERE routes.id = journal.route_id
                  AND auto_id IN (SELECT id FROM auto WHERE personnel_id = driver1)
                  AND time_in IS NOT NULL
                  AND time_out > start_date
                  AND time_in < end_date
                  AND route_id = item.id;
                SELECT TO_CHAR(MIN(time_in - time_out))
                INTO time2
                FROM routes,
                     journal
                WHERE routes.id = journal.route_id
                  AND auto_id IN (SELECT id FROM auto WHERE personnel_id = driver2)
                  AND time_in IS NOT NULL
                  AND time_out > start_date
                  AND time_in < end_date
                  AND route_id = item.id;
                IF time1 IS NULL AND time2 IS NOT NULL THEN routes2 := routes2 + 1; END IF;
                IF time1 IS NOT NULL AND time2 IS NULL THEN routes1 := routes1 + 1; END IF;
                IF time1 IS NOT NULL AND time2 IS NOT NULL AND (time1) < (time2) THEN routes1 := routes1 + 1; END IF;
            EXCEPTION
                WHEN NO_DATA_FOUND THEN CONTINUE;
            END;
        END LOOP;
    routes := routes1 - routes2;
END;

-- CREATE OR REPLACE PROCEDURE GetFromUsers(new_login in VARCHAR, new_hash out VARCHAR) IS
-- BEGIN SELECT hash INTO new_hash FROM users WHERE login = new_login FETCH FIRST 1 ROWS ONLY;;
--

CREATE OR
    REPLACE PROCEDURE CalculatePrizes(start_date IN DATE, end_date IN DATE, prize_sum IN VARCHAR) IS
    first_result                             NUMBER;
    second_result                            NUMBER; third_result NUMBER; current_result NUMBER; CURSOR personnel_cursor IS
        SELECT id
        FROM auto_personnel; first_driver_id personnel_cursor%ROWTYPE; second_driver_id personnel_cursor%ROWTYPE;
    third_driver_id                          personnel_cursor%ROWTYPE;
BEGIN
    IF NOT personnel_cursor%ISOPEN THEN OPEN personnel_cursor; END IF; FETCH personnel_cursor INTO first_driver_id;
    FETCH personnel_cursor INTO second_driver_id; FETCH personnel_cursor INTO third_driver_id;
    CLOSE personnel_cursor;
    FOR personnel IN personnel_cursor
        LOOP
            IF personnel.id = first_driver_id.id THEN CONTINUE; END IF;
            FindRecord(personnel.id, first_driver_id.id, start_date, end_date, current_result);
            IF current_result > 0 THEN first_driver_id := personnel; CONTINUE; END IF;

            IF personnel.id = second_driver_id.id THEN CONTINUE; END IF;
            FindRecord(personnel.id, second_driver_id.id, start_date, end_date, current_result);
            IF current_result > 0 THEN second_driver_id := personnel; CONTINUE; END IF;
            IF personnel.id = third_driver_id.id THEN CONTINUE; END IF;
            FindRecord(personnel.id, third_driver_id.id, start_date, end_date, current_result);
            IF current_result > 0 THEN third_driver_id := personnel; CONTINUE; END IF;
        END LOOP;
    first_result := prize_sum * 0.5; second_result := prize_sum * 0.3; third_result := prize_sum * 0.2;
    DBMS_OUTPUT.enable; DBMS_OUTPUT.put_line('First driver: ' || first_driver_id.id || '. Sum: ' || first_result);
    DBMS_OUTPUT.put_line('Second driver: ' || second_driver_id.id || '. Sum: ' || second_result);
    DBMS_OUTPUT.put_line('Third driver: ' || third_driver_id.id || '. Sum: ' || third_result);
END;

BEGIN
    CalculatePrizes('20.01.2019', '28.09.2021', 200900);
END;


CREATE OR REPLACE PROCEDURE FindRecordOnRoute(new_route_id IN NUMBER, car_num OUT VARCHAR, min_time OUT VARCHAR)
    IS
BEGIN
    SELECT num, TO_CHAR(MIN(time_in - time_out))
    INTO car_num, min_time
    FROM journal
             JOIN auto ON journal.auto_id = auto.id
             JOIN routes ON journal.route_id = routes.id
    WHERE ROUTE_ID = new_route_id

      AND time_in IS NOT NULL
    GROUP BY num
    ORDER BY min_time FETCH FIRST 1 ROWS ONLY;
    DBMS_OUTPUT.enable; DBMS_OUTPUT.put_line('CAR NUMBER: ' || car_num || '. TIME: ' || min_time);
END;

SELECT COUNT(*) as count FROM JOURNAL  WHERE JOURNAL.TIME_IN is null and ROUTE_ID = 9
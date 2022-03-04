-- •	Триггера на вставку:
-- 1.	Создать триггер, который не позволяет отправить в рейс автомобиль, который еще не вернулся в парк.

SELECT *
FROM JOURNAL;

--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
CREATE OR REPLACE TRIGGER car_in_trip
    BEFORE INSERT
    ON JOURNAL
    FOR EACH ROW
DECLARE
    v_is_exist PLS_INTEGER;
BEGIN
    SELECT COUNT(1) into v_is_exist FROM JOURNAL WHERE TIME_IN is NULL AND AUTO_ID = :NEW.AUTO_ID;
    IF (v_is_exist > 0) THEN
        RAISE_APPLICATION_ERROR(-20000, 'THIS CAR IS ALREADY IN TRIP');
    end if;
END;

CREATE OR REPLACE TRIGGER tr_journal_before_insert
    BEFORE UPDATE
    ON journal
    FOR EACH ROW
BEGIN
    IF :OLD.time_out > :NEW.time_in THEN
        RAISE_APPLICATION_ERROR(-20003, 'Время прибытия не может быть меньше времени отправки');
    END IF;
END;
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------

INSERT INTO JOURNAL (TIME_OUT, AUTO_ID, ROUTE_ID)
VALUES ((select to_timestamp(sysdate) + (dbms_random.value(0, 86400) / 86400) - 5
         from dual),
        6,
        15);


SELECT *
FROM JOURNAL
ORDER BY AUTO_ID;

-- •	Триггера на модификацию:
-- 1.	Создать триггер, который при изменении маршрута, в случае наличия ссылок из журнала, делает новый маршрут, хранящий неизмененный (прежний) вариант маршрута и подменять все ссылки на него. Таким образом, старые записи журнала будут по-прежнему ссылаться на маршрут, по которому они были созданы.

CREATE OR REPLACE TRIGGER tr_journal_before_insert
    BEFORE UPDATE
    ON journal
    FOR EACH ROW
BEGIN
    IF :OLD.time_out > :NEW.time_in THEN
        RAISE_APPLICATION_ERROR(-20003, 'Время прибытия не может быть меньше времени отправки');
    END IF;
END;
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
CREATE OR REPLACE TRIGGER route_modify
    BEFORE UPDATE
    ON ROUTES
    FOR EACH ROW
DECLARE
    v_is_exist  PLS_INTEGER;
    inserted_ID int;
    PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    SELECT COUNT(1) into v_is_exist FROM JOURNAL WHERE ROUTE_ID = :OLD.ID;
    IF (v_is_exist > 0) THEN
        INSERT INTO ROUTES (NAME) VALUES (:OLD.NAME) returning ID INTO inserted_ID;
        UPDATE JOURNAL SET ROUTE_ID = inserted_ID WHERE ROUTE_ID = :OLD.ID;
    end if;
    COMMIT;
END;
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------

SELECT *
FROM JOURNAL
         JOIN ROUTES R on R.ID = JOURNAL.ROUTE_ID;

UPDATE ROUTES
SET NAME = 'NewRoute №2'
WHERE ID = 2;

-- •	Триггера на удаление:
-- 1.	Создать триггер, который при удалении водителя, в случае наличия на него ссылок, откатывает транзакцию.

--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
CREATE OR REPLACE TRIGGER driver_delete
    BEFORE DELETE
    ON AUTO_PERSONNEL
    FOR EACH ROW
DECLARE
    v_is_exist PLS_INTEGER;
BEGIN
    SELECT COUNT(1) into v_is_exist FROM AUTO WHERE PERSONNEL_ID = :OLD.ID;
    IF (v_is_exist > 0) THEN
        RAISE_APPLICATION_ERROR(-20000, 'THIS DRIVER HAS REFERENCES IN OTHER TABLES');
    end if;
END;
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------

SELECT *
FROM AUTO;

DELETE
FROM AUTO_PERSONNEL
WHERE ID = 6;

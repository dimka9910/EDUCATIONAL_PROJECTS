-- Вставка данных
-- •	однотабличная вставка:
-- 1.	Добавить водителю с заданной фамилией два автомобиля.
SELECT *
FROM AUTO
         JOIN AUTO_PERSONNEL AP on AP.ID = AUTO.PERSONNEL_ID
WHERE LAST_NAME = 'LAST_NAME №17';


SELECT *
FROM AUTO_PERSONNEL;

DECLARE
    i   NUMBER       := 0;
    j   NUMBER       := 2;
    tmp VARCHAR2(50) := 'LAST_NAME №20';

BEGIN
    LOOP
        i := i + 1;

        insert into AUTO (NUM, COLOR, MARK, PERSONNEL_ID)
        values ('-', '-', '-',
                (SELECT ID FROM (SELECT ID FROM AUTO_PERSONNEL WHERE LAST_NAME = tmp) WHERE ROWNUM = 1)) returning ID into j;

        --SELECT MAX(id) into j from AUTO;

        UPDATE AUTO
        SET NUM   = CONCAT('NUM №', TO_CHAR(j)),
            COLOR = CONCAT('COLOR №', j),
            MARK  = CONCAT('MARK №', j)
        WHERE ID = j;

        EXIT WHEN (i >= 2);
    END LOOP;
END;

-- 2.	Отправить водителя с заданной фамилией на желтой машине в рейс по маршруту с известным id.
SELECT *
FROM AUTO
WHERE COLOR = 'YELLOW';

SELECT *
FROM ROUTES;

UPDATE AUTO
SET PERSONNEL_ID = 24
WHERE ID = 34;

SELECT ID FROM (SELECT AUTO.ID, COLOR FROM AUTO JOIN AUTO_PERSONNEL AP on AP.ID = AUTO.PERSONNEL_ID WHERE LAST_NAME = 'LAST_NAME №24' and COLOR = 'YELLOW') WHERE ROWNUM = 1;

SELECT * FROM JOURNAL JOIN AUTO A2 on A2.ID = JOURNAL.AUTO_ID join AUTO_PERSONNEL AP on AP.ID = A2.PERSONNEL_ID WHERE LAST_NAME = 'LAST_NAME №24';

DELETE FROM JOURNAL WHERE ID = 61;

INSERT INTO JOURNAL (TIME_OUT, AUTO_ID, ROUTE_ID)
VALUES ((SELECT SYSTIMESTAMP from dual),
           (SELECT ID FROM (SELECT AUTO.ID, COLOR FROM AUTO JOIN AUTO_PERSONNEL AP on AP.ID = AUTO.PERSONNEL_ID WHERE LAST_NAME = 'LAST_NAME №24' and COLOR = 'YELLOW') WHERE ROWNUM = 1)
        , 20);


-- •	многотабличная вставка в рамках транзакции:
-- 1.	Добавить запись в журнал в случае, если автомобилей в данном рейсе больше 2-х, транзакцию откатить.

DECLARE
    routeId number := 10;
    c number := 0;

BEGIN
    savepoint a;

    INSERT INTO JOURNAL (TIME_OUT, AUTO_ID, ROUTE_ID)
    VALUES ((SELECT SYSTIMESTAMP from dual),
            13, routeId);

    SELECT count into c FROM (SELECT COUNT(*) as count, ROUTE_ID FROM JOURNAL WHERE TIME_IN is NULL AND ROUTE_ID = routeId GROUP BY ROUTE_ID) WHERE ROWNUM = 1;

    IF c > 1 THEN
        ROLLBACK;
    ELSE
        COMMIT;
    END IF;
end;


    SELECT count FROM (SELECT COUNT(*) as count, ROUTE_ID FROM JOURNAL WHERE TIME_IN is NULL AND ROUTE_ID = 10 GROUP BY ROUTE_ID) WHERE ROWNUM = 1;


SELECT COUNT(*) as count, ROUTE_ID FROM JOURNAL WHERE TIME_IN is NULL GROUP BY ROUTE_ID
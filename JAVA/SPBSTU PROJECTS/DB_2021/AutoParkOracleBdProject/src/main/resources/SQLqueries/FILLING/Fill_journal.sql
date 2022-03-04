SELECT *
FROM JOURNAL WHERE ROUTE_ID = 4;

DELETE
FROM JOURNAL;

------------ЗАПОЛНЕНИЕ ЖУРНАЛА СЛУЧАЙНЫМИ МАШИНАМИ, МАРШРУТАМИ И ВРЕМЕНЕМ ОТПРАВЛЕНИЯ-----------------
DECLARE
    autoId  NUMBER;
    routeId NUMBER;
    k       NUMBER := 0;

BEGIN
    LOOP
        k := k + 1;

        SELECT id
        into autoId
        FROM (SELECT *
              FROM AUTO WHERE NOT EXISTS(SELECT * FROM JOURNAL WHERE AUTO_ID = AUTO.ID AND TIME_IN IS NULL )
              ORDER BY dbms_random.RANDOM())
        WHERE rownum = 1;

        SELECT id
        into routeId
        FROM (SELECT *
              FROM ROUTES
              ORDER BY dbms_random.RANDOM())
        WHERE rownum = 1;

        INSERT INTO JOURNAL(TIME_OUT, AUTO_ID, ROUTE_ID)
        VALUES ((select to_timestamp(sysdate) + (dbms_random.value(0, 86400) / 86400) - 5
                 from dual),
                autoId,
                routeId);


        EXIT WHEN (k >= 5);
    END LOOP;
END;
---------------------------------------------



------------ЗАПОЛНЕНИЕ ЖУРНАЛА СЛУЧАЙНЫМИ МАШИНАМИ-----------------
DECLARE
    journalId  NUMBER;
    k       NUMBER := 0;

BEGIN
    LOOP
        k := k + 1;

        SELECT id
        into journalId
        FROM (SELECT *
              FROM JOURNAL
              ORDER BY dbms_random.RANDOM())
        WHERE rownum = 1;


        UPDATE JOURNAL
        SET TIME_IN = (select to_timestamp(sysdate) + (dbms_random.value(0, 86400) / 86400) - 4
                       from dual)
        WHERE JOURNAL.ID = journalId;


        EXIT WHEN (k >= 10);
    END LOOP;
END;
---------------------------------------------

SELECT * FROM JOURNAL WHERE TIME_IN IS NULL ORDER BY AUTO_ID

DELETE FROM JOURNAL WHERE ID = 8;



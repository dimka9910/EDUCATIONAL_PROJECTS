alter table
    AUTO
    modify
        (PERSONNEL_ID NULL);


DELETE
FROM AUTO;

SELECT *
FROM AUTO LEFT JOIN AUTO_PERSONNEL AP on AP.ID = AUTO.PERSONNEL_ID;




-- ГЕНЕРАЦИЯ ЗАПИСЕЙ В ЗАВИСИМОСТИ ОТ ID--
DECLARE
    i NUMBER := 0;
    j NUMBER;

BEGIN
    LOOP
        i := i + 1;


        insert into AUTO (NUM, COLOR, MARK) values ('-', '-', '-');
        SELECT MAX(id) into j from AUTO;

        UPDATE AUTO
        SET NUM   = CONCAT('NUM №', TO_CHAR(j)),
            COLOR = CONCAT('COLOR №', j),
            --COLOR = 'YELLOW',
            MARK  = CONCAT('MARK №', j)
        WHERE ID = j;

        EXIT WHEN (i >= 5);
    END LOOP;
END;
---------------------------------------------------------------




------------НАЗНАЧЕНИЕ СЛУЧАЙНЫХ ВОДИТЕЛЕЙ-----------------
DECLARE
    autoId   NUMBER;
    personId NUMBER;
    k        NUMBER := 0;

BEGIN
    LOOP
        k := k + 1;

        SELECT id into autoId
        FROM (SELECT id
              FROM AUTO
              ORDER BY dbms_random.RANDOM())
        WHERE rownum = 1;

        SELECT id into personId
        FROM (SELECT *
              FROM AUTO_PERSONNEL
              ORDER BY dbms_random.RANDOM())
        WHERE rownum = 1;

        UPDATE AUTO
        SET PERSONNEL_ID = personId
        WHERE ID = autoId;

        EXIT WHEN (k >= 20);
    END LOOP;
END;
------------------------------------------------------------------------

SELECT * FROM AUTO
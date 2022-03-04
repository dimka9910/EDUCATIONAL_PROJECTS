DELETE
FROM AUTO_PERSONNEL;

SELECT *
FROM AUTO_PERSONNEL;



--------------- ЗАПОЛНЕНИЕ ПЕРСОНАЛОМ----------
DECLARE
    i NUMBER := 0;
    j NUMBER;

BEGIN
    LOOP
        i := i + 1;
        insert into AUTO_PERSONNEL (FIRST_NAME, LAST_NAME, FATHER_NAME) values ('-', '-', '-');
        SELECT MAX(id) into j from AUTO_PERSONNEL;

        UPDATE AUTO_PERSONNEL
        SET FIRST_NAME = CONCAT('Name №', TO_CHAR(j)),  --TRUNC(j/5)
                          LAST_NAME = CONCAT('LAST_NAME №', j),
                          FATHER_NAME = CONCAT('FATHER_NAME №', j)
        WHERE ID = j;

        EXIT WHEN (i >= 15);
    END LOOP;
END;
-----------------------------------------------------ы
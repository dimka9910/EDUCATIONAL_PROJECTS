DELETE FROM ROUTES;

SELECT * FROM ROUTES;



DECLARE
    i NUMBER := 0;
    j NUMBER;
BEGIN
    LOOP			-- start loop 2
    i := i + 1;
    insert into ROUTES (NAME) values ('-');

    SELECT MAX(id) into j from ROUTES;

    UPDATE ROUTES
    SET NAME = CONCAT('ROUTE №', TO_CHAR(j))
    WHERE ID = j;

    EXIT WHEN (i >= 5);
    END LOOP;
END;
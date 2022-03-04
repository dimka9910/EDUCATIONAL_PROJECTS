-- •	модификация по фильтру:
-- 1.	Изменить время прибытия у заданной строки журнала оператора.
SELECT * FROM JOURNAL;

UPDATE JOURNAL
SET TIME_IN = (TO_TIMESTAMP('2021-03-11 23:25:00.000000000', 'YYYY-MM-DD HH24:MI:SS.FF'))
WHERE ID = 63;

-- 2.	Изменить маршрут, по которому следует автомобиль с заданным номером.
SELECT * FROM JOURNAL JOIN AUTO A2 on A2.ID = JOURNAL.AUTO_ID;

UPDATE JOURNAL
SET ROUTE_ID = 3
WHERE ID =
(SELECT j FROM (SELECT JOURNAL.ID as j FROM JOURNAL JOIN AUTO A2 on JOURNAL.AUTO_ID = A2.ID WHERE TIME_IN IS NULL AND NUM = 'NUM №1') WHERE ROWNUM = 1);

-- •	модификация в рамках транзакции:
-- 1.	В рамках транзакции поменять заданный маршрут всех поездок в журнале на другой и удалить заданный маршрут.

DECLARE
    routeIdFrom number := 3;
    routeIdTo number := 13;
BEGIN
    SAVEPOINT a;

    UPDATE JOURNAL
        SET ROUTE_ID = routeIdTo
    WHERE ROUTE_ID = routeIdFrom;

    DELETE FROM ROUTES WHERE id = routeIdFrom;
    ROLLBACK to a;
END;
-- 2.	то же, что и п.1, но транзакцию откатить.

UPDATE AUTO

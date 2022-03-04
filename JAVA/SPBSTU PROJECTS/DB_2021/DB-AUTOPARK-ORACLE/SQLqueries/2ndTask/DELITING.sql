-- Удаление данных
-- •	удаление по фильтру и удаление из связанных таблиц:
-- 1.	Удалить маршрут и все связанные с ним записи в журнале.
SELECT * FROM ROUTES;
SELECT * FROM JOURNAL;

DELETE FROM JOURNAL WHERE ROUTE_ID = 2;
DELETE FROM ROUTES WHERE ID = 2;

-- 2.	Удалить персонал, не имеющий автомобилей.
SELECT * FROM AUTO_PERSONNEL LEFT JOIN AUTO A2 on AUTO_PERSONNEL.ID = A2.PERSONNEL_ID WHERE PERSONNEL_ID is null;

DELETE FROM AUTO_PERSONNEL WHERE NOT EXISTS(SELECT * FROM AUTO WHERE PERSONNEL_ID = AUTO_PERSONNEL.ID) and AUTO_PERSONNEL.ID > 20

-- •	удаление в рамках транзакции:
-- 1.	Удалить в рамках транзакции заданного водителя и его автомобили.

SELECT * FROM AUTO_PERSONNEL LEFT JOIN AUTO A2 on AUTO_PERSONNEL.ID = A2.PERSONNEL_ID ORDER BY AUTO_PERSONNEL.ID;


DECLARE
    id1 NUMBER;
    surname varchar2(50):= 'LAST_NAME №17';
BEGIN
SELECT id into id1 FROM AUTO_PERSONNEL WHERE LAST_NAME = surname;
DELETE FROM AUTO WHERE PERSONNEL_ID = id1;
END;

-- 2.	то же, что и п.1, но транзакцию откатить.
DECLARE
    id1 NUMBER;
    surname varchar2(50):= 'LAST_NAME №20';
BEGIN
    SELECT id into id1 FROM AUTO_PERSONNEL WHERE LAST_NAME = surname;
    SAVEPOINT a;
    DELETE FROM AUTO WHERE PERSONNEL_ID = id1;
    DELETE FROM AUTO_PERSONNEL WHERE id = id1;
    ROLLBACK to a;
END;
-- Выборка данных
-- •	однотабличная выборка:
-- 1.	Вывести ФИО персонала, упорядочив в алфавитном порядке по фамилии и в обратном порядке по имени.
SELECT * FROM AUTO_PERSONNEL ORDER BY FIRST_NAME, LAST_NAME DESC; --сперва сортируем по первому полю, затем 1е остаётся на месте и сортируется второе

-- 2.	Посчитать количество автомобилей, у которых первая буква номера «р».
SELECT * FROM AUTO WHERE LOWER(SUBSTR(NUM,0,1)) = 'p';

SELECT COUNT(*) as "Starts with P" FROM AUTO WHERE LOWER(SUBSTR(NUM,0,1)) = 'p';


-- •	выборка с подзапросами:
-- 1.	Вывести номера автомобилей водителя с заданной фамилией.
SELECT * FROM AUTO LEFT JOIN AUTO_PERSONNEL AP on AP.ID = AUTO.PERSONNEL_ID WHERE LAST_NAME = 'LAST_NAME №1';

SELECT NUM FROM AUTO WHERE PERSONNEL_ID = (SELECT ID FROM (SELECT ID FROM AUTO_PERSONNEL WHERE LAST_NAME = 'LAST_NAME №1') WHERE ROWNUM = 1);

-- 2.	Вывести наименования маршрутов, на которых есть не вернувшиеся автомобили.
SELECT DISTINCT NAME FROM JOURNAL JOIN ROUTES R on JOURNAL.ROUTE_ID = R.ID WHERE JOURNAL.TIME_IN is NULL ORDER BY NAME;

SELECT NAME FROM ROUTES WHERE ID IN (SELECT ROUTE_ID FROM JOURNAL WHERE TIME_IN IS NULL) ORDER BY NAME;


-- •	соединение таблиц (join):
-- 1.	Вывести время отправки из журнала оператора и наименования маршрутов, включая маршруты, по которым рейсов не было.
SELECT TIME_OUT, NAME FROM JOURNAL RIGHT JOIN ROUTES R on R.ID = JOURNAL.ROUTE_ID;

-- 2.	Вывести времена отправки/прибытия из журнала оператора, наименования маршрутов поездок, включая маршруты,
-- по которым не было рейсов, и номера автомобилей, включая автомобили, которые не участвовали в рейсах.
SELECT TIME_OUT, TIME_IN, NUM, NAME FROM JOURNAL RIGHT JOIN ROUTES R on R.ID = JOURNAL.ROUTE_ID FULL JOIN AUTO A2 on A2.ID = JOURNAL.AUTO_ID


-- •	для реализации проекта:
-- 1.	Вывести самое короткое время проезда по заданному наименованием маршруту и номер автомобиля, который поставил рекорд.
SELECT *
FROM JOURNAL WHERE ROUTE_ID = 4;

SELECT time, NUM FROM (SELECT (TIME_IN - TIME_OUT) as time, NUM FROM JOURNAL JOIN AUTO A2 on A2.ID = JOURNAL.AUTO_ID GROUP BY TIME_IN, TIME_OUT, NUM ORDER BY time)
WHERE ROWNUM = 1;

-- 2.	Количество автомобилей, находящихся в рейсе по заданному наименованием маршруту.

SELECT NAME, COUNT(*) FROM JOURNAL JOIN ROUTES R on R.ID = JOURNAL.ROUTE_ID WHERE TIME_IN IS NULL AND NAME = 'ROUTE №4' GROUP BY NAME;




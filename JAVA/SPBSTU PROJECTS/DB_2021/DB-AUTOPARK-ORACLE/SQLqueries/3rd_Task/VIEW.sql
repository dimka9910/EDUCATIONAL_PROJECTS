-- Представления
-- 1.	Создать представление, отображающее всех водителей.
CREATE VIEW drivers1 AS
SELECT *
FROM AUTO_PERSONNEL;

SELECT *
FROM drivers1;



CREATE VIEW drivers2 AS
SELECT *
FROM AUTO_PERSONNEL
WHERE EXISTS(SELECT * FROM AUTO WHERE PERSONNEL_ID = AUTO_PERSONNEL.ID);

SELECT *
FROM drivers2;


-- 2.	Создать представление, отображающее все маршруты и количество автомобилей, находящихся на каждом маршруте.

CREATE VIEW carsOnRoads AS
SELECT NAME, COUNT(NAME) count
FROM ROUTES
         JOIN JOURNAL J on ROUTES.ID = J.ROUTE_ID
         JOIN AUTO A2 on A2.ID = J.AUTO_ID
WHERE J.TIME_IN IS NULL
GROUP BY NAME
ORDER BY NAME;

SELECT *
FROM carsOnRoads;
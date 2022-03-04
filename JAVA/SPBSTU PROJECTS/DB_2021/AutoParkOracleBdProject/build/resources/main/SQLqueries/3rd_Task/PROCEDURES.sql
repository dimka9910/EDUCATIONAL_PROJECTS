-- Хранимые процедуры
-- •	без параметров:
-- 1.	Создать хранимую процедуру, выводящую все маршруты и среднее время проезда по ним в минутах.

CREATE OR REPLACE PROCEDURE AvgTimeOnEachRoad IS
    CURSOR cur1 IS
        SELECT NAME,
               AVG(
                           + EXTRACT(MINUTE FROM INTRVL)
                           + EXTRACT(HOUR FROM INTRVL) * 60
                           + EXTRACT(DAY FROM INTRVL) * 60 * 24) AVERAGE
        FROM (
                 SELECT (TIME_IN - TIME_OUT) INTRVL, NAME
                 FROM ROUTES
                          LEFT JOIN JOURNAL J on ROUTES.ID = J.ROUTE_ID
                 WHERE TIME_IN IS NOT NULL
             )
        GROUP BY NAME;
    var1 varchar2(50);
    var2 long;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Маршрут    ' || '   Среднее время в пути');
    DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------- ');
    OPEN cur1;
    LOOP
        FETCH cur1 INTO var1,var2;
        DBMS_OUTPUT.PUT_LINE(var1 || '          ' || var2);
        EXIT WHEN cur1%NOTFOUND;
    END LOOP;
    CLOSE cur1;
END;


begin
    AvgTimeOnEachRoad;
end;

select *
FROM JOURNAL;


-- •	с входными параметрами:
-- 1.	Создать хранимую процедуру, имеющую два параметра «автомобиль1» и «автомобиль2».
--   Она должна возвращать маршруты, по которым «автомобиль1» проехал быстрее «автомобиля2».
--   Если на каком-либо маршруте один из автомобилей не проезжал, такой маршрут не рассматривается.

CREATE OR REPLACE PROCEDURE procedure2(car1 in int, car2 in int) IS
    CURSOR cur1 IS
        SELECT ROUTE_ID
        FROM (
                 SELECT ROUTE_ID, AUTO_ID, MIN(TIME_IN - TIME_OUT) time
                 FROM JOURNAL
                 WHERE AUTO_ID = car1
                   AND TIME_IN IS NOT NULL
                 GROUP BY ROUTE_ID, AUTO_ID

                 UNION

                 SELECT ROUTE_ID, AUTO_ID, MIN(TIME_IN - TIME_OUT) time
                 FROM JOURNAL
                 WHERE AUTO_ID = car2
                   AND TIME_IN IS NOT NULL
                 GROUP BY ROUTE_ID, AUTO_ID
             )

                 JOIN

             (SELECT MIN(TIME) as ttt, ROUTE_ID as nnn
              FROM (
                       SELECT ROUTE_ID, AUTO_ID, MIN(TIME_IN - TIME_OUT) time
                       FROM JOURNAL jj
                       WHERE AUTO_ID = car1
                         AND TIME_IN IS NOT NULL
                         AND EXISTS(SELECT *
                                    FROM JOURNAL
                                    WHERE JOURNAL.AUTO_ID = car2
                                      AND JOURNAL.ROUTE_ID = jj.ROUTE_ID
                                      AND TIME_IN IS NOT NULL)
                       GROUP BY ROUTE_ID, AUTO_ID

                       UNION

                       SELECT ROUTE_ID, AUTO_ID, MIN(TIME_IN - TIME_OUT) time
                       FROM JOURNAL jj
                       WHERE AUTO_ID = car2
                         AND TIME_IN IS NOT NULL
                         AND EXISTS(SELECT *
                                    FROM JOURNAL
                                    WHERE JOURNAL.AUTO_ID = car1
                                      AND JOURNAL.ROUTE_ID = jj.ROUTE_ID
                                      AND TIME_IN IS NOT NULL)
                       GROUP BY ROUTE_ID, AUTO_ID
                   )
              GROUP BY ROUTE_ID)
             on time = ttt and ROUTE_ID = nnn;
    var2 long;
BEGIN

    DBMS_OUTPUT.PUT_LINE('Маршрут    ');
    DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------- ');
    OPEN cur1;
    LOOP
        FETCH cur1 INTO var2;
        EXIT WHEN cur1%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(var2);
    END LOOP;
    CLOSE cur1;
end;

BEGIN
    procedure2(2, 5);
end;



-- •	с выходными параметрами:
-- 1.	Создать хранимую процедуру с входным параметром «маршрут» и двумя выходными параметрами, возвращающими самое короткое время проезда по заданному маршруту, и автомобиль, поставивший рекорд.

SELECT *
FROM ROUTES
         JOIN JOURNAL J on ROUTES.ID = J.ROUTE_ID;

CREATE OR REPLACE
    PROCEDURE MinTimeOnRoad(route_id_in IN int, car OUT int, time OUT INTERVAL DAY TO SECOND)
    IS
BEGIN
    select (TIME_IN - TIME_OUT) as lol
    into time
    FROM AUTO
             join JOURNAL J on AUTO.ID = J.AUTO_ID
    where (TIME_IN - TIME_OUT) in
          (SELECT MIN(TIME_IN - TIME_OUT) as t FROM (SELECT * FROM JOURNAL WHERE route_id = route_id_in));

    select AUTO_ID
    into car
    FROM AUTO
             join JOURNAL J on AUTO.ID = J.AUTO_ID
    where (TIME_IN - TIME_OUT) in
          (SELECT MIN(TIME_IN - TIME_OUT) as t FROM (SELECT * FROM JOURNAL WHERE route_id = route_id_in));
end;



DECLARE
    car  INT;
    time INTERVAL DAY TO SECOND;
begin
    MinTimeOnRoad(1, car, time);
    DBMS_OUTPUT.PUT_LINE('Auto Num = ' || car);
    DBMS_OUTPUT.PUT_LINE('Time In Road = ' || time);
end;


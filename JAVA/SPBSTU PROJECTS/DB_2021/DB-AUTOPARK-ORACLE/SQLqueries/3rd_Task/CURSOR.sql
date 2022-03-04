CREATE OR REPLACE PROCEDURE reward(from1 in TIMESTAMP,
                                   to2 in TIMESTAMP,
                                   totalReward in NUMBER,
                                   Id1 OUT NUMBER,
                                   Id2 OUT NUMBER,
                                   Id3 OUT NUMBER,
                                   reward1 OUT float,
                                   reward2 OUT float,
                                   reward3 OUT float)
    IS
    CURSOR PERSONNEL
        IS
        SELECT COUNT(PERSONNEL_ID) as ccc, PERSONNEL_ID FROM (SELECT ROUTE_ID, MIN(TIME_IN - TIME_OUT) tutu
                                                              FROM JOURNAL
                                                                       JOIN AUTO A2 on JOURNAL.AUTO_ID = A2.ID
                                                              where TIME_IN is not NULL AND TIME_OUT BETWEEN from1 AND to2
                                                              GROUP BY ROUTE_ID) JOIN
                                                             (SELECT (TIME_IN - TIME_OUT) as titi, ROUTE_ID, PERSONNEL_ID
                                                              FROM JOURNAL
                                                                       JOIN AUTO A2 on JOURNAL.AUTO_ID = A2.ID
                                                              where TIME_IN is not NULL AND PERSONNEL_ID is not null
                                                             ) on tutu = titi GROUP BY PERSONNEL_ID ORDER BY ccc DESC;
    topCount     number;
    currentPersonnelId number;
    counter number:= 0;

    TYPE array_t IS TABLE OF NUMBER  -- Associative array type
        INDEX BY VARCHAR2(64);
BEGIN

    counter := 0;
    Id1 := -1;
    Id2 := -1;
    Id3 := -1;

    open PERSONNEL;
    LOOP
        FETCH PERSONNEL INTO topCount, currentPersonnelId;
        EXIT WHEN PERSONNEL%NOTFOUND OR counter = 3;
        counter := counter + 1;
        if (Id1 < 0) then
            Id1 := currentPersonnelId;
        ELSIF
            (Id2 < 0) then
            Id2 := currentPersonnelId;
        ELSIF
            (Id3 < 0) then
            Id3 := currentPersonnelId;
        end if;
    end loop;
    close PERSONNEL;


    reward1 := totalReward * 0.5;
    reward2 := totalReward * 0.3;
    reward3 := totalReward * 0.2;
END;


DECLARE
    Id1         NUMBER;
    Id2         NUMBER;
    Id3         NUMBER;
    reward1     float;
    reward2     float;
    reward3     float;
begin
    reward(TIMESTAMP '2020-04-03 23:57:03.000', TIMESTAMP '2023-04-03 23:57:03.000',125,Id1,Id2,Id3,reward1,reward2,reward3);
    DBMS_OUTPUT.PUT_LINE('Person1 = ' || Id1 );
    DBMS_OUTPUT.PUT_LINE('Person2 = ' || Id2 );
    DBMS_OUTPUT.PUT_LINE('Person3 = ' || Id3 );
    DBMS_OUTPUT.PUT_LINE('Reward1 = ' || reward1 );
    DBMS_OUTPUT.PUT_LINE('Reward2 = ' || reward2 );
    DBMS_OUTPUT.PUT_LINE('Reward3 = ' || reward3 );
end;

use LantHotelier;
go
delete from Log_Serviciu;
delete from Log_RezervareServiciu;
delete from Log_Rezervare;

--TESTARE CRUDS pe tabele implicate in m:n
--=========CRUDS PE SERVICIU====================
--create valid
exec S_Create 'dfghjklkjhgfd', 102;
select * from Serviciu ORDER BY id_serviciu ASC;


--create invalid
exec S_Create '' ,-10;
select * from Serviciu ORDER BY id_serviciu ASC;

--delete valid
exec S_Delete 18;
select * from Serviciu ORDER BY id_serviciu ASC;
select * from Log_Serviciu;

--delete invalid
exec S_Delete 420; --nu arunc eroare, nu se sterge nimic din tabela, nu inserez nimic in log_serviciu


--update valid

exec S_Update 17 ,'ionica', 344.77;
select * from Serviciu;
select * from Log_Serviciu;

--update invalid

exec S_update 17, ' ', 10;
select * from Serviciu;
select * from Log_Serviciu;



--read
exec S_Read 1;

--===================CRUDS PE REZERVARE=============================

--create valid
EXEC R_Create 11, '2025-06-10', '2025-06-15', 500;
SELECT * FROM Rezervare;


--create invalid
--ceva cu o camera ocupata(inexistenta)/ date fara sens stil calatorie in timp / hotelul sa te plateasca sa dormi la ei etc
EXEC R_Create 11, '2025-06-10', '2025-06-15', 500;
EXEC R_Create 12, '2026-06-10', '2025-06-15', 500;
EXEC R_Create 12, '2025-06-10', '2025-06-15', -10;
EXEC R_Create 999, '2025-06-10', '2025-06-12', 200;
SELECT * FROM Rezervare;
--delete
exec R_Delete 11;

--update
--valid
EXEC R_Update 1, 1, '2099-06-11', '2100-06-16', 650;
SELECT * FROM Rezervare;
SELECT * FROM Log_Rezervare;
--invalid
EXEC R_Update 1, 1, '2099-06-11', '2099-06-16', 1;


--read
exec R_Read 1;

--==================CRUDS PE REZERVARESERVICIU=======================

--create
EXEC RS_Create 2, 3;
SELECT * FROM RezervareServiciu;
--read
exec RS_Read 1,1;
--update
EXEC RS_Update 2, 3, 4;
SELECT * FROM RezervareServiciu;
SELECT * FROM Log_RezervareServiciu;
--delete
EXEC RS_Delete 2, 4;
SELECT * FROM RezervareServiciu;
SELECT * FROM Log_RezervareServiciu;
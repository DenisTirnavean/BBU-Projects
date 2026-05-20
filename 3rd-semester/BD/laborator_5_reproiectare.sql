use LantHotelier_backup;
GO

CREATE TABLE Legaturi_eliminate(
NumeTabelSt VARCHAR(50),
IdSt INT,
NumeTabelDr VARCHAR(50),
IdDr INT
);

CREATE TABLE Masini(
	id_client INT,
	id_masina INT IDENTITY PRIMARY KEY,
	numar_inmatriculare VARCHAR(50),
	marca VARCHAR(50),
	model VARCHAR(50),
	culoare VARCHAR(50),
	CONSTRAINT fk_masini_id_client FOREIGN KEY(id_client) REFERENCES Client(id_client) ON UPDATE CASCADE ON DELETE CASCADE
);


INSERT INTO Masini (id_client, numar_inmatriculare, marca, model, culoare) VALUES
(1, 'B-101-ABC', 'Dacia', 'Logan', 'Alb'),
(1, 'B-245-XYZ', 'Volkswagen', 'Golf', 'Negru'),
(1, 'CJ-23-MMM', 'BMW', 'X5', 'Gri'),
(2, 'IF-88-RTY', 'Audi', 'A4', 'Albastru'),
(3, 'TM-55-KLM', 'Mercedes', 'C200', 'Rosu'),
(4, 'BV-09-HHH', 'Ford', 'Focus', 'Alb'),
(5, 'BT-44-QWE', 'Toyota', 'Corolla', 'Argintiu'),
(6, 'GL-72-ZZZ', 'Renault', 'Megane', 'Verde'),
(8, 'CT-33-BBB', 'Skoda', 'Octavia', 'Negru'),
(9, 'PH-18-AAA', 'Hyundai', 'Tucson', 'Bej'),
(8, 'CJ-49-DEN', 'Volkswagen', 'Golf4', 'Argintiu'),
(8, 'MS-72-ION', 'Lambourghini', 'Huracan', 'Rosu ca focu'),
(7, 'CT-99-BOS', 'Ford', 'Transporter', 'Alb,rosu,albastru(ambulanta)'),
(7, 'PH-18-WAD', 'Ford', 'Focus', 'RebeccaPurple');


--relatii de modificat
-- 3 relatii 1:n
--		1:n =====> n:1 (aici voi modifica client-masini ( adaug tabela masini in relatie n:1 cu client ca sa pastrez toate tabele implicate distincte))
--		1:n ======> m:n (aici voi modifica program-angajat)
--		1:n ======> 1:1	(aici voi modifica hotel-camera)
-- 1 relatie m:n
--		m:n ======> 1:n	(aici voi modifica rezervare-serviciu)

--1:n ====> n:1 mut cheia straina din tabela cu n in tabela cu 1
--Client(1) ---> Masini(n) o fac in Client(n) --->Masini(1)

ALTER TABLE Client
ADD id_masina INT;

UPDATE Client SET id_masina = (
    SELECT MAX(id_masina)
    FROM Masini
    WHERE Masini.id_client = Client.id_client
);

INSERT INTO Legaturi_eliminate
SELECT 'Client', M.id_client,'Masini', M.id_masina
FROM Masini M
WHERE M.id_masina NOT IN (
    SELECT id_masina FROM Client WHERE id_masina IS NOT NULL
);
ALTER TABLE Masini DROP CONSTRAINT fk_masini_id_client;
ALTER TABLE Masini DROP COLUMN id_client;

ALTER TABLE Client
ADD CONSTRAINT FK_Client_Masini FOREIGN KEY (id_masina) REFERENCES Masini(id_masina);

SELECT * FROM Legaturi_eliminate;
SELECT * FROM Client;
SELECT * FROM Masini;

--1:n ====>1:1 declar cheia straina ca fiind unique
--Hotel(1)----> Camera(n) transform in Hotel(1)-->Camera(1)

INSERT INTO Legaturi_eliminate
SELECT 'Hotel', C.id_hotel,'Camera', C.id_camera
FROM Camera C
WHERE C.id_camera NOT IN (
    SELECT MAX(id_camera) FROM Camera
	GROUP BY id_hotel
);

DELETE FROM Camera WHERE id_camera NOT IN (
    SELECT MAX(id_camera) FROM Camera
	GROUP BY id_hotel
);

ALTER TABLE Camera
ADD CONSTRAINT Uniq_camera_hotel UNIQUE(id_hotel);

select * from Camera;
select * from Hotel;
--1:n ====> m:n tabela de legatura yay
--Angajat(1)---> Program(n) il transform in Angajat(m) ---> Program(n), adaug tabela AngajatProgram, lejer

CREATE TABLE AngajatProgram(
	id_angajat INT,
	id_program INT,
	CONSTRAINT FK_id_angajat_angajatprogram FOREIGN KEY(id_angajat) REFERENCES Angajat(id_angajat),
	CONSTRAINT FK_id_program_angajatprogram FOREIGN KEY(id_program) REFERENCES Program(id_program)
);

INSERT INTO AngajatProgram SELECT id_angajat, id_program FROM Program;

ALTER TABLE Program
Drop CONSTRAINT FK_id_angajat;

ALTER TABLE Program
DROP column id_angajat;

select * from AngajatProgram;

--m:n ===> 1:n sterg tabela de legatura, adaug o cheie straina undeva intr-una din tabele, populata pe baza intrarilor din tabela de legatura 
--Serviciu(m)---> Rezervare(n) o transform in Serviciu(1)--->Rezervare(n),  
--o rezervare poate avea maxim un serviciu, un servicu se poate aplica la mai multe rezervari, deci cheia straina logic ar fi sa o pun
-- in ...  rezervare

alter table Rezervare
add id_serviciu INT;

UPDATE Rezervare SET id_serviciu = (
    SELECT MAX(id_serviciu)
    FROM RezervareServiciu
    WHERE RezervareServiciu.id_rezervare = Rezervare.id_rezervare
);

INSERT INTO Legaturi_eliminate
SELECT 'Rezervare', RS.id_rezervare,'Serviciu', RS.id_serviciu
FROM RezervareServiciu RS
WHERE RS.id_serviciu NOT IN (
    SELECT id_serviciu FROM Rezervare WHERE Rezervare.id_rezervare = RS.id_rezervare
);

ALTER TABLE Rezervare
ADD CONSTRAINT FK_Rezervare_Serviciu FOREIGN KEY (id_serviciu) REFERENCES Serviciu(id_serviciu);

DROP TABLE RezervareServiciu;

select * from Rezervare;
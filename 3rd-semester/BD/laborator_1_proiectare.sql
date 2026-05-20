CREATE DATABASE LantHotelier;
GO
USE LantHotelier;


CREATE TABLE Hotel(
	id_hotel INT IDENTITY(1,1),
	nume VARCHAR(100) NOT NULL,
	adresa VARCHAR(100) NOT NULL,
	telefon NVARCHAR(15) NOT NULL,
	email NVARCHAR(30) NOT NULL,
	CONSTRAINT PK_Hotel PRIMARY KEY (id_hotel),
	CONSTRAINT UNQ_nume UNIQUE (nume)
);


CREATE TABLE Camera(
	id_camera INT IDENTITY,
	id_hotel INT,
	numar_camera INT,
	tip VARCHAR(50),
	pret_noapte FLOAT,
	CONSTRAINT PK_id_camera PRIMARY KEY (id_camera),
	CONSTRAINT FK_id_hotel FOREIGN KEY (id_hotel) REFERENCES Hotel(id_hotel) ON UPDATE CASCADE ON DELETE CASCADE
);

--worker dude: menajera, bucatar, paznic, lobby clerk, room-service thing, cel cu bagajele ::skull::
CREATE TABLE Angajat(
	id_angajat INT IDENTITY,
	id_hotel INT,
	nume NVARCHAR(30) NOT NULL,
	functie NVARCHAR(100) NOT NULL,
	salariu INT,
	telefon NVARCHAR(15) NOT NULL,
	CONSTRAINT PK_id_angajat PRIMARY KEY (id_angajat),
	CONSTRAINT FK2_id_hotel FOREIGN KEY (id_hotel) REFERENCES Hotel(id_hotel)
);
--un angajat poate avea program flexibil, adica mai multe programe de lucru
CREATE TABLE Program(
	id_program INT IDENTITY(1,1),
	id_angajat INT,
	data_program DATE,
	inceput DATETIME,
	sfarsit DATETIME,
	CONSTRAINT PK_id_program PRIMARY KEY (id_program),
	CONSTRAINT FK_id_angajat FOREIGN KEY (id_angajat) REFERENCES Angajat(id_angajat)
);
--average guy
CREATE TABLE Client(
	id_client INT PRIMARY KEY IDENTITY(1,1),
	nume NVARCHAR(40),
	prenume NVARCHAR(40),
	telefon NVARCHAR(15),
	email NVARCHAR(30)
);
--o camera per rezervare, vrei mai multe camere n-ai csf, mai multe rezervari
CREATE TABLE Rezervare(
	id_rezervare INT IDENTITY NOT NULL,
	id_camera INT UNIQUE NOT NULL,
	checkIn DATETIME NOT NULL,
	checkOut DATETIME NOT NULL,
	sold_plata FLOAT NOT NULL,
	CONSTRAINT PK_id_rezervare PRIMARY KEY (id_rezervare),
	CONSTRAINT FK_id_camera FOREIGN KEY (id_camera) REFERENCES Camera(id_camera)
);

--un client poate avea mai multe rezervari, o rezervare poate avea mai multi clienti(familie, cuplu, etc)
CREATE TABLE RezervareClient(
	id_client INT NOT NULL,
	id_rezervare INT NOT NULL,
	CONSTRAINT FK_id_client_rezervare FOREIGN KEY (id_client) REFERENCES Client(id_client) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT FK_id_rezervare_client FOREIGN KEY (id_rezervare) REFERENCES Rezervare(id_rezervare) ON UPDATE CASCADE ON DELETE CASCADE
);

--serviciu = room service and other bs
CREATE TABLE Serviciu(
	id_serviciu INT IDENTITY(1,1),
	nume NVARCHAR(41),
	pret FLOAT,
	CONSTRAINT PK_id_serviciu PRIMARY KEY (id_serviciu)
);

--o rezervare poate cere mai multe servicii(daca ai bani totul este posibil), 
--un serviciu poate fi oferit mai multor rezervari
CREATE TABLE RezervareServiciu(
	id_rezervare INT,
	id_serviciu INT,
	CONSTRAINT FK_id_rezervare_serviciu FOREIGN KEY (id_rezervare) REFERENCES Rezervare(id_rezervare) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT FK_id_serviciu_rezervare FOREIGN KEY (id_serviciu) REFERENCES Serviciu(id_serviciu) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Plata(
	id_plata INT PRIMARY KEY IDENTITY,
	id_rezervare INT NOT NULL,
	data_plata DATETIME NOT NULL,
	suma FLOAT NOT NULL,
	metoda_plata NVARCHAR(20),
	FOREIGN KEY (id_rezervare) REFERENCES Rezervare(id_rezervare)
);
--o factura poate avea doar o singura plata, foreign key unique lmao
CREATE TABLE Factura(
	id_factura INT PRIMARY KEY IDENTITY,
	id_plata INT UNIQUE NOT NULL,
	numar_factura INT NOT NULL,
	data_emiterii DATETIME NOT NULL,
	FOREIGN KEY (id_plata) REFERENCES Plata(id_plata)
);

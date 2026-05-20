USE LantHotelier;
GO

-- Hoteluri
INSERT INTO Hotel (nume, adresa, telefon, email)
VALUES 
('Hotel Luxor', 'Bd. Unirii 10, Bucuresti', '0722123456', 'contact@luxor.ro'),
('Hotel Marina', 'Str. Marea 25, Constanta', '0733556677', 'info@marina.ro'),
('Hotel Montana', 'Str. Valea Frumoasa 12, Brasov', '0744111222', 'contact@montana.ro');
INSERT INTO Hotel (nume, adresa, telefon, email)
VALUES 
('Hotel Royal', 'Str. Principala 10, Bucuresti', '0722123456', 'contact@royal.ro'),
('Hotel Clooj', 'Splaiul independentei 23, Cluj', '0723344556', 'info@clooj.ro'),
('Hotel Muresh', 'Str. Bradului 5, Targu-Mures', '0722765432', 'contact@muresh.ro');


-- Camere
INSERT INTO Camera (id_hotel, numar_camera, tip, pret_noapte)
VALUES
(1, 101, 'Single', 250),
(1, 102, 'Double', 380),
(2, 201, 'Suite', 500),
(2, 202, 'Double', 350),
(3, 301, 'Single', 220),
(3, 302, 'Deluxe', 600);
INSERT INTO Camera (id_hotel, numar_camera, tip, pret_noapte)
VALUES
(4, 101, 'Single', 300),
(4, 102, 'Double', 450),
(4, 201, 'Suite', 700),
(5, 101, 'Single', 280),
(5, 102, 'Double', 520),
(6, 101, 'Double', 480),
(6, 202, 'Suite', 800);

-- Angajati
INSERT INTO Angajat (id_hotel, nume, functie, salariu, telefon)
VALUES
(1, 'Ion Popescu', 'Menajera', 3200, '0711111111'),
(1, 'Elena Ionescu', 'Receptioner', 4000, '0722222222'),
(2, 'Vasile Georgescu', 'Bucatar', 4500, '0733333333'),
(2, 'Maria Dinu', 'Room Service', 3000, '0744444444'),
(3, 'Radu Matei', 'Paznic', 2800, '0755555555');

INSERT INTO Angajat (id_hotel, nume, functie, salariu, telefon)
VALUES
(4, 'Ionescu Maria', 'Receptioner', 3500, '0711223344'),
(4, 'Popescu Andrei', 'Manager', 6000, '0722334455'),
(5, 'Dumitrescu Ana', 'Bucatar', 4200, '0733445566'),
(5, 'Radu Mihai', 'Menajera', 2800, '0744556677'),
(6, 'Stoica Elena', 'Receptioner', 3700, '0755667788'),
(6, 'Denis', 'Patron', 8000, '0748606729');


-- Programe de lucru
INSERT INTO Program (id_angajat, data_program, inceput, sfarsit)
VALUES
(1, '2025-10-10', '2025-10-10 08:00', '2025-10-10 16:00'),
(1, '2025-10-11', '2025-10-11 10:00', '2025-10-11 18:00'),
(2, '2025-10-10', '2025-10-10 09:00', '2025-10-10 17:00'),
(3, '2025-10-10', '2025-10-10 07:00', '2025-10-10 15:00'),
(4, '2025-10-11', '2025-10-11 14:00', '2025-10-11 22:00');
INSERT INTO Program (id_angajat, data_program, inceput, sfarsit)
VALUES
(5, '2025-10-01', '2025-10-01 08:00', '2025-10-01 16:00'),
(5, '2025-10-02', '2025-10-02 08:00', '2025-10-02 16:00'),
(6, '2025-10-01', '2025-10-01 09:00', '2025-10-01 17:00'),
(6, '2025-10-03', '2025-10-03 10:00', '2025-10-03 18:00'),
(7, '2025-10-04', '2025-10-04 08:00', '2025-10-04 16:00');


-- Clienti
INSERT INTO Client (nume, prenume, telefon, email)
VALUES
('Popa', 'Andrei', '0761111111', 'andrei.popa@gmail.com'),
('Marinescu', 'Ioana', '0762222222', 'ioana.m@gmail.com'),
('Gheorghiu', 'Radu', '0763333333', 'radu.g@yahoo.com'),
('Petrescu', 'Elena', '0764444444', 'elena.p@yahoo.com');
INSERT INTO Client (nume, prenume, telefon, email)
VALUES
('Pop', 'Ion al Glanetasului', '0766554433', 'ion.pop@sapa.com'),
('Eusebiu', 'Eusebiu', '0766778899', 'fakemaileusebiu@yahoo.com'),
('Dexter', 'Morgan', '0755887766', 'patrickbateman@gmail.com'),
('Klaus', 'Iohanis', '0744998877', 'klausica@pnl.com'),
('VIctor', 'Ponta', '0744998877', 'klausica@pnl.com');


-- Rezervari
INSERT INTO Rezervare (id_camera, checkIn, checkOut, sold_plata)
VALUES
(1, '2025-10-12 14:00', '2025-10-15 12:00', 750),
(2, '2025-10-20 15:00', '2025-10-23 11:00', 1140),
(3, '2025-10-10 14:00', '2025-10-13 12:00', 1500),
(5, '2025-11-01 16:00', '2025-11-03 10:00', 440);
INSERT INTO Rezervare (id_camera, checkIn, checkOut, sold_plata)
VALUES
(6, '2025-02-10', '2025-02-15', 1200),
(7, '2025-03-01', '2025-03-03', 900),
(8, '2025-03-15', '2025-03-20', 3500),
(9, '2025-04-01', '2025-04-05', 2100),
(10, '2025-06-10', '2025-06-15', 4000);


-- RezervareClient
INSERT INTO RezervareClient (id_client, id_rezervare)
VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(1, 2);
INSERT INTO RezervareClient (id_client, id_rezervare)
VALUES
(5, 5),
(6, 6),
(7, 7),
(8, 8),
(5, 9);



-- Servicii
INSERT INTO Serviciu (nume, pret)
VALUES
('Room Service', 80),
('Spa Access', 150),
('Mic dejun inclus', 50),
('Transfer Aeroport', 100);
INSERT INTO Serviciu (nume, pret)
VALUES
('Bancuri', 150),
('Parcare', 300),
('ViP', 50),
('Netflix', 30),
('Masaj tailandez', 200);

-- RezervareServiciu
INSERT INTO RezervareServiciu (id_rezervare, id_serviciu)
VALUES
(1, 1),
(1, 3),
(2, 2),
(3, 4),
(4, 1),
(4, 2);
INSERT INTO RezervareServiciu (id_rezervare, id_serviciu)
VALUES
(9, 9),
(5, 9),
(5, 8),
(6, 7),
(6, 5),
(7, 5),
(7, 6),
(8, 2);

-- Plati
INSERT INTO Plata (id_rezervare, data_plata, suma, metoda_plata)
VALUES
(1, '2025-10-10', 750, 'Card'),
(2, '2025-10-18', 1140, 'Cash'),
(3, '2025-10-09', 1500, 'Transfer bancar'),
(4, '2025-10-30', 440, 'Card');
INSERT INTO Plata (id_rezervare, data_plata, suma, metoda_plata)
VALUES
(5, '2025-02-15', 1200, 'Munca fizica'),
(6, '2025-03-03', 900, 'Cash'),
(7, '2025-03-20', 3500, 'Card'),
(8, '2025-04-05', 2100, 'Card'),
(9, '2025-06-15', 4000, 'Transfer Bancar');

select * from Plata;
-- Facturi
INSERT INTO Factura (id_plata, numar_factura, data_emiterii)
VALUES
(1, 1001, '2025-10-10'),
(2, 1002, '2025-10-18'),
(3, 1003, '2025-10-09'),
(4, 1004, '2025-10-30');

INSERT INTO Factura (id_plata, numar_factura, data_emiterii)
VALUES
(5, 1001, '2025-02-15'),
(6, 1002, '2025-03-03'),
(7, 1003, '2025-03-20'),
(8, 1004, '2025-04-05'),
(9, 1005, '2025-06-15');


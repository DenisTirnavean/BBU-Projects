--Selectari/ Interogari in baza de date, lab 3- Baze de date
use LantHotelier;
go


--1--la ce hoteluri s-a cazat fiecare client--------------------------
SELECT DISTINCT cl.nume, cl.prenume, h.nume AS Hotel
FROM Client cl
JOIN RezervareClient rc ON cl.id_client = rc.id_client
JOIN Rezervare r ON rc.id_rezervare = r.id_rezervare
JOIN Camera c ON r.id_camera = c.id_camera
JOIN Hotel h ON c.id_hotel = h.id_hotel;


--2--Clientii care au mai mult de 1000 de lei de plata---------------------------------------------------------

SELECT cl.nume, cl.prenume, SUM(p.suma) AS TotalPlatit
FROM Client cl
JOIN RezervareClient rc ON cl.id_client = rc.id_client
JOIN Rezervare r ON rc.id_rezervare = r.id_rezervare
JOIN Plata p ON r.id_rezervare = p.id_rezervare
GROUP BY cl.nume, cl.prenume
HAVING SUM(p.suma) > 1000;

--3--Toti clientii care au beneficiat de servicii--------------------------------------------------------------------------------

SELECT DISTINCT cl.nume, cl.prenume, s.nume AS Serviciu
FROM Client cl
JOIN RezervareClient rc ON cl.id_client = rc.id_client
JOIN Rezervare r ON rc.id_rezervare = r.id_rezervare
JOIN RezervareServiciu rs ON r.id_rezervare = rs.id_rezervare
JOIN Serviciu s ON rs.id_serviciu = s.id_serviciu;

--4--Toate facturile emise in anul 2025-------------------------------------------------------------------------------

SELECT h.nume AS Hotel, f.numar_factura, f.data_emiterii, p.suma
FROM Factura f
JOIN Plata p ON f.id_plata = p.id_plata
JOIN Rezervare r ON p.id_rezervare = r.id_rezervare
JOIN Camera c ON r.id_camera = c.id_camera
JOIN Hotel h ON c.id_hotel = h.id_hotel
WHERE f.data_emiterii BETWEEN '2025-01-01' AND '2025-12-31';



--5--Numarul de camere si cat costa o camera in medie per hotel-------------------------------------------------------------------------------

SELECT h.nume AS Hotel, COUNT(c.id_camera) AS NrCamere, AVG(c.pret_noapte) AS PretMediu
FROM Hotel h
JOIN Camera c ON h.id_hotel = c.id_hotel
GROUP BY h.nume;


---6--Clientii care au rezervat camere scumpe-------------------------------------------------------------------------------

SELECT cl.nume, cl.prenume, c.numar_camera, c.pret_noapte
FROM Client cl
JOIN RezervareClient rc ON cl.id_client = rc.id_client
JOIN Rezervare r ON rc.id_rezervare = r.id_rezervare
JOIN Camera c ON r.id_camera = c.id_camera
WHERE c.pret_noapte > 500;


--7--Venit total pe hotel--------------------------------------------------------------------------------

SELECT h.nume AS Hotel, SUM(p.suma) AS VenitTotal
FROM Hotel h
JOIN Camera c ON h.id_hotel = c.id_hotel
JOIN Rezervare r ON c.id_camera = r.id_camera
JOIN Plata p ON r.id_rezervare = p.id_rezervare
GROUP BY h.nume;


--8--Angajatii care muncesc in hoteluri de lux---------------------------------------------------------------------------------

SELECT DISTINCT a.nume AS Angajat, a.functie, h.nume AS Hotel
FROM Angajat a
JOIN Hotel h ON a.id_hotel = h.id_hotel
JOIN Camera c ON h.id_hotel = c.id_hotel
WHERE c.pret_noapte > 400;


--9--Salariul mediu pe functiile 'bine platite'------------------------------------------------------------------------------------

SELECT functie, AVG(salariu) AS SalariuMediu
FROM Angajat
GROUP BY functie
HAVING AVG(salariu) > 4000;

--10--Programele de lucru ale angajatilor din Royal----------------------------------------------------------------------------------

SELECT h.nume AS Hotel, a.nume AS Angajat, p.data_program, p.inceput, p.sfarsit
FROM Program p
JOIN Angajat a ON p.id_angajat = a.id_angajat
JOIN Hotel h ON a.id_hotel = h.id_hotel
WHERE h.nume = 'Hotel Royal';





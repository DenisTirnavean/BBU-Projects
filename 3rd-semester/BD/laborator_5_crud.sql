--=======cruds pe rezervare-serviciu===============
USE LantHotelier;
GO

select * from Log_Rezervare;
SELECT * FROM Log_Serviciu;
select * from Log_RezervareServiciu;
--cruds pe serviciu
ALTER TABLE Serviciu
ADD CONSTRAINT pret_valid_serviciu check (pret>0);

GO
CREATE FUNCTION ValidService(@nume VARCHAR(41), @pret FLOAT)
returns bit
as
begin
    IF EXISTS(SELECT 1 FROM Serviciu WHERE nume=@nume and pret = @pret)
        BEGIN
            return 0
        END;
    IF (@pret<0)
        BEGIN
            return 0
        END;
    IF (LTRIM(@nume)= '')
        BEGIN
            return 0
        END;
    if LEN(@nume) < 3
        BEGIN
            return 0
        END;
    return 1
end;
go

--c
GO
create procedure S_Create @nume NVARCHAR(41), @pret FLOAT
AS
BEGIN
    if dbo.ValidService(@nume,@pret)=0
    BEGIN
        RAISERROR('Serviciu invalid', 16, 1);
        RETURN;
    END
    INSERT INTO Serviciu(nume,pret) VALUES(@nume, @pret)
END;
GO

--r

CREATE procedure S_Read @id_serviciu INT
as
begin
    select * from Serviciu where id_serviciu=@id_serviciu;
end;
go



--u

CREATE PROCEDURE S_Update @id_serviciu INT, @nume NVARCHAR(41), @pret FLOAT
AS
BEGIN
    if dbo.ValidService(@nume,@pret) =0
    BEGIN
        RAISERROR('Update invalid',16,1)
        return;
    END;
    UPDATE Serviciu set nume = @nume, pret = @pret where id_serviciu=@id_serviciu;
END;
GO



--d
CREATE PROCEDURE S_Delete @id_serviciu INT
AS 
BEGIN
    DELETE FROM Serviciu where id_serviciu = @id_serviciu;
END;

--cruds pe rezervare
ALTER TABLE Rezervare
ADD CONSTRAINT sold_valid_rezervare check(sold_plata>0);

ALTER TABLE Rezervare 
ADD CONSTRAINT date_valide_check CHECK (checkIn < checkOut);

go
CREATE FUNCTION ValidRezervare(@id_camera INT, @checkIn DATETIME, @checkOut DATETIME, @sold_plata FLOAT)
returns bit
as
begin
    IF EXISTS (SELECT 1 from Rezervare WHERE 
        id_camera = @id_camera and checkIn = @checkIn and checkOut = @checkOut and sold_plata = @sold_plata)
        BEGIN
            return 0
        END;
    IF @checkIn>@checkOut
        Begin
            return 0
        End;
    IF @sold_plata<0
        BEGin
            return 0
        END;
    IF NOT EXISTS(Select 1 from Camera where id_camera = @id_camera)
        Begin
            return 0
        end;
    return 1
end;


go
--c
GO
create procedure R_Create @id_camera INT, @checkIn DATETIME, @checkOut DATETIME, @sold_plata FLOAT
AS
BEGIN
    if dbo.ValidRezervare(@id_camera,@checkIn, @checkOut, @sold_plata)=0
    BEGIN
        RAISERROR('Rezervare invalida', 16, 1);
        RETURN;
    END
    INSERT INTO Rezervare(id_camera,checkIn, checkOut, sold_plata) VALUES(@id_camera,@checkIn, @checkOut, @sold_plata);
END;
GO
--r

CREATE procedure R_Read @id_rezervare INT
as
begin
    select * from Rezervare where id_rezervare = @id_rezervare;
end;
go



--u
CREATE PROCEDURE R_Update @id_rezervare INT, @id_camera INT, @checkIn DATETIME, @checkOut DATETIME, @sold_plata FLOAT
AS
BEGIN

    IF dbo.ValidRezervare(@id_camera,@checkIn, @checkOut, @sold_plata) =0
    BEGIN
        RAISERROR('Update invalid',16,1)
        RETURN;
    END;
    UPDATE Rezervare
    set id_camera = @id_camera , checkIn= @checkIn, checkOut =@checkOut
        ,sold_plata = @sold_plata
    where id_rezervare=@id_rezervare;
END;
GO



--d

CREATE PROCEDURE R_Delete @id_rezervare INT
AS 
BEGIN
    DELETE FROM Rezervare where id_rezervare= @id_rezervare;
END;


--crud pe tabela de legatura

--validare
GO
CREATE FUNCTION ValidRezervareServiciu(@id_rezervare INT, @id_serviciu INT)
RETURNS BIT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM RezervareServiciu
        WHERE id_rezervare = @id_rezervare
          AND id_serviciu = @id_serviciu
    )
        RETURN 0;
    RETURN 1;
END;

--create
GO
CREATE PROCEDURE RS_Create @id_rezervare INT, @id_serviciu INT
AS
BEGIN
    IF dbo.ValidRezervareServiciu(@id_rezervare, @id_serviciu) = 0
    BEGIN
        RAISERROR('Serviciul deja prezent in rezervare', 16, 1);
        RETURN;
    END

    INSERT INTO RezervareServiciu(id_rezervare, id_serviciu)
    VALUES (@id_rezervare, @id_serviciu);
END;

--read
go
CREATE PROCEDURE RS_Read @id_rezervare INT, @id_serviciu INT
AS
BEGIN
    SELECT r.id_rezervare, s.nume, s.pret
    FROM RezervareServiciu rs
    JOIN Rezervare r ON r.id_rezervare = rs.id_rezervare
    JOIN Serviciu s ON s.id_serviciu = rs.id_serviciu
    where rs.id_rezervare = @id_rezervare and rs.id_serviciu = @id_serviciu;
END;

--update
GO
CREATE PROCEDURE RS_Update @id_rezervare INT, @id_serviciu_vechi INT, @id_serviciu_nou INT
AS
BEGIN
    IF dbo.ValidRezervareServiciu(@id_rezervare, @id_serviciu_nou) =0
    BEGIN
        RAISERROR('Ipdate invalid', 16,1);
        RETURN; 
    END;
    UPDATE RezervareServiciu SET id_serviciu = @id_serviciu_nou
    WHERE id_rezervare = @id_rezervare and id_serviciu = @id_serviciu_vechi;
END;



--delete

GO
CREATE PROCEDURE RS_Delete @id_rezervare INT, @id_serviciu INT
AS
BEGIN
    IF EXISTS(SELECT * FROM RezervareServiciu where id_rezervare=@id_rezervare and id_serviciu=@id_serviciu)
        DELETE FROM RezervareServiciu
        WHERE id_rezervare = @id_rezervare and id_serviciu = @id_serviciu;
        return;
    RAISERROR('Nothing to delete here, lmao',16,1);
END;


---tabele de logging

CREATE TABLE Log_Serviciu
(
    id_log INT IDENTITY PRIMARY KEY,
    id_serviciu INT,
    nume NVARCHAR(41),
    pret FLOAT,
    operatie NVARCHAR(10),
    data_operatie DATETIME DEFAULT GETDATE(),
    utilizator SYSNAME
);


CREATE TABLE Log_Rezervare
(
    id_log INT IDENTITY PRIMARY KEY,
    id_rezervare INT,
    id_camera INT,
    checkIn DATETIME,
    checkOut DATETIME,
    sold_plata FLOAT,
    operatie NVARCHAR(10),
    data_operatie DATETIME DEFAULT GETDATE(),
    utilizator SYSNAME,
);

CREATE TABLE Log_RezervareServiciu
(
    id_log INT IDENTITY PRIMARY KEY,
    id_rezervare INT,
    id_serviciu INT,
    operatie NVARCHAR(10),
    data_operatie DATETIME DEFAULT GETDATE(),
    utilizator SYSNAME
);

--triggere :()

--=========Serviciu
--delete
GO
CREATE TRIGGER trg_S_Log_Delete
ON Serviciu
AFTER DELETE
AS
BEGIN
    INSERT INTO Log_Serviciu
        (id_serviciu, nume, pret, operatie, utilizator)
    SELECT
        d.id_serviciu,
        d.nume,
        d.pret,
        'DELETE',
        SYSTEM_USER
    FROM deleted d;
END;
GO

--update
GO
CREATE TRIGGER trg_S_Log_Update
ON Serviciu
AFTER UPDATE
AS
BEGIN
    INSERT INTO Log_Serviciu
        (id_serviciu, nume, pret, operatie, utilizator)
    SELECT
        d.id_serviciu,
        d.nume,
        d.pret,
        'UPDATE',
        SYSTEM_USER
    FROM deleted d;
END;
GO

--=========Rezervare
--delete
GO
CREATE TRIGGER trg_R_Log_Delete
ON Rezervare
AFTER DELETE
AS
BEGIN
    INSERT INTO Log_Rezervare
        (id_rezervare, id_camera, checkIn, checkOut, sold_plata, operatie, utilizator)
    SELECT
        d.id_rezervare,
        d.id_camera,
        d.checkIn,
        d.checkOut,
        d.sold_plata,
        'DELETE',
        SYSTEM_USER
    FROM deleted d;
END;
GO
--update
GO
CREATE TRIGGER trg_R_Log_Update
ON Rezervare
AFTER UPDATE
AS
BEGIN
    INSERT INTO Log_Rezervare
        (id_rezervare, id_camera, checkIn, checkOut, sold_plata, operatie, utilizator)
    SELECT
        d.id_rezervare,
        d.id_camera,
        d.checkIn,
        d.checkOut,
        d.sold_plata,
        'UPDATE',
        SYSTEM_USER
    FROM deleted d;
END;
GO


--=========RezervareServiciu
--delete
GO
CREATE TRIGGER trg_RS_Log_Delete
ON RezervareServiciu
AFTER DELETE
AS
BEGIN
    INSERT INTO Log_RezervareServiciu
        (id_rezervare, id_serviciu, operatie, utilizator)
    SELECT
        d.id_rezervare,
        d.id_serviciu,
        'DELETE',
        SYSTEM_USER
    FROM deleted d;
END;
GO
--update

GO
CREATE TRIGGER trg_RS_Log_Update
ON RezervareServiciu
AFTER UPDATE
AS
BEGIN
    INSERT INTO Log_RezervareServiciu
        (id_rezervare, id_serviciu, operatie, utilizator)
    SELECT
        d.id_rezervare,
        d.id_serviciu,
        'UPDATE',
        SYSTEM_USER
    FROM deleted d;
END;
GO

--views si  indecsi
go
create nonclustered index IDX_S_pret
on Serviciu(pret ASC) include (id_serviciu, nume);

GO
create nonclustered index IDX_R_checkOut
on Rezervare(checkOut DESC) include(id_rezervare, id_camera, checkIn, sold_plata);


go
create view vw_Service_scump
as
Select id_serviciu, nume, pret from Serviciu where pret>100


go 
create view vw_RezervariFinalizate
as
Select id_rezervare, id_camera, checkIn, checkOut, sold_plata 
from Rezervare where checkOut < GETDATE(); 

--sper ca or merge

select * from vw_Service_scump;
select * from vw_RezervariFinalizate;
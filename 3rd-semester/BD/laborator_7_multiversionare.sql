USE LantHotelier;
GO

----Partea cu versiunile bazei de date 
---presupun ca fiecare cerinta reprezinta cumulativ o versiune diferita,  adica cerinta 1 ---> versiune 2
															--					cerinta 1 si cerinta 2 ---->versiune 3 etc

CREATE TABLE Versions(
	current_version INT DEFAULT 1
);
INSERT INTO Versions VALUES(1);
 

--SCRIPTURI CARE
--=================1===========================.
--MODIFIFCA	TIPUL UNEI COLOANE
--SET-UP
GO
CREATE PROCEDURE ModifyColumn_v1_2
AS
BEGIN
	ALTER TABLE Client
	ALTER COLUMN telefon NVARCHAR(30);
	UPDATE Versions SET current_version = current_version+1;
END;
GO

--TEAR-DOWN
GO
CREATE PROCEDURE UnModifyColumn_v2_1
AS	
	BEGIN
	ALTER TABLE Client
	ALTER COLUMN telefon NVARCHAR(15);
	UPDATE Versions SET current_version = current_version-1;
END;


--=================2===========================.
--CARE ADAUGA CONSTRANGERE DE VALOARE IMPLICITA
--SET-UP

GO
CREATE PROCEDURE AddSalariuDefault_v2_3
AS
	BEGIN
		ALTER TABLE Angajat
		ADD CONSTRAINT df_salary DEFAULT 2000 for salariu; 
		UPDATE Versions SET current_version = current_version+1;
END;

--TEAR-DOWN

GO
CREATE PROCEDURE DropSalariuDefault_v3_2
AS
	BEGIN
		ALTER TABLE Angajat
		DROP CONSTRAINT df_salary;
		UPDATE Versions SET current_version = current_version-1;
END;




--=================3===========================.
--CREEAZA/STERGE O TABELA

--SET-UP
GO
CREATE PROCEDURE CreateTableParcari_v3_4
AS 
	BEGIN
		CREATE TABLE Parcari(
			numar INT IDENTITY PRIMARY KEY,
			id_hotel INT,
			tip VARCHAR(20)
		);
		UPDATE Versions SET current_version = current_version+1;
END;


--TEAR-DOWN
GO
CREATE PROCEDURE DropTableParcari_v4_3
AS 
	BEGIN
		DROP TABLE Parcari;
		UPDATE Versions SET current_version = current_version-1;
END;


--=================4===========================.
--Adauga un camp nou

--SET-UP

GO
CREATE PROCEDURE NewField_v4_5
AS
	BEGIN
		ALTER TABLE Serviciu
		ADD nota_serviciu INT ;
		ALTER TABLE Serviciu
		ADD CONSTRAINT df_grade DEFAULT 10 for nota_serviciu;
		UPDATE Versions SET current_version = current_version+1;
END;


--TEAR-DOWN

GO
CREATE PROCEDURE DeleteField_v5_4
AS
	BEGIN
		ALTER TABLE Serviciu
		DROP CONSTRAINT df_grade;
		ALTER TABLE Serviciu
		DROP COLUMN nota_serviciu;
		UPDATE Versions SET current_version = current_version-1;
END;



--=================5===========================.
--Creeaza/Anihileaza o cheie straina


--TEAR-DOWN nu gasesc ce cheie straina sa mai creez, sterg una existenta si o-i creea-o inapoi
GO
CREATE PROCEDURE KillForeignKey_v5_6
AS
	BEGIN
		ALTER TABLE Program
		DROP CONSTRAINT FK_id_angajat;
		UPDATE Versions SET current_version = current_version+1;
END;


--SET-UP
GO
CREATE PROCEDURE MakeForeignKey_v6_5
AS
	BEGIN
	ALTER TABLE Program
	ADD CONSTRAINT FK_id_angajat FOREIGN KEY(id_angajat) REFERENCES Angajat(id_angajat);
	UPDATE Versions SET current_version = current_version-1;
END;


--=======================Partea cu migrarea intre versiuni==============================
--daca vreau versiunea 3 trebuie aplicate si schimbarile din versiunea 1 si versiunea 2 cumulate
--daca vreau versiunea 5 => v1->v2->v3->v4
--daca sunt pe v6 si vreau v3 => undo de la 6-5, 5-4, 4-3



GO
CREATE PROCEDURE Migrate @wanted_version INT
AS
	BEGIN
		DECLARE @current INT;
		SELECT @current = current_version FROM Versions;
			
		 WHILE @current< @wanted_version --aplic pentru fiecare versiune update-ul corespunzator trecerii la next version
		 BEGIN
			IF @current= 1 EXEC ModifyColumn_v1_2;
			IF @current= 2 EXEC AddSalariuDefault_v2_3;
			IF @current= 3 EXEC CreateTableParcari_v3_4;
			IF @current= 4 EXEC NewField_v4_5;
			IF @current= 5 EXEC KillForeignKey_v5_6;

			SELECT @current= current_version FROM Versions;
		END
		WHILE @current> @wanted_version --aplic pentru fiecare versiune downgrade-ul corespunzator trecerii la old version
		 BEGIN
			IF @current= 2 EXEC UnModifyColumn_v2_1;
			IF @current= 3 EXEC DropSalariuDefault_v3_2;
			IF @current= 4 EXEC DropTableParcari_v4_3;
			IF @current= 5 EXEC DeleteField_v5_4;
			IF @current= 6 EXEC MakeForeignKey_v6_5;

			SELECT @current= current_version FROM Versions;
		END

END;
GO
select * from Versions;
EXEC Migrate 1;



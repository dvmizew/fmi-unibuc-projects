CREATE DATABASE IF NOT EXISTS transport_public;
USE transport_public;

CREATE TABLE `Angajati` (
  `ID_Angajati` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `Nume` varchar(50) NOT NULL,
  `Prenume` varchar(50) NOT NULL,
  `Adresa` varchar(100) UNIQUE,
  `Tip_personal` varchar(50) NOT NULL,
  `Data_angajarii` date NOT NULL,
  `Salariu` decimal(10, 2) NOT NULL
);

CREATE TABLE `Clienti` (
  `ID_Clienti` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `Nume` varchar(50) NOT NULL,
  `Prenume` varchar(50) NOT NULL,
  `Adresa` varchar(100) UNIQUE,
  `NumarTelefon` bigint NOT NULL,
  `AdresaEmail` varchar(100) UNIQUE,
  `ParolaHash` varchar(64) NOT NULL,
  `ProfilPrivat` boolean NOT NULL
);

ALTER TABLE `Clienti`
  ADD CONSTRAINT `Check_NumarTelefon` CHECK (LENGTH(NumarTelefon) >= 9);

CREATE TABLE `ParcareAutovehicule` (
  `ID_ParcareAutovehicule` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `Locatie` varchar(100) UNIQUE
);

CREATE TABLE `Autovehicule` (
  `ID_Autovehicule` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `Model` varchar(50) NOT NULL,
  `Capacitate` int NOT NULL,
  `Conditie` varchar(50) NOT NULL
);

CREATE TABLE `Statii` (
  `ID_Statii` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `Nume` varchar(50) UNIQUE,
  `Adresa` varchar(256) UNIQUE
);

CREATE TABLE `Abonamente` (
  `ID_Abonamente` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `TipAbonament` varchar(50) NOT NULL,
  `Tip_persoana_acordat` varchar(50) NOT NULL,
  `Durata` integer NOT NULL,
  `Pret` decimal(10, 2) NOT NULL,
  `ClientID` int NOT NULL
);

ALTER TABLE `Abonamente`
  ADD CONSTRAINT `Check_Durata` CHECK (`Durata` >= 0),
  ADD CONSTRAINT `Check_Durata_Max` CHECK (`Durata` <= 100),
  ADD CONSTRAINT `FK_ClientID_Abonamente` FOREIGN KEY (`ClientID`) REFERENCES `Clienti` (`ID_Clienti`) ON DELETE CASCADE;

CREATE TABLE `LiniiAutovehicule` (
  `ID_LiniiAutovehicule` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `NumarLinie` varchar(10) UNIQUE,
  `Traseu` varchar(100) UNIQUE,
  `OraPlecare` time NOT NULL,
  `OraSosire` time NOT NULL,
  `Orar` JSON NOT NULL
);

CREATE TABLE `Autovehicule_LiniiAutovehicul` (
  `ID_Autovehicule_LiniiAutovehicul` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `AutovehiculeID` int NOT NULL,
  `LiniiAutovehiculID` int NOT NULL
);

ALTER TABLE `Autovehicule_LiniiAutovehicul`
  ADD CONSTRAINT `FK_AutovehiculeID_Autovehicule_LiniiAutovehicul` FOREIGN KEY (`AutovehiculeID`) REFERENCES `Autovehicule` (`ID_Autovehicule`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_LiniiAutovehiculID_Autovehicule_LiniiAutovehicul` FOREIGN KEY (`LiniiAutovehiculID`) REFERENCES `LiniiAutovehicule` (`ID_LiniiAutovehicule`) ON DELETE CASCADE;

CREATE TABLE `ParcareAutovehicule_Autovehicule` (
  `ID_ParcareAutovehicule_Autovehicule` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `ParcareAutovehiculeID` int NOT NULL,
  `AutovehiculeID` int NOT NULL
);

ALTER TABLE `ParcareAutovehicule_Autovehicule`
  ADD CONSTRAINT `FK_ParcareAutovehiculeID_ParcareAutovehicule_Autovehicule` FOREIGN KEY (`ParcareAutovehiculeID`) REFERENCES `ParcareAutovehicule` (`ID_ParcareAutovehicule`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_AutovehiculeID_ParcareAutovehicule_Autovehicule` FOREIGN KEY (`AutovehiculeID`) REFERENCES `Autovehicule` (`ID_Autovehicule`) ON DELETE CASCADE;

CREATE TABLE `Angajati_Autovehicule` (
  `ID_Angajati_Autovehicule` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `AngajatID` int NOT NULL,
  `AutovehiculID` int NOT NULL
);

ALTER TABLE `Angajati_Autovehicule`
  ADD CONSTRAINT `FK_AngajatID_Angajati_Autovehicule` FOREIGN KEY (`AngajatID`) REFERENCES `Angajati` (`ID_Angajati`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_AutovehiculID_Angajati_Autovehicule` FOREIGN KEY (`AutovehiculID`) REFERENCES `Autovehicule` (`ID_Autovehicule`) ON DELETE CASCADE;


CREATE TABLE `Abonamente_Linii` (
    `ID_Abonamente_Linii` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `AbonamentID_Abonamente_Linii` int NOT NULL,
  `LiniiAutovehiculID` int NOT NULL
);

ALTER TABLE `Abonamente_Linii`
  ADD CONSTRAINT `FK_AbonamentID_Abonamente_Linii` FOREIGN KEY (`AbonamentID_Abonamente_Linii`) REFERENCES `Abonamente` (`ID_Abonamente`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_LiniiAutovehiculID_Abonamente_Linii` FOREIGN KEY (`LiniiAutovehiculID`) REFERENCES `LiniiAutovehicule` (`ID_LiniiAutovehicule`) ON DELETE CASCADE;

CREATE TABLE `LiniiAutovehicule_Statii` (
  `ID_LiniiAutovehicule_Statii` int PRIMARY KEY AUTO_INCREMENT NOT NULL,
  `LinieAutovehiculeID` int NOT NULL,
  `StatieID` int NOT NULL
);

ALTER TABLE `LiniiAutovehicule_Statii`
  ADD CONSTRAINT `FK_LinieAutovehiculeID_LiniiAutovehicule_Statii` FOREIGN KEY (`LinieAutovehiculeID`) REFERENCES `LiniiAutovehicule` (`ID_LiniiAutovehicule`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_StatieID_LiniiAutovehicule_Statii` FOREIGN KEY (`StatieID`) REFERENCES `Statii` (`ID_Statii`) ON DELETE CASCADE;

-- Inserare date in tabele

INSERT INTO `Angajati` (`Nume`, `Prenume`, `Adresa`, `Tip_personal`, `Data_angajarii`, `Salariu`)
VALUES
    ('Popescu', 'Ion', 'Bucuresti, Strada Victoriei, Nr. 1', 'Sofer', '2019-01-01', 2000.00),
    ('Ionescu', 'Maria', 'Bucuresti, Strada Unirii, Nr. 2', 'Sofer', '2019-01-01', 2000.00),
    ('Georgescu', 'Andrei', 'Bucuresti, Calea Victoriei, Nr. 3', 'Sofer', '2019-01-01', 2000.00),
    ('Radu', 'Elena', 'Bucuresti, Bulevardul Magheru, Nr. 4', 'Sofer', '2019-01-01', 2000.00),
    ('Stefanescu', 'Mihai', 'Bucuresti, Piata Romana, Nr. 5', 'Sofer', '2019-01-01', 2000.00),
    ('Popa', 'Ana', 'Bucuresti, Piata Universitatii, Nr. 6', 'Sofer', '2019-01-01', 2000.00),
    ('Dumitrescu', 'Alexandru', 'Bucuresti, Piata Unirii, Nr. 7', 'Sofer', '2019-01-01', 2000.00),
    ('Constantin', 'Laura', 'Bucuresti, Bulevardul Unirii, Nr. 8', 'Sofer', '2019-01-01', 2000.00),
    ('Mihai', 'Cristian', 'Bucuresti, Piata Victoriei, Nr. 9', 'Sofer', '2019-01-01', 2000.00),
    ('Gheorghe', 'Andreea', 'Bucuresti, Calea Dorobantilor, Nr. 10', 'Sofer', '2019-01-01', 2000.00);

INSERT INTO `Clienti` (`Nume`, `Prenume`, `AdresaEmail`, `NumarTelefon`, `ProfilPrivat`, `ParolaHash`)
VALUES
    ('Popescu', 'Ion', 'popescu.ion@gmail.com', '0723456789', true, 'parola1'),
    ('Ionescu', 'Maria', 'ionescu.maria@gmail.com', '0734567890', false, 'parola2'),
    ('Georgescu', 'Andrei', 'georgescu.andrei@gmail.com', '0745678901', true, 'parola3'),
    ('Radu', 'Elena', 'radu.elena@gmail.com', '0756789012', false, 'parola4'),
    ('Stefanescu', 'Mihai', 'stefanescu.mihai@gmail.com', '0767890123', true, 'parola5'),
    ('Popa', 'Ana', 'popa.ana@gmail.com', '0778901234', false, 'parola6'),
    ('Dumitrescu', 'Alexandru', 'dumitrescu.alexandru@gmail.com', '0789012345', true, 'parola7'),
    ('Constantin', 'Laura', 'constantin.laura@gmail.com', '0790123456', false, 'parola8'),
    ('Mihai', 'Cristian', 'mihai.cristian@gmail.com', '0701234567', true, 'parola9'),
    ('Gheorghe', 'Andreea', 'gheorghe.andreea@gmail.com', '0712345678', false, 'parola10');

INSERT INTO `ParcareAutovehicule` (`Locatie`)
VALUES
    ('Bucuresti, Strada Victoriei, Nr. 1'),
    ('Bucuresti, Strada Unirii, Nr. 2'),
    ('Bucuresti, Calea Victoriei, Nr. 3'),
    ('Bucuresti, Bulevardul Magheru, Nr. 4'),
    ('Bucuresti, Piata Romana, Nr. 5'),
    ('Bucuresti, Piata Universitatii, Nr. 6'),
    ('Bucuresti, Piata Unirii, Nr. 7'),
    ('Bucuresti, Bulevardul Unirii, Nr. 8'),
    ('Bucuresti, Piata Victoriei, Nr. 9'),
    ('Bucuresti, Calea Dorobantilor, Nr. 10');


INSERT INTO `Autovehicule` (`Model`, `Capacitate`, `Conditie`)
VALUES
    ('Mercedes-Benz Citaro', 50, 'Buna'),
    ('MAN Lion''s City', 50, 'Buna'),
    ('Volvo 7900', 50, 'Buna'),
    ('Solaris Urbino', 50, 'Buna'),
    ('Iveco Urbanway', 50, 'Buna'),
    ('Scania Citywide', 50, 'Buna'),
    ('Van Hool Exqui.City', 50, 'Buna'),
    ('Neoplan Tourliner', 50, 'Buna'),
    ('Setra S 415 UL', 50, 'Buna'),
    ('Temsa Avenue', 50, 'Buna'),
    ('Mercedes-Benz Citaro', 60, 'Buna'),
    ('MAN Lion''s City', 60, 'Buna'),
    ('Volvo 7900', 60, 'Buna'),
    ('Solaris Urbino', 60, 'Buna'),
    ('Iveco Urbanway', 60, 'Buna'),
    ('Scania Citywide', 60, 'Buna'),
    ('Van Hool Exqui.City', 60, 'Buna'),
    ('Neoplan Tourliner', 60, 'Buna'),
    ('Setra S 415 UL', 60, 'Buna'),
    ('Temsa Avenue', 60, 'Buna');


INSERT INTO `Statii` (`Nume`, `Adresa`)
VALUES
    ('Piata Presei', 'Bucuresti, Piata Presei, Nr. 1'),
    ('Piata Romana', 'Bucuresti, Piata Romana, Nr. 2'),
    ('Piata Unirii', 'Bucuresti, Piata Unirii, Nr. 3'),
    ('Bulevardul Magheru', 'Bucuresti, Bulevardul Magheru, Nr. 4'),
    ('Strada Victoriei', 'Bucuresti, Strada Victoriei, Nr. 5'),
    ('Strada Unirii', 'Bucuresti, Strada Unirii, Nr. 6'),
    ('Piata Universitatii', 'Bucuresti, Piata Universitatii, Nr. 7'),
    ('Bulevardul Unirii', 'Bucuresti, Bulevardul Unirii, Nr. 8'),
    ('Piata Victoriei', 'Bucuresti, Piata Victoriei, Nr. 9'),
    ('Calea Dorobantilor', 'Bucuresti, Calea Dorobantilor, Nr. 10');


INSERT INTO `Abonamente` (`TipAbonament`, `Tip_persoana_acordat`, `Durata`, `Pret`, `ClientID`)
VALUES
    ('Abonament lunar', 'Pensionar', 30, 100.00, 1),
    ('Abonament saptamanal', 'Student', 7, 50.00, 2),
    ('Abonament lunar', 'Elev', 30, 100.00, 3),
    ('Abonament saptamanal', 'Pensionar', 7, 50.00, 4),
    ('Abonament lunar', 'Student', 30, 100.00, 5),
    ('Abonament saptamanal', 'Elev', 7, 50.00, 6),
    ('Abonament lunar', 'Pensionar', 30, 100.00, 7),
    ('Abonament saptamanal', 'Student', 7, 50.00, 8),
    ('Abonament lunar', 'Elev', 30, 100.00, 9),
    ('Abonament saptamanal', 'Pensionar', 7, 50.00, 10);


INSERT INTO `LiniiAutovehicule` (`NumarLinie`, `Traseu`, `OraPlecare`, `OraSosire`, `Orar`)
VALUES
    ('1', 'Piata Presei - Complex Apusului', '08:00:00', '16:00:00', '{"Luni": "08:00 - 16:00", "Marti": "08:00 - 16:00", "Miercuri": "08:00 - 16:00", "Joi": "08:00 - 16:00", "Vineri": "08:00 - 16:00"}'),
    ('2', 'Piata Romana - Bulevardul Mihalache', '09:00:00', '17:00:00', '{"Luni": "09:00 - 17:00", "Marti": "09:00 - 17:00", "Miercuri": "09:00 - 17:00", "Joi": "09:00 - 17:00", "Vineri": "09:00 - 17:00"}'),
    ('3', 'Piata Unirii - Piata Victoriei', '10:00:00', '18:00:00', '{"Luni": "10:00 - 18:00", "Marti": "10:00 - 18:00", "Miercuri": "10:00 - 18:00", "Joi": "10:00 - 18:00", "Vineri": "10:00 - 18:00"}'),
    ('4', 'Bulevardul Magheru - Cartier Militari', '11:00:00', '19:00:00', '{"Luni": "11:00 - 19:00", "Marti": "11:00 - 19:00", "Miercuri": "11:00 - 19:00", "Joi": "11:00 - 19:00", "Vineri": "11:00 - 19:00"}'),
    ('5', 'Strada Victoriei - Bulevardul Unirii', '12:00:00', '20:00:00', '{"Luni": "12:00 - 20:00", "Marti": "12:00 - 20:00", "Miercuri": "12:00 - 20:00", "Joi": "12:00 - 20:00", "Vineri": "12:00 - 20:00"}'),
    ('6', 'Strada Unirii - Calea Victoriei', '13:00:00', '21:00:00', '{"Luni": "13:00 - 21:00", "Marti": "13:00 - 21:00", "Miercuri": "13:00 - 21:00", "Joi": "13:00 - 21:00", "Vineri": "13:00 - 21:00"}'),
    ('7', 'Piata Presei - Complex Gorjului', '14:00:00', '22:00:00', '{"Luni": "14:00 - 22:00", "Marti": "14:00 - 22:00", "Miercuri": "14:00 - 22:00", "Joi": "14:00 - 22:00", "Vineri": "14:00 - 22:00"}'),
    ('8', 'Piata Romana - Piata Universitatii', '15:00:00', '23:00:00', '{"Luni": "15:00 - 23:00", "Marti": "15:00 - 23:00", "Miercuri": "15:00 - 23:00", "Joi": "15:00 - 23:00", "Vineri": "15:00 - 23:00"}'),
    ('9', 'Piata Unirii - Piata Alba Iulia', '16:00:00', '00:00:00', '{"Luni": "16:00 - 00:00", "Marti": "16:00 - 00:00", "Miercuri": "16:00 - 00:00", "Joi": "16:00 - 00:00", "Vineri": "16:00 - 00:00"}'),
    ('10', 'Bulevardul Magheru - Calea Dorobantilor', '17:00:00', '01:00:00', '{"Luni": "17:00 - 01:00", "Marti": "17:00 - 01:00", "Miercuri": "17:00 - 01:00", "Joi": "17:00 - 01:00", "Vineri": "17:00 - 01:00"}');


INSERT INTO `Autovehicule_LiniiAutovehicul` (`AutovehiculeID`, `LiniiAutovehiculID`)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 6),
    (7, 7),
    (8, 8),
    (9, 9),
    (10, 10);


INSERT INTO `ParcareAutovehicule_Autovehicule` (`ParcareAutovehiculeID`, `AutovehiculeID`)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 6),
    (7, 7),
    (8, 8),
    (9, 9),
    (10, 10);


INSERT INTO `Angajati_Autovehicule` (`AngajatID`, `AutovehiculID`)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 6),
    (7, 7),
    (8, 8),
    (9, 9),
    (10, 10);


INSERT INTO `Abonamente_Linii` (`AbonamentID_Abonamente_Linii`, `LiniiAutovehiculID`)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 6),
    (7, 7),
    (8, 8),
    (9, 9),
    (10, 10);


INSERT INTO `LiniiAutovehicule_Statii` (`LinieAutovehiculeID`, `StatieID`)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5),
    (6, 6),
    (7, 7),
    (8, 8),
    (9, 9),
    (10, 10);

# drop database transport_public;
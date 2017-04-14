/* Project Part 2 */

/*1 is in the PDF submitted*/

/*2*/
CREATE TABLE airline_staff(
	username			VARCHAR(320)		NOT NULL,
	password			VARCHAR(320)		NOT NULL,
	first_name			VARCHAR(40)			NOT NULL,
	last_name			VARCHAR(40)			NOT NULL,
	date_of_birth		DATE				NOT NULL,
	PRIMARY KEY (username)
);

CREATE TABLE works_for(
	name				VARCHAR(40)			NOT NULL,
	username			VARCHAR(320)		NOT NULL,
	PRIMARY KEY (name, username)
);

CREATE TABLE airline(
	name				VARCHAR(40)			NOT NULL,
	PRIMARY KEY (name)
);

CREATE TABLE owned_by(
	name				VARCHAR(40)			NOT NULL,
	ID					INT					NOT NULL,
	PRIMARY KEY (name, ID)
);

CREATE TABLE airplane(
	ID					INT					NOT NULL,
	seats				INT					NOT NULL,
	PRIMARY KEY (ID)
);

CREATE TABLE operated_by(
	name				VARCHAR(40)			NOT NULL,
	flight_num			VARCHAR(40)			NOT NULL,
	PRIMARY KEY (name, flight_num)
);

CREATE TABLE uses(
	ID					INT					NOT NULL,
	flight_num			VARCHAR(40)			NOT NULL,
	PRIMARY KEY (ID, flight_num)
);

CREATE TABLE airport(
	name				VARCHAR(40)			NOT NULL,
	city				VARCHAR(40)			NOT NULL,
	PRIMARY KEY (name)
);

CREATE TABLE arrives(
	name				VARCHAR(40)			NOT NULL,
	flight_num			VARCHAR(40)			NOT NULL,
	PRIMARY KEY (name, flight_num)
);

CREATE TABLE departs(
	name				VARCHAR(40)			NOT NULL,
	flight_num			VARCHAR(40)			NOT NULL,
	PRIMARY KEY (name, flight_num)
);

CREATE TABLE flight(
	flight_num			VARCHAR(40)			NOT NULL,
	departure_time		DATETIME			NOT NULL,
	arrival_time		DATETIME			NOT NULL,
	price				NUMERIC(7,2)		NOT NULL,
	status				VARCHAR(40)			NOT NULL,
	PRIMARY KEY (flight_num)
);

CREATE TABLE ticket_for(
	flight_num			VARCHAR(40)			NOT NULL,
	ticket_ID			BIGINT					NOT NULL,
	PRIMARY KEY (flight_num, ticket_ID)
);

CREATE TABLE ticket(
	ticket_ID			BIGINT					NOT NULL,
	PRIMARY KEY (ticket_ID)
);

CREATE TABLE purchases(
	ticket_ID			BIGINT				NOT NULL,
	booking_agent_ID	VARCHAR(320),
	customer_email		VARCHAR(320)		NOT NULL,
	PRIMARY KEY (ticket_ID, customer_email)
);

CREATE TABLE customer(
	email				VARCHAR(320)		NOT NULL,
	name				VARCHAR(40)			NOT NULL,
	password			VARCHAR(320)		NOT NULL,
	building_number		VARCHAR(40)			NOT NULL,
	street				VARCHAR(40)			NOT NULL,
	city				VARCHAR(40)			NOT NULL,
	state				VARCHAR(40)			NOT NULL,
	phone_number		BIGINT				NOT NULL,
	passport_number		INT					NOT NULL,
	passport_expiration	DATE				NOT NULL,
	passport_country	VARCHAR(40)			NOT NULL,
	date_of_birth		DATE				NOT NULL,
	PRIMARY KEY (email)
);

CREATE TABLE booking_agent(
	email				VARCHAR(320)		NOT NULL,
	password			VARCHAR(320)		NOT NULL,
	booking_agent_ID	INT					NOT NULL,
	PRIMARY KEY (email)
);

/*3*/
/*a*/
INSERT INTO airline(name)
	VALUES ('Emirates');
/*b*/
INSERT INTO airport(name, city)
	VALUES 	('JFK', 'NYC'),
			('Chicago International Airport', 'Chicago');
/*c*/
INSERT INTO customer(email, name, password, building_number, street, city, state, phone_number, passport_number, passport_expiration, passport_country, date_of_birth)
	VALUES 	('owsla@gmail.com', 'John Moore', 'nicesprites', '320', 'Jay Street', 'Brooklyn', 'New York', 6263191039, 31195885, '2021-11-18', 'United States of America', '2021-12-10'),
			('kasbo@yahoo.com', 'Helena Li', 'missingpanda', '321', 'Daniel Street', 'Berkeley', 'California', 7072460152, 27302885, '2022-12-26', 'United States of America', '2021-11-19');
/*d*/
INSERT INTO airplane(ID, seats)
	VALUES 	(371362, 416),
			(102857, 524);

INSERT INTO owned_by(name, ID)
	VALUES 	('Emirates', 371362),
			('Emirates', 102857);
/*e*/
INSERT INTO airline_staff(username, password, first_name, last_name, date_of_birth)
	VALUES 	('yesty', 'supersecureonepassword', 'Matt', 'Foley', '1990-12-16');

INSERT INTO works_for(name, username)
	VALUES 	('Emirates','yesty');
/*f*/
INSERT INTO flight(flight_num, departure_time, arrival_time, price, status)
	VALUES 	('VA1178', '2017-04-30 2:30:00', '2017-04-30 10:50:00', 42.51, 'upcoming'),
			('JBU616', '2017-02-15 11:40:00', '2017-02-15 3:13:00', 70.25, 'delayed'),
			('JBU615', '2017-02-20 2:00:00', '2017-02-20 10:27:00', 183.70, 'upcoming');
/*g*/
INSERT INTO ticket(ticket_ID)
	VALUES 	(16986459877452),
			(84358584634533);

INSERT INTO ticket_for(flight_num, ticket_ID)
	VALUES	('VA1178', 16986459877452),
			('JBU616', 84358584634533);

INSERT INTO purchases(ticket_ID, booking_agent_ID, customer_email)
	VALUES	(16986459877452, NULL, 'owsla@gmail.com'),
			(84358584634533, 24215418551542, 'kasbo@yahoo.com');

/*4*/
/*a*/
SELECT *
FROM flight
WHERE status = 'upcoming';

/*b*/
SELECT *
FROM flight
WHERE status = 'delayed';
/*c*/
SELECT customer.name, purchases.booking_agent_ID
FROM customer, purchases
WHERE customer.email = purchases.customer_email
AND purchases.booking_agent_ID IS NOT NULL;
/*d*/
SELECT *
FROM airplane NATURAL JOIN owned_by
WHERE name = 'Emirates';
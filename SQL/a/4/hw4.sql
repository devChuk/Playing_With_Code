/*Problem 1           */

/*1*/
SELECT a.ID
FROM takes AS a, takes as b
WHERE a.id = b.id AND a.grade = 'A' AND a.course_id = 'CS-101' AND b.grade = 'A' AND b.course_id = 'CS-319';

/*2*/
SELECT DISTINCT student.ID, student.name
FROM student NATURAL JOIN takes AS a, takes AS b
WHERE a.id = b.id AND a.grade = 'A' AND a.course_id = 'CS-319' AND
b.course_id = 'CS-101' AND b.grade = 'A';

/*3*/
SELECT DISTINCT student.ID, student.name
FROM student NATURAL JOIN takes AS a, takes AS b
WHERE a.id = b.id AND a.grade = 'A' AND a.course_id = 'CS-319' AND
b.course_id = 'CS-101' AND b.grade <> 'A';

/*4*/
SELECT ID, name
FROM student NATURAL JOIN takes WHERE grade = 'A' AND course_id = 'CS-319'
AND ID NOT IN (SELECT ID
			   FROM takes
			   WHERE course_id = 'CS-101' AND grade = A);

/*5*/
SELECT ID
FROM takes
GROUP BY ID, course_id
HAVING COUNT(course_id) > 1;

/*6*/
CREATE TABLE gradepoint(
	grade		varchar(3),
	point		numeric(2,1)
);

INSERT INTO gradepoint(grade, point)
	VALUES 	('A', 4.0)
			('A', 3.7)
			('B+', 3.3)
			('B', 3.0)
			('B-', 2.7)
			('C+', 2.3)
			('C', 2.0)
			('C-', 1.7)
			('D+', 1.3)
			('D', 1.0)
			('F', 0.0);

SELECT
    student.ID,
    SUM(course.credits * gradepoint.point) / SUM(course.credits) AS GPA
FROM student
INNER JOIN takes ON student.ID = takes.ID
INNER JOIN course ON course.course_id = takes.course_id
INNER JOIN gradepoint ON gradepoint.grade = takes.grade
GROUP BY student.ID;


/*7*/
/* The constrait is on takes. If a grade exists on takes, it exists on gradepoint */

/*8*/
CREATE VIEW deanslist(ID, name) AS
	SELECT DISTINCT student.ID, student.name
	FROM 	(SELECT
			    student.ID,
			    SUM(course.credits * gradepoint.point) / SUM(course.credits) AS GPA
			FROM student
			INNER JOIN takes ON student.ID = takes.ID
			INNER JOIN course ON course.course_id = takes.course_id
			INNER JOIN gradepoint ON gradepoint.grade = takes.grade
			GROUP BY student.ID) AS studentgpa
	NATURAL JOIN student
	WHERE GPA > 3.0;

/*9*/
SELECT dept_name, COUNT(*)
FROM deanslist NATURAL JOIN student
GROUP BY dept_name

/*10*/
	SELECT ID, name
	FROM (
		SELECT student.ID, student.name, MAX(GPA)
		FROM 	(SELECT
				    student.ID,
				    SUM(course.credits * gradepoint.point) / SUM(course.credits) AS GPA
				FROM student
				INNER JOIN takes ON student.ID = takes.ID
				INNER JOIN course ON course.course_id = takes.course_id
				INNER JOIN gradepoint ON gradepoint.grade = takes.grade
				WHERE student.dept_name = 'Comp. Sci.'
				GROUP BY student.ID) AS studentgpa
		NATURAL JOIN student
	) AS maxGPA

/*11*/
SELECT *
FROM takes AS a, takes AS b
WHERE a.id = b.id AND a.course_id = 'CS-101' AND b.course_id = 'CS-347' AND a.grade < b.grade;

/*12*/
SELECT ID
FROM student
WHERE ID NOT IN (
	SELECT ID
	FROM takes
	WHERE grade >= 'B+'
)

/*13*/
SELECT a.course_id
FROM section AS a, section as b
WHERE a.course_id = b.course_id AND a.year = b.year + 1;

/*14*/
SELECT ID
FROM teaches
WHERE course_id LIKE '%CS%'
GROUP BY ID
HAVING COUNT(course_id) = (SELECT COUNT(*) FROM course WHERE dept_name = 'Comp. Sci.');

/*15*/
SELECT ID, name
FROM 	(SELECT ID, year, semester
		FROM takes
		GROUP BY ID, year, semester) AS A
		NATURAL JOIN
		(SELECT ID, year, semester
		FROM takes
		WHERE course_id LIKE '%CS%') AS B
WHERE COUNT(*) = 	(SELECT ID, year, semester
					FROM takes
					GROUP BY ID, year, semester);

/*16*/
SELECT course_id, ID
FROM courses NATURAL LEFT JOIN teaches

/*Problem 2           */

/*1*/
/*The teaches and advisor tables would change. The tuples with the same instructor ID would have their ID set to NULL*/

/*2*/
/*The teaches and advisor tables would change. The tuples with the same instructor ID would deleted*/

/*3*/
ALTER TABLE takes
ADD CONSTRAINT FK_SECTION FOREIGN KEY (course_id) REFERENCES teaches(course_id),
ADD CONSTRAINT FK_SECTION FOREIGN KEY (semester) REFERENCES teaches(semester),
ADD CONSTRAINT FK_SECTION FOREIGN KEY (year) REFERENCES teaches(year),
ADD CONSTRAINT FK_SECTION FOREIGN KEY (sec_id) REFERENCES teaches(sec_id);

/*4*/

/*(Packard, 100)*/
/*Each building and room number exists, but the pair does not inside classroom.
/*1*/
SELECT name FROM student
WHERE dept_name = 'Finance' OR dept_name = 'History'

/*2*/
SELECT ID,name FROM student
WHERE dept_name = 'Elec. Eng.' AND tot_cred > 65

/*3*/
SELECT title FROM course
WHERE dept_name = 'Biology' AND credits = 65

/*4*/
SELECT ID FROM takes
WHERE course_id = 'CS-1315' AND 

/*5*/
SELECT student.ID, student.name
FROM student JOIN takes
ON student.ID = takes.ID
WHERE course_id = 'CS-315' AND grade = 'A'

/*6*/
SELECT student.ID, student.name
FROM student JOIN takes
ON student.ID = takes.ID
WHERE (takes.course_id = 'CS-315' OR takes.course_id = 'CS-319') AND takes.grade = 'B'

/*7*/
SELECT instructor.ID, instructor.name, course.title
FROM teaches
JOIN instructor ON teaches.ID = instructor.ID
JOIN course ON teaches.course_id = course.course_id
WHERE course.dept_name = 'Comp. Sci.' AND title LIKE '%Intro%'

/*8*/
SELECT student.ID, student.name
FROM student
JOIN takes ON student.ID = takes.ID
JOIN teaches ON takes.course_id = teaches.course_id AND takes.sec_id = teaches.sec_id
JOIN instructor ON instructor.ID = teaches.ID
WHERE instructor.salary < 75000

/*9*/
SELECT student.ID, student.name
FROM student
JOIN takes ON student.ID = takes.ID
JOIN section ON takes.course_id = section.course_id
WHERE section.building = 'Painter'

/*10*/
SELECT DISTINCT student.ID, student.name
FROM student
JOIN takes ON student.ID = takes.ID
JOIN teaches ON takes.course_id = teaches.course_id AND takes.sec_id = teaches.sec_id
JOIN instructor ON instructor.ID = teaches.ID
WHERE instructor.name = 'Einstein'

/*11*/
SELECT COUNT(student.ID) 
FROM student JOIN takes
ON student.ID = takes.ID
WHERE takes.course_id =  'CS-315'

/*12*/
SELECT grade, COUNT(*) AS num
FROM takes
WHERE takes.course_id = 'CS-101'
GROUP BY takes.grade

/*13*/
SELECT teaches.ID, COUNT(*) AS num
FROM teaches
GROUP BY teaches.ID

/*14*/
SELECT takes.ID, SUM(course.credits) AS total_credits
FROM takes
JOIN course ON takes.course_id = course.course_id
GROUP BY takes.ID

/*15*/
SELECT student.name, student.ID, COUNT(*) AS num_taken
FROM student
JOIN takes ON student.ID = takes.ID
WHERE takes.year = 2009
GROUP BY takes.ID
HAVING COUNT(*) > 1

/*16*/
SELECT student.name, COUNT(*) AS num_taken
FROM student
JOIN takes ON student.ID = takes.ID
WHERE student.dept_name = 'Comp. Sci.'
GROUP BY takes.ID
HAVING COUNT(*) < 3

/*17*/
SELECT student.name, COUNT(*) AS num_taken
FROM student
JOIN takes ON student.ID = takes.ID
JOIN course ON takes.course_id = course.course_id
WHERE student.dept_name = 'Comp. Sci.'
GROUP BY takes.ID
HAVING COUNT(*) < 3

/*18*/
SELECT instructor.dept_name, AVG(instructor.salary)
FROM instructor
GROuP BY instructor.dept_name

/*19*/
SELECT building, year, semester, COUNT(*)
FROM section
GROUP BY building, year, semester

/*20*/
SELECT MIN(salary)
FROM instructor
WHERE instructor.dept_name = 'Physics'

from flask import Flask, render_template, session, redirect, url_for, request, jsonify
import hashlib
import string
import requests
import pymysql.cursors
import datetime

app = Flask(__name__)
app.config['DEBUG'] =True
app.config['SECRET_KEY'] = hashlib.sha1("".join([hex(ord(x)).strip("0x") for x in string.printable])).hexdigest()

# Configure MySQL~~~~~~~~~~~~~
conn = pymysql.connect(host='localhost',
	user='root',
	password='chocolate',
	db='AirTicketReservation',
	charset='utf8mb4',
	cursorclass=pymysql.cursors.DictCursor)

# GENERAL ACTIONS//////////////////////////////////////////////////////////////

# Home page
@app.route("/")
def index():
	if 'username' in session:
		upcoming_flights = []
		data = []
		cursor = conn.cursor()

		cursor.execute('SELECT * FROM airport')
		airport_data = cursor.fetchall();
		airport_dict = {};
		for row in airport_data:
			airport_dict[row['airport_name']] = row['airport_city']

		if session['type'] == 'customer':
			query = 'SELECT * FROM purchases NATURAL JOIN ticket NATURAL JOIN flight WHERE customer_email = %s'
			cursor.execute(query, (session['username']))
			data = cursor.fetchall()
		if session['type'] == 'booking_agent':
			cursor.execute('SELECT booking_agent_id FROM booking_agent WHERE email=%s', session['username']);
			ID = cursor.fetchone()['booking_agent_id']

			query = 'SELECT * FROM purchases NATURAL JOIN ticket NATURAL JOIN flight WHERE booking_agent_id = %s'
			cursor.execute(query, (ID))
			data = cursor.fetchall()
		if session['type'] == 'airline_staff':
			cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
			airline_name = cursor.fetchone()
			airline_name = airline_name['airline_name']
			cursor.execute('SELECT * FROM flight WHERE airline_name = %s', (airline_name))		
			data = cursor.fetchall()

		for row in data:
			t = {
				'airline_name': row['airline_name'],
				'flight_num': row['flight_num'],
				'departure_airport': row['departure_airport'],
				'departure_time': row['departure_time'],
				'departure_city': airport_dict[row['departure_airport']],
				'arrival_airport': row['arrival_airport'],
				'arrival_time': row['arrival_time'],
				'arrival_city': airport_dict[row['arrival_airport']],
				'price': str(row['price']),
				'status': row['status'],
				'airplane_ID': row['airplane_id']
			}
			upcoming_flights.append(t)

		return render_template("index.html", username=session['username'], user_type=session['type'], upcoming_flights=upcoming_flights)
	else:
		return render_template("index.html", username=None)

@app.route("/search")
def search():
	cursor = conn.cursor()

	cursor.execute('SELECT * FROM airport')
	airport_data = cursor.fetchall();
	airport_dict = {};
	for row in airport_data:
		airport_dict[row['airport_name']] = row['airport_city']

	cursor.execute('SELECT * FROM flight')
	data = cursor.fetchall()
	for row in data:
		row['price'] = str(row['price'])
		row['departure_city'] = airport_dict[row['departure_airport']]
		row['arrival_city'] = airport_dict[row['arrival_airport']]

	if 'username' in session:
		return render_template("search.html", user_type=session['type'], flights=data)
	else:
		return render_template("search.html", user_type=None, flights=data)

@app.route("/buyFlight", methods=['POST'])
def buyFlight():
	if 'username' in session and (session['type'] == 'customer' or session['type'] == 'booking_agent'):
		airline_name = request.form['airline_name']
		flight_num = request.form['flight_num']

		cursor = conn.cursor()
		cursor.execute('SELECT MAX(ticket_id) as max_id FROM ticket')
		ID = cursor.fetchone()['max_id'] + 1

		ticket_query = 'INSERT INTO ticket VALUES (%s, %s, %s)'
		cursor.execute(ticket_query, (ID, airline_name, flight_num))

		email = session['username']
		booking_agent_id = None

		if (session['type'] == 'booking_agent'):
			email = request.form['customer_email']
			cursor.execute('SELECT booking_agent_id FROM booking_agent WHERE email = %s', session['username'])
			booking_agent_id = cursor.fetchone()['booking_agent_id']
		purchase_date=datetime.datetime.now().strftime("%Y-%m-%d")

		purchases_query = 'INSERT INTO purchases VALUES (%s, %s, %s, %s)'
		cursor.execute(purchases_query, (ID, email, booking_agent_id, purchase_date))

		conn.commit()
		cursor.close()
		return "Success"
	else:
		return "Not logged in as valid user"	

# BOOKING AGENT ACTIONS//////////////////////////////////////////////////////////////
@app.route("/commission")
def commission():
	if 'username' in session and session['type'] == 'booking_agent':
		cursor = conn.cursor()
		cursor.execute('SELECT booking_agent_id FROM booking_agent WHERE email=%s', session['username']);
		ID = cursor.fetchone()['booking_agent_id']
		currtime=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

		query = 'SELECT SUM(price) * 0.1 as total, AVG(price) * 0.1 as average, COUNT(*) as num FROM booking_agent NATURAL JOIN purchases NATURAL JOIN ticket NATURAL JOIN flight WHERE booking_agent_id = %s AND DATEDIFF(purchase_date, %s) >= -31'
		cursor.execute(query, (ID, currtime))
		data = cursor.fetchone()
		total_commission = data['total']
		average_commission = data['average']
		num = data['num']


		return render_template("viewcommission.html", total_commission=total_commission, average_commission=average_commission, num=num)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/getCommissionAndNum", methods=['POST'])
def getCommissionAndNum():
	if 'username' in session and session['type'] == 'booking_agent':
		start_date = request.form['start_date']
		end_date = request.form['end_date']
		cursor = conn.cursor()
		cursor.execute('SELECT booking_agent_id FROM booking_agent WHERE email=%s', session['username']);
		ID = cursor.fetchone()['booking_agent_id']

		query = 'SELECT COUNT(*) as count, SUM(price) * 0.1 as comm FROM booking_agent NATURAL JOIN purchases NATURAL JOIN ticket NATURAL JOIN flight WHERE booking_agent_id = %s AND DATEDIFF(purchase_date, %s) >= 0 AND DATEDIFF(%s, purchase_date) >= 0'
		cursor.execute(query, (ID, start_date, end_date))
		data = cursor.fetchone()
		response = {'count': data['count'],
					'comm': str(data['comm'])}

		return jsonify(response)
	else:
		return "Permission denied"

# AIRLINE STAFF ACTIONS//////////////////////////////////////////////////////////////

# Create Flight
@app.route("/createFlight")
def createFlight():
	if 'username' in session and session['type'] == 'airline_staff':
		return render_template("createflight.html")
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/createFlightAuth", methods=['POST'])
def createFlightAuth():
	if 'username' in session and session['type'] == 'airline_staff':
		flight_num = request.form['Flight_Num']
		departure_airport = request.form['Departure_Airport']
		departure_time = request.form['Departure_Time']
		arrival_airport = request.form['Arrival_Airport']
		arrival_time = request.form['Arrival_Time']
		price = request.form['Price']
		status = request.form['Status']
		airplane_ID = request.form['Airplane_ID']

		cursor = conn.cursor()
		cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
		airline_name = cursor.fetchone()
		airline_name = airline_name['airline_name']

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM flight WHERE airline_name = %s AND flight_num = %s', (airline_name, flight_num))
		data = cursor.fetchone()

		if (data):
			error = "This flight already exists"
			return render_template('createflight.html', error=error)
		else:
			ins = 'INSERT INTO flight VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)'
			cursor.execute(ins, (airline_name, flight_num, departure_airport, departure_time, arrival_airport, arrival_time, price, status, airplane_ID))
			conn.commit()
			cursor.close()
			return redirect(url_for('index'))
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

# Change Flight Status
@app.route("/changeFlightStatus", methods=['POST'])
def changeFlightStatus():
	if 'username' in session and session['type'] == 'airline_staff':
		airline_name = request.form['airline_name']
		flight_num = request.form['flight_num']
		status = request.form['status']

		cursor = conn.cursor()
		query = 'UPDATE flight SET status=%s WHERE airline_name=%s and flight_num=%s'
		cursor.execute(query, (status, airline_name, flight_num))
		conn.commit()
		cursor.close()

		return "Success"
	else:
		return "Permission denied"

# Add Airplane
@app.route("/addPlane")
def addPlane():
	if 'username' in session and session['type'] == 'airline_staff':
		return render_template("addplane.html")
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/addPlaneAuth", methods=['POST'])
def addPlaneAuth():
	if 'username' in session and session['type'] == 'airline_staff':
		airplane_ID = request.form['Airplane_ID']
		seats = request.form['Seats']

		cursor = conn.cursor()
		cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
		airline_name = cursor.fetchone()
		airline_name = airline_name['airline_name']

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM airplane WHERE airline_name = %s AND airplane_id = %s', (airline_name, airplane_ID))
		data = cursor.fetchone()

		if (data):
			error = "This airplane already exists"
			return render_template('addplane.html', error=error)
		else:
			ins = 'INSERT INTO airplane VALUES (%s, %s, %s)'
			cursor.execute(ins, (airline_name, airplane_ID, seats))
			conn.commit()
			

			cursor.execute('SELECT * FROM airplane WHERE airline_name = %s', airline_name)
			airplanes = cursor.fetchall()
			cursor.close()
			return render_template('addplane.html', airplanes=airplanes)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)


# Add Airport
@app.route("/addAirport")
def addAirport():
	if 'username' in session and session['type'] == 'airline_staff':
		return render_template("addairport.html")
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/addAirportAuth", methods=['POST'])
def addAirportAuth():
	if 'username' in session and session['type'] == 'airline_staff':
		name = request.form['Name']
		city = request.form['City']

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM airport WHERE airport_name = %s', (name))
		data = cursor.fetchone()

		if (data):
			error = "This airport already exists"
			return render_template('addairport.html', error=error)
		else:
			ins = 'INSERT INTO airport VALUES (%s, %s)'
			cursor.execute(ins, (name, city))
			conn.commit()
			cursor.close()
			return redirect(url_for('index'))
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/viewBookingAgents")
def viewBookingAgents():
	if 'username' in session and session['type'] == 'airline_staff':
		cursor = conn.cursor()

		cursor.execute('SELECT * FROM booking_agent')
		all_agents = cursor.fetchall()

		currtime=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
		query = 'SELECT booking_agent.email, booking_agent.booking_agent_id FROM booking_agent NATURAL JOIN purchases WHERE datediff(purchase_date,%s)<=31 GROUP BY booking_agent.email ORDER BY COUNT(*) DESC'
		cursor.execute(query, (currtime))
		top_sales_month_agents = cursor.fetchmany(5)

		query = 'SELECT booking_agent.email, booking_agent.booking_agent_id FROM booking_agent NATURAL JOIN purchases WHERE datediff(purchase_date,%s)<=365 GROUP BY booking_agent.email ORDER BY COUNT(*) DESC'
		cursor.execute(query, (currtime))
		top_sales_year_agents = cursor.fetchmany(5)

		query = 'SELECT booking_agent.email, booking_agent.booking_agent_id FROM booking_agent NATURAL JOIN purchases NATURAL JOIN ticket NATURAL JOIN flight WHERE datediff(purchase_date,%s)<=365 GROUP BY booking_agent.email ORDER BY SUM(price) DESC'
		cursor.execute(query, (currtime))
		top_commission_year_agents = cursor.fetchmany(5)

		return render_template('viewbookingagents.html', all_agents=all_agents, top_sales_month_agents=top_sales_month_agents, top_sales_year_agents=top_sales_year_agents, top_commission_year_agents=top_commission_year_agents)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/viewCustomers")
def viewCustomers():
	if 'username' in session and session['type'] == 'airline_staff':
		cursor = conn.cursor()
		customers=[]

		currtime=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
		query = 'SELECT customer.email, COUNT(*) as tickets FROM customer, purchases WHERE customer.email = purchases.customer_email AND datediff(purchase_date,%s)<=365 GROUP BY customer.email ORDER BY COUNT(*) DESC'
		cursor.execute(query, (currtime))
		customers = cursor.fetchall()

		return render_template('viewcustomers.html', customers=customers)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/viewCustomers/<email>")
def viewCustomer(email):
	if 'username' in session and session['type'] == 'airline_staff':
		cursor = conn.cursor()
		flights = []
		
		cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
		airline_name = cursor.fetchone()
		airline_name = airline_name['airline_name']

		query = 'SELECT flight_num FROM customer, purchases NATURAL JOIN ticket WHERE customer.email = purchases.customer_email AND airline_name=%s AND customer.email = %s'
		cursor.execute(query, (airline_name, email))
		flights = cursor.fetchall()

		return render_template('viewcustomerinfo.html', email=email, flights=flights)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/viewReports")
def viewreports():
	if 'username' in session and session['type'] == 'airline_staff':
		cursor = conn.cursor()
		cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
		airline_name = cursor.fetchone()
		airline_name = airline_name['airline_name']

		query = 'SELECT EXTRACT(MONTH from purchase_date) as month, COUNT(*) as count FROM purchases NATURAL JOIN ticket WHERE airline_name = %s GROUP BY EXTRACT(MONTH from purchase_date)'
		cursor.execute(query, (airline_name))
		monthlyReport = cursor.fetchall()

		return render_template('viewreports.html', monthlyReport=monthlyReport)
	else:
		error = "Permission denied"
		return render_template('index.html', username=session['username'], user_type=session['type'], error=error)

@app.route("/getNumTicketsSold", methods=['POST'])
def getNumTicketsSold():
	if 'username' in session and session['type'] == 'airline_staff':
		start_date = request.form['start_date']
		end_date = request.form['end_date']

		cursor = conn.cursor()
		cursor.execute('SELECT airline_name FROM airline_staff WHERE username = %s', (session['username']))		
		airline_name = cursor.fetchone()
		airline_name = airline_name['airline_name']
		query = 'SELECT COUNT(*) as total FROM purchases NATURAL JOIN ticket WHERE DATEDIFF(purchase_date, %s) >= 0 AND DATEDIFF(%s, purchase_date) >= 0 AND airline_name=%s'
		cursor.execute(query, (start_date, end_date, airline_name))
		count = cursor.fetchone()['total']
		response = {'count': count}

		return jsonify(response)
	else:
		return "Permission denied"

# ACCOUNT HANDLING//////////////////////////////////////////////////////////////

# Login page
@app.route('/login')
def login():
    return render_template('login.html')

# Register page
@app.route('/register')
def register():
    return render_template('register.html')

# Login auth
@app.route('/loginAuth', methods=['POST'])
def loginAuth():
	user_type = request.form['user_type']
	if user_type == 'customer':
		email = request.form['Email']
		password = request.form['Password']
		md5_password = hashlib.md5(password).hexdigest()

		cursor = conn.cursor()
		query = 'SELECT * FROM customer WHERE email = %s AND password = %s'
		cursor.execute(query, (email, md5_password))
		data = cursor.fetchone()
		cursor.close()

		if not data:
			error = 'Invalid login or username'
			return render_template('login.html', error=error)
		else:
			session['username'] = email
			session['type'] = user_type
			return redirect(url_for('index'))
	elif user_type == 'booking_agent':
		email = request.form['Email']
		password = request.form['Password']
		booking_agent_ID = request.form['Booking_Agent_ID']
		md5_password = hashlib.md5(password).hexdigest()

		cursor = conn.cursor()
		query = 'SELECT * FROM booking_agent WHERE email = %s AND password = %s AND booking_agent_id = %s'
		cursor.execute(query, (email, md5_password, booking_agent_ID))
		data = cursor.fetchone()
		cursor.close()

		if not data:
			error = 'Invalid login or username'
			return render_template('login.html', error=error)
		else:
			session['username'] = email
			session['type'] = user_type
			return redirect(url_for('index'))
	elif user_type == 'airline_staff':
		username = request.form['Username']
		password = request.form['Password']
		md5_password = hashlib.md5(password).hexdigest()
		
		cursor = conn.cursor()
		query = 'SELECT * FROM airline_staff WHERE username = %s AND password = %s'
		cursor.execute(query, (username, md5_password))
		data = cursor.fetchone()
		cursor.close()

		if not data:
			error = 'Invalid login or username'
			return render_template('login.html', error=error)
		else:
			session['username'] = username
			session['type'] = user_type
			return redirect(url_for('index'))
	return "Error. User type not found"

# Register auth
@app.route('/registerAuth', methods=['POST'])
def registerAuth():
	user_type = request.form['user_type']
	if user_type == 'customer':
		email = request.form['Email']
		password = request.form['Password']
		name = request.form['Name']
		building_number = request.form['Building_Number']
		street = request.form['Street']
		city = request.form['City']
		state = request.form['State']
		phone_number = request.form['Phone_Number']
		passport_number = request.form['Passport_Number']
		passport_expiration = request.form['Passport_Expiration']
		passport_country = request.form['Passport_Country']
		date_of_birth = request.form['Date_Of_Birth']
		md5_password = hashlib.md5(password).hexdigest()

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM customer WHERE email = %s', (email))
		data = cursor.fetchone()

		if (data):
			error = "This user already exists"
			return render_template('register.html', error=error)
		else:
			ins = 'INSERT INTO customer VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)'
			cursor.execute(ins, (email, name, md5_password, building_number, street, city, state, int(phone_number), passport_number, passport_expiration, passport_country, date_of_birth))
			conn.commit()
			cursor.close()

			session['username'] = email
			session['type'] = user_type
			return redirect(url_for('index'))
	elif user_type == 'booking_agent':
		email = request.form['Email']
		password = request.form['Password']
		booking_agent_ID = request.form['Booking_Agent_ID']
		md5_password = hashlib.md5(password).hexdigest()

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM booking_agent WHERE email = %s', (email))
		data = cursor.fetchone()

		if (data):
			error = "This user already exists"
			return render_template('register.html', error=error)
		else:
			ins = 'INSERT INTO booking_agent VALUES (%s, %s, %s)'
			cursor.execute(ins, (email, md5_password, int(booking_agent_ID)))
			conn.commit()
			cursor.close()

			session['username'] = email
			session['type'] = user_type
			return redirect(url_for('index'))
	elif user_type == 'airline_staff':
		username = request.form['Username']
		password = request.form['Password']
		md5_password = hashlib.md5(password).hexdigest()
		first_name = request.form['First_Name']
		last_name = request.form['Last_Name']
		date_of_birth = request.form['Date_Of_Birth']
		airline_name = request.form['Airline_Name']

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM airline_staff WHERE username = %s', (username))
		data = cursor.fetchone()

		if (data):
			error = "This user already exists"
			return render_template('register.html', error=error)
		else:
			ins = 'INSERT INTO airline_staff VALUES (%s, %s, %s, %s, %s, %s)'
			cursor.execute(ins, (username, md5_password, first_name, last_name, date_of_birth, airline_name))
			conn.commit()
			cursor.close()

			session['username'] = username
			session['type'] = user_type
			return redirect(url_for('index'))
	return "Error. User type not found"

# Logout
@app.route('/logout')
def logout():
	session.pop('username', None)
	session.pop('type', None)
	return redirect(url_for('index'))




if __name__ == "__main__":
	app.run()
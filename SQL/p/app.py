from flask import Flask, render_template, session, redirect, url_for,request,flash
import hashlib
import string
import requests
import pymysql.cursors

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

# Routing/Rendering template~~~~~~~~~~~~~


# Home page
@app.route("/")
def index():
	# cursor = conn.cursor();
	# query = 'SELECT * FROM airplane'
	# cursor.execute(query)
	# data = cursor.fetchall()
	# cursor.close()
	# print data
	if 'username' in session:
		return render_template("index.html", username=session['username'])
	else:
		return render_template("index.html", username=None)

# Login page
@app.route('/login')
def login():
    return render_template('login.html')

# Register page
@app.route('/register')
def register():
    return render_template('register.html')

# Login page
@app.route('/loginAuth', methods=['POST'])
def loginAuth():
    print request.form
    if request.form['user_type'] == 'customer':
    	return "ayylmao"
    elif request.form['user_type'] == 'booking_agent':
    	return "booking"
    elif request.form['user_type'] == 'airline_staff':
    	return "airline"

# Register page
@app.route('/registerAuth', methods=['POST'])
def registerAuth():
	print request.form
	if request.form['user_type'] == 'customer':
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

		
		# TODO validate all inputs pls

		cursor = conn.cursor()
		cursor.execute('SELECT * FROM customer WHERE email = %s', (email))
		data = cursor.fetchone()

		if (data):
			error = "This user already exists"
			return render_template('register.html', error = error)
		else:
			ins = 'INSERT INTO customer VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)'
			cursor.execute(ins, (email, name, password, building_number, street, city, state, int(phone_number), passport_number, passport_expiration, passport_country, date_of_birth))
			conn.commit()
			cursor.close()

			session['username'] = email
			return redirect(url_for('index'))

	elif request.form['user_type'] == 'booking_agent':
		return "booking"
	elif request.form['user_type'] == 'airline_staff':
		return "airline"

# Logout
@app.route('/logout')
def logout():
	session.pop('username', None)
	return redirect(url_for('index'))




if __name__ == "__main__":
	app.run()
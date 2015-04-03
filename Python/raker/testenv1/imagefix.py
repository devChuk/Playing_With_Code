"""
Apparently most of the Bergdorf Goodman items are missing images. This code is meant to fix that.

PROCESS:

Go through each item, grab the url from that item.
Make the scraper visit that item's page.
And just add the images to the existing item.

	[{'images': [<list of img links>], 'color_families': <one element of 'color_families'>, 'name': <'color_families'>}]
	color_families isn't showing up because there are no color families derp
leggoo
"""
# IMPORTS
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait # available since 2.4.0
from selenium.webdriver.common.by import By

import time
import pymongo
from pymongo import MongoClient

# SETUP
driver = webdriver.Firefox() # Create a new instance of the Firefox driver

client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
db = client['frockhub2']
bergdorf = db['bergdorf']


#{'color': u'black', 'images': [u'LINK', u'LINK', u'http://assets.burberry.com/is/image/Burberryltd/71581cc1c5e1fd7d6a628faf1f27b83ed706746c?$prod_main$'], 'color_family': ''}
def edit():
	x = 0
	for doc in bergdorf.find({}):
		try:
			v = doc['colors']
			if len(v) == 0:
				# setting up elements of colors
				print str(x) + "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				x= x + 1
				colors = []
				sources = []
				fam = doc['color_families']
				# scraping
				driver.get(doc['url'])
				WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "img-wrap")))
				name = driver.find_element_by_class_name("nsStyle").text.lower()
				data = driver.find_element_by_class_name('img-wrap').find_element_by_tag_name('img').get_attribute('src')
				sources.append(data)
				# create colors list (which only has one element because of how bergdorf goodman is formatted)
				colors.append({'name': name, 'color_family': fam, 'images': sources})
				print doc['colors']
				print colors
				time.sleep(1.4)
				print doc['_id']
				bergdorf.update({'_id':doc['_id']}, {'$set':{'colors':colors}}) ##################SUPER DANGEROUS MAKE SURE PRIOR CODE WORKS OR DATA WILL GET CORRUPTED LOLOLOL
		except:
			print "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
	print str(x) + " fixed"

def observe():
	for doc in bergdorf.find({}):
		try:
			v = doc['colors']
			if len(v) == 0:
				print doc
		except:
			print "argh"

# for doc in bergdorf.find({}):
# 	doc['colors'].update(newColor)

# RUN
observe()
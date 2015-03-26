## Specification
# category:
# brand:
# gender:
# name:
# description:
# origin: 
# currency:
# url:
# price: int
# size: []
# material: []
# event: []
# color: []
# color_family: []
# images: []

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait # available since 2.4.0

from time import sleep
import pymongo
from pymongo import MongoClient

# SETUP

##########ASK ABOUT MONGODB CREDENTIALS
#client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
#db = client['frockhub2']
#collection = db['burberry']

##########SELENIUM CHROME DRIVER MAGIC (this stuff is actually pretty cool)
driver = webdriver.Firefox() # Create a new instance of the Firefox driver




"""
	browser.get(pageUrl)
	possible = browser.find_elements_by_tag_name("li")
	possible = [item for item in possible if 'l-2' in item.get_attribute("class")]
	possible = [item.find_element_by_tag_name("ul") for item in possible if 'active' in item.find_element_by_tag_name("a").get_attribute("class")][0].find_elements_by_tag_name("li")
	categories = {}
	for category in possible:
		category = category.find_element_by_tag_name("a")
		categories.update({category.text.lower():category.get_attribute("href")})
	return categories
"""


def maleCategoriesfilter(text):
	return text and "\n" not in text and "DESIGNERS" not in text and "MEN" not in text and text != "SHOES" and text != "BELTS" and "BG" not in text and "NEW" not in text and "BEST" not in text and "MARCUS" not in text and text != "ACCESSORIES"

def grabCategories(pageUrl):
	driver.get(pageUrl)
	categories = {}
	possibles = [thing for thing in driver.find_elements_by_tag_name("li") if maleCategoriesfilter(thing.text)]#thing.text and "\n" not in thing.text and "DESIGNERS" not in thing.text] #This piece finds all the possible li's that we need
	for possible in possibles:
		print possible
		print possible.text
	return categories

def startUrl(url, gender):
	result = []
	print "\n"
	print "scraping from:"
	print url + " for " + gender + "\n"
	categories = grabCategories(url)
	return result

def scrape(): #love how there's a single tab for mens and the rest are all for women
	products = []
	#browser.find_element_by_xpath()
	#urls = [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"], ["http://www.bergdorfgoodman.com/5F-Contemporary/5F-Apparel/Shop-All-5F/cat441205_cat232503_cat230300/c.cat", "women"], ["http://www.bergdorfgoodman.com/Categories/Scarves/cat408112_cat408110_cat408107/c.cat","women"], ["http://www.bergdorfgoodman.com/Shoe-Salon/cat200648/c.cat?siloId=cat200648&navid=topNavShoeSalon","women"], ["http://www.bergdorfgoodman.com/Handbags/cat257221/c.cat?siloId=cat257221&navid=topNavHandbags","women"]]
	urls = [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"]]
	for url in urls:
		gender = url.pop()
		link = url.pop()
		startUrl(link, gender)

# RUN
scrape()
driver.quit()
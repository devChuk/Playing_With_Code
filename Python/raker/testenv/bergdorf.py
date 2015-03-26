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


def grabCategories(pageUrl):
	driver.get(pageUrl)
	categories = {}
	possible = driver.find_elements_by_tag_name("li").toString()
	print possible
	return categories

def startUrl(url, gender):
	result = []
	print "\n"
	print "scraping from:"
	print url + " for " + gender
	categories = grabCategories(url)


	return result

def scrape(): #love how there's a single tab for mens and the rest are all for women
	products = []
	#browser.find_element_by_xpath()
	urls = [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"]]
	for url in urls:
		gender = url.pop()
		link = url.pop()
		startUrl(link, gender)

# RUN
scrape()
driver.quit()
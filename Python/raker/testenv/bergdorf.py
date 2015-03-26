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
from time import sleep
import pymongo
from pymongo import MongoClient
##########ASK ABOUT MONGODB CREDENTIALS
#client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
#db = client['frockhub2']
#collection = db['burberry']
# chromedriver = "./chromedriver"
# browser = webdriver.Chrome(executable_path = chromedriver)

def grabCategories(pageUrl):
	categories = {}
	return categories

def startUrl(url, gender):
	result = []
	categories = grabCategories(url)
	print categories
	for page in categories:
		item_sets = grabItemSets(categories[page])
		for track in item_sets:
			for item in item_sets[track]:
				try:
					result.append(scrapeProductUrl(item, gender, page, track))
				except:
					result.append(scrapeProductUrl(item, gender, page, track))
	return result

def scrape(): #love how there's a single tab for mens and the rest are all for women
	products = []
	#browser.find_element_by_xpath()
	urls = [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"]]
	for url in urls:
		print ', '.join(urls)


scrape()
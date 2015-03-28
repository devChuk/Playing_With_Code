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

client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
db = client['frockhub2']
bergdorf = db['bergdorf']


##########SELENIUM CHROME DRIVER MAGIC (this stuff is actually pretty cool)
driver = webdriver.Firefox() # Create a new instance of the Firefox driver
c_colors = ['brown', 'orange', 'yellow', 'red', 'purple', 'blue', 'green', 'gray', 'white', 'black', 'pink', 'gold', 'silver', 'beige']
materialz = ['silk', 'cotton', 'chiffon', 'satin', 'silt', 'wool', 'linen', 'cashmere', 'taffita', 'leather', 'mink', 'fur', 'suade', 'tweed', 'fleece', 'velvet', 'grogaine', 'corduroy', 'denim']

def getColors():
	ans = []
	try:
		print driver.find_element_by_class_name("colorSelectTop.colorSelect").text
	except:
		ans = []
	try:
		text = driver.find_element_by_class_name("oneColor").text.lower()
		images = driver.find_elements_by_class_name('alt-shot')
		sources = []
		for image in images:
			sources.append(image.get_attribute("src"))
		for color in c_colors:
			if color in text:
				ans.append({'name':color, 'color_family': color, 'images': sources})
		return ans
	except:
		text = driver.find_elements_by_xpath("//option")
	return ans

def getc_fam():
	ans = []
	try:
		text = driver.find_element_by_class_name("oneColor").text.lower()
	except:
		text = ""
	for color in c_colors:
		if color in text:
			ans.append(color)
	return ans

def getMaterials():
	ans = []
	text = driver.find_element_by_class_name("qvTopBorder").text
	for mat in materialz:
		if mat in text:
			ans.append(mat)
	return ans

def getSizes():
	ans = []
	all_sizes = driver.find_elements_by_xpath("//option")
	for size in all_sizes:
		size = size.get_attribute("value")
		ans.append(size)
	return ans

def scrapeProduct(productUrl, gender, category):
	scraped_item = {}
	print driver.find_element_by_id("qvHeaderPrice").text
	if "." in driver.find_element_by_id("qvHeaderPrice").text and "," in driver.find_element_by_id("qvHeaderPrice").text:
		try:
			pprice = int(driver.find_element_by_id("qvHeaderPrice").text.replace(",","")[1:(driver.find_element_by_id("qvHeaderPrice").text.index(".") - 1)])
		except:
			#find_element_by_css_selector(".price.pos1");
			pprice = int(driver.find_element_by_css_selector(".price.pos1").text.replace(",","")[1:(driver.find_element_by_css_selector(".price.pos1").text.index(".") - 1)])
		print category + " " + str(pprice)
		scraped_item = {"available": True, "unavailable": {}, "url": productUrl, "gender":gender, "category":category, "currency":"USD", "price": pprice, "brand":driver.find_element_by_id("productDesignerName").text, "name":driver.find_element_by_class_name("displayName").text, "description":driver.find_element_by_class_name("qvTopBorder").text, "color_families":getc_fam(), "materials":getMaterials(), "colors":getColors(), "sizes":getSizes(), "events":[], "attributes":[]}	
	elif "." in driver.find_element_by_id("qvHeaderPrice").text:
		scraped_item = {"available": True, "unavailable": {}, "url": productUrl, "gender":gender, "category":category, "currency":"USD", "price":int(driver.find_element_by_id("qvHeaderPrice").text[1:(driver.find_element_by_id("qvHeaderPrice").text.index("."))]), "brand":driver.find_element_by_id("productDesignerName").text, "name":driver.find_element_by_class_name("displayName").text, "description":driver.find_element_by_class_name("qvTopBorder").text, "color_families":getc_fam(), "materials":getMaterials(), "colors":getColors(), "sizes":getSizes(), "events":[], "attributes":[]}	
		print category + " " + str(scraped_item["price"])
	elif "-$" in driver.find_element_by_id("qvHeaderPrice").text:
		scraped_item = {"available": True, "unavailable": {}, "url": productUrl, "gender":gender, "category":category, "currency":"USD", "price":int(driver.find_element_by_class_name("rtlPrice").text[1:]), "brand":driver.find_element_by_id("productDesignerName").text, "name":driver.find_element_by_class_name("lineItemNameSpan").text, "description":driver.find_element_by_class_name("qvTopBorder").text, "color_families":getc_fam(), "materials":getMaterials(), "colors":getColors(), "sizes":getSizes(), "events":[], "attributes":[]}	
		print category + " " + str(scraped_item["price"])
	elif "," in driver.find_element_by_id("qvHeaderPrice").text:
		pprice = int(driver.find_element_by_id("qvHeaderPrice").text.text.replace(",",""))
		scraped_item = {"available": True, "unavailable": {}, "url": productUrl, "gender":gender, "category":category, "currency":"USD", "price": pprice, "brand":driver.find_element_by_id("productDesignerName").text, "name":driver.find_element_by_class_name("displayName").text, "description":driver.find_element_by_class_name("qvTopBorder").text, "color_families":getc_fam(), "materials":getMaterials(), "colors":getColors(), "sizes":getSizes(), "events":[], "attributes":[]}
		print category + " " + str(scraped_item["price"])
	return scraped_item

def grabCategoryProducts(pageUrl, gender, page):
	products = []
	driver.get(pageUrl)
	WebDriverWait(driver, 10)
	driver.find_element_by_id("HundredTwentyPerPage").click() #try
	# while driver.find_element_by_class_name("pagingNav").text == "NEXT":
	all_products = driver.find_elements_by_class_name("qv-tip")
	for product in all_products:
		# try:
		product.click()
		WebDriverWait(driver, 25).until(EC.element_to_be_clickable((By.ID,'qvViewProductDetails')))
		prod = scrapeProduct(driver.find_element_by_class_name("prodPageLink").get_attribute("href"), gender, page)
			# bergdorf.insert(prod)##############################################################################################
		# except:	
		# 	print "SKIPPED ITEM " + page
	return products

def maleCategoriesfilter(text):
	return text and "\n" not in text and "DESIGNERS" not in text and "MEN" not in text and text != "SHOES" and text != "BELTS" and "BG" not in text and "NEW" not in text and "BEST" not in text and "MARCUS" not in text and "ACCESSORIES" not in text and "ALL" not in text and "MAGAZINE" not in text and "LOOKS" not in text and "STORIES" not in text and "SUN" not in text and "OPTICAL" not in text and "WATCH" not in text and "SWIM" not in text

def grabCategories(pageUrl):
	driver.get(pageUrl)
	categories = {}
	possibles = [thing for thing in driver.find_elements_by_tag_name("li") if maleCategoriesfilter(thing.text)]#thing.text and "\n" not in thing.text and "DESIGNERS" not in thing.text] #This piece finds all the possible li's that we need
	for possible in possibles:
		possible = possible.find_element_by_tag_name("a")
		print possible.get_attribute("href")
		print possible.text
		categories.update({possible.text.lower():(possible.get_attribute("href"))})
	print "Categories grabbed. Now scraping from each category~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	return categories

def startUrl(url, gender):
	result = []
	print "\n"
	print "scraping from:"
	print url + " for " + gender + "\n"
	categories = grabCategories(url)
	categoryProducts = {}
	for page in categories:
		print gender + ": " + page + ":  " + categories[page]
		categoryProducts.update({page:grabCategoryProducts(categories[page], gender, page)})

	# for categoryProduct in categoryProducts
	# 	superfunc()
	return result

def scrape(): #love how there's a single tab for men and the rest are all for women
	products = []
	#browser.find_element_by_xpath()
	#["http://www.bergdorfgoodman.com/Shoe-Salon/cat200648/c.cat?siloId=cat200648&navid=topNavShoeSalon","women"], ["http://www.bergdorfgoodman.com/Handbags/cat257221/c.cat?siloId=cat257221&navid=topNavHandbags","women"]]
	#urls = [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"], ["http://www.bergdorfgoodman.com/5F-Contemporary/5F-Apparel/Shop-All-5F/cat441205_cat232503_cat230300/c.cat", "women"], ["http://www.bergdorfgoodman.com/Categories/Scarves/cat408112_cat408110_cat408107/c.cat","women"]]
	urls = [["http://www.bergdorfgoodman.com/5F-Contemporary/5F-Apparel/Shop-All-5F/cat441205_cat232503_cat230300/c.cat", "women"]]
	#DONE: [["http://www.bergdorfgoodman.com/Mens-Store/Clothing/cat000024_cat202802_cat000000/c.cat", "men"]], 
	for url in urls:
		gender = url.pop()
		link = url.pop()
		startUrl(link, gender)

# RUN
scrape()
driver.quit()
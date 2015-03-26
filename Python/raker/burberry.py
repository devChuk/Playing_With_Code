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
# client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
# db = client['frockhub2']
# collection = db['burberry']
# chromedriver = "./chromedriver"
# browser = webdriver.Chrome(executable_path = chromedriver)
materials = ['silk', 'cotton', 'chiffon', 'satin', 'silt', 'wool', 'linen', 'cashmere', 'taffita', 'leather', 'mink', 'fur', 'suade', 'tweed', 'fleece', 'velvet', 'grogaine', 'corduroy', 'denim']

def scrapeProductUrl(productUrl, gender, category, track):
	if collection.find_one({'url':productUrl}) != None:
		return None
	print productUrl
	scraped_item = {"available": False, "unavailable": {}, "url": productUrl, "gender":gender, "category":category, "currency":"USD", "price":0, "brand":"burberry", "name":"", "description":"", "color_families":[], "materials":[], "colors":[], "sizes":[], "events":[], "attributes":[track]}
	browser.get(productUrl)

	if track == "dressy":
		scraped_item['events'].append("office")
	if track == "casual":
		scraped_item['events'].append("casual")

	try:
		scraped_item['name'] = browser.find_element_by_class_name('product-title').text
		scraped_item['price'] = int(browser.find_element_by_class_name("price-amount").text.replace('$', '').replace(',', '').replace('.', ''))
		description = browser.find_element_by_class_name("product-info-content").find_element_by_tag_name("ul").find_elements_by_tag_name("li")
	except:
		return None

	description = [li.text for li in description]
	for li in description:
		scraped_item['description'] = scraped_item['description'] + "\n" + li
	## Do everything before we do color!
	# We need to get images for each color
	try:
		links = [link.get_attribute("data-color-link") for link in browser.find_elements_by_class_name("color-swatch-link")]
	except:
		return None

	for link in links:
		browser.get("http://"+productUrl.split("/")[2]+link)
		sleep(0.1)
		color = browser.find_element_by_class_name("color-name").text.lower()
		# Mark that /something/ is available
		if scraped_item['available'] == False and (browser.find_elements_by_id("frmProduct_ddlQuantity") != []):
			scraped_item['available'] = True
		if browser.find_elements_by_id("frmProduct_ddlQuantity") == []:
			scraped_item['unavailable'].update({color:[]})
		## Iterate through sizes
		## Find what's not availible
		for size in browser.find_elements_by_class_name("-radio-span"):
			if not size.text.lower() in scraped_item['sizes']:
				scraped_item['sizes'].append(size.text.lower())
			if 'disabled' in size.get_attribute("class"):
				size = size.text.lower()
				if color in scraped_item['unavailable']:
					if size.isdigit():
						scraped_item['unavailable'][color].append(int(size))
					else:
						scraped_item['unavailable'][color].append(size)
				else:
					scraped_item['unavailable'].update({color: [size]})
		try:
			scraped_item['colors'].append({'color': color, 'color_family': '', 'images': [li.find_element_by_tag_name("img").get_attribute("src") for li in browser.find_elements_by_class_name("product-image")]})
		except:
			scraped_item['colors'].append({'color': color, 'color_family': '', 'images': [li.find_element_by_tag_name("img").get_attribute("src") for li in browser.find_elements_by_class_name("product-image")]})

	for material in materials:
		if material in scraped_item['name'].lower() or material in scraped_item['description'].lower():
			scraped_item['materials'].append(material)
	try:
		collection.insert(scraped_item)
	except:
		print "SKIPPED ITEM"


def grabItemSets(pageUrl):
	product_urls = {"casual":[], "dressy":[], "trendy":[], "other":[]}
	browser.get(pageUrl)
	item_sets = browser.find_elements_by_tag_name("ul")
	product_sets = [p_set for p_set in item_sets if "product-set" in p_set.get_attribute("class")]
	for product_set in product_sets:
		track_name = product_set.get_attribute("data-track-name").lower()
		track_type = ""
		if track_name == "prorsum":
			track_type = "trendy"
		elif track_name == "london":
			track_type = "dressy"
		elif "brit" in track_name:
			track_type = "casual"
		else:
			track_type = "other"
		for product in product_set.find_elements_by_tag_name("li"):
			if not 'product' in product.get_attribute("class"):
				continue
			product_urls[track_type].append(product.find_element_by_tag_name("a").get_attribute("href"))
	return product_urls

def grabCategories(pageUrl):
	browser.get(pageUrl)
	possible = browser.find_elements_by_tag_name("li")
	possible = [item for item in possible if 'l-2' in item.get_attribute("class")]
	possible = [item.find_element_by_tag_name("ul") for item in possible if 'active' in item.find_element_by_tag_name("a").get_attribute("class")][0].find_elements_by_tag_name("li")
	categories = {}
	for category in possible:
		category = category.find_element_by_tag_name("a")
		categories.update({category.text.lower():category.get_attribute("href")})
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


def scrape():
	products = []
	#browser.find_element_by_xpath()
	## Women
	urls = [["http://us.burberry.com/womens-clothing/", "women"], ["http://us.burberry.com/womens-trench-coats/", "women"], ["http://us.burberry.com/womens-bags/", "women"], ["http://us.burberry.com/womens-scarves/", "women"], ["http://us.burberry.com/womens-shoes/", "women"]]
	for url in urls:
		print startUrl(*url)

scrape()
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from time import sleep
import pymongo
from pymongo import MongoClient
client = MongoClient("mongodb://cris:cris1@c18.candidate.43.mongolayer.com:10018,c333.candidate.40.mongolayer.com:10333/frockhub2")
db = client['frockhub2']
collection = db['barneys']
chromedriver = "./chromedriver"
browser = webdriver.Chrome(executable_path = chromedriver)
materials = ['silk', 'cotton', 'chiffon', 'satin', 'silt', 'wool', 'linen', 'cashmere', 'taffita', 'leather', 'mink', 'fur', 'suade', 'tweed', 'fleece', 'velvet', 'grogaine', 'corduroy', 'denim']
c_colors = ['brown', 'orange', 'yellow', 'red', 'purple', 'blue', 'green', 'gray', 'white', 'black', 'pink', 'gold', 'silver', 'beige']

urls = [["http://www.barneys.com/barneys-new-york/women/clothing", "women"]]
def startUrl(url, gender):
	categories_ = grabCategories(url, gender)
	categories__ = {}
	categories = {}
	for category in categories_:
		categories__.update({category['name']: category['url']})
	for category in categories__:
		categories.update({category: grabItems(categories__[category])})
	for category in categories:
		try:
			categories.update({category: [scrapeItem(item, gender, category) for item in categories[category]]})
		except:
			pass

def grabCategories(url, gender):
	browser.get(url)
	category_list = browser.find_element_by_id("category-level-2")
	categories = []
	for element in category_list.find_elements_by_tag_name("li"):
		expandable = ("expandable" in element.get_attribute("class"))
		link = element.find_element_by_tag_name("a")
		categories.append({'name':link.get_attribute("title"), 'url':link.get_attribute("href"), 'expandable':expandable, 'gender': gender})
	return categories

def scrapeItem(url, gender, category):
	if collection.find_one({'url':url}) != None:
		return None
	scraped_item = {"available": False, "unavailable": {}, "url": url, "gender":gender, "category":category, "currency":"USD", "price":0, "brand":"", "name":"", "description":"", "color_families":[], "materials":[], "colors":[], "sizes":[], "events":[], "attributes":[]}
	browser.get(url)
	scraped_item['description'] = browser.find_element_by_class_name("panel-body").text
	scraped_item['brand'] = browser.find_element_by_class_name("brand").text.lower()
	scraped_item['name'] = browser.find_element_by_class_name("product-name").text
	scraped_item['price'] = int(browser.find_element_by_class_name("price-sales").text.replace('$', '').replace(',', ''))
	scraped_item['images'] = [img.get_attribute("src") for img in browser.find_element_by_class_name("product-image-carousel").find_elements_by_tag_name("img")]
	for color in c_colors:
		if color in scraped_item['description'] or color in scraped_item['name']:
			scraped_item['color_families'].append(color)
			scraped_item['colors'].append({'name': color, 'color_family': color, 'images': scraped_item['images']})
	if 'available in' in scraped_item['description'].lower():
		findColor = scraped_item['description'].lower().split()
		index = findColor.index("available")
		color = findColor[index + 2].replace('.', '')
		change = True
		for item in scraped_item['colors']:
			if color in item['name']:
				change = False
		if change == True:
			scraped_item['colors'].append({'name': color, 'color_family': '', 'images': scraped_item['images']})
	if len(scraped_item['colors']) < 1:
		scraped_item['colors'].append({'name': '', 'color_family': '', 'images': scraped_item['images']})
	if browser.find_elements_by_id("add-to-cart") == []:
		scraped_item['available'] = False
	else:
		scraped_item['available'] = ("buy" in browser.find_element_by_id("add-to-cart").text.lower())
	scraped_item['sizes'] = [size.find_element_by_tag_name("a").text.lower() for size in browser.find_elements_by_class_name("emptyswatch")]
	for size in browser.find_elements_by_class_name("emptyswatch"):
		if 'unselectable' in size.get_attribute("class"):
			for color in scraped_item['colors']:
				if color['name'] in scraped_item['unavailable']:
					scraped_item['unavailable'][color['name']].append(size.find_element_by_tag_name("a").text.lower())
				else:
					scraped_item['unavailable'].update({color['name']: [size.find_element_by_tag_name("a").text.lower()]})
	for material in materials:
		if material in scraped_item['description'] or material in scraped_item['name']:
			scraped_item['materials'].append(material)
	print scraped_item
	collection.insert(scraped_item)


def grabItems(url):
	urls = []
	browser.get(url)
	browser.get([link.get_attribute("href") for link in browser.find_elements_by_class_name("sorting-option") if "48" in link.text][0])
	sleep(1)
	pages = browser.find_elements_by_class_name("page-no")[-1].find_element_by_tag_name("a").text
	if pages.isdigit():
		pages = int(pages)
	else:
		return
	for page in range(pages):
		urls.extend([link.get_attribute("href") for link in browser.find_elements_by_class_name("thumb-link")])
		if page == pages-1:
			continue
		if browser.find_elements_by_class_name("page-next") != []:
			browser.get(browser.find_elements_by_class_name("page-next")[-1].get_attribute("href"))
		else:
			browser.get(browser.find_elements_by_class_name("page-no")[-1].find_element_by_tag_name("a").get_attribute("href"))
		sleep(1)
	return list(set(urls))
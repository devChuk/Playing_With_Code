"""
Apparently most of the Bergdorf Goodman items are missing images. This code is meant to fix that.

PROCESS:

Go through each item, grab the url from that item.
Make the scraper visit that item's page.
And just add the images to the existing item.

leggoo
"""
from time import sleep
import pymongo
from pymongo import MongoClient
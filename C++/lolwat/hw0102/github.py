#brian chuk
from bs4 import BeautifulSoup
import requests

r = requests.get('https://github.com/trending')
soup = BeautifulSoup(r.text)

list = []

for link in soup.find_all('h3', class_="repo-list-name"):
    list.append('https://github.com' + link.contents[1].get('href'))

print list
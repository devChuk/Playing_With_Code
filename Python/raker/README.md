Notes on raker project
======================

(this is a freelance project)


#Format
https://docs.google.com/document/d/10cGMGMSijke0lIZUNIiIQu6_MwH8ktVJNlx6h_p-1wU/edit?usp=sharing


#Target
http://www.bergdorfgoodman.com/

**Process:**

	scrapeProductUrl(productUrl, gender, category, track)

run for every single product

	grabItemSets(pageUrl)

organizes product URLs into item sets (dressy, casual, trendy, etc)

	grabCategories(pageUrl)

just finds out the categories in the url given (prorsum, new arrivals, clothing, trench coats, bags, scarves, make-up, etc)

	startUrl(url, gender)

called for every URL, figures out the categories, and returns an array of item sets

	scrape()

the main function that kicks it off
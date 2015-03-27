Notes on raker project
======================

(this is a freelance project)


#Setup
**Links:**

[Format](https://docs.google.com/document/d/10cGMGMSijke0lIZUNIiIQu6_MwH8ktVJNlx6h_p-1wU/edit?usp=sharing)

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

#Execution
**Links:**

[Mens](http://www.bergdorfgoodman.com/Mens-Store/cat202802/c.cat?siloId=cat202802&navid=topNavMens) | 
[Women's scarves](http://www.bergdorfgoodman.com/Categories/Scarves/cat408112_cat408110_cat408107/c.cat) | 
[Women's shoes](http://www.bergdorfgoodman.com/Shoe-Salon/cat200648/c.cat?siloId=cat200648&navid=topNavShoeSalon) | 
[Women's bags](http://www.bergdorfgoodman.com/Handbags/cat257221/c.cat?siloId=cat257221&navid=topNavHandbags) | 
[Women's clothes](http://www.bergdorfgoodman.com/5F-Contemporary/5F-Apparel/Shop-All-5F/cat441205_cat232503_cat230300/c.cat)


**Process:**

>Needs specialization for men & 5F pages. High amt of repeats on bags, will need to check for repeats text
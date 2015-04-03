Notes on raker project
======================

(this is a freelance project)

#TODO

Fix image issue

#Misc Notes

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
cd 
#Execution
**Links:**

[Mens](http://www.bergdorfgoodman.com/Mens-Store/cat202802/c.cat?siloId=cat202802&navid=topNavMens) | 
[Women's scarves](http://www.bergdorfgoodman.com/Categories/Scarves/cat408112_cat408110_cat408107/c.cat) | 
[Women's shoes](http://www.bergdorfgoodman.com/Shoe-Salon/cat200648/c.cat?siloId=cat200648&navid=topNavShoeSalon) | 
[Women's bags](http://www.bergdorfgoodman.com/Handbags/cat257221/c.cat?siloId=cat257221&navid=topNavHandbags) | 
[Women's clothes](http://www.bergdorfgoodman.com/5F-Contemporary/5F-Apparel/Shop-All-5F/cat441205_cat232503_cat230300/c.cat)


**Process:**

>Needs specialization for men & 5F pages. High amt of repeats on bags, will need to check for repeats text

* boys and girls are the genders for kid items
* make sure sizes are right, they're formatted a little strangely
* ^do this by filtering with gender & category in the website itself

Here's the links to scrape:

**Boy:**

[jackets](http://www.bergdorfgoodman.com/Kids/Boys/cat413109_cat000006_cat000000/c.cat?fromDrawer=true#endecaDrivenSiloRefinements=fromDrawer%3Dtrue&userConstrainedResults=true&refinements=4294924778,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=) | [tops](http://www.bergdorfgoodman.com/Kids/Boys/cat413109_cat000006_cat000000/c.cat?fromDrawer=true#endecaDrivenSiloRefinements=fromDrawer%3Dtrue&userConstrainedResults=true&refinements=4294924777,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=)

**Girl:**

[dresses](http://www.bergdorfgoodman.com/Kids/Girls/cat356400_cat000006_cat000000/c.cat#userConstrainedResults=true&refinements=4294924774,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=) | [jackets](http://www.bergdorfgoodman.com/Kids/Girls/cat356400_cat000006_cat000000/c.cat#userConstrainedResults=true&refinements=4294924778,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=) | [shorts](http://www.bergdorfgoodman.com/Kids/Girls/cat356400_cat000006_cat000000/c.cat#userConstrainedResults=true&refinements=4294924780,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=) | [tops](http://www.bergdorfgoodman.com/Kids/Girls/cat356400_cat000006_cat000000/c.cat#userConstrainedResults=true&refinements=4294924777,&page=1&pageSize=120&sort=PCS_SORT&definitionPath=/nm/commerce/pagedef/template/EndecaDriven&allStoresInput=false&onlineOnly=)
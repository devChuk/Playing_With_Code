Filterable Portfolios
======================

A test HTML setup for [devchuk.github.io/portfolio](http://devchuk.github.io/portfolio)

Made with [MixItUp](https://mixitup.kunkalabs.com/).

I'm just going to dump some notes here in order to see if I can automate this with Jekyll.
You should probably view this in RAW format to make sense of the code.

This is a normal li html setup for one of the projects.

                <li class="mix category-1" data-myorder="1">                    
                    <figure>
                        <img src="http://tympanus.net/Tutorials/CaptionHoverEffects/images/2.png" alt="img02">
                        <figcaption>
                            <h3>Music</h3>
                            <span>Jacob Cummings</span>
                            <a href="http://dribbble.com/shots/1115960-Music">Take a look</a>
                        </figcaption>
                    </figure>
                </li>

Our variables are:

CLASS

DATA-MYORDER

IMAGE REF

TITLE

DATE

Our collection name is: projects

Here's an example of Liquid using a Jekyll post.

				<div class="posts">
				  {% for post in paginator.posts %}
				  <div class="post">
				    <span style="color:#de3230;font-weight:bold" class="post-title">
				      <a href="{{ post.url }}">
				        {{ post.title }}
				      </a>
				    </span>

				    <small style="float:right" class="post-date">{{ post.date | date_to_long_string }}</small>

				    {{ post.content }}
				    <br>
				    <hr>
				  </div>
				  {% endfor %}
				</div>

Based on this we'd do:

	            <div id="Container" class="grid cs-style-2">
	            {% for proj in site.projects %}
	            	<li class="{{ proj.cat }}" data-myorder="{{ proj.order }}">                    
                    	<figure>
                        	<img src="{{ proj.img }}">
                        	<figcaption>
                            	<h3>{{ proj.title }}</h3>
                            	<span>J{{ proj.date }}</span>
                            	<a href="{{ proj.url }}">Take a look</a>
        	                </figcaption>
            	        </figure>
                	</li>
				{% endfor %}                	


YAML
---
layout: post
title: Hello There
cat: mix category-#
order: #
date: 14 January 2014
img: <IMGREF LINK>
---

WARNING: Collections are still an experimenal feature in Jekyll so we'll never know if we might have to redo the entire thing or cry a lot.

SOLUTION: Prepare to cry haha.

Alright it's all planned. Let's have a procedure here:

1)Test to see if portfolio is friendly with this html setup. Will have to tweak .css file.
2)Setup a [collection](http://jekyllrb.com/docs/collections/) with _config.yml and make a dir and yada yada
3)add js setups and other required stuffs
4)add plan!


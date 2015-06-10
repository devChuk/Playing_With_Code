# A tester for [redacted]
require 'page-object'
require 'selenium-webdriver'
require 'rubygems'

class Login
	include PageObject
end

@browser = Selenium::WebDriver.for :phantomjs
@browser.manage.timeouts.implicit_wait = 10
# @browser.manage.window.resize_to(1000, 800) 1124, 850
@browser.manage.window.resize_to(1124, 850)

@browser.get "http://qa.betterpath.com"
hurr = Login.new(@browser)


@browser.find_element(:name => 'email').text

@browser.save_screenshot("./blah.png")

@browser.quit
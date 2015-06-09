# A tester for [redacted]

require 'page-object'
require 'selenium-webdriver'

@browser = Selenium::WebDriver.for $webdriver
@browser.manage.timeouts.implicit_wait = 10
# @browser.manage.window.resize_to(1000, 800) 1124, 850
@browser.manage.window.resize_to(1124, 850)
@super_admin = Admin.new(@browser)
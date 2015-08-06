var request = require('request');

var accesstoken = 'sk_test_JOvryBKzdIpItgkWg1mMY5tD'; //just a test token dw

var data = {
	'amount': 400,
    'currency': 'usd',
    'description': "Charge for test",
    'source': {
        'cvc': 123,
        'number': 4242424242424242,
        'object': "card",
        'exp_month': 12,
        'exp_year': 2016
    }
};

var base_url = 'https://api.stripe.com/v1/charges';

request.post(
    base_url,
    {
        form: data,
        auth: {
        'user': accesstoken
  }
    },
    function (error, response, body) {
            console.log(body);
    }
);
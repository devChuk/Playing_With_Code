# https://stripe.com/us/features
# https://stripe.com/docs/api#intro
import requests
# import syncano
import json

# from syncano.models.base import Object

# extract data from the ARGS
# if none are passed, it will raise an error
# you can pass those ARGS e.g. in a webhook by calling:
# https://api.syncano.io/v1/instances/<instance>/webhooks/p/<public_link>/?amount=0.01&currency=usd&description=helloworld...
# or in a direct CodeBox call:
# CodeBox.please.run(instance_name='YOUR_INSTANCE_NAME',
# id=the_CodeBox_id, payload={'amount': '0.01', 'currency': 'usd',
# 'description': 'helloworld'...})

accesstoken = 'sk_test_JOvryBKzdIpItgkWg1mMY5tD' #just a test token dw
# connection = syncano.connect(api_key='SYNCANO_API_KEY')

# data = {'amount': ARGS.get("amount", None),
#         'currency': ARGS.get("currency", None),
#         'description': ARGS.get("description", None),
#         'obj': "card",
#         'number': ARGS.get("number", None),
#         'exp_month': ARGS.get("exp_month", None),
#         'exp_year': ARGS.get("exp_year", None),
#         'cvc': ARGS.get("cvc", None)
#         }
data = {
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
}

missing = []
for key in data:
    if data[key] is None:
        missing.append(key)
if len(missing) > 0:
    parameters = ""
    for param in missing:
        parameters += ", " + param
    raise ValueError("Parameters not found: " + parameters[2:])

# base url of Stripe payment API
base_url = "https://api.stripe.com/v1/charges"

# send POST request to pay amount
r = requests.post(base_url, auth=(accesstoken, ''), data=json.dumps(data))

print(r.status_code, r.reason)
print(r.text)

# balance = r.json()
# print(balance['data']['balance'])

# Object.please.create(balance=float(balance['data']['balance']),
#                      amount=float(amount),
#                      note=note,
#                      phone=phone,
#                      instance_name="INSTANCE_NAME",
#                      class_name="venmo_payment")

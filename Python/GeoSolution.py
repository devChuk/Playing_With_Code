import requests, syncano, json
from syncano.models.base import Object

accesstoken = 'INSERT_GOOGLEMAPS_API_TOKEN_HERE'
connection = syncano.connect(api_key='INSERT_SYNCANO_API_KEY_HERE')

lat = ARGS.get("lat", None)
lon = ARGS.get("lon", None)
address = ARGS.get("address", None)
# either the lat & lon or the address can be used

if address is None:
    if lat is None and lon is None:
        raise ValueError("ERROR: no parameters found")
    if lat is None or lon is None:
        raise ValueError("ERROR: coordinate is invalid")

if address is not None:  # address takes precedence
    base_url = "https://maps.googleapis.com/maps/api/geocode/json?address="
    accesstoken = '&key=' + accesstoken
    address = address.strip(" ").replace(" ", "+")

    url = base_url + address + accesstoken
    r = requests.get(url)

    print(r.status_code, r.reason)
    response = r.json()['results'][0]['geometry']['location']
    lat = response['lat']
    lon = response['lng']

Object.please.create(lat=float(lat),
                     lon=float(lon),
                     instance_name="INSTANCE_NAME",
                     class_name="location")

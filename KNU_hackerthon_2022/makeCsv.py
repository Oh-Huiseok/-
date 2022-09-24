#!/usr/bin/python
# pip install lxml
# pip install geopy
# pip install xmltodict
# pip install googlemaps
# pip install Pillow

from logging import error
import requests
import pandas as pd
from bs4 import BeautifulSoup
from urllib.parse import quote
from urllib.request import Request, urlopen
import ssl
import json
import googlemaps
import xmltodict

googlemaps_key = "AIzaSyCWpyN2lFq3QU71QEDUVzNRiemE_LI58Co"
maxwidth = 400
maxheight = 400

print("Process initiating")
gmaps = googlemaps.Client(key=googlemaps_key)

decodingKey = "obvb6zpR5qgYzRB5yjXWoHY+/zhFKzZ7rVuItJKMVKU+5BgtGwgwuTbqVAUZLyWEVxqAivJ/DdBNiGAvR+3lPQ=="
url = 'http://apis.data.go.kr/6270000/getTourKorAttract/getTourKorAttractList'
params = {'serviceKey': decodingKey, 'numOfRows': 255}
response = requests.get(url, params=params)
soup = BeautifulSoup(response.content, 'lxml-xml')
items = soup.find_all("item")


'''
data_dict = open('data.xml', 'r', encoding='utf-8-sig')
soup = BeautifulSoup(data_dict, 'lxml')
fullcnt = soup.find("totalCount")
'''

row = []


def parse(item, i):
    try:
        ID = i
        NAME = item.find("attractname").get_text()
        CONTENT = item.find("attractcontents").get_text()
        if len(CONTENT) > 500:
            CONTENT = CONTENT[:500] + '...중략'
        ADDRESS = item.find("address").get_text()

        PAGE_URL = item.find("homepage").get_text()
        TEL = item.find('tel').get_text()
        HOUR = item.find('attr01').get_text()

        
        geo_location = gmaps.geocode(ADDRESS)[0].get('geometry')
        test = geo_location['location']
        LAT = geo_location['location']['lat']
        LON = geo_location['location']['lng']
        COORDINATE = [LAT, LON]

        place_result = gmaps.geocode(NAME)[0]
        #print(place_result)
        my_place_id = place_result['place_id']
        #print(my_place_id)
        place_details = gmaps.place(place_id=my_place_id, fields=['photo'])
        photo_id = place_details['result']['photos'][0]['photo_reference']
        raw_image_data = gmaps.places_photo(photo_reference=photo_id, max_height=maxheight,
                                            max_width=maxwidth)
        #print(raw_image_data)
        filename = "images/%d.jpg" % i
        
        print(filename + " create")
        f = open(filename, 'wb')

        for chunk in raw_image_data:
            if chunk:
                f.write(chunk)

        f.close()
        
        return {
            "id": ID,
            "name": NAME,
            "contents": CONTENT,
            "homepage": PAGE_URL,
            "address": ADDRESS,
            "tel": TEL,
            "hour": HOUR,
            "coordinate" : COORDINATE
        }
    except:
        return {
            "id": None,
            "name": None,
            "contents": None,
            "homepage": None,
            "address": None,
            "tel": None,
            "hour": None,
            "coordinate" : None
        }


for (i, item) in enumerate(items):
    row.append(parse(item, i))

df = pd.DataFrame(row)

df.to_csv("테스트 데이터셋.csv", index=False, mode='w', encoding="utf-8-sig")
print(".csv file create")
print('Program shut down')
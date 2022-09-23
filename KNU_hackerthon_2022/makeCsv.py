#!/usr/bin/python
# pip install lxml
# pip install geopy
# pip install xmltodict

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
gmaps = googlemaps.Client(key=googlemaps_key)


decodingKey = "obvb6zpR5qgYzRB5yjXWoHY+/zhFKzZ7rVuItJKMVKU+5BgtGwgwuTbqVAUZLyWEVxqAivJ/DdBNiGAvR+3lPQ=="
url = 'http://apis.data.go.kr/6270000/getTourKorAttract/getTourKorAttractList'
params = {'serviceKey': decodingKey, 'numOfRows':225}
response = requests.get(url, params=params)
soup = BeautifulSoup(response.content, 'lxml-xml')
items = soup.find_all("item")
'''
data_dict = open('data.xml', 'r', encoding='utf-8-sig')
soup = BeautifulSoup(data_dict, 'lxml')
fullcnt = soup.find("totalCount")'''

row = []

def parse(item, i):
    try:
        ID = i
        NAME = item.find("attractname").get_text()
        CONTENT = item.find("attractcontents").get_text()
        if len(CONTENT) > 500:
            CONTENT = CONTENT[:500] + '...중략'
        ADDRESS = item.find("address").get_text()

        geo_location = gmaps.geocode(ADDRESS)[0].get('geometry')
        test = geo_location['location']
        LAT = geo_location['location']['lat']
        LON = geo_location['location']['lng']

        PAGE_URL = item.find("homepage").get_text()
        TEL = item.find('tel').get_text()
        HOUR = item.find('attr01').get_text()

        return {
            "id": ID,
            "name": NAME,
            "content": CONTENT,
            "address": ADDRESS,
            "homepage": PAGE_URL,
            "tel": TEL,
            "hour": HOUR,
            "lat": LAT,
            "lon": LON
        }
    except:
        print("error")
        return {
            "id": None,
            "name": None,
            "content": None,
            "address": None,
            "homepage": None,
            "tel": None,
            "hour": None,
            "lat": None,
            "lon": None,
        }

for (i,item) in enumerate(items):
    row.append(parse(item, i))

df = pd.DataFrame(row)

df.to_csv("테스트 데이터셋.csv", index=False, mode='w', encoding="utf-8-sig")


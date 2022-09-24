# pip install aspose-words

import telegram
import psycopg2
import json
#import googlemaps
import numpy as np
import math
import copy
from telegram import Update, Bot
from telegram.ext import Updater, CallbackContext, CommandHandler
from telegram.ext import MessageHandler, Filters
import time
from decimal import *
import aspose.words as aw
token = '5655224412:AAGxbrlGN4a4DcmQ45sKJ-wwWUoxTpswj3k'
can_go_landmark = []
new_can_go = []
bot = telegram.Bot(token)
updates = bot.getUpdates()
'''
for u in updates:
    print(u.message)'''

id = '1384253707'

doc = aw.Document()
builder = aw.DocumentBuilder(doc)

builder.insert_image('images/0/0-0.jpg')

doc.save("Output.html")

# bot.sendMessage(chat_id=id, text="테스트 중입니다.")
images = []
images.append('0-1.jpg')
images.append('Output.001.jpeg')

media_1 = telegram.InputMediaDocument(media=open('0-1.jpg', 'rb'))
media_2 = telegram.InputMediaDocument(media= open('Output.001.jpeg', 'rb'))
bot.sendPhoto(chat_id=id,  photo=open('images/0/0-0.jpg', 'rb'), caption="대구광역시 중구 동성로 2길 80")
bot.sendMediaGroup(chat_id=id, media=images)

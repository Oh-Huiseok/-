#!/usr/bin/python

import argparse
import subprocess
from flask import Flask, jsonify, request
from flask import render_template
import re
import requests
from bs4 import BeautifulSoup
import sys
from elasticsearch import Elasticsearch

app = Flask(__name__)


global urlW

@app.route('/info', methods=['POST'])
def home_html():
    if request.method == 'POST':
        urlW = request.form[u'urlW']
        res = requests.get(urlW)
        
        html = BeautifulSoup(res.text, 'html.parser')
        
        tb = html.select("div.mw-parser-output>p")
        
        elements=[]
        
        for string in range(0,len(tb)-1):
            cleaned_text = re.sub('[\{\}\[\]\/?.,;:|\)*~`!^\-_+<>@\#$%&\\\=\(\'\"]','', tb[string].get_text())
            elements.append(cleaned_text)
        
        words = {}
        
        for sent in elements:
            s = sent.split()
            for word in s:
                if word not in words.keys():
                    words[word]=0
                words[word] += 1
        
        w = []
        f = []

        for x, y in words.items():
            w.append(x)
            f.append(y)
        
        e1={
                "url":urlW,
                "words":w,
                "frequencies":f
        }

        es_host="http://localhost:9200"

        es = Elasticsearch(es_host)
       
        res = es.index(index="web", id=1, document=e1)
        
        return render_template("home.html", parsed_page=words)

@app.route('/')
def HW09_html():
    return render_template('HW09.html')

if __name__=='__main__':
    try:
        parser = argparse.ArgumentParser(description="")
        parser.add_argument('--listen-port', type=str, required=True, help='REST service listen port')
        args = parser.parse_args()
        listen_port = args.listen_port
    except Exception as e:
        print('Error: %s' % str(e))

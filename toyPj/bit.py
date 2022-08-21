import pyupbit
import pandas as pd
import time
import datetime

keys = open('/mnt/c/Users/오희석/api키.txt','r')
keys = keys.read().splitlines()

coins = {'비트코인' : 'KRW-BTC', '이더리움' : 'KRW-ETH', '이더리움 클래식' : 'KRW-ETC'}

access = keys[0][7:]
secret = keys[1][7:]

def get_target_price(ticker, k):
    """변동성 돌파 전략으로 매수 목표가 조회"""
    df = pyupbit.get_ohlcv(ticker, interval="day", count=2)
    target_price = df.iloc[0]['close'] + (df.iloc[0]['high'] - df.iloc[0]['low']) * k
    return target_price

def get_start_time(ticker):
    """시작 시간 조회"""
    df = pyupbit.get_ohlcv(ticker, interval="day", count=1)
    start_time = df.index[0]
    return start_time

def get_ma15(ticker):
    """15일 이동 평균선 조회"""
    df = pyupbit.get_ohlcv(ticker, interval="day", count=15)
    ma15 = df['close'].rolling(15).mean().iloc[-1]
    return ma15


def get_ma7(ticker):
    """7일 이동 평균선 조회"""
    df = pyupbit.get_ohlcv(ticker, interval="day", count=7)
    ma7 = df['close'].rolling(7).mean().iloc[-1]
    return ma7

def get_balance(ticker):
    """잔고 조회"""
    balances = upbit.get_balances()
    for b in balances:
        if b['currency'] == ticker:
            if b['balance'] is not None:
                return float(b['balance'])
            else:
                return 0
    return 0

def get_current_price(ticker): # full 코드 필요
    """현재가 조회"""
    return pyupbit.get_orderbook(ticker=ticker)["orderbook_units"][0]["ask_price"]


def get_profit(ticker):
    balanceticker = ticker[4:]
    print(balanceticker)
    current_price = get_current_price(ticker)
    current_balance= get_balance(balanceticker)

# 로그인
upbit = pyupbit.Upbit(access, secret)
print("autotrade start")
get_profit("KRW-BTC")
print(get_current_price("KRW-BTC"))
print(get_balance("BTC"))
print(get_current_price("KRW-BTC") * get_balance("BTC"))
#매수평균가 x 보유수량 = 평가금액,
#매수평균가는 upbit.balances에서 빼오고
#매수금액 = 매수평균가 * 보유수량
#평가금액 - 매수금액 (평가손익) / 매수금액 = 수익률

# 자동매매 시작
while True:
    try:
        now = datetime.datetime.now()
        start_time = get_start_time("KRW-BTC")
        end_time = start_time + datetime.timedelta(hours=6)

        for value in coins.values():
            if start_time < now < end_time - datetime.timedelta(seconds=10):
                target_price = get_target_price(value, 0.5)
                ma15 = get_ma15(value)
                ma7 = get_ma7(value)
                current_price = get_current_price(value)
                print(target_price, current_price)
                if target_price < current_price and ma15 < current_price and ma15 < ma7:
                    krw = get_balance("KRW")
                    if krw > 5000:
                        print("buy ", value)
                        upbit.buy_market_order(value, krw*0.3)
            else:
                btc = get_balance("BTC")
                eth = get_balance("ETH")
                etc = get_balance("ETC")
                if btc > 5000/get_current_price("KRW-BTC"):
                    print("sell ", "KRW-BTC")
                    upbit.sell_market_order("KRW-BTC", btc*0.9995)
                if eth > 1000/get_current_price("KRW-ETH"):
                    print("sell ", "KRW-ETH")
                    upbit.sell_market_order("KRW-ETH", eth*0.9995)
                if etc > 1000/get_current_price("KRW-ETC"):
                    print("sell ", "KRW-ETH")
                    upbit.sell_market_order("KRW-ETC", etc*0.9995)
        time.sleep(3)
    except Exception as e:
        print(e)
        time.sleep(1)
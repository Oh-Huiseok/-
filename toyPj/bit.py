import pyupbit
import pandas as pd
import time
import datetime
import sys

keys = open('/mnt/c/Users/오희석/api키.txt','r')
keys = keys.read().splitlines()

coins = {'비트코인' : 'KRW-BTC', '이더리움' : 'KRW-ETH', '이더리움 클래식' : 'KRW-ETC'}

profit_delta = {0, 0, 0} #미구현

access = keys[0][7:]
secret = keys[1][7:]

def get_target_price(ticker, k):
    """변동성 돌파 전략으로 매수 목표가 조회"""
    df = pyupbit.get_ohlcv(ticker, interval="minute30", count=8)
    high = 0 
    for x in df.iloc[:,1]:
        if high < x:
            high = x
    low = sys.maxsize
    for x in df.iloc[:,2]:
        if low > x:
            low = x
    close = df.iloc[7]['close']
    target_price = close + (high - close) * k
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

def get_current_price(ticker): # 코인 full 코드 필요
    """현재가 조회"""
    return pyupbit.get_orderbook(ticker=ticker)["orderbook_units"][0]["ask_price"]

def get_avg_buy_price(ticker):
    balances = upbit.get_balances()
    for b in balances:
        if b['currency'] == ticker:
            if b['avg_buy_price'] is not None:
                return float(b['avg_buy_price'])
            else:
                return 0
    return 0


def get_profit(ticker): # 코인 full 코드
    balanceticker = ticker[4:]

    current_price = get_current_price(ticker) # 현재 ticker 가격
    current_balance= get_balance(balanceticker) # 보유중인 ticker 개수
    avg_buy_price = get_avg_buy_price(balanceticker) # 매수평균가
    market_price =  float(current_price * current_balance) # 평가금액
    buy_price = float(avg_buy_price * current_balance) # 매수금액
    profit = float((market_price - buy_price)/buy_price * 100) #수익률

    return profit

# 로그인
upbit = pyupbit.Upbit(access, secret)
print("autotrade start")

#매수평균가 x 보유수량 = 평가금액,
#매수평균가는 upbit.balances에서 빼오고
#매수금액 = 매수평균가 * 보유수량
#평가금액 - 매수금액 (평가손익) / 매수금액 = 수익률

# 자동매매 시작

while True:
    try:
        now = datetime.datetime.now()
        start_time = get_start_time("KRW-BTC")
        end_time = start_time + datetime.timedelta(days=1)
        idx = 0

        for value in coins.values():
            if start_time < now < end_time - datetime.timedelta(seconds=10):
                coin_balance = get_balance(value[4:])
                if value == "KRW-BTC":
                    if coin_balance > 5000/get_current_price(value) and get_profit(value) > 3: # 최소 매도 금액 넘고 수익률 3%이상일때 전량 매도 
                        print("sell ", value)
                        upbit.sell_market_order(value, coin_balance * 0.9995)
                if value == "KRW-ETH":
                    if coin_balance > 5000/get_current_price(value) and get_profit(value) > 3:
                        print("sell ", value)
                        upbit.sell_market_order(value, coin_balance * 0.9995)
                else :
                    if coin_balance > 1000/get_current_price(value) and get_profit(value > 3):
                        print("sell ", value)
                        upbit.sell_market_order(value, coin_balance * 0.9995)
                
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
                if get_profit(value) < -5: #수익률 -5%넘어가면 전량매도
                    upbit.sell_market_order(value, coin_balance * 0.9995)
        time.sleep(3)
    except Exception as e:
        print(e)
        time.sleep(1)
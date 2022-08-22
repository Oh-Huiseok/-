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

def get_avg_buy_price(ticker):
    balances = upbit.get_balances()
    for b in balances:
        if b['currency'] == ticker:
            if b['avg_buy_price'] is not None:
                return float(b['avg_buy_price'])
            else:
                return 0
    return 0


def get_profit(ticker):
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

#평가금액 = 현재가격 x 보유수량
#매수평균가는 upbit.balances에서 빼오고
#매수금액 = 매수평균가 * 보유수량
#평가금액 - 매수금액 (평가손익) / 매수금액 = 수익률

# 자동매매 시작
import pypupbit

accessKey = pI6EEKXvZWeCzqxx6b5zof1wGh2gVOCnC4ljImQ7
secretKey = NjhWmWOy96v33tZxcBNEiOwJYoynxknX9FRj66Fy
upbit = pypupbit.Upbit(access, secret)

print(upbit.get_balance("KRW-BTC"))
print(upbit.get_Balance("KRW"))
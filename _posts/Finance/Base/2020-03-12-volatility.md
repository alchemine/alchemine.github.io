---
title: Volatility Clustering & Leverage Effect
tags: Finance_Base
---

# Remarks
본 포스팅은 [파이썬을 활용한 금융분석(한빛미디어, 2016) 978-89-6848-277-9](https://books.google.co.kr/books/about/%ED%8C%8C%EC%9D%B4%EC%8D%AC%EC%9D%84_%ED%99%9C%EC%9A%A9%ED%95%9C_%EA%B8%88%EC%9C%B5_%EB%B6%84%EC%84%9D.html?id=crpUDwAAQBAJ&printsec=frontcover&source=kp_read_button&redir_esc=y#v=onepage&q&f=false)를 기반으로 작성되었습니다.

<!--more-->

---

### Volatility Clustering(변동성 군집현상)
변동성은 시간에 따라 일정하게 유지되지 않고, 변동성이 높게 유지되는 구간과 변동성이 낮게 유지되는 구간이 존재하여 cluster를 이루는 현상을 말한다. 확률적으로 검증된 현상이라고 한다.

### Leverage Effect(레버리지 효과)
Leverage effect란 차입금 등의 타인의 자본을 지렛대처럼 이용하여 자신의 수익률을 높이는 것으로 지렛대 효과라고도 한다. ([https://1boon.kakao.com/zigbang/5ddcc4b6bcd34944b2b9a3d6](https://1boon.kakao.com/zigbang/5ddcc4b6bcd34944b2b9a3d6) 참고)


다음의 예제는 독일 DAX 지수의 종가를 분석하여 volatility(로그 수익률의 표준편차)가 cluster를 이루는 것을 확인하고 시장과 volatility가 음의 상관관계를 가지는 것을 통해 레버리지 효과 가설을 확인한다(?).


```python
import pandas_datareader.data as web

DAX = web.DataReader(name='^GDAXI', data_source='yahoo', start='2000-1-1')
DAX.info()
```

    <class 'pandas.core.frame.DataFrame'>
    DatetimeIndex: 5124 entries, 2000-01-03 to 2020-03-12
    Data columns (total 6 columns):
    High         5124 non-null float64
    Low          5124 non-null float64
    Open         5124 non-null float64
    Close        5124 non-null float64
    Volume       5124 non-null float64
    Adj Close    5124 non-null float64
    dtypes: float64(6)
    memory usage: 280.2 KB



```python
DAX['log(Return)'] = np.log(DAX['Close'] / DAX['Close'].shift(1))  # 0 이상이면 상승, 이하면 하락

fig, ax1 = plt.subplots(figsize=(20, 5))
DAX['log(Return)'].plot(color='b', alpha=0.5);
plt.axhline(0, color='r', ls='--');
plt.ylabel('log(Return)')
plt.legend();

ax2 = ax1.twinx()
DAX['Close'].plot(color='g');
plt.ylabel('Close')
plt.grid();  plt.legend();
```


![png](/images/Prog_Finance/2020-03-12-volatility/output_4_0.png)



```python
DAX['Mov_Vol'] = -DAX['Ret'].rolling(window=252).std() * np.sqrt(252)

fig, ax1 = plt.subplots(figsize=(20, 5))
DAX['Mov_Vol'].plot(color='b', alpha=0.5);
plt.ylabel('-Stddev of log(Return)')
plt.legend();

ax2 = ax1.twinx()
DAX['Close'].plot(color='g');
plt.ylabel('Close')
plt.grid();  plt.legend();
```


![png](/images/Prog_Finance/2020-03-12-volatility/output_5_0.png)

---
title: Pandas Cheetsheet
tags: Python
---

<!--more-->

`pandas` 에서 주로 사용하는데도 매번 헷갈리는 친구들을 기록해보고자 한다.

# 1. 값 추가/수정
```
df = pd.DataFrame(columns=['col1', 'col2'])

# Others
row_list = [val_11, val_21]
row_dict = {'col1': [val_11, val_12], 'col2': [val_21, val_22]}
df_other = pd.DataFrame({'col1': [val_11, val_12], 'col2': [val_21, val_22]}, index=[0, 1])
val      = 10

# Set index
df.loc[0] = row_list
df.loc[(df['col1'] == val_11) & (df['col2'] == val_21), 'col3'] = val

# Ignore index
df = df.append(row_list, ignore_index=True)
df = df.append(row_dict, ignore_index=True)
df = df.append(df_other, ignore_index=False)  # CAUTION: duplicate index
```

---
title: MySQL Query Notes
tags: Database
---

- Example
```
SELECT
    A.AUTHOR_ID,
    B.AUTHOR_NAME,
    A.CATEGORY,
    SUM(A.PRICE * C.SALES) AS TOTAL_SALES
FROM
    BOOK A
LEFT JOIN AUTHOR B ON
    A.AUTHOR_ID = B.AUTHOR_ID
LEFT JOIN BOOK_SALES C ON
    A.BOOK_ID = C.BOOK_ID AND
    SALES_DATE LIKE '2022-01-%'
GROUP BY
    A.AUTHOR_ID,
    A.CATEGORY
ORDER BY
    A.AUTHOR_ID,
    A.CATEGORY DESC
```


# 1. Data Type
## 1.1 String
### 1.1.1 Substring
#### 1.1.1.1 Contains
```
WHERE address LIKE '%강원도%'
```

#### 1.1.1.2 Starts with
```
WHERE address LIKE '강원도%'
WHERE address RLIKE '^강원도'
```

#### 1.1.1.3 Ends with
```
WHERE address LIKE '%강원도'
WHERE address RLIKE '강원도$'
```

## 1.2 Number
### 1.2.1 Between
```
WHERE age BETWEEN 20 and 29  # 20 <= age <= 29
```

## 1.3 Datetime
### 1.3.1 YEAR, MONTH
```
WHERE YEAR(datetime) = 2022 AND MONTH(datetime) = 1
```


# 2. Aggregation Function
1. COUNT(col)
2. DISTINCT
3. SUM(col)
. 
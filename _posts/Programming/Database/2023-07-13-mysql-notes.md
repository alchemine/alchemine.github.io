---
title: MySQL Query Notes
tags: Database
---

<!--more-->

- Example
```sql
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
### 1.1.1 Regular Expression
#### 1.1.1.1 `LIKE`
[MySQL Wildcards](https://www.w3schools.com/mysql/mysql_wildcards.asp) 참고

```sql
# _ : single character
WHERE address LIKE '_철수'
WHERE address LIKE '__수'
WHERE address LIKE '___'
```

```sql
# % : zero or more character
WHERE address LIKE '%철수'
```

#### 1.1.1.2 `RLIKE`
[Regular Expression](https://alchemine.github.io/2021/10/27/re.html) 참고

```sql
WHERE address RLIKE '강원도'   # contains
WHERE address RLIKE '^강원도'  # startswith
WHERE address RLIKE '강원도$'  # endswith
```

### 1.1.2 Substring
#### 1.1.2.1 `SUBSTR`
Substring 추출

```sql
SELECT SUBSTR(code, 1, 3)  # SUBSTR(col, start, length)
SELECT SUBSTR(code, -2)    # SUBSTR(col, length from back)
```

#### 1.1.2.2 `LEFT`, `RIGHT`
```sql
SELECT LEFT(code, 2)       # SUBSTR(col, 1, 2)
SELECT RIGHT(code, 2)      # SUBSTR(col, -2)
```

## 1.2 Number
### 1.2.1 `BETWEEN`
```sql
# Same
WHERE 20 <= age AND age <= 29
WHERE age BETWEEN 20 and 29
```

## 1.3 Datetime
### 1.3.1 `YEAR`, `MONTH`
```sql
WHERE YEAR(datetime) = 2022 AND MONTH(datetime) = 1
```

### 1.3.2 `DATE_FORMAT`
```sql
SELECT DATE_FORMAT(datetime, '%Y-%m-%d %H:%i:%s')
```


# 2. Aggregation Function
1. `COUNT`(col), `COUNT`(*)
2. `DISTINCT`
3. `SUM`(col)


# 3. Conditional Statement
## 3.1 `WHERE` Condition
### 3.1.1 `OR`
```sql
# Same
WHERE animal_type = 'Dog' OR animal_type = 'Cat'
WHERE animal_type IN ('Dog', 'Cat')
```

### 3.1.2 `=`
```sql
WHERE
    A.member_id = (
        SELECT
            member_id
        FROM
            rest_review
        LIMIT 1
    )
```

## 3.2 `SELECT` Condition
### 3.2.1 `CASE`
```sql
SELECT
    CASE
        WHEN sex_upon_intake RLIKE '^[Neutered|Spayed]'
            THEN 'O'
        ELSE 'X
    END '중성화'
```

### 3.2.2 `IF`
```sql
SELECT
    IF(sex_upon_intake RLIKE '^[Neutered|Spayed]', 'O', 'X') AS '중성화'
```


# 4. Alias
## 4.1 Group
```sql
SELECT
    HOUR(datetime) AS hour,
    COUNT(animal_id) AS count
FROM
    animal_outs
GROUP BY
    hour
HAVING
    hour between 9 and 19
ORDER BY
    hour
```
`SELECT`에서 정의한 변수를 `GROUP BY`, `HAVING` 등에서 사용 가능 \
**변수명**을 **함수명**으로 지정해도 함수와 변수를 자동으로 인식하기 때문에 사용 가능


# 5. Merge Table
## 5.1 Join
[Join](https://alchemine.github.io/2022/08/04/join.html) 참고

## 5.2 Union
```sql
SELECT
    0 AS NUM 

UNION ALL

SELECT
    NUM+1
FROM
    HOURS
WHERE
    NUM < 23
```


# 6. Common Table Expression(CTE)
## 6.1 Non-Recursive CTE
```sql
WITH tabel1(<cols>) AS (
  <query>
)
WITH table2(<cols>) AS (
  <query which can reference table1>
)
SELECT
    <cols>
FROM
    <tmp_table1>,
    <tmp_table2>
```

## 6.2 Recursive CTE
```sql
WITH RECURSIVE HOURS AS (
    SELECT
        0 AS NUM 
    
    UNION ALL
    
    SELECT
        NUM+1
    FROM
        HOURS
    WHERE
        NUM < 2
)

SELECT
    *
FROM
    HOURS
```

```
NUM
---
0
1
2
```


# 7. NULL
## 7.1 `IFNULL`: Impute NULL
```sql
SELECT IFNULL(count, 0)
```

## 7.2 `IS NULL`: Check NULL
```sql
WHERE name IS NULL  
WHERE name IS NOT NULL  
```

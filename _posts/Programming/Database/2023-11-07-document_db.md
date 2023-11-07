---
title: Document Database
tags: Database
---

# Remarks
본 글은 AWS DocumentDB(MongoDB)를 기준으로 작성되었습니다.

<!--more-->
---

# Use Cases
1. Document DB(이하 DocDB)는 **유연한 스키마**가 필요한 워크로드에 유용
    - **유연한 스키마**: 속성(attributes)과 데이터 값(values)이 다른 문서를 저장할 수 있음
    - 문서의 데이터 구조를 동적으로 변경할 수 있기 때문에, 신속한 개발 및 동적으로 변화하는 환경에 적합
2. 희소 데이터를 처리하는 데 적합
3. 문서 간의 중복성이 존재하나, 스토리지가 저렴하고 join 없이 key-value query를 통해 빠르게 검색할 수 있는 장점

## User Profiles
1. 서로 다른 사용자들은 **다양한 유형의 정보**를 프로필로 사용할 수 있음
2. 사용자가 프로필 정보를 추가하거나 제거한 경우, **해당 문서의 추가된 버전과 제거된 버전으로 쉽게 바꿀 수 있음**
    - Individuality, fluidity에 강하다!

## Real-Time Big Data
1. 운영 데이터에서 정보를 추출하기 위한 기존의 방식: 운영 DB 와 분석 DB 를 분리하고 서로 다른 환경에서 유지 관리 (비효율적) \
DocDB는 모든 소스에서 운영 데이터를 저장/관리할 수 있고, 분석을 위해 데이터를 BI 엔진에 전달할 수 있음 (효율적)

## Content Management
1. 다양한 소스(images, comments, videos 등)에서 수집된 콘텐츠를 저장하여 고객에게 제공할 수 있음


# Understanding Documents
1. DocDB는 반구조화된 데이터를 문서(document)로 저장하는데 사용
2. Document: 중첩된 key-value pair를 사용하여 구조 또는 스키마를 제공

## SQL vs Nonrelational Terminology

| SQL          | MongoDB         |
|--------------|-----------------|
| Table   | Collection |
| Row | Document      |
| Column   | Field      |
| Primary Key | ObjectId          |
| Index | Index      |
| View  | View       |
| Nested Table or Object | Embedded Document |
| Array | Array       |


# Documents Structure
## Simple Documents
```json
{
   "SSN": "123-45-6789",
   "LName": "Rivera",
   "FName": "Martha",
   "DOB": "1992-11-16",
   "Street": "125 Main St.",
   "City": "Anytown",
   "State-Province": "WA",
   "PostalCode": "98117",
   "Country": "USA"
}
```

## Embedded Documents
```json
{
   "SSN": "123-45-6789",
   "LName": "Rivera",
   "FName": "Martha",
   "DOB": "1992-11-16",
   "Address": 
   {
       "Street": "125 Main St.",
       "City": "Anytown",
       "State-Province": "WA",
       "PostalCode": "98117",
       "Country": "USA" 
   }
}
```


# Working with Documents
## Adding Documents
### Adding a Single Document
```json
db.example.insertOne(
    {
        "Item": "Ruler",
        "Colors": ["Red","Green","Blue","Clear","Yellow"],
        "Inventory": {
            "OnHand": 47,
            "MinOnHand": 40
        },
        "UnitPrice": 0.89
    }
)
```

### Adding Multiple Documents
```json
db.example.insertMany(
    [
        {
            "Item": "Pen",
            "Colors": ["Red","Green","Blue","Black"],
            "Inventory": {
                "OnHand": 244,
                "MinOnHand": 72 
            }
        },
        {
            "Item": "Poster Paint",
            "Colors": ["Red","Green","Blue","Black","White"],
            "Inventory": {
                "OnHand": 47,
                "MinOnHand": 50 
            }
        },
        {
            "Item": "Spray Paint",
            "Colors": ["Black","Red","Green","Blue"],
            "Inventory": {
                "OnHand": 47,
                "MinOnHand": 50,
                "OrderQnty": 36
            }
        }    
    ]
)
```

### Querying Documents
`find().pretty()`를 사용하면 정렬된 형태로 출력값을 볼 수 있음.

#### Retrieving All Documents in a Collection
```json
db.example.find( {} ).pretty()
```
→ Ruler, Pen, Poster Paint, Spray Paint

#### Retrieving Documents That Match a Field Value
```json
db.example.find( { "Item": "Pen" } ).pretty()
```
→ Pen

#### Retrieving Documents That Match an Embedded Document
```json
db.example.find({
    "Inventory": {
        "OnHand": 47,
        "MinOnHand": 50
    }
}).pretty()
```
→ Poster Paint

#### Retrieving Documents That Match a Field Value in an Embedded Document
```json
db.example.find({
    "Inventory.OnHand": 47,
    "Inventory.MinOnHand": 50
}).pretty()
```
→ Poster Paint, Spray Paint

#### Retrieving Documents That Match an Array
```json
db.example.find( { "Colors": ["Red", "Green", "Blue", "Black"] } ).pretty()
```
→ Pen \
**배열의 순서가 중함!**

#### Retrieving Documents That Match a value in an Array
```json
db.example.find( { "Colors": "Red" })
```
→ Ruler, Pen, Poster Paint, Spray Paint

#### Retrieving Documents Using Operators
```json
db.example.find({ "Inventory.OnHand": { $lt: 50 } }).pretty()
```
→ `Inventory.OnHand` 값이 50 미만인 모든 문서를 반환
- [쿼리 및 프로젝션 연산자](https://docs.aws.amazon.com/ko_kr/documentdb/latest/developerguide/mongo-apis.html#mongo-apis-query) 참고


## Updating Documents
`update()`를 이용하여 기존 문서를 업데이트할 수 있음.
- Parameters
    - 1st document parameter: **document identifier**
    - 2nd document parameter: **document to be updated**

- Previous data
    ```json
    {
        "Item": "Ruler",
        "Colors": ["Red","Green","Blue","Clear","Yellow"],
        "Inventory": {
            "OnHand": 47,
            "MinOnHand": 40
        },
        "UnitPrice": 0.89
    },
    {
        "Item": "Pen",
        "Colors": ["Red","Green","Blue","Black"],
        "Inventory": {
            "OnHand": 244,
            "MinOnHand": 72 
        }
    },
    {
        "Item": "Poster Paint",
        "Colors": ["Red","Green","Blue","Black","White"],
        "Inventory": {
            "OnHand": 47,
            "MinOnHand": 50 
        }
    },
    {
        "Item": "Spray Paint",
        "Colors": ["Black","Red","Green","Blue"],
        "Inventory": {
            "OnHand": 47,
            "MinOnHand": 50,
            "OrderQnty": 36
        }
    }
    ```

- `$set`: field 변경 및 추가
    ```json
    db.example.update(
        { "Item" : "Pen" },
        { $set: { "Item": "Gel Pen" } }
    )
    ```

    ```json
    db.example.update(
        { "Item" : "Poster Paint" },
        { $set: { "Colors": ["Red","Green","Blue","Orange","Black"] } }
    )
    ```

    ```json
    db.example.update(
        { "Item": "Spray Paint" },
        { $set: { "UnitPrice": 3.99 } } 
    )
    ```

    ```json
    db.example.update(
        { "DocName" : "Document 1" },
        { $set: { "Date": { "Month": 4, "Day": 18 } } }
    )
    ```

    ```json
    db.example.update(
        { "DocName" : "Document 1" },
        { $set: { "Date.Year": 1987, 
                "Date.DoW": "Saturday",
                "Words": 2482 } }
    )
    ```
- `$unset`: field 제거
    - `$unset`에 해당하는 doc의 값으로 `1` 을 넣는 것이 관례
        ```json
        db.example.update(
            { "DocName" : "Document 1" },
            { $unset: { Words:1 } }
        )
        ```
        - `$unset` + `multi`: 여러 문서에서 필드 제거
            ```json
            db.example.update(
                {},
                { $unset: { Inventory:1 } },
                { multi: true }
            )
            ```

## Remove Documents
```json
db.example.remove( { "Item": "Gel Pen" } )
```

- 모든 문서 제거
    ```json
    db.example.remove( { } )
    ```

---

# Reference
- [https://docs.aws.amazon.com/ko_kr/documentdb/latest/developerguide/document-database-use-cases.html](https://docs.aws.amazon.com/ko_kr/documentdb/latest/developerguide/document-database-use-cases.html)

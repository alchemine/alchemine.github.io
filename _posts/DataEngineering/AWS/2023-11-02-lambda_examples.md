---
title: Lambda Examples
tags: AWS
---

<!--more-->

# Cointegration with S3
- Lambda 작업환경에서 `/tmp` 만 접근 가능.

## Download From S3 Bucket
```python
import boto3
import uuid
from urllib.parse import unquote_plus
            

s3_client = boto3.client('s3')
            
def lambda_handler(event, context):
  for record in event['Records']:
    bucket = record['s3']['bucket']['name']
    key    = unquote_plus(record['s3']['object']['key'])
    tmpkey = key.replace('/', '')
    
    download_path = '/tmp/{}{}'.format(uuid.uuid4(), tmpkey)
    s3_client.download_file(bucket, key, download_path)
```
- 파일의 크기가 큰 경우(>1MB?), timeout(3초) 에러가 발생


## Uplad To S3 Bucket
```python
import boto3
            

s3_client = boto3.client('s3')
            

def lambda_handler(event, context):
  for record in event['Records']:
    bucket = record['s3']['bucket']['name']
    key    = unquote_plus(record['s3']['object']['key'])
    tmpkey = key.replace('/', '')
    
    upload_path = '/tmp/{}'.format(tmpkey)
    s3_client.upload_file(upload_path, bucket, 'resized-{}'.format(key))
```

---
title: Lambda Examples
tags: AWS
---

<!--more-->

# Cointegration with S3
- Lambda 작업환경에서 `/tmp` 만 접근 가능.([참고](https://alchemine.github.io/2023/11/01/lambda.html#configuration))

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

# Logging
- [AWS Lambda function logging in Python](https://docs.aws.amazon.com/lambda/latest/dg/python-logging.html)
```python
import os
import logging
logger = logging.getLogger()
logger.setLevel(logging.INFO)

def lambda_handler(event, context):
  logger.info('## ENVIRONMENT VARIABLES')
  logger.info(os.environ['AWS_LAMBDA_LOG_GROUP_NAME'])
  logger.info(os.environ['AWS_LAMBDA_LOG_STREAM_NAME'])
  logger.info('## EVENT')
  logger.info(event)
```

```
START RequestId: 1c8df7d3-xmpl-46da-9778-518e6eca8125 Version: $LATEST
[INFO]  2023-08-31T22:12:58.534Z    1c8df7d3-xmpl-46da-9778-518e6eca8125    ## ENVIRONMENT VARIABLES
[INFO]  2023-08-31T22:12:58.534Z    1c8df7d3-xmpl-46da-9778-518e6eca8125    /aws/lambda/my-function
[INFO]  2023-08-31T22:12:58.534Z    1c8df7d3-xmpl-46da-9778-518e6eca8125    2023/01/31/[$LATEST]1bbe51xmplb34a2788dbaa7433b0aa4d
[INFO]  2023-08-31T22:12:58.535Z    1c8df7d3-xmpl-46da-9778-518e6eca8125    ## EVENT
[INFO]  2023-08-31T22:12:58.535Z    1c8df7d3-xmpl-46da-9778-518e6eca8125    {'key': 'value'}
END RequestId: 1c8df7d3-xmpl-46da-9778-518e6eca8125
REPORT RequestId: 1c8df7d3-xmpl-46da-9778-518e6eca8125  Duration: 2.75 ms   Billed Duration: 3 ms Memory Size: 128 MB Max Memory Used: 56 MB  Init Duration: 113.51 ms
XRAY TraceId: 1-5e34a66a-474xmpl7c2534a87870b4370   SegmentId: 073cxmpl3e442861 Sampled: true
```


# Official Examples
- [Get started creating and invoking Lambda functions using an AWS SDK](https://docs.aws.amazon.com/lambda/latest/dg/example_lambda_Scenario_GettingStartedFunctions_section.html)
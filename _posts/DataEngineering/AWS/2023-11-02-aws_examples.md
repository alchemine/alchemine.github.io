---
title: AWS Examples
tags: AWS
---

<!--more-->

## Tutorial: Using an Amazon S3 trigger to invoke a Lambda function
![](https://docs.aws.amazon.com/images/lambda/latest/dg/images/services-s3-example/s3_tut_config.png) \
![](https://docs.aws.amazon.com/images/lambda/latest/dg/images/services-s3-example/s3trigger_tut_steps1.png)

- Reference \
[https://docs.aws.amazon.com/lambda/latest/dg/with-s3-example.html](https://docs.aws.amazon.com/lambda/latest/dg/with-s3-example.html)


## Tutorial: Using an Amazon S3 trigger to create thumbnail images
![](https://docs.aws.amazon.com/images/lambda/latest/dg/images/services-s3-tutorial/s3thumb_tut_resources.png) \
![](https://docs.aws.amazon.com/images/lambda/latest/dg/images/services-s3-tutorial/s3thumb_tut_steps1.png)

- Reference \
[https://docs.aws.amazon.com/lambda/latest/dg/with-s3-tutorial.html](https://docs.aws.amazon.com/lambda/latest/dg/with-s3-tutorial.html)


## Creating and connecting to a PostgreSQL DB instance
![](https://docs.aws.amazon.com/images/AmazonRDS/latest/UserGuide/images/getting-started-postgresql.png)

![](https://docs.aws.amazon.com/images/AmazonRDS/latest/UserGuide/images/getting-started-postgresql.png)


## Tutorial: Create a web server and an Amazon RDS DB instance
![](https://docs.aws.amazon.com/images/AmazonRDS/latest/UserGuide/images/con-VPC-sec-grp.png)

- Reference \
[https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/TUT_WebAppWithRDS.html](https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/TUT_WebAppWithRDS.html)


<details>
<summary>Procedures</summary>
<hr>

1. EC2 instance (DB compute resource) 생성
2. DB instance 생성
3. EC2 instance에 web server 설치
4. `ec2-user`를 `apache` group에 추가하여 apache web server 권한 얻기
5. Web server 구현 후 확인

<hr>
</details>


## Tutorial: Using a Lambda function to access an Amazon RDS database
![](https://docs.aws.amazon.com/images/AmazonRDS/latest/UserGuide/images/TUT_Lambda_1.png)
![](https://docs.aws.amazon.com/images/AmazonRDS/latest/UserGuide/images/TUT_Lambda_step1.png)

- Reference \
[https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/rds-lambda-tutorial.html](https://docs.aws.amazon.com/AmazonRDS/latest/UserGuide/rds-lambda-tutorial.html)

<details>
  <summary>Procedures</summary>
  <hr>

1. DB 생성
2. `RDS/Lambda 연결 설정` 에서 Lambda function 생성
3. Role 생성 (`AWSLambdaSQSQueueExecutionRole`, `AWSLambdaVPCAccessExecutionRole`)
4. 

  <hr>
</details>
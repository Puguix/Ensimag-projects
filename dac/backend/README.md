# Backend with spring-boot

Launch a service:

`mvn spring-boot:run`

Generate pair of RSA keys

`openssl genpkey -algorithm RSA -out private_key.pem -aes256`

`openssl rsa -pubout -in private_key.pem -out public_key.pem`

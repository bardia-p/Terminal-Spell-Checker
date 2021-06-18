FROM alpine:3.4

RUN apk update && apk add g++ make git

COPY . /autocorrect

WORKDIR /autocorrect


CMD ["bash", "startup.sh"]

FROM ahmad88me/googletest:latest

RUN mkdir -p /app
WORKDIR /app

COPY scripts /app/scripts
COPY Makefile /app/
#COPY *.c /app/
COPY *.cpp /app/
COPY *.h /app/
COPY .git /app/.git
COPY *.csv /app/

CMD ["sh", "scripts/main.sh"]


docker image build -t tparser:latest .
docker container run  --interactive --tty --rm --name tparser tparser:latest

# building and running

```bash
docker build . -t backend
docker save backend > backend.tar

docker load < backend.tar
docker run -p 5000:5000 backend:latest
```

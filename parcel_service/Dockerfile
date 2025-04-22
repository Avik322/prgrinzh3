FROM python:3.11-slim

WORKDIR /app

COPY . .

RUN chmod +x wait-for-it.sh

RUN pip install --no-cache-dir -r requirements.txt

CMD ["./wait-for-it.sh", "db:5432", "--", "uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8081"]

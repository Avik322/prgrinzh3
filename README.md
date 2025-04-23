# Лабораторная работа №3

## Описание

Реализована микросервисная система, включающая следующие сервисы:

- `user_service` — C++ сервис с аутентификацией и JWT-токенами.
- `parcel_service` — FastAPI-сервис с PostgreSQL, отвечает за посылки.
- `delivery_service` — FastAPI-сервис, отвечает за информацию о доставке.

Все сервисы запускаются через `docker-compose`, используют общую базу PostgreSQL, поддерживают аутентификацию и взаимодействие между собой.

## Стек технологий

- C++ + Poco (user_service)
- FastAPI + SQLAlchemy + PostgreSQL (parcel_service, delivery_service)
- Docker + Docker Compose
- JWT-токены для авторизации

## Команды запуска

```bash
docker-compose up --build

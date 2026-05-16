#!/bin/bash
echo "🚀 Запуск сборки Docker Compose..."
docker-compose down
docker-compose up --build -d
echo "✅ Всё готово! Контейнеры подняты в фоне!"

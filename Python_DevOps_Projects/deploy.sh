#!/bin/bash
echo " Запуск деплоя проекта..."
git pull origin main  # Если пользуешься гитом
sudo docker compose down
sudo docker compose up -d --build
echo "✅ Всё готово, пользователь! Бот в строю."

#!/bin/bash

# Проверяем, передан ли параметр
if [ $# -ne 1 ]; then
    echo "Usage: ./main.sh [1|2|3|4]"
    exit 1
fi

method=$1
# Путь к логам из Part 4
logs="../04/*.log"

# Проверяем, существуют ли логи
if ! ls $logs >/dev/null 2>&1; then
    echo "Error: No log files found in ../04/"
    exit 1
fi

case $method in
    1)
        # 1. Все записи, отсортированные по коду ответа
        # Код ответа — это 9-й столбец в нашем формате лога
        awk '{print $0}' $logs | sort -k9
        ;;
    2)
        # 2. Все уникальные IP (IP — это 1-й столбец)
        awk '{print $1}' $logs | sort -u
        ;;
    3)
        # 3. Все запросы с ошибками (коды 4xx и 5xx)
        # Проверяем 9-й столбец на наличие 4 или 5 в начале
        awk '$9 ~ /^[45]/ {print $0}' $logs
        ;;
    4)
        # 4. Уникальные IP только среди ошибочных запросов
        awk '$9 ~ /^[45]/ {print $1}' $logs | sort -u
        ;;
    *)
        echo "Invalid parameter. Use 1, 2, 3 or 4."
        exit 1
        ;;
esac

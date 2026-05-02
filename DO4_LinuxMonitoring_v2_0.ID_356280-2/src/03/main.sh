#!/bin/bash

# Проверка параметра (1, 2 или 3)
if [ $# -ne 1 ]; then
    echo "Usage: ./main.sh [1|2|3]"
    exit 1
fi

method=$1

# 1. Очистка по лог-файлу (Самый безопасный способ)
if [ "$method" -eq 1 ]; then
    log_file="../02/file_clogging.log" # Укажи правильный путь к логу из Part 2
    if [ ! -f "$log_file" ]; then
        echo "Error: Log file not found."
        exit 1
    fi
    # Вытаскиваем пути из лога (строки начинающиеся с DIR и FILE)
    paths=$(awk '/DIR:|FILE:/ {print $2}' "$log_file")
    for p in $paths; do
        if [ -e "$p" ]; then rm -rf "$p"; fi
    done
    echo "Cleanup by log file completed."

# 2. Очистка по дате и времени
elif [ "$method" -eq 2 ]; then
    echo "Enter start time (YYYY-MM-DD HH:MM):"
    read start_date
    echo "Enter end time (YYYY-MM-DD HH:MM):"
    read end_date

    # Ищем файлы, созданные в этом промежутке
    # -newermt сравнивает дату модификации
    find / -newermt "$start_date" ! -newermt "$end_date" -name "*_$(date +%d%m%y)*" 2>/dev/null -exec rm -rf {} +
    echo "Cleanup by date interval completed."

# 3. Очистка по маске (символы, подчеркивание, дата)
elif [ "$method" -eq 3 ]; then
    echo "Enter name mask (example: abcde_$(date +%d%m%y)):"
    read mask
    # Ищем по всей системе папки и файлы, подходящие под маску
    find / -name "*${mask}*" 2>/dev/null -exec rm -rf {} +
    echo "Cleanup by mask completed."

else
    echo "Invalid method. Use 1, 2 or 3."
fi

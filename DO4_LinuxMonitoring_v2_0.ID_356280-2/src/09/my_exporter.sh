#!/bin/bash
# Путь к файлу, который будет читать Nginx
OUTPUT_FILE="/var/www/html/metrics.html"

while true; do
  # 1. Считаем CPU (загрузка за последнюю минуту)
  CPU_LOAD=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')

  # 2. Считаем RAM (в процентах)
  MEM_USED=$(free | grep Mem | awk '{print $3/$2 * 100.0}')

  # 3. Считаем Диск (заполненность корневого раздела)
  DISK_USAGE=$(df / | grep / | awk '{print $5}' | sed 's/%//')

  # Формируем файл в формате Prometheus
  cat <<EOF > $OUTPUT_FILE
# HELP my_cpu_usage CPU usage in percent
# TYPE my_cpu_usage gauge
my_cpu_usage $CPU_LOAD

# HELP my_mem_usage Memory usage in percent
# TYPE my_mem_usage gauge
my_mem_usage $MEM_USED

# HELP my_disk_usage Disk usage in percent
# TYPE my_disk_usage gauge
my_disk_usage $DISK_USAGE
EOF

  sleep 3
done

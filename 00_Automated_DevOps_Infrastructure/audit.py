import os
import shutil
import platform
import getpass
from datetime import datetime
import requests
import psutil
import time
import psycopg2

TOKEN = "8874275515:AAHjSErhnhlcvLqMgq4G8H0UtHHK9nAS9RU"
CHAT_ID = 8278904536 

def send_telegram(message):
    try:
        url = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={CHAT_ID}&text={message}"
        response = requests.get(url)
        print(response.json())
    except Exception as e:
        print(f"❌ Telegram API Error: {e}")

def check_cyber_attacks():
    try:
        connection = psycopg2.connect(
            user="user_devops", password="password123", host="db", port="5432", database="monitoring_db"
        )
        cursor = connection.cursor()
        cursor.execute("SELECT message FROM ram_alerts ORDER BY id DESC LIMIT 1;")
        last_log = cursor.fetchone()
        cursor.close()
        connection.close()
        
        if last_log and "КИБЕРАТАКА" in last_log[0]:
            if not hasattr(check_cyber_attacks, "last_alerted_msg") or check_cyber_attacks.last_alerted_msg != last_log[0]:
                print("🚨 Security Event: DDoS Incident detected!")
                send_telegram(f"⚠️ SECURITY ALERT: {last_log[0]}")
                check_cyber_attacks.last_alerted_msg = last_log[0]
    except Exception as error:
        print(f"❌ Security Scanner DB Error: {error}")

def save_to_db(ram_usage, cpu_usage, hdd_usage, message):
    try:
        connection = psycopg2.connect(user="user_devops", password="password123", host="db", port="5432", database="monitoring_db")
        cursor = connection.cursor()
        # Предполагаем, что в БД есть колонка cpu_usage, если нет - подправь схему
        insert_query = "INSERT INTO ram_alerts (ram_usage, cpu_usage, hdd_usage, message) VALUES (%s, %s, %s, %s)"
        cursor.execute(insert_query, (ram_usage, cpu_usage, hdd_usage, message))
        connection.commit()
        cursor.close()
        connection.close()
    except Exception as error:
        print(f"⚠️ DB Error: {error}")

def audit_my_repo():
    user = getpass.getuser()
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Сбор метрик
    total, used, free = shutil.disk_usage("/")
    hdd_usage = round((used / total) * 100, 2) 
    memory = psutil.virtual_memory()
    ram_usage = memory.percent 
    cpu_usage = psutil.cpu_percent(interval=1) # Замер CPU

    print(f"\n--- Report {now} ---")
    print(f"🧠 RAM: {ram_usage}% | ⚙️ CPU: {cpu_usage}% | 💾 HDD: {hdd_usage}%")

    # Сохранение
    save_to_db(ram_usage, cpu_usage, hdd_usage, f"RAM {ram_usage}%, CPU {cpu_usage}%, HDD {hdd_usage}%")

    # Алерты
    if ram_usage > 90:
        send_telegram(f"🚨 ALERT: High RAM Usage ({ram_usage}%)")
    if cpu_usage > 90:
        send_telegram(f"🚨 ALERT: High CPU Usage ({cpu_usage}%)")
    if (total - used) // (2**30) < 10:
        send_telegram(f"🚨 ALERT: Critical Disk Space!")

    # Логи
    if not os.path.exists('LOGS'): os.mkdir('LOGS')
    with open('LOGS/report.txt', 'a', encoding='utf-8') as f:
        f.write(f"[{now}] RAM: {ram_usage}% | CPU: {cpu_usage}% | HDD: {hdd_usage}%\n")

if __name__ == "__main__":
    print("🚀 DevOps Monitoring daemon initialized...")
    loop_count = 0
    while True:
        check_cyber_attacks()
        if loop_count % 100 == 0:
            audit_my_repo()
        loop_count += 1
        time.sleep(3)

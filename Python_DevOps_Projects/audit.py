import os
import shutil
import platform
import getpass
import datetime

def audit_my_repo():
    # 1. Узнаем, кто тут Босс и на чем сидит
    user = getpass.getuser()
    system = platform.system()
    current_dir = os.getcwd()

    # 2. Считаем проекты (твой старый добрый код)
    all_items = os.listdir('.')
    # Оставляем папки, которые не начинаются с точки
    directories = [d for d in all_items if os.path.isdir(d) and not d.startswith('.')]

    # 3. ПРОВЕРКА ЖЕЛЕЗА (Наш новый DevOps-слой)
    # Проверяем диск (корень "/")
    total, used, free = shutil.disk_usage("/")
    free_gb = free // (2**30)  # Конвертируем в Гб

    print(f"\n---  DevOps Audit Report  ---")
    print(f"👤 Пользователь: {user}")
    print(f"💻 Операционка: {system}")
    print(f"📍 Где мы: {current_dir}")
    print(f"📁 Активных проектов: {len(directories)} ({', '.join(directories)})")
    
    print(f"\n--- 💾 Состояние памяти ---")
    print(f"Свободно на диске: {free_gb} GB")

    # 4. АВТО-ДИАГНОСТИКА (Скрипт начинает «думать»)
    if free_gb < 5:
        print("🛑 КРИТИЧЕСКИЙ УРОВЕНЬ: Срочно удаляй мусор!")
    elif free_gb < 20:
        print("⚠️ ПРЕДУПРЕЖДЕНИЕ: Место заканчивается. Будь аккуратнее. ")
    else:
        print("✅ ВСЁ ХОРОШО: Места полно, кодим дальше! ✨")
    print(f"------------------------------\n")
 
    # 5. Проверяем папку для логов
    if not os.path.exists('LOGS'):
        os.mkdir('LOGS')
        print("📁 Папка LOGS создана!")
    else:
        print("✅ Папка LOGS уже существует.")
   
    # 6. ЗАПИСЬ В ЛОГ 
    log_path = os.path.join('LOGS', 'report.txt')
    
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")    
    with open(log_path, 'a', encoding='utf-8') as f:
        f.write("\n" + "="*30 + "\n")
        f.write(f"Время отчета: {now}\n")
        f.write(f"Отчет от {user}\n")
        f.write(f"Система: {system}\n")
        f.write(f"Проектов найдено: {len(directories)}\n")
        f.write(f"Свободно места: {free_gb} GB\n")
        f.write(f"Время отчета: {now}\n")    
    print(f"📝 Отчет сохранен в {log_path}! ")
if __name__ == "__main__":
    audit_my_repo()
